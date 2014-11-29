/****************************************************************************/
/* DL_2DFrameWorkGamepad.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKGAMEPAD_H_
#define	DL_2DFRAMEWORKGAMEPAD_H_


/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! �p�b�h���̎擾
struct S_PadDeviceInfomation
{
	dlSTRING product_Name;				//< �W���C�p�b�h�̎�ޖ�
	dlSTRING unique_Name;				//< MAC�A�h���X
	std::vector<dlS32> neutral_List;	//< �j���[�g�����l���X�g
};

//!2D�Q�[���p�t���[�����[�N(�Q�[���p�b�h)
class C_DL2DFrameWorkGamepad
{	
friend class C_DL2DFrameWork;
private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
	C_DL2DFrameWorkGamepad	(void){}
	~C_DL2DFrameWorkGamepad	(void){}
	C_DL2DFrameWorkGamepad	(const C_DL2DFrameWork &){}

public:
	void	Initialize				(void);
	void	Terminate				(void);

	dlU32	GetConnectGamePadVal	(void) const;
	void	GetValidPrsGamePadNoList(std::list<dlU32>& out_List) const;
	void	GetValidPadKeyList		(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_KeyInfo>& out_List) const;
	void	GetValidPadPovList		(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_PovInfo>& out_List) const;
	void	GetValidPadStickList	(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_StickInfo>& out_List) const;
	dlBOOL	GetPadDeviceInfomation	(dlU32 gamepad_Index , S_PadDeviceInfomation& out_Info_S) const;
	void	SetActive				(dlBOOL window_Active_Flg);
	dlBOOL	IsWaitPeriod			(void) const;

	dlBOOL	IsPrsKey				(dlU8 key_No) const;
	dlBOOL	IsTrgKey				(dlU8 key_No) const;
	dlBOOL	IsRlsKey				(dlU8 key_No) const;
	dlBOOL	IsRepeatKey				(dlU8 key_No) const;
	dlBOOL	IsDoubleClickKey		(dlU8 key_No) const;
	dlBOOL	IsKey					(dlU8 key_No , dlS32 state) const;

private:
	class C_DirectXPadDevice*		_gamepad_Device_CP;	//< �Q�[���p�b�h�f�o�C�X
};

}

#endif
