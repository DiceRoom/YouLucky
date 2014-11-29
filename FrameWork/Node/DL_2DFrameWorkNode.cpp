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
//! ����������
void C_DL2DFrameWorkNode::Initialize(dlU32 line_Val)
{
	//FrameWork���Ŏg���V�X�e�����C�����l��
	_node_Line_List.resize(line_Val + kSYSTEM_LINE_VAL);
	_all_EndUser_Node_Valid_Flg = dlTRUE;
}

//============================================================================
//! �I������
void C_DL2DFrameWorkNode::Terminate(void)
{
	_RemoveNode();

	//�폜���m�[�h���c���Ă���΃G���[
	if(_node_Map.size() != 0)
	{
		SystemError(kSYSER_NODE_MEMORYLEAK);
	}
}

//============================================================================
//! �m�[�h�̎擾
C_CoreNode *C_DL2DFrameWorkNode::GetNode(NODE_HANDLE node_Handle) const
{
	NODE_MAP::const_iterator itr = _node_Map.find(node_Handle);
	
	//�}�b�v���ɑ��݂��Ȃ�
	return (itr == _node_Map.end()) ? 0 : itr -> second.node_CP;
}

//============================================================================
//! �w�胉�C���ɓo�^����Ă���m�[�h��
dlU32 C_DL2DFrameWorkNode::GetRegistLineNodeVal(dlS32 line_No) const
{
	line_No += kUSE_ENDUSER_LINE;
	return static_cast<dlU32>(_node_Line_List[line_No].size());
}

//============================================================================
//! �o�^����Ă���m�[�h��
dlU32 C_DL2DFrameWorkNode::GetRegistNodeVal(void) const
{
	return static_cast<dlU32>(_node_Map.size());
}

//============================================================================
//! �m�[�h�����C���ɒǉ�
void C_DL2DFrameWorkNode::AddNode(C_CoreNode*node_CP , dlU32 line_No , dlS32 priority , DL::NODE_HANDLE* out_Handle /*= 0 */, dlBOOL system_Node_Flg /*= dlFALSE*/)
{
	//�������C���ԍ��ɕϊ�
	if(!system_Node_Flg)
	{
		line_No += kUSE_ENDUSER_LINE;
	}
	else
	{
		//�V�X�e�����C���ݒ�̏ꍇ
		if(line_No >= kUSE_ENDUSER_LINE)
		{
			line_No -= (kSYSTEM_FRONT_LIVE_VAL + 1);
			line_No += static_cast<dlS32>(_node_Line_List.size());
		}
	}

	node_CP -> SetPriority(priority);

	//�n���h���t��
	NODE_HANDLE handle = _GetUseAbletHandle();
	node_CP -> SetHandle(handle);
	if(out_Handle != 0){*out_Handle = handle;}

	//���C���ɒǉ�(Update���ł���薳��)
	S_NodeRegistInfo info_S;
	info_S.node_CP = node_CP;
	info_S.regist_No = line_No;
	_node_Map.insert(std::pair<NODE_HANDLE , S_NodeRegistInfo>(handle , info_S));
	
	//priority�����������ԂɍX�V�����
	std::vector<C_CoreNode*>::iterator itr , end_Itr = _node_Line_List[line_No].end();
	for(itr = _node_Line_List[line_No].begin() ; itr != end_Itr ; ++ itr)
	{
		if((*itr) -> GetPriority() >= priority){break;}
	}
	if(itr == end_Itr)	{_node_Line_List[line_No].push_back(node_CP);}
	else				{_node_Line_List[line_No].insert(itr , node_CP);}
}

//============================================================================
//! �m�[�h�̍폜
dlBOOL C_DL2DFrameWorkNode::DeleteNode(NODE_HANDLE node_Handle)
{
	return _RegistRemoveNode(node_Handle , dlTRUE);
}

//============================================================================
//! �m�[�h�̏��O
dlBOOL C_DL2DFrameWorkNode::EraseNode(DL::NODE_HANDLE node_Handle)
{
	return _RegistRemoveNode(node_Handle , dlFALSE);
}

//============================================================================
//! �m�[�h�̖���/�L���ύX
dlBOOL C_DL2DFrameWorkNode::SetValidFlg(NODE_HANDLE handle , dlBOOL valid_Flg)
{
	NODE_MAP::iterator find_Itr = _node_Map.find(handle);
	
	//�}�b�v���ɑ��݂��Ȃ�
	if(find_Itr == _node_Map.end()){return dlFALSE;}

	find_Itr -> second.node_CP -> SetValidFlg(valid_Flg);

	return dlTRUE;
}

//============================================================================
//! �e��m�[�h��Update
void C_DL2DFrameWorkNode::_UpdateNode(void)
{
	//���C���m�[�h�X�V(Update�̂�)
	_main_Node_CP -> Update();

	//�A�b�v�f�[�g(�e�폈���̊Ԃɒǉ����s���Ă����v)
	_NodeFunction(&C_CoreNode::Update);
}

//============================================================================
//! �e��m�[�h��Revision
void C_DL2DFrameWorkNode::_RevisionNode(void)
{
	_NodeFunction(&C_CoreNode::Revision);
}

//============================================================================
//! �e��m�[�h��Finish
void C_DL2DFrameWorkNode::_FinishNode(void)
{
	_NodeFunction(&C_CoreNode::Finish);
}

//============================================================================
//! �e��m�[�h�̏���
void C_DL2DFrameWorkNode::_NodeFunction(void (C_CoreNode::*func_P)(void))
{
	std::list<C_CoreNode*> update_List;

	dlS32 counter = -1;
	const dlS32 user_Line_Val = kSYSTEM_FRONT_LIVE_VAL + static_cast<dlS32>(_node_Line_List.size());
	ItrLoopDef(std::vector< std::vector< C_CoreNode* > > , _node_Line_List , line_Itr)
	{
		++ counter;

		//�V�X�e���m�[�h�ȊO
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

		//�L���ȃ��X�g�����X�V
		ItrLoopDef(std::list<C_CoreNode*> , update_List , itr)
		{
			((*itr) ->* func_P)();
		}

		//�폜�\��̃m�[�h���폜���A�}�b�v���珜�O
		_RemoveNode();
	}
}

//============================================================================
//! �m�[�h���C������̏����o�^
dlBOOL C_DL2DFrameWorkNode::_RegistRemoveNode(NODE_HANDLE node_Handle , dlBOOL delete_Flg)
{
	//���ɍ폜�\�胊�X�g�ɂ���Ζ���
	ItrLoopDef(ERASE_HANDLE_LIST , _erase_Handle_List , itr)
	{
		if((*itr).first == node_Handle)
		{
			return dlFALSE;
		}
	}

	//�}�b�v����n���h���������擾
	NODE_MAP::iterator find_Itr = _node_Map.find(node_Handle);
	if(find_Itr == _node_Map.end())
	{
		return dlFALSE;
	}

	//���C������폜
	const S_NodeRegistInfo& info_S = (*find_Itr).second;
	std::vector< C_CoreNode* >::iterator line_Find_Itr = ALFind(_node_Line_List[info_S.regist_No] , info_S.node_CP);
	if(line_Find_Itr != _node_Line_List[info_S.regist_No].end())
	{
		_node_Line_List[info_S.regist_No].erase(line_Find_Itr);
	}
	
	//�폜����镨�����I���������Ă�
	if(delete_Flg)
	{
		(*find_Itr).second.node_CP -> Terminate();
	}

	//�폜�\��ɓ����
	_erase_Handle_List.push_back(std::make_pair(node_Handle , delete_Flg));

	return dlTRUE;
}

//============================================================================
//! �g�p�\�ȃm�[�h�ԍ���Ԃ�
NODE_HANDLE C_DL2DFrameWorkNode::_GetUseAbletHandle(void)
{
GET_RANDOM:
	//ID�ԍ��擾
	dlU32 new_No = C_DL2DFrameWork::UTILITY -> GetRandom(0x7FFFFFFF);
	if(_node_Map.find(new_No) != _node_Map.end())
	{
		goto GET_RANDOM;
	}
	return new_No;
}

//============================================================================
//! �m�[�h�̍ŏI�폜
void C_DL2DFrameWorkNode::_RemoveNode(void)
{
LOOP:
	ERASE_HANDLE_LIST delete_Handle_List = _erase_Handle_List;
	_erase_Handle_List.clear();

	ItrLoopDef(ERASE_HANDLE_LIST , delete_Handle_List , itr)
	{
		//�}�b�v����n���h���������擾
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
//! �w�肵�����C���ɓo�^����Ă���m�[�h�̃n���h�������X�g�����Ď擾
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
//! �w�肵���^�C�v�̃m�[�h�̃n���h�����X�g���擾
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
//! �w��n���h���̃m�[�h�Ƀ��b�Z�[�W�𑗐M����
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
//! �w��^�C�v�̃m�[�h�Ƀ��b�Z�[�W�𑗐M����
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
//! �w�胉�C���ɓo�^���Ă���m�[�h�Ƀ��b�Z�[�W�𑗂�
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
//! �S�Ẵm�[�h�Ƀ��b�Z�[�W�𑗐M����
void C_DL2DFrameWorkNode::SendAllNodeMessage(dlS32 msg_No , void *date_P)
{
	ItrLoopDef(NODE_MAP , _node_Map , itr)
	{
		itr -> second.node_CP -> RevMessage(msg_No , date_P);
	}
}

}