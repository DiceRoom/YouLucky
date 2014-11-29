/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkGamepad.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>

#ifdef WIN32
#include <rpc.h>
#pragma comment (lib, "rpcrt4.lib")
#endif

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkGamepad::Initialize(void)
{
	_gamepad_Device_CP = dlNEW C_DirectXPadDevice();
	_gamepad_Device_CP -> CreateDevice(C_DL2DFrameWork::WINDOW -> GetWindowHandle());
}

//============================================================================
//! ������
void C_DL2DFrameWorkGamepad::Terminate(void)
{
	dlDELETE _gamepad_Device_CP;
}

//============================================================================
//! �ڑ�����Ă���Q�[���p�b�h�̖{�����擾
dlU32 C_DL2DFrameWorkGamepad::GetConnectGamePadVal(void) const
{
	return _gamepad_Device_CP -> GetConnectGamePadVal();
}

//============================================================================
//! �ڑ�����Ă���Q�[���p�b�h�̂����ǂ̃p�b�h���L����Ԃ�(���炩�̃L�[�APOV�A�A�i���O�l��PRS���)
void C_DL2DFrameWorkGamepad::GetValidPrsGamePadNoList(std::list<dlU32>& out_List) const
{
	const dlU32 pad_Val = _gamepad_Device_CP -> GetConnectGamePadVal();
	for(dlU32 cnt = 0 ; cnt < pad_Val ; ++ cnt)
	{
		if(_gamepad_Device_CP -> IsValidSome(cnt)){out_List.push_back(cnt);}
	}
}

//============================================================================
//! �w��Q�[���p�b�h�ԍ��̕��ŉ�����Ă���L�[�{�^�����擾
void C_DL2DFrameWorkGamepad::GetValidPadKeyList(dlU32 gamepad_No , std::vector<C_DirectXPadDeviceDefinition::S_KeyInfo>& out_List) const
{
	_gamepad_Device_CP -> GetValidKeyList(gamepad_No , out_List);
}

//============================================================================
//! �w��Q�[���p�b�h�ԍ��̕��ŉ�����Ă���POV�{�^���̏����擾
void C_DL2DFrameWorkGamepad::GetValidPadPovList(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_PovInfo> &out_List) const
{
	_gamepad_Device_CP -> GetValidPovList(gamepad_Index , out_List);
}

//============================================================================
//! �w��Q�[���p�b�h�ԍ��̕��ŉ�����Ă���X�e�B�b�N�̏����擾
void C_DL2DFrameWorkGamepad::GetValidPadStickList(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_StickInfo> &out_List) const
{
	_gamepad_Device_CP -> GetValidStickList(gamepad_Index , out_List);
}


//============================================================================
//! �W���C�X�e�B�b�N�̏����擾
dlBOOL C_DL2DFrameWorkGamepad::GetPadDeviceInfomation(dlU32 gamepad_Index , S_PadDeviceInfomation& out_Info_S) const
{
	if(_gamepad_Device_CP -> GetConnectGamePadVal() <= gamepad_Index){return dlFALSE;}

	LPDIRECTINPUTDEVICE8 device = _gamepad_Device_CP -> GetGamepadDevice(gamepad_Index);
	DIDEVICEINSTANCE device_Info;
	device_Info.dwSize = sizeof(DIDEVICEINSTANCE);
	device -> GetDeviceInfo(&device_Info);

	//��ޖ��̎擾
	out_Info_S.product_Name = device_Info.tszProductName;
	
	//���j�[�N���̎擾
	dlU8* unique_Name = NULL;
	UuidToString(&device_Info.guidInstance , &unique_Name);
	out_Info_S.unique_Name = boost::lexical_cast<dlSTRING>(unique_Name);
	RpcStringFree(&unique_Name);

	//�j���[�g�����l�̎擾
	_gamepad_Device_CP -> GetGamepadNeutralList(gamepad_Index , out_Info_S.neutral_List);

	return dlTRUE;
}

//============================================================================
//! �f�o�C�X�̃A�N�e�B�u�ύX
void C_DL2DFrameWorkGamepad::SetActive(dlBOOL window_Active_Flg)
{
	_gamepad_Device_CP -> SetUpdateFlg(window_Active_Flg);
}

//============================================================================
//! �E�B���h�E�̃A�N�e�B�u�ύX
dlBOOL C_DL2DFrameWorkGamepad::IsWaitPeriod(void) const
{
	return _gamepad_Device_CP -> IsWaitPeriod();
}

//============================================================================
//! �w��L�[��������Ă��邩
dlBOOL C_DL2DFrameWorkGamepad::IsPrsKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kPRS , key_No);
}

//============================================================================
//! �w��L�[�������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkGamepad::IsTrgKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kTRG , key_No);
}

//============================================================================
//! �w��L�[�������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkGamepad::IsRlsKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kRLS , key_No);
}

//============================================================================
//! �w��L�[�����s�[�g��Ԃ�
dlBOOL C_DL2DFrameWorkGamepad::IsRepeatKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kREPEAT , key_No);
}

//============================================================================
//! �w��L�[���_�u���N���b�N���ꂽ��
dlBOOL C_DL2DFrameWorkGamepad::IsDoubleClickKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kDOUBLE_CLICK , key_No);
}

//============================================================================
//! �w��L�[�`�F�b�N
dlBOOL C_DL2DFrameWorkGamepad::IsKey(dlU8 key_No , dlS32 state) const
{
	return _gamepad_Device_CP -> IsButton(state , key_No);
}

}