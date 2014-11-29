/****************************************************************************/
/* DL_CoreNode.h															*/
/****************************************************************************/
#ifndef DL_CORENODE_H_
#define	DL_CORENODE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! ノードタイプ
enum E_NodeType
{
	kBUTTON_NODE		= -6,	//< ボタン
	kTEXT_NODE			= -5,	//< テキスト	
	kPRIMITIVE_NODE		= -4,	//< プリミティブノード
	kIMAGE_NODE			= -3,	//< イメージノード
	kRENDER_CORE_NODE	= -2,	//< 描画コアノード
	
	///ユーザー定義
	kCOMMON_NODE = 1,
};

//! 基礎ノード
class C_CoreNode
{
public:
	C_CoreNode(void):_node_Type(-1),_valid_Flg(dlTRUE),_priority(0),_handle(-1){};
	virtual ~C_CoreNode(void){};
	
	virtual void Initialize	(void){};
	virtual void Terminate	(void){};
	
	virtual void RevMessage (dlS32 , void *){};

	void Update		(void){_Update();};
	void Revision	(void){_Revision();};
	void Finish		(void){_Finish();};
	
private:
	virtual void _Update	(void){};
	virtual void _Revision	(void){};
	virtual void _Finish	(void){};

private:
	ACS_MEB(private , dlS32 , _node_Type , NodeType);	//< ノードの種類
	ACS_MEB(private , NODE_HANDLE , _handle , Handle);	//< 登録中のハンドル
	ACS_B_MEB(private , _valid_Flg , ValidFlg);			//< ノードが有効かどうか
	ACS_MEB(private , dlS32 , _priority , Priority);	//< 優先度
};

}

#endif
