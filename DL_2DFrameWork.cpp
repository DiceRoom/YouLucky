/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWork.h"


#ifdef _DEBUG
#pragma comment(lib , "DLFrameWork_deb.lib")
#else
#pragma comment(lib , "DLFrameWork.lib")
#endif

#ifdef WIN32
#include <crtdbg.h>
#include <tchar.h>
#include "FrameWork/Window/DL_2DFrameWorkWindow.h"
#include "FrameWork/Input/DL_2DFrameWorkKeyboard.h"
#include "FrameWork/Input/DL_2DFrameWorkMouse.h"
#include "FrameWork/Input/DL_2DFrameWorkGamepad.h"
#endif
#include "FrameWork/Utility/DL_2DFrameWorkUtility.h"
#include "FrameWork/Node/DL_2DFrameWorkNode.h"
#include "FrameWork/Timer/DL_2DFrameWorkTimer.h"
#include "FrameWork/Scene/DL_2DFrameWorkScene.h"
#include "FrameWork/Collision/DL_2DFrameWorkCls.h"
#include "FrameWork/Sound/DL_2DFrameWorkSound.h"
#include "FrameWork/Render/DL_2DFrameWorkRender.h"
#include "FrameWork/Render/Image/DL_2DFrameWorkImage.h"
#include "FrameWork/Render/Primitive/DL_2DFrameWorkDrawPrimitive.h"
#include "FrameWork/Render/Text/DL_2DFrameWorkText.h"
#include "FrameWork/Core/DL_2DFrameWorkCore.h"

namespace DL
{

C_DL2DFrameWorkCore*			C_DL2DFrameWork::CORE;
C_DL2DFrameWorkUtility*			C_DL2DFrameWork::UTILITY;
#ifdef WIN32
C_DL2DFrameWorkWindow*			C_DL2DFrameWork::WINDOW;
C_DL2DFrameWorkKeyboard*		C_DL2DFrameWork::KEYBOARD;
C_DL2DFrameWorkMouse*			C_DL2DFrameWork::MOUSE;
C_DL2DFrameWorkGamepad*			C_DL2DFrameWork::PAD;
#endif
C_DL2DFrameWorkNode*			C_DL2DFrameWork::NODE;
C_DL2DFrameWorkScene*			C_DL2DFrameWork::SCENE;
C_DL2DFrameWorkCollision*		C_DL2DFrameWork::CLS;
C_DL2DFrameWorkSound*			C_DL2DFrameWork::SOUND;
C_DL2DFrameWorkTimer*			C_DL2DFrameWork::TIMER;
C_DL2DFrameWorkRender*			C_DL2DFrameWork::RENDER;
C_DL2DFrameWorkImage*			C_DL2DFrameWork::IMAGE;
C_DL2DFrameWorkText*			C_DL2DFrameWork::TEXT;
C_DL2DFrameWorkDrawPrimitive*	C_DL2DFrameWork::DRAW_PRIMITIVE;

C_DL2DFrameWork::E_RunState C_DL2DFrameWork::_run_State = C_DL2DFrameWork::kSTATE_INITIALIZE;

//============================================================================
//! システムエラー
void SystemError(dlS32 error_No , const dlSTRING& plus_Str)
{
	C_DL2DFrameWork::Error("SystemError" , SystemError_A[error_No].message + "\n" + plus_Str , SystemError_A[error_No].forced_End_Flg);
}

//============================================================================
//! 初期化
void C_DL2DFrameWork::Initialize(dlU16 wnd_W_Size , dlU16 wnd_H_Size , const dlSTRING &wnd_Name , dlU32 node_Line_Val)
{
#ifdef WIN32
	//実行ファイルのフルパス名取得
	TCHAR path[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	GetModuleFileName(NULL , path , _MAX_PATH);
	//フルパス名の分解
#ifdef __STDC_WANT_SECURE_LIB__
	_tsplitpath_s(path, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
#else
	_tsplitpath(path, drive, dir, NULL, NULL);
#endif

	//ドライブ名とディレクトリ名のみをコピー
	lstrcpy(path , drive);
	lstrcat(path , dir);

	//カレントディレクトリの設定
	SetCurrentDirectory(path);
#endif

	CORE = dlNEW C_DL2DFrameWorkCore();
	UTILITY = dlNEW C_DL2DFrameWorkUtility();
#ifdef WIN32
	WINDOW = dlNEW C_DL2DFrameWorkWindow();
	KEYBOARD = dlNEW C_DL2DFrameWorkKeyboard();
	MOUSE = dlNEW C_DL2DFrameWorkMouse();
	PAD = dlNEW C_DL2DFrameWorkGamepad();
#endif
	NODE = dlNEW C_DL2DFrameWorkNode();
	SCENE = dlNEW C_DL2DFrameWorkScene();
	CLS = dlNEW C_DL2DFrameWorkCollision();
	SOUND = dlNEW C_DL2DFrameWorkSound();
	TIMER = dlNEW C_DL2DFrameWorkTimer();
	RENDER = dlNEW C_DL2DFrameWorkRender();
	IMAGE = dlNEW C_DL2DFrameWorkImage();
	TEXT = dlNEW C_DL2DFrameWorkText();
	DRAW_PRIMITIVE = dlNEW C_DL2DFrameWorkDrawPrimitive();
	
	/*
	各種フレームワークモジュールの初期化
	
	WINDOW → CORE
	→ NODE → UTILITY
	→ KEYBOARD → MOUSE → PAD → INPUT → SOUND
	→ RENDER → IMAGE → DRAW_PRIMITIVE → TEXT
	→ CLS → TIMER → SCENE
	*/
#ifdef WIN32
	WINDOW -> Initialize(wnd_W_Size , wnd_H_Size , wnd_Name , C_DL2DFrameWork::_FrameWorkLoop);
#endif
	CORE -> Initialize();
	NODE -> Initialize(node_Line_Val);
	UTILITY -> Initialize();
#ifdef WIN32
	KEYBOARD -> Initialize();
	MOUSE -> Initialize();
	PAD -> Initialize();
#endif
	
	SOUND -> Initialize();
	
	RENDER -> Initialize();
	IMAGE -> Initialize(wnd_W_Size , wnd_H_Size);
	DRAW_PRIMITIVE -> Initialize();
	TEXT -> Initialize(wnd_W_Size , wnd_H_Size);
	
	CLS -> Initialize();
	TIMER -> Initialize();
	SCENE -> Initialize();

#ifdef WIN32
	//位置変更
	TCHAR oldPath[4096];
	GetCurrentDirectory(4096, oldPath);
	SetCurrentDirectory("DLL");
#endif

	//その他コントローラー初期化
	MovieController::sharedInstance() -> setWindowSize(wnd_W_Size , wnd_H_Size);
#ifdef WIN32
	MovieController::sharedInstance() -> setDirectXDevice(CORE -> GetDirectXDevice() -> GetDevice());
#endif
	MovieController::sharedInstance() -> setAudioController(AudioController::sharedInstance());

//	NPlayerController::sharedInstance() -> setWindowSize(wnd_W_Size , wnd_H_Size);
#ifdef WIN32
	NPlayerController::sharedInstance() -> setDirectXDevice(CORE -> GetDirectXDevice() -> GetDevice());
#endif

#ifdef WIN32
	SetCurrentDirectory(oldPath);
#endif
}

//============================================================================
//! 実際実行するループ
void C_DL2DFrameWork::Run(C_CoreNode* main_Node_CP)
{
#ifdef WIN32
	//初期化が行われていない場合エラー
	if(CORE -> GetDirectXDevice() == 0)
	{
		SystemError(kSYSER_INJ_C_DL2DFrameWork_INIT);
	}
#endif
	//メインノードの作成してシステムラインに追加
	main_Node_CP -> Initialize();
	NODE -> _main_Node_CP = main_Node_CP;

	//ゲーム開始
	_RunCore();
	
	//終了処理
	main_Node_CP -> Terminate();
	_Terminate();
}

//============================================================================
//! 現在のステータス取得
dlS32 C_DL2DFrameWork::GetCurrentRunState(void)
{
	return _run_State;
}

#ifdef WIN32
//============================================================================
//! デバイスロストした時に呼ばれるコールバック
void C_DL2DFrameWork::DeviceLostCallback(void)
{

}
#else
void C_DL2DFrameWork::PreProcess(C_CoreNode* main_Node_CP){

	//メインノードの作成してシステムラインに追加
	main_Node_CP -> Initialize();
	NODE -> _main_Node_CP = main_Node_CP;
	
	//ゲーム開始
	_RunCore();

}
void C_DL2DFrameWork::PostProcess(){
	NODE -> _main_Node_CP -> Terminate();
	_Terminate();
}

#endif

//============================================================================
//! エラー
void C_DL2DFrameWork::Error(const dlSTRING& title , const dlSTRING& error_Text , dlBOOL forced_End_Flg)
{
#ifdef _WIN32 
	if(forced_End_Flg)
	{
		C_DL2DFrameWork::WINDOW -> DispDialog(title , error_Text , MB_OK | MB_ICONSTOP);
		DL_HALT();
	}
	else
	{
		const dlU32 ret_Val = C_DL2DFrameWork::WINDOW -> DispDialog(title , error_Text + "\nGameStop?" , MB_YESNO | MB_ICONSTOP);
		if(ret_Val == IDYES)
		{
			DL_HALT();
		}
	}
#else
//	assert(!"Not Windows");
#endif
}

//============================================================================
//! 実行
void C_DL2DFrameWork::_RunCore(void)
{
#ifdef WIN32
	C_Window::AddCallBack(-1 , _FrameWorkCallBack);
	C_Window::Run();
#else
    CORE->Render();
#endif
}

//============================================================================
//! 実際実行するループ
void C_DL2DFrameWork::_FrameWorkLoop(void)
{
	//音響
	SOUND -> Update();

	//システムウェイトチェック
	if(CORE -> CheckWait())
	{
		_run_State = kSTATE_SYSTEM_WAIT;
		return;
	}

#ifdef WIN32
	//入力条件の更新
	_run_State = kSTATE_UPDATE_INPUT;
	KEYBOARD -> _keyboard_Device_CP -> Update();
	MOUSE -> _mouse_Device_CP -> Update();
	PAD -> _gamepad_Device_CP -> Update();
#endif

	//ノードの更新
	_run_State = kSTATE_UPDATE_NODE;
	NODE -> _UpdateNode();
	_run_State = kSTATE_REVISION_NODE;
	NODE -> _RevisionNode();
	_run_State = kSTATE_FINISH_NODE;
	NODE -> _FinishNode();

#ifdef WIN32
	//描画処理
	_run_State = kSTATE_RENDER;
	CORE -> Render();
#endif
}

//============================================================================
//! 終了処理
void C_DL2DFrameWork::_Terminate(void)
{
	_run_State = C_DL2DFrameWork::kSTATE_TERMINATE;
	DL::C_DL2DFrameWork::SCENE -> SetSceneValidFlg(dlTRUE);

	/*
	→ SCENE → TIMER → NODE → CLS
	→ INPUT → KEYBOARD → MOUSE → PAD → SOUND
	→ IMAGE → DRAW_PRIMITIVE → TEXT → NODE → RENDER
	→ UTILITY → WINDOW → NODE → CORE
	*/

	SCENE -> Termiante();
	TIMER -> Terminate();
	NODE -> _RemoveNode();
	CLS -> Terminate();

#ifdef WIN32
	KEYBOARD -> Terminate();
	MOUSE -> Terminate();
	PAD -> Terminate();
#endif

	SOUND -> Terminate();

	IMAGE -> Terminate();
	RENDER -> InValidGrid();
	DRAW_PRIMITIVE -> Terminate();
	TEXT -> Terminate();
	NODE -> _RemoveNode();
	RENDER -> Terminate();

	UTILITY -> Terminate();
#ifdef WIN32
	WINDOW -> Terminate();
#endif
	NODE -> Terminate();
	CORE -> Terminate();

	dlDELETE CORE;
	dlDELETE UTILITY;
#ifdef WIN32
	dlDELETE WINDOW;
	dlDELETE KEYBOARD;
	dlDELETE MOUSE;
	dlDELETE PAD;
#endif
	dlDELETE NODE;
	dlDELETE SCENE;
	dlDELETE CLS;
	dlDELETE SOUND;
	dlDELETE TIMER;
	dlDELETE RENDER;
	dlDELETE IMAGE;
	dlDELETE TEXT;
	dlDELETE DRAW_PRIMITIVE;
}

#ifdef WIN32
//============================================================================
//! コールバック
dlBOOL C_DL2DFrameWork::_FrameWorkCallBack(HWND wnd_Handle , dlU32 msg , WPARAM w_Param , LPARAM l_Param)
{
	//ユーザー側から設定されているコールバックの呼び出し
	dlS32 return_Val = (WINDOW -> _callback_Proc_Map.size() == 0) ? C_DL2DFrameWorkWindow::kALL_PROC : 0;
	MapItrLoop(dlS32 , C_DL2DFrameWorkWindow::C_MessageCallback , WINDOW -> _callback_Proc_Map , itr)
	{
		return_Val |= ((*itr).second)(wnd_Handle , msg , w_Param , l_Param);

		//他コールバック無視
		if((return_Val & WINDOW -> kCALLBACK_OTHER) == 0)
		{
			break;
		}
	}

	//フレームワークコールバック
	if((return_Val & WINDOW -> kCALLBACK_FRAMEWORK) != 0)
	{
		//メッセージ処理
		switch(msg)
		{
			//入力装置の為のアクティブ、非アクティブの切り替え
		case WM_ACTIVATE:
			CORE -> SetActiveFlg((LOWORD(w_Param) != 0));
			MOUSE -> SetActive(CORE -> IsActiveFlg());
			KEYBOARD -> SetActive(CORE -> IsActiveFlg());
			PAD -> SetActive(CORE -> IsActiveFlg());
			break;

			//ハードウェア構成の変更があった場合ジョイパッドを再設定
		case WM_DEVICECHANGE:
			PAD -> _gamepad_Device_CP -> ResetDevice();
			break;

		case WM_CLOSE:
			CORE -> SetRenderDefaultCallback();
			break;
		}
	}

	return ((return_Val & WINDOW -> kCALLBACK_LIBRARY) == 0);
}
#endif

}