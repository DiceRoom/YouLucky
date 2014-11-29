/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkWindow.h"
#include <DL_2DFrameWork.h>

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkWindow::Initialize(dlU16 wnd_W_Size , dlU16 wnd_H_Size , const dlSTRING& wnd_Name , void (*game_Proc_P)(void))
{
	_window_Size_Int32_S = S_IntVec2(wnd_W_Size , wnd_H_Size);
	_window_Size_S = S_Vector2(wnd_W_Size , wnd_H_Size);
	C_Window::Initialize(wnd_Name , wnd_W_Size , wnd_H_Size , game_Proc_P , dlFALSE);
}

//============================================================================
//! �I������
void C_DL2DFrameWorkWindow::Terminate(void)
{
	C_Window::Terminate();
}

//============================================================================
//! ���b�Z�[�W�R�[���o�b�N�̒ǉ�
void C_DL2DFrameWorkWindow::AddCallBack(dlS32 priority , C_MessageCallback callback_Proc_P)
{
	//�����D��x���ݒ肳�ꂽ��G���[
	if(_callback_Proc_Map.find(priority) != _callback_Proc_Map.end())
	{
		assert(!"Add Windows Callback Same Priority");
	}

	_callback_Proc_Map.insert(std::pair<dlS32 , C_MessageCallback>(priority , callback_Proc_P));
}

//============================================================================
//! ���b�Z�[�W�R�[���o�b�N�̍폜
void C_DL2DFrameWorkWindow::EraseCallBack(dlS32 priority)
{
	_callback_Proc_Map.erase(priority);
}

//============================================================================
//! �E�B���h�E�I�����ɌĂ΂��R�[���o�b�N�̐ݒ�
void C_DL2DFrameWorkWindow::SetCloseWindowCallback(const C_CloseWindowCallback& close_Callback)
{
	C_Window::SetCloseWindowCallback(close_Callback);
}

//============================================================================
//! �E�B���h�E�n���h���̎擾
HWND C_DL2DFrameWorkWindow::GetWindowHandle(void) const
{
	return C_Window::GetWindowHandle();
}

//============================================================================
//! �E�B���h�E�̈ʒu��ύX
void C_DL2DFrameWorkWindow::SetWindowPosition(const S_IntVec2& pos_S)
{
	SetWindowPos(GetWindowHandle() , HWND_TOP , pos_S.x , pos_S.y , 0 , 0 , SWP_NOSIZE);
}

//============================================================================
//! �E�B���h�E�̈ʒu���擾
S_IntVec2 C_DL2DFrameWorkWindow::GetWindowPosition(void) const
{
	DL::S_IntVec2 ret_Pos_S;

	HWND window_Handle = C_Window::GetWindowHandle();
	if(window_Handle != 0)
	{
		RECT rect;
		GetWindowRect(window_Handle , &rect);
		ret_Pos_S.x = rect.left;
		ret_Pos_S.y = rect.top;
	}
	else
	{
		C_Window::GetLastWindowPosition(ret_Pos_S.x , ret_Pos_S.y);
	}

	return ret_Pos_S;
}

//============================================================================
//! �_�C�A���O�{�b�N�X��\������
dlU32 C_DL2DFrameWorkWindow::DispDialog(const dlSTRING& title , const dlSTRING& text , dlU32 type)
{
	return MessageBox(C_Window::GetWindowHandle() , text.c_str() , title.c_str() , type);
}

}