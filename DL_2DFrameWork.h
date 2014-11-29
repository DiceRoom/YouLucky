/****************************************************************************/
/* DL_2DFrameWork.h															*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORK_H_
#define	DL_2DFRAMEWORK_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "FrameWork/Node/DL_CoreNode.h"
#include "DL_2DFrameWorkSystemErrorInc.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! 2Dゲーム用フレームワーク(モノステートパターン)
class C_DL2DFrameWork
{
public:
	//! 現在の状況
	enum E_RunState
	{
		kSTATE_INITIALIZE = 0,		//< 初期化
		kSTATE_SYSTEM_WAIT,			//< システムウェイト
		kSTATE_UPDATE_INPUT,		//< 入力情報の更新
		kSTATE_UPDATE_NODE,			//< ノード更新中(Update)
		kSTATE_REVISION_NODE,		//< ノード更新中(Revision)
		kSTATE_FINISH_NODE,			//< ノード更新中(Finish)
		kSTATE_RENDER,				//< 描画中
		kSTATE_TERMINATE,			//< 終了処理
	};
	
private:
	C_DL2DFrameWork	(void){}
	~C_DL2DFrameWork(void){}
	C_DL2DFrameWork	(const C_DL2DFrameWork &){}

public:
	typedef dlCALLBACK<void (void)> GAME_END_CALLBACK;

public:
	static void		Initialize			(dlU16 wnd_W_Size , dlU16 wnd_H_Size , const dlSTRING &wnd_Name , dlU32 node_Line_Val);
	static void		Run					(C_CoreNode* main_Node_CP);
	static dlS32	GetCurrentRunState	(void);
#ifdef WIN32
	static void	DeviceLostCallback	(void);
#else
	static void PreProcess(C_CoreNode* main_Node_CP);
	static void PostProcess();
#endif

	//その他
	static void	Error(const dlSTRING& title , const dlSTRING& error_Text , dlBOOL forced_End_Flg);

private:
	static void		_RunCore			(void);
	static void		_Terminate			(void);
#ifdef WIN32
	static void		_FrameWorkLoop		(void);
	static dlBOOL	_FrameWorkCallBack	(HWND wnd_Handle , dlU32 msg , WPARAM w_Param , LPARAM l_Param);
#else
public:
	static void		_FrameWorkLoop		(void);
#endif
    
	//全てアクセス可能(ユーザー使用可能型)
public:
	static class C_DL2DFrameWorkCore*			CORE;			//< コア
	static class C_DL2DFrameWorkUtility*		UTILITY;		//< ユーティリティ
	static class C_DL2DFrameWorkNode*			NODE;			//< ノード
	static class C_DL2DFrameWorkScene*			SCENE;			//< シーン情報
	static class C_DL2DFrameWorkCollision*		CLS;			//< 当たり判定情報
#ifdef WIN32
	static class C_DL2DFrameWorkWindow*			WINDOW;			//< ウィンドウ関連
	static class C_DL2DFrameWorkKeyboard*		KEYBOARD;		//< キーボード操作
	static class C_DL2DFrameWorkMouse*			MOUSE;			//< マウス操作
	static class C_DL2DFrameWorkGamepad*		PAD;			//< パッド操作
#endif
	static class C_DL2DFrameWorkSound*			SOUND;			//< 音響関連
	static class C_DL2DFrameWorkTimer*			TIMER;			//< タイマー関連
	static class C_DL2DFrameWorkRender*			RENDER;			//< 描画関連
	static class C_DL2DFrameWorkImage*			IMAGE;			//< イメージ
	static class C_DL2DFrameWorkText*			TEXT;			//< テキスト
	static class C_DL2DFrameWorkDrawPrimitive*	DRAW_PRIMITIVE;	//< プリミティブ描画

private:
	static E_RunState _run_State;
};

typedef C_DL2DFrameWork FW;

}

#endif
