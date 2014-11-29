/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkNode.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Utility/DL_2DFrameWorkUtility.h>

namespace DL
{

//============================================================================
//! 初期化処理
void C_DL2DFrameWorkNode::Initialize(dlU32 line_Val)
{
	//FrameWork内で使うシステムラインを考慮
	_node_Line_List.resize(line_Val + kSYSTEM_LINE_VAL);
	_all_EndUser_Node_Valid_Flg = dlTRUE;
}

//============================================================================
//! 終了処理
void C_DL2DFrameWorkNode::Terminate(void)
{
	_RemoveNode();

	//削除時ノードが残っていればエラー
	if(_node_Map.size() != 0)
	{
		SystemError(kSYSER_NODE_MEMORYLEAK);
	}
}

//============================================================================
//! ノードの取得
C_CoreNode *C_DL2DFrameWorkNode::GetNode(NODE_HANDLE node_Handle) const
{
	NODE_MAP::const_iterator itr = _node_Map.find(node_Handle);
	
	//マップ内に存在しない
	return (itr == _node_Map.end()) ? 0 : itr -> second.node_CP;
}

//============================================================================
//! 指定ラインに登録されているノード数
dlU32 C_DL2DFrameWorkNode::GetRegistLineNodeVal(dlS32 line_No) const
{
	line_No += kUSE_ENDUSER_LINE;
	return static_cast<dlU32>(_node_Line_List[line_No].size());
}

//============================================================================
//! 登録されているノード数
dlU32 C_DL2DFrameWorkNode::GetRegistNodeVal(void) const
{
	return static_cast<dlU32>(_node_Map.size());
}

//============================================================================
//! ノードをラインに追加
void C_DL2DFrameWorkNode::AddNode(C_CoreNode*node_CP , dlU32 line_No , dlS32 priority , DL::NODE_HANDLE* out_Handle /*= 0 */, dlBOOL system_Node_Flg /*= dlFALSE*/)
{
	//実質ライン番号に変換
	if(!system_Node_Flg)
	{
		line_No += kUSE_ENDUSER_LINE;
	}
	else
	{
		//システムライン設定の場合
		if(line_No >= kUSE_ENDUSER_LINE)
		{
			line_No -= (kSYSTEM_FRONT_LIVE_VAL + 1);
			line_No += static_cast<dlS32>(_node_Line_List.size());
		}
	}

	node_CP -> SetPriority(priority);

	//ハンドル付け
	NODE_HANDLE handle = _GetUseAbletHandle();
	node_CP -> SetHandle(handle);
	if(out_Handle != 0){*out_Handle = handle;}

	//ラインに追加(Update中でも問題無い)
	S_NodeRegistInfo info_S;
	info_S.node_CP = node_CP;
	info_S.regist_No = line_No;
	_node_Map.insert(std::pair<NODE_HANDLE , S_NodeRegistInfo>(handle , info_S));
	
	//priorityが小さい順番に更新される
	std::vector<C_CoreNode*>::iterator itr , end_Itr = _node_Line_List[line_No].end();
	for(itr = _node_Line_List[line_No].begin() ; itr != end_Itr ; ++ itr)
	{
		if((*itr) -> GetPriority() >= priority){break;}
	}
	if(itr == end_Itr)	{_node_Line_List[line_No].push_back(node_CP);}
	else				{_node_Line_List[line_No].insert(itr , node_CP);}
}

//============================================================================
//! ノードの削除
dlBOOL C_DL2DFrameWorkNode::DeleteNode(NODE_HANDLE node_Handle)
{
	return _RegistRemoveNode(node_Handle , dlTRUE);
}

//============================================================================
//! ノードの除外
dlBOOL C_DL2DFrameWorkNode::EraseNode(DL::NODE_HANDLE node_Handle)
{
	return _RegistRemoveNode(node_Handle , dlFALSE);
}

//============================================================================
//! ノードの無効/有効変更
dlBOOL C_DL2DFrameWorkNode::SetValidFlg(NODE_HANDLE handle , dlBOOL valid_Flg)
{
	NODE_MAP::iterator find_Itr = _node_Map.find(handle);
	
	//マップ内に存在しない
	if(find_Itr == _node_Map.end()){return dlFALSE;}

	find_Itr -> second.node_CP -> SetValidFlg(valid_Flg);

	return dlTRUE;
}

//============================================================================
//! 各種ノードのUpdate
void C_DL2DFrameWorkNode::_UpdateNode(void)
{
	//メインノード更新(Updateのみ)
	_main_Node_CP -> Update();

	//アップデート(各種処理の間に追加が行われても大丈夫)
	_NodeFunction(&C_CoreNode::Update);
}

//============================================================================
//! 各種ノードのRevision
void C_DL2DFrameWorkNode::_RevisionNode(void)
{
	_NodeFunction(&C_CoreNode::Revision);
}

//============================================================================
//! 各種ノードのFinish
void C_DL2DFrameWorkNode::_FinishNode(void)
{
	_NodeFunction(&C_CoreNode::Finish);
}

//============================================================================
//! 各種ノードの処理
void C_DL2DFrameWorkNode::_NodeFunction(void (C_CoreNode::*func_P)(void))
{
	std::list<C_CoreNode*> update_List;

	dlS32 counter = -1;
	const dlS32 user_Line_Val = kSYSTEM_FRONT_LIVE_VAL + static_cast<dlS32>(_node_Line_List.size());
	ItrLoopDef(std::vector< std::vector< C_CoreNode* > > , _node_Line_List , line_Itr)
	{
		++ counter;

		//システムノード以外
		if(!_all_EndUser_Node_Valid_Flg &&
		   counter >= kUSE_ENDUSER_LINE &&
		   counter < user_Line_Val)
		{
			continue;
		}

		update_List.clear();
		ItrLoopDef(std::vector<C_CoreNode*> , (*line_Itr) , itr)
		{
			if((*itr) -> IsValidFlg()){update_List.push_back((*itr));}
		}

		//有効なリストだけ更新
		ItrLoopDef(std::list<C_CoreNode*> , update_List , itr)
		{
			((*itr) ->* func_P)();
		}

		//削除予約のノードを削除し、マップから除外
		_RemoveNode();
	}
}

//============================================================================
//! ノードラインからの除去登録
dlBOOL C_DL2DFrameWorkNode::_RegistRemoveNode(NODE_HANDLE node_Handle , dlBOOL delete_Flg)
{
	//既に削除予定リストにあれば無視
	ItrLoopDef(ERASE_HANDLE_LIST , _erase_Handle_List , itr)
	{
		if((*itr).first == node_Handle)
		{
			return dlFALSE;
		}
	}

	//マップからハンドルを情報を取得
	NODE_MAP::iterator find_Itr = _node_Map.find(node_Handle);
	if(find_Itr == _node_Map.end())
	{
		return dlFALSE;
	}

	//ラインから削除
	const S_NodeRegistInfo& info_S = (*find_Itr).second;
	std::vector< C_CoreNode* >::iterator line_Find_Itr = ALFind(_node_Line_List[info_S.regist_No] , info_S.node_CP);
	if(line_Find_Itr != _node_Line_List[info_S.regist_No].end())
	{
		_node_Line_List[info_S.regist_No].erase(line_Find_Itr);
	}
	
	//削除される物だけ終了処理を呼ぶ
	if(delete_Flg)
	{
		(*find_Itr).second.node_CP -> Terminate();
	}

	//削除予定に入れる
	_erase_Handle_List.push_back(std::make_pair(node_Handle , delete_Flg));

	return dlTRUE;
}

//============================================================================
//! 使用可能なノード番号を返す
NODE_HANDLE C_DL2DFrameWorkNode::_GetUseAbletHandle(void)
{
GET_RANDOM:
	//ID番号取得
	dlU32 new_No = C_DL2DFrameWork::UTILITY -> GetRandom(0x7FFFFFFF);
	if(_node_Map.find(new_No) != _node_Map.end())
	{
		goto GET_RANDOM;
	}
	return new_No;
}

//============================================================================
//! ノードの最終削除
void C_DL2DFrameWorkNode::_RemoveNode(void)
{
LOOP:
	ERASE_HANDLE_LIST delete_Handle_List = _erase_Handle_List;
	_erase_Handle_List.clear();

	ItrLoopDef(ERASE_HANDLE_LIST , delete_Handle_List , itr)
	{
		//マップからハンドルを情報を取得
		NODE_MAP::iterator find_Itr = _node_Map.find((*itr).first);
		if(find_Itr != _node_Map.end())
		{
			if((*itr).second)
			{
				dlDELETE (*find_Itr).second.node_CP;
			}
			_node_Map.erase(find_Itr);
		}
	}

	if(_erase_Handle_List.size() != 0)
	{
		goto LOOP;
	}
}

//============================================================================
//! 指定したラインに登録されているノードのハンドルをリスト化して取得
void C_DL2DFrameWorkNode::GetNodeListLine(dlS32 line_No , std::vector<NODE_HANDLE>& handle_List)
{
	handle_List.clear();
	line_No += kUSE_ENDUSER_LINE;
	ConstItrLoopDef(std::vector<C_CoreNode*> , _node_Line_List[line_No] , itr)
	{
		handle_List.push_back((*itr) -> GetHandle());
	}
}

//============================================================================
//! 指定したタイプのノードのハンドルリストを取得
void C_DL2DFrameWorkNode::GetNodeListType(dlS32 node_Type , std::vector<NODE_HANDLE>& handle_List)
{
	handle_List.clear();
	ConstItrLoopDef(NODE_MAP , _node_Map , itr)
	{
		C_CoreNode *node_CP = itr -> second.node_CP;
		if(node_CP -> GetNodeType() == node_Type){handle_List.push_back(itr -> first);}
	}
}

//============================================================================
//! 指定ハンドルのノードにメッセージを送信する
dlBOOL C_DL2DFrameWorkNode::SendMessageHandle(NODE_HANDLE handle , dlS32 msg_No , void *date_P)
{
	C_CoreNode *node_CP = GetNode(handle);
	if(node_CP != 0)
	{
		node_CP -> RevMessage(msg_No , date_P);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! 指定タイプのノードにメッセージを送信する
void C_DL2DFrameWorkNode::SendMessageType(dlS32 node_Type , dlS32 msg_No , void *date_P)
{
	ItrLoopDef(NODE_MAP , _node_Map , itr)
	{
		if(itr -> second.node_CP -> GetNodeType() == node_Type)
		{
			itr -> second.node_CP -> RevMessage(msg_No , date_P);
		}
	}
}

//============================================================================
//! 指定ラインに登録してあるノードにメッセージを送る
void C_DL2DFrameWorkNode::SendMessageLine(dlS32 line_No , dlS32 msg_No , void *date_P)
{
	line_No += kUSE_ENDUSER_LINE;

	std::vector<C_CoreNode*> node_List = _node_Line_List[line_No];
	ConstItrLoopDef(std::vector<C_CoreNode*> , node_List , itr)
	{
		(*itr) -> RevMessage(msg_No , date_P);
	}
}

//============================================================================
//! 全てのノードにメッセージを送信する
void C_DL2DFrameWorkNode::SendAllNodeMessage(dlS32 msg_No , void *date_P)
{
	ItrLoopDef(NODE_MAP , _node_Map , itr)
	{
		itr -> second.node_CP -> RevMessage(msg_No , date_P);
	}
}

}