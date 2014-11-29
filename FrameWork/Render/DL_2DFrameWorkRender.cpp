/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include "DL_2DFrameWorkRender.h"
#include "Image/DL_2DFrameWorkImage.h"
#include "Text/DL_2DFrameWorkText.h"
#include "Primitive/DL_2DFrameWorkDrawPrimitive.h"
#include "DL_RenderCoreNode.h"

#include <FrameWork/Node/DL_2DFrameWorkNode.h>
#include <FrameWork/Utility/DL_2DFrameWorkUtility.h>
#ifdef WIN32
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>
#else
#include "DL_Information.h"
#endif

namespace DL
{

//! ワーカーノード(レンダリングの更新)
class C_RenderUpdateNode : public C_CoreNode
{
private:
	void _Finish(void)
	{
		_render_CP -> _ResetPosition();
	};

private:
	ACS_PS_MEB(private , C_DL2DFrameWorkRender* , _render_CP , RenderAddress);
};

namespace
{

//! グリッドの縦横共通情報
struct S_GridCommonInfo
{
	S_Color					line_Color_S;		//< 色
	dlF32					interval;			//< 間隔
	std::list<NODE_HANDLE>	handle_List;		//< グリッドハンドルリスト
};

//============================================================================
//! グリッドのベース位置を取得
dlF32 GetGridBasePosition(dlF32 camera_Pos , dlF32 between_Size)
{
	dlS32 base_Area = static_cast<dlS32>(camera_Pos) / static_cast<dlS32>(between_Size);
	return static_cast<dlF32>(base_Area * between_Size);
}

}

//! グリッド情報
struct S_GridInfo
{
	dlS32				grid_State;			//< グリッド表示ステータス
	S_GridCommonInfo	grid_Info_SA[2];	//< 縦横のグリッド情報
};

//============================================================================
//! 初期化
void C_DL2DFrameWorkRender::Initialize(void)
{
	C_RenderUpdateNode* node_CP = C_DL2DFrameWork::NODE -> CreateNode<C_RenderUpdateNode>(kSYSTEM_BACK_LINE , kSYS_NODE_PRI_RENDER , &_update_Node_Handle , dlTRUE);
	node_CP -> SetRenderAddress(this);
	_change_Virtual_Camera_Flg = dlTRUE;
	_grid_Info_SP = dlNEW S_GridInfo();
	_grid_Info_SP -> grid_State = kGRID_NONE;
}
	
//============================================================================
//! 終了処理
void C_DL2DFrameWorkRender::Terminate(void)
{
	//予約削除も消しておく
	_EraseReservation();

	//削除時レンダリング物が残っていればエラー
	if(_render_Info_List.size() != 0)
	{
		SystemError(kSYSER_RND_MEMORYLEAK);
	}

	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
	dlDELETE _grid_Info_SP;
}

//============================================================================
//! 描画
void C_DL2DFrameWorkRender::Render(void)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		//有効な物のみ描画
		C_RenderCoreNode* node_CP = (*itr).node_CP;
		if(node_CP -> IsValidFlg()){node_CP -> Render();}
	}

	//削除予定の物を削除する
	_EraseReservation();
}

//============================================================================
//! 疑似カメラ位置の設定
void C_DL2DFrameWorkRender::SetVirtualCameraPos(const S_Vector2& pos_S)
{
	//値が違う時のみ反映
	if(_virtual_Camera_Pos_S != pos_S)
	{
		_virtual_Camera_Pos_S = pos_S;
		_change_Virtual_Camera_Flg = dlTRUE;
	}
}

//============================================================================
//! 描画リストに登録されている数
dlU32 C_DL2DFrameWorkRender::GetRenderNodeVal(void) const
{
	return static_cast<dlU32>(_render_Info_List.size());
}

//============================================================================
/* 指定ハンドルの物が何のハンドルであるかを取得
	
	-1	: 存在しないハンドル
	0	: イメージ
	1	: プリミティブ
	2	: テキスト
	3	: ボタン
*/
dlS32 C_DL2DFrameWorkRender::GetRenderKind(NODE_HANDLE handle) const
{
	C_RenderCoreNode* node_CP = _GetNodeAddress(handle);

	if(node_CP == 0){return dlFALSE;}

	return (node_CP -> GetNodeType() + 3);
}

//============================================================================
//! カメラの位置に影響するかどうかの変更
void C_DL2DFrameWorkRender::SetCameraInfluenceFlg(NODE_HANDLE handle , dlBOOL flg)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if(handle == (*itr).node_CP -> GetHandle())
		{
			(*itr).camera_Influence_Flg = flg;
			(*itr).virtual_Flip_Flg = flg;
			_change_Virtual_Camera_Flg = dlTRUE;
			return;
		}
	}
}

//============================================================================
//! 描画リストから削除
dlBOOL C_DL2DFrameWorkRender::_Erase(NODE_HANDLE handle)
{
	//線形削除になるが・・・
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if(handle == (*itr).node_CP -> GetHandle())
		{
			(*itr).node_CP -> Terminate();
			dlDELETE (*itr).node_CP;
			_render_Info_List.erase(itr);
			return dlTRUE;
		}
	}

	return dlFALSE;
}

//============================================================================
//! 描画リストから削除予約
void C_DL2DFrameWorkRender::_ReservateErase(NODE_HANDLE handle)
{
	_erase_List.push_back(handle);
}

//============================================================================
//! 表示/非表示の取得
dlBOOL C_DL2DFrameWorkRender::_IsValidFlg(NODE_HANDLE handle , dlBOOL& flg) const
{
	//ノードの取得
	C_RenderCoreNode* node_CP = _GetNodeAddress(handle);

	if(node_CP == 0){return dlFALSE;}

	flg = node_CP -> IsValidFlg();

	return dlTRUE;
}

//============================================================================
//! 表示/非表示の変更
dlBOOL C_DL2DFrameWorkRender::_SetValidFlg(NODE_HANDLE handle , dlBOOL flg)
{
	//ノードの取得
	C_RenderCoreNode* node_CP = _GetNodeAddress(handle);

	if(node_CP == 0){return dlFALSE;}

	node_CP -> SetValidFlg(flg);

	return dlTRUE;
}

//============================================================================
//! 位置の再設定
dlBOOL C_DL2DFrameWorkRender::_SetPosition(NODE_HANDLE handle , const S_Vector2& pos_S)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if((*itr).node_CP -> GetHandle() == handle)
		{
			//バーチャル反転していない場合はそのままの値を直接指定
			if((*itr).virtual_Flip_Flg)
			{
				(*itr).pos_S = pos_S;
				(*itr).node_CP -> SetPosition(_GetYFlipPosition(pos_S , (*itr).camera_Influence_Flg));
			}
			else
			{
				(*itr).pos_S = pos_S;
				(*itr).node_CP -> SetPosition(pos_S);
			}
			return dlTRUE;
		}
	}

	return dlFALSE;
}

//============================================================================
//! 深度の変更
dlBOOL C_DL2DFrameWorkRender::_ChangeDepth(NODE_HANDLE handle , dlS32 depth)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		C_RenderCoreNode* node_CP = (*itr).node_CP;
		if(node_CP -> GetHandle() == handle)
		{
			node_CP -> SetPriority(depth);

			const S_Vector2 pos_S = (*itr).pos_S;
			const dlBOOL virtual_Flip_Flg = (*itr).virtual_Flip_Flg;

			//現状の物を除去
			_render_Info_List.erase(itr);
			
			//新たに設定した深度で再挿入
			_InsertNode(node_CP , virtual_Flip_Flg);
			_SetPosition(handle , pos_S);

			return dlTRUE;
		}
	}
	
	return dlFALSE;
}

//============================================================================
//! 位置の再設定
void C_DL2DFrameWorkRender::_ResetPosition(void)
{
	//疑似カメラが変更された時のみ有効
	if(!_change_Virtual_Camera_Flg)
	{
		return;
	}
	_change_Virtual_Camera_Flg = dlFALSE;

	//バーチャル反転していない場合は触らない
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if((*itr).camera_Influence_Flg)
		{
			(*itr).node_CP -> SetPosition(_GetYFlipPosition((*itr).pos_S , dlTRUE));

			if((*itr).node_CP -> GetNodeType() == kIMAGE_NODE)
			{
				static_cast<C_ImageNode*>((*itr).node_CP) -> SetBlurOffset(S_Vector2(_virtual_Camera_Pos_S.x , -_virtual_Camera_Pos_S.y));
			}
		}
	}

	//グリッド設定
	if(_grid_Info_SP -> grid_State == kGRID_FREE)
	{
		_ResetGridPosition();
	}
}

//============================================================================
//! グリッドの位置設定
void C_DL2DFrameWorkRender::_ResetGridPosition(void)
{
	const S_Vector2 base_Pos_S(GetGridBasePosition(_virtual_Camera_Pos_S.x , _grid_Info_SP -> grid_Info_SA[0].interval),
							   GetGridBasePosition(_virtual_Camera_Pos_S.y , _grid_Info_SP -> grid_Info_SA[1].interval));

	//縦線
	S_Vector2 set_Pos_S(base_Pos_S.x , _virtual_Camera_Pos_S.y);
	ItrLoopDef(std::list<NODE_HANDLE> , _grid_Info_SP -> grid_Info_SA[0].handle_List , itr)
	{
		DL::C_DL2DFrameWork::DRAW_PRIMITIVE -> SetPosition((*itr) , set_Pos_S);
		set_Pos_S.x += _grid_Info_SP -> grid_Info_SA[0].interval;
	}

	//横線
	set_Pos_S = DL::S_Vector2(_virtual_Camera_Pos_S.x , base_Pos_S.y);
	ItrLoopDef(std::list<NODE_HANDLE> , _grid_Info_SP -> grid_Info_SA[1].handle_List , itr)
	{
		DL::C_DL2DFrameWork::DRAW_PRIMITIVE -> SetPosition((*itr) , set_Pos_S);
		set_Pos_S.y += _grid_Info_SP -> grid_Info_SA[1].interval;
	}
}

//============================================================================
//! 予約削除
void C_DL2DFrameWorkRender::_EraseReservation(void)
{
	ItrLoopDef(std::list<NODE_HANDLE> , _erase_List , itr)
	{
		_Erase((*itr));
	}
}

//============================================================================
//! アドレスの取得
C_RenderCoreNode* C_DL2DFrameWorkRender::_GetNodeAddress(NODE_HANDLE handle) const
{
	//検索
	ConstItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		C_RenderCoreNode* node_CP = (*itr).node_CP;
		if(node_CP -> GetHandle() == handle){return node_CP;}
	}
	return 0;
}

//============================================================================
//! 位置の取得
dlBOOL C_DL2DFrameWorkRender::_GetPosition(NODE_HANDLE handle , S_Vector2& out_Pos_S)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		C_RenderCoreNode* node_CP = (*itr).node_CP;
		if(node_CP -> GetHandle() == handle)
		{
			out_Pos_S = (*itr).pos_S;
			return dlTRUE;
		}
	}
	return dlFALSE;
}

//============================================================================
//! 疑似３Ｄ反転している描画ノードか調べる
dlBOOL C_DL2DFrameWorkRender::_IsVirtualFlip(NODE_HANDLE handle , dlBOOL& flip_Flg)
{
	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		C_RenderCoreNode* node_CP = (*itr).node_CP;
		if(node_CP -> GetHandle() == handle)
		{
			flip_Flg = (*itr).virtual_Flip_Flg;
			return dlTRUE;
		}
	}

	return dlFALSE;
}

//============================================================================
//! ノードをリスト内に入れる
void C_DL2DFrameWorkRender::_InsertNode(C_RenderCoreNode* node_CP , dlBOOL virtual_Flip_Flg)
{
	const dlS32 depth = node_CP -> GetPriority();

	//小さい順に入れる
	std::list<S_RenderNodeInfo>::iterator itr , end_Itr = _render_Info_List.end();
	for(itr = _render_Info_List.begin() ; itr != end_Itr ; ++ itr)
	{
		if((*itr).node_CP -> GetPriority() >= depth){break;}
	}

	//挿入
	S_RenderNodeInfo set_Info_S = {node_CP , virtual_Flip_Flg , virtual_Flip_Flg};
	if(itr == end_Itr)	{_render_Info_List.push_back(set_Info_S);}
	else				{_render_Info_List.insert(itr , set_Info_S);}
}

//============================================================================
//! 使用可能なノード番号を返す
NODE_HANDLE C_DL2DFrameWorkRender::_GetUseAbletHandle(void)
{
GET_RANDOM:
	//ID番号取得
	const dlS32 new_No = C_DL2DFrameWork::UTILITY -> GetRandom(0x7FFFFFFF);

	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if((*itr).node_CP -> GetHandle() == new_No){goto GET_RANDOM;}
	}

	return new_No;
}

//============================================================================
//! イメージのハンドルリストを取得
void C_DL2DFrameWorkRender::_GetImageHandleList(std::vector<NODE_HANDLE>& out_List)
{
	out_List.clear();

	ItrLoopDef(std::list<S_RenderNodeInfo> , _render_Info_List , itr)
	{
		if((*itr).node_CP -> GetNodeType() == kIMAGE_NODE)
		{
			out_List.push_back((*itr).node_CP -> GetHandle());
		}
	}
}

//============================================================================
//! Y軸反転位置の取得
S_Vector2 C_DL2DFrameWorkRender::_GetYFlipPosition(const S_Vector2& pos_S , dlBOOL camera_Influence_Flg) const
{
	DL::S_Vector2 ret_Pos_S = pos_S;
	
	if(camera_Influence_Flg)
	{
		ret_Pos_S -= _virtual_Camera_Pos_S;
	}
#ifdef WIN32
	ret_Pos_S.y = C_DL2DFrameWork::WINDOW -> GetWindowSize().y - ret_Pos_S.y;
#else
    ret_Pos_S.y = C_DLInformation::sharedInstance()->GetWindowSize().y - ret_Pos_S.y;
#endif
	return ret_Pos_S;
}

//============================================================================
//! グリッドの表示設定
void C_DL2DFrameWorkRender::ValidGrid(dlS32 state , const S_IntVec2& depth_S , const S_Vector2& split_Size_S , const S_Color& width_Line_Color_S , const S_Color& height_Line_Color_S)
{
	InValidGrid();

	if(state != kGRID_NONE)
	{
		_grid_Info_SP -> grid_State = state;
		_grid_Info_SP -> grid_Info_SA[0].interval = split_Size_S.x;
		_grid_Info_SP -> grid_Info_SA[1].interval = split_Size_S.y;
		_grid_Info_SP -> grid_Info_SA[0].line_Color_S = width_Line_Color_S;
		_grid_Info_SP -> grid_Info_SA[1].line_Color_S = height_Line_Color_S;

		//グリッド用プリミティブの作成
#ifdef WIN32
		const S_Vector2 window_Size_S = C_DL2DFrameWork::WINDOW -> GetWindowSize();
#else
		const S_Vector2 window_Size_S = C_DLInformation::sharedInstance()->GetWindowSize();
#endif
		S_IntVec2 grid_Line_Val_S = DL::S_IntVec2(static_cast<dlS32>(floor(window_Size_S.x / split_Size_S.x)) + 1,
												  static_cast<dlS32>(floor(window_Size_S.y / split_Size_S.y)) + 1);

		const dlBOOL flip_Flg = (state == kGRID_FREE);
		
		//縦方向のグリッド作成
		for(dlS32 cnt = 0 ; cnt < grid_Line_Val_S.x ; ++ cnt)
		{
			DL::NODE_HANDLE handle = DL::C_DL2DFrameWork::DRAW_PRIMITIVE -> CreateLine(DL::S_Vector2(static_cast<dlF32>(cnt) * split_Size_S.x , 0.f),
																	   DL::S_Vector2(0.f , window_Size_S.y),
																	   width_Line_Color_S,
																	   depth_S.x,
																	   flip_Flg);
			_grid_Info_SP -> grid_Info_SA[0].handle_List.push_back(handle);
		}

		//横方向のグリッド作成
		for(dlS32 cnt = 0 ; cnt < grid_Line_Val_S.x ; ++ cnt)
		{
			DL::NODE_HANDLE handle = DL::C_DL2DFrameWork::DRAW_PRIMITIVE -> CreateLine(DL::S_Vector2(0.f , static_cast<dlF32>(cnt) * split_Size_S.y),
																	   DL::S_Vector2(window_Size_S.x , 0.f),
																	   height_Line_Color_S,
																	   depth_S.x,
																	   flip_Flg);
			_grid_Info_SP -> grid_Info_SA[1].handle_List.push_back(handle);
		}

		//カメラ依存の場合は位置の再設定準備
		if(flip_Flg)
		{
			_change_Virtual_Camera_Flg = dlTRUE;
		}
	}
}

//============================================================================
//! グリッドを非表示状態に変更
void C_DL2DFrameWorkRender::InValidGrid(void)
{
	if(_grid_Info_SP -> grid_State != kGRID_NONE)
	{
		_grid_Info_SP -> grid_State = kGRID_NONE;

		ItrLoopDef(std::list<NODE_HANDLE> , _grid_Info_SP -> grid_Info_SA[0].handle_List , itr)
		{
			C_DL2DFrameWork::DRAW_PRIMITIVE -> DeletePrimitive((*itr));
		}
		_grid_Info_SP -> grid_Info_SA[0].handle_List.clear();

		ItrLoopDef(std::list<NODE_HANDLE> , _grid_Info_SP -> grid_Info_SA[1].handle_List , itr)
		{
			C_DL2DFrameWork::DRAW_PRIMITIVE -> DeletePrimitive((*itr));
		}
		_grid_Info_SP -> grid_Info_SA[1].handle_List.clear();
	}
}

}