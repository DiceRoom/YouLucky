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

//! �m�[�h�^�C�v
enum E_NodeType
{
	kBUTTON_NODE		= -6,	//< �{�^��
	kTEXT_NODE			= -5,	//< �e�L�X�g	
	kPRIMITIVE_NODE		= -4,	//< �v���~�e�B�u�m�[�h
	kIMAGE_NODE			= -3,	//< �C���[�W�m�[�h
	kRENDER_CORE_NODE	= -2,	//< �`��R�A�m�[�h
	
	///���[�U�[��`
	kCOMMON_NODE = 1,
};

//! ��b�m�[�h
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
	ACS_MEB(private , dlS32 , _node_Type , NodeType);	//< �m�[�h�̎��
	ACS_MEB(private , NODE_HANDLE , _handle , Handle);	//< �o�^���̃n���h��
	ACS_B_MEB(private , _valid_Flg , ValidFlg);			//< �m�[�h���L�����ǂ���
	ACS_MEB(private , dlS32 , _priority , Priority);	//< �D��x
};

}

#endif
