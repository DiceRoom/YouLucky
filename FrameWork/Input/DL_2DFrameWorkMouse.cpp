/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkMouse.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkMouse::Initialize(void)
{
	_mouse_Device_CP = dlNEW C_DirectXMouseDevice();
	_mouse_Device_CP -> CreateDevice(C_DL2DFrameWork::WINDOW -> GetWindowHandle() , C_DL2DFrameWork::CORE -> GetDirectXDevice() -> GetDirectXInput8());
}

//============================================================================
//! �I������
void C_DL2DFrameWorkMouse::Terminate(void)
{
	dlDELETE _mouse_Device_CP;
}

//============================================================================
//! �}�E�X�̍��{�^���������ꂽ��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsPrsLMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kPRS , 0);
}

//============================================================================
//! �}�E�X�̍��{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsTrgLMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kTRG , 0);
}

//============================================================================
//! �}�E�X�̍��{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRlsLMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kRLS , 0);
}

//============================================================================
//! �}�E�X�̍��{�^�������s�[�g��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRepeatLMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kREPEAT , 0);
}

//============================================================================
//! �}�E�X�̍��{�^�����_�u���N���b�N���ꂽ�� 
dlBOOL C_DL2DFrameWorkMouse::IsDoubleClickLMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kDOUBLE_CLICK , 0);
}

//============================================================================
//! �}�E�X�̍��{�^���̏�Ԏw��`�F�b�N
dlBOOL C_DL2DFrameWorkMouse::IsLMouse(dlS32 state) const
{
	return _mouse_Device_CP -> IsButton(state , 0);
}

//============================================================================
//! �}�E�X�̉E�{�^���������ꂽ��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsPrsRMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kPRS , 1);
}

//============================================================================
//! �}�E�X�̉E�{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsTrgRMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kTRG , 1);
}

//============================================================================
//! �}�E�X�̉E�{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRlsRMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kRLS , 1);
}

//============================================================================
//! �}�E�X�̉E�{�^�������s�[�g��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRepeatRMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kREPEAT , 1);
}

//============================================================================
//! �}�E�X�̉E�{�^�����_�u���N���b�N���ꂽ�� 
dlBOOL C_DL2DFrameWorkMouse::IsDoubleClickRMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kDOUBLE_CLICK , 1);
}

//============================================================================
//! �}�E�X�̉E�{�^���̏�Ԏw��`�F�b�N
dlBOOL C_DL2DFrameWorkMouse::IsRMouse(dlS32 state) const
{
	return _mouse_Device_CP -> IsButton(state , 1);
}

//============================================================================
//! �}�E�X�̒����{�^���������ꂽ��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsPrsCMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kPRS , 2);
}

//============================================================================
//! �}�E�X�̒����{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsTrgCMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kTRG , 2);
}

//============================================================================
//! �}�E�X�̒����{�^���������ꂽ�u�Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRlsCMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kRLS , 2);
}
//============================================================================
//! �}�E�X�̒����{�^�������s�[�g��Ԃ�
dlBOOL C_DL2DFrameWorkMouse::IsRepeatCMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kREPEAT , 2);
}

//============================================================================
//! �}�E�X�̒����{�^�����_�u���N���b�N���ꂽ�� 
dlBOOL C_DL2DFrameWorkMouse::IsDoubleClickCMouse(void) const
{
	return _mouse_Device_CP -> IsButton(kDOUBLE_CLICK , 2);
}

//============================================================================
//! �}�E�X�̒����{�^���̏�Ԏw��`�F�b�N
dlBOOL C_DL2DFrameWorkMouse::IsCMouse(dlS32 state) const
{
	return _mouse_Device_CP -> IsButton(state , 2);
}

//============================================================================
//! �}�E�X�̃L�[�̏�Ԏw��`�F�b�N
dlBOOL C_DL2DFrameWorkMouse::IsMouseKey(dlS32 key_No , dlS32 state) const
{
	return _mouse_Device_CP -> IsButton(state , key_No);
}

//============================================================================
//! �}�E�X�z�C�[���̈ړ��ʎ擾
dlBOOL C_DL2DFrameWorkMouse::GetMouseWheelMove(dlS32& out_Move) const
{
	if(!C_DL2DFrameWork::CORE -> IsActiveFlg())
	{
		return dlFALSE;
	}

	out_Move = _mouse_Device_CP -> GetMouseInfo().mouse_Wheel_Move;
	return dlTRUE;
}

//============================================================================
//! �}�E�X�J�[�\���̌��݈ʒu
dlBOOL C_DL2DFrameWorkMouse::GetMousePos(S_IntVec2& out_Pos_S) const
{
	if(!C_DL2DFrameWork::CORE -> IsActiveFlg())
	{
		return dlFALSE;
	}

	S_Mouse mouse_Pos_S = _mouse_Device_CP -> GetMouseInfo();
	out_Pos_S = S_IntVec2(mouse_Pos_S.mouse_From_Client_X , mouse_Pos_S.mouse_From_Client_Y);
	return dlTRUE;
}

//============================================================================
//! �E�B���h�E�̃A�N�e�B�u�ύX
void C_DL2DFrameWorkMouse::SetActive(dlBOOL window_Active_Flg)
{
	_mouse_Device_CP -> SetUpdateFlg(window_Active_Flg);
}

}