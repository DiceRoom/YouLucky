/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkWindow.h"
#include <DL_2DFrameWork.h>

namespace DL
{

//============================================================================
//! 初期化
void C_DL2DFrameWorkWindow::Initialize(dlU16 wnd_W_Size , dlU16 wnd_H_Size , const dlSTRING& wnd_Name , void (*game_Proc_P)(void))
{
	_window_Size_Int32_S = S_IntVec2(wnd_W_Size , wnd_H_Size);
	_window_Size_S = S_Vector2(wnd_W_Size , wnd_H_Size);
	C_Window::Initialize(wnd_Name , wnd_W_Size , wnd_H_Size , game_Proc_P , dlFALSE);
}

//============================================================================
//! 終了処理
void C_DL2DFrameWorkWindow::Terminate(void)
{
	C_Window::Terminate();
}

//============================================================================
//! メッセージコールバックの追加
void C_DL2DFrameWorkWindow::AddCallBack(dlS32 priority , C_MessageCallback callback_Proc_P)
{
	//同じ優先度が設定されたらエラー
	if(_callback_Proc_Map.find(priority) != _callback_Proc_Map.end())
	{
		assert(!"Add Windows Callback Same Priority");
	}

	_callback_Proc_Map.insert(std::pair<dlS32 , C_MessageCallback>(priority , callback_Proc_P));
}

//============================================================================
//! メッセージコールバックの削除
void C_DL2DFrameWorkWindow::EraseCallBack(dlS32 priority)
{
	_callback_Proc_Map.erase(priority);
}

//============================================================================
//! ウィンドウ終了時に呼ばれるコールバックの設定
void C_DL2DFrameWorkWindow::SetCloseWindowCallback(const C_CloseWindowCallback& close_Callback)
{
	C_Window::SetCloseWindowCallback(close_Callback);
}

//============================================================================
//! ウィンドウハンドルの取得
HWND C_DL2DFrameWorkWindow::GetWindowHandle(void) const
{
	return C_Window::GetWindowHandle();
}

//============================================================================
//! ウィンドウの位置を変更
void C_DL2DFrameWorkWindow::SetWindowPosition(const S_IntVec2& pos_S)
{
	SetWindowPos(GetWindowHandle() , HWND_TOP , pos_S.x , pos_S.y , 0 , 0 , SWP_NOSIZE);
}

//============================================================================
//! ウィンドウの位置を取得
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
//! ダイアログボックスを表示する
dlU32 C_DL2DFrameWorkWindow::DispDialog(const dlSTRING& title , const dlSTRING& text , dlU32 type)
{
	return MessageBox(C_Window::GetWindowHandle() , text.c_str() , title.c_str() , type);
}

}