/****************************************************************************/
/* DL_2DFrameWorkNode.h														*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKNODE_H_
#define	DL_2DFRAMEWORKNODE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

class C_CoreNode;

//! �V�X�e�����C�����
enum
{
	kSYSTEM_FRONT_LINE,		//< �V�X�e�����C��(�O)
	kSYSTEM_BUTTON_LINE,	//< �V�X�e���{�^�����C��
	kSYSTEM_FRONT_LIVE_VAL,	//< �G���h���[�U�������C�����O�ɂ���V�X�e�����C����

	kUSE_ENDUSER_LINE = kSYSTEM_FRONT_LIVE_VAL,

	kSYSTEM_BACK_LINE = kUSE_ENDUSER_LINE,	//< �V�X�e�����C��(��)
	kSYSTEM_LINE_VAL,						//< �V�X�e�����C����
};

//! �V�X�e���m�[�h�̗D��x�ݒ�
enum E_SystemNodePriority
{
	kSYS_NODE_PRI_TIMER			= 20,
	kSYS_NODE_PRI_DEVICE		= 50,
	kSYS_NODE_PRI_BUTTON_UPDATE	= 70,
	kSYS_NODE_PRI_BUTTON_FINISH	= 70,
	kSYS_NODE_PRI_SQUIRREL		= 85,
	kSYS_NODE_PRI_SCENE			= 100,
	kSYS_NODE_PRI_CLS_UPDATE	= 150,
	kSYS_NODE_PRI_CLS_FINISH	= 150,
	kSYS_NODE_PRI_RENDER		= 1000,
};


//! 2D�Q�[���p�t���[�����[�N(�m�[�h)
class C_DL2DFrameWorkNode
{
friend class C_DL2DFrameWork;
private:
	//! �m�[�h�̔z����Ȃǂ̏��
	struct S_NodeRegistInfo
	{
		C_CoreNode* node_CP;	//< �m�[�h�A�h���X
		dlU32 regist_No;		//< �z�����C���ԍ�
	};

	typedef dlMAP<NODE_HANDLE , S_NodeRegistInfo>			NODE_MAP;
	typedef std::vector< std::vector<C_CoreNode*> >			NODE_LINE_LIST;
	typedef std::vector< std::pair<NODE_HANDLE , dlBOOL> >	ERASE_HANDLE_LIST;

private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
	C_DL2DFrameWorkNode	(void){}
	~C_DL2DFrameWorkNode(void){}
	C_DL2DFrameWorkNode	(const C_DL2DFrameWorkNode &){}

public:
	void Initialize(dlU32 line_Val);
	void Terminate(void);

	template <class NODE_NAME> NODE_NAME *CreateNode(dlU32 line_No , dlS32 priority , DL::NODE_HANDLE* out_Handle = 0 , dlBOOL system_Node_Flg = dlFALSE);
	void		AddNode				(C_CoreNode*node_CP , dlU32 line_No , dlS32 priority , DL::NODE_HANDLE* out_Handle = 0 , dlBOOL system_Node_Flg = dlFALSE);
	dlBOOL		DeleteNode			(DL::NODE_HANDLE node_Handle);
	dlBOOL		EraseNode			(DL::NODE_HANDLE node_Handle);
	dlBOOL		SetValidFlg			(NODE_HANDLE node_Handle , dlBOOL valid_Flg);
	C_CoreNode*	GetNode				(NODE_HANDLE node_Handle) const;
	dlU32		GetRegistLineNodeVal(dlS32 line_No) const;
	dlU32		GetRegistNodeVal	(void) const;

	void		GetNodeListLine	(dlS32 node_Type , std::vector<NODE_HANDLE>& handle_List);
	void		GetNodeListType	(dlS32 node_Type , std::vector<NODE_HANDLE>& handle_List);

	//�m�[�h�ւ̃��b�Z�[�W���M�Q
	dlBOOL	SendMessageHandle	(NODE_HANDLE handle		, dlS32 msg_No ,	void *date_P = 0);
	void	SendMessageType		(dlS32 node_Type		, dlS32 msg_No ,	void *date_P = 0);
	void	SendMessageLine		(dlS32 line_No			, dlS32 msg_No ,	void *date_P = 0);
	void	SendAllNodeMessage	(dlS32 msg_No			,					void *date_P = 0);

private:
	void		_UpdateNode			(void);
	void		_RevisionNode		(void);
	void		_FinishNode			(void);
	void		_NodeFunction		(void (C_CoreNode::*func_P)(void));
	dlBOOL		_RegistRemoveNode	(NODE_HANDLE node_Handle , dlBOOL delete_Flg);
	void		_RemoveNode			(void);
	NODE_HANDLE _GetUseAbletHandle	(void);

private:
	NODE_MAP			_node_Map;											//< �S�m�[�h�}�b�v
	NODE_LINE_LIST		_node_Line_List;									//< �m�[�h�̃��C�����X�g
	ERASE_HANDLE_LIST	_erase_Handle_List;									//< �폜�p���X�g
	C_CoreNode*			_main_Node_CP;										//< ���C���m�[�h�A�h���X
	ACS_B_MEB(private , _all_EndUser_Node_Valid_Flg , AllValidNodeLine);	//< �S��(�V�X�e���m�[�h�ȊO)�̃m�[�h���X�g�b�v������
};

//============================================================================
//! �J�X�^���m�[�h�̒ǉ�(�G���h���[�U�[����)
template <class NODE_NAME>
NODE_NAME *C_DL2DFrameWorkNode::CreateNode(dlU32 line_No , dlS32 priority , DL::NODE_HANDLE* out_Handle , dlBOOL system_Node_Flg)
{
	NODE_NAME *node_CP = dlNEW NODE_NAME();
	AddNode(node_CP , line_No , priority , out_Handle , system_Node_Flg);
	node_CP -> Initialize();
	return node_CP;
}

}

#endif
