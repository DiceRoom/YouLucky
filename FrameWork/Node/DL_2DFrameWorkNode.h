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

//! システムライン情報
enum
{
	kSYSTEM_FRONT_LINE,		//< システムライン(前)
	kSYSTEM_BUTTON_LINE,	//< システムボタンライン
	kSYSTEM_FRONT_LIVE_VAL,	//< エンドユーザ向けラインより前にあるシステムライン数

	kUSE_ENDUSER_LINE = kSYSTEM_FRONT_LIVE_VAL,

	kSYSTEM_BACK_LINE = kUSE_ENDUSER_LINE,	//< システムライン(後)
	kSYSTEM_LINE_VAL,						//< システムライン数
};

//! システムノードの優先度設定
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


//! 2Dゲーム用フレームワーク(ノード)
class C_DL2DFrameWorkNode
{
friend class C_DL2DFrameWork;
private:
	//! ノードの配属先などの情報
	struct S_NodeRegistInfo
	{
		C_CoreNode* node_CP;	//< ノードアドレス
		dlU32 regist_No;		//< 配属ライン番号
	};

	typedef dlMAP<NODE_HANDLE , S_NodeRegistInfo>			NODE_MAP;
	typedef std::vector< std::vector<C_CoreNode*> >			NODE_LINE_LIST;
	typedef std::vector< std::pair<NODE_HANDLE , dlBOOL> >	ERASE_HANDLE_LIST;

private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
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

	//ノードへのメッセージ送信群
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
	NODE_MAP			_node_Map;											//< 全ノードマップ
	NODE_LINE_LIST		_node_Line_List;									//< ノードのラインリスト
	ERASE_HANDLE_LIST	_erase_Handle_List;									//< 削除用リスト
	C_CoreNode*			_main_Node_CP;										//< メインノードアドレス
	ACS_B_MEB(private , _all_EndUser_Node_Valid_Flg , AllValidNodeLine);	//< 全て(システムノード以外)のノードをストップさせる
};

//============================================================================
//! カスタムノードの追加(エンドユーザー向け)
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
