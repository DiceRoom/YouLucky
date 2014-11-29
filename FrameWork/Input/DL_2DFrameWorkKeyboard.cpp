/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkKeyboard.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkKeyboard::Initialize(void)
{
	_keyboard_Device_CP = dlNEW C_DirectXKeyboardDevice();
	_keyboard_Device_CP -> CreateDevice(C_DL2DFrameWork::WINDOW -> GetWindowHandle() , C_DL2DFrameWork::CORE -> GetDirectXDevice() -> GetDirectXInput8());
}

//============================================================================
//! �I������
void C_DL2DFrameWorkKeyboard::Terminate(void)
{
	dlDELETE _keyboard_Device_CP;
}

//============================================================================
//! �w��L�[��������Ă��邩
dlBOOL C_DL2DFrameWorkKeyboard::IsPrsKey(dlU8 key_No) const
{
	return _keyboard_Device_CP -> IsButton(DL::kPRS , key_No);
}

//============================================================================
//! �w��L�[�������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkKeyboard::IsTrgKey(dlU8 key_No) const
{
	return _keyboard_Device_CP -> IsButton(DL::kTRG , key_No);
}

//============================================================================
//! �w��L�[�������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkKeyboard::IsRlsKey(dlU8 key_No) const
{
	return _keyboard_Device_CP -> IsButton(DL::kRLS , key_No);
}

//============================================================================
//! �w��L�[�����s�[�g��Ԃ�
dlBOOL C_DL2DFrameWorkKeyboard::IsRepeatKey(dlU8 key_No) const
{
	return _keyboard_Device_CP -> IsButton(DL::kREPEAT , key_No);
}

//============================================================================
//! �w��L�[���_�u���N���b�N���ꂽ��
dlBOOL C_DL2DFrameWorkKeyboard::IsDoubleClickKey(dlU8 key_No) const
{
	return _keyboard_Device_CP -> IsButton(DL::kDOUBLE_CLICK , key_No);
}

//============================================================================
//! �w��L�[�`�F�b�N
dlBOOL C_DL2DFrameWorkKeyboard::IsKey(dlU8 key_No , dlS32 state) const
{
	return _keyboard_Device_CP -> IsButton(state , key_No);
}

//============================================================================
//! �L�[�{�[�h�̃L�[�ŉ�����Ă���ԍ��̃��X�g���擾
void C_DL2DFrameWorkKeyboard::GetPrsKeyboardKeyList(std::list<dlU8>& out_List) const
{
	const dlU8* key_Data_P = _keyboard_Device_CP -> GetCurrentKeyData();
	out_List.clear();
	for(dlU32 cnt = 0 ; cnt < 256 ; ++ cnt)
	{
		if(key_Data_P[cnt] != 0){out_List.push_back(static_cast<dlU8>(cnt));}
	}
}

//============================================================================
//! �E�B���h�E�̃A�N�e�B�u�ύX
void C_DL2DFrameWorkKeyboard::SetActive(dlBOOL window_Active_Flg)
{
	_keyboard_Device_CP -> SetUpdateFlg(window_Active_Flg);
}

}