/****************************************************************************/
/* DL_2DFrameWorkSystemErrorInc.h											*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKSYSTEMERRORINC_H_
#define	DL_2DFRAMEWORKSYSTEMERRORINC_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/

/****************************************************************************/
/////////////////////////////////// 型定義 ///////////////////////////////////
/****************************************************************************/

namespace DL
{

/****************************************************************************/
/* 型																		*/
/****************************************************************************/

//! システムエラー番号
enum E_SystemError
{
	//FrameWork
	kSYSER_INJ_C_DL2DFrameWork_INIT = 0,		//< フレームワークの初期化が行われていない

	//Utility
	kSYSER_NF_LIBFONT,			//< libFontRenderが無い
	kSYSER_NF_LIBIMAGE,			//< libImageRenderが無い
	kSYSER_NF_LIBAUDIO,			//< libAudioControllerが無い
	kSYSER_NF_LIBNOVEL,			//< libNovelPlayerが無い
	kSYSER_NF_LIBRENDERCORE,	//< libRenderCoreが無い
	kSYSER_NF_LIBMOVIE,			//< libMovieRenderが無い
	kSYSER_NF_LIBDATAARCHIVE,	//< libDataArchiveが無い
	kSYSER_INJ_RANDOM_ARG,		//< ランダム取得時の引数が負の数
	
	//Input
	kSYSER_INJ_IC_INIT,				//< INPUT条件の初期化が不正に呼び出された
	kSYSER_INJ_IC_ALREADY_SETTING,	//< INPUT条件が既に途中なのに開始命令がよばれた
	kSYSER_INJ_IC_ARG_OVERFLOW,		//< 設定を開始しようとしたINPUT条件の番号が最大値を超えている
	kSYSER_INJ_IC_RE_REF,			//< INPUT条件の設定が終わって追加した条件のチェック時に違う条件から再度参照された
	kSYSER_INJ_IC_ADD_NONE,			//< INPUT条件の設定が終わって追加した条件のチェック時に一つも条件が検出されなかった場合
	kSYSER_IC_NOT_BEGIN_SETTING,	//< INPUT条件設定が開始されていない状態で、条件の追加を行おうとした
	kSYSER_IC_STILL_BEGIN_CHECKED,	//< INPUT条件設定が開始されている状態で、条件のチェックをしようとした
	kSYSER_INJ_IC_CHECK_OVERFLOW,	//< 設定済みのINPUT条件のチェックをしようとした時の番号が最大値を超えている
	kSYSER_INJ_IC_GET_CONDITION,	//< 取得しようとしたINPUT条件がKEY,POV,STICKのいずれでもない
	kSYSER_INJ_IC_CREATE_CONDITION,	//< 作成しようとしたINPUT条件がKEY,POV,STICKのいずれでもない
	kSYSER_SAME_CALLBACK_PRIORITY,	//< 同一番号の優先順位のコールバックが指定された

	//Timer
	kSYSER_INJ_TMR_COLLIDE_HANDLE,	//< タイマー作成時に作ろうとしたハンドルが既に存在する
	kSYSER_TMR_NF_HANDLE0,			//< タイマー削除時、指定ハンドルが存在しない
	kSYSER_TMR_NF_HANDLE1,			//< タイマー初期化時、指定ハンドルが存在しない
	kSYSER_TMR_NF_HANDLE2,			//< 指定タイマーの前回フレームからの経過時間を取得時、指定ハンドルが存在しない
	kSYSER_TMR_NF_HANDLE3,			//< タイマー経過時間取得時、指定ハンドルが存在しない
	kSYSER_TMR_NF_HANDLE4,			//< タイマーフレーム数取得時、指定ハンドルが存在しない
	kSYSER_INJ_UNDER_ZERO,			//< 関数タイマー作成時に０以下が設定された

	//Render
	kSYSER_RND_MEMORYLEAK,			//< ゲーム終了時削除されていないノードが存在する

	//Image
	kSYSER_IMG_LOAD_FAILED,			//< イメージのロードに失敗

	//Button
	kSYSER_BT_ALREADY_LOAD_IMAGE,	//< ボタンに既にイメージがロードされている状態で再ロード
	kSYSER_BT_NF_BT_HANDLE0,		//< ボタンイメージ作成時、同一ハンドルが存在しない

	//Node
	kSYSER_NODE_MEMORYLEAK,			//< ゲーム終了時削除されていないノードが存在する

	//Core
	kSYSER_CORE_SQUIRRER_INIT,		//< Squirrelの起動に失敗
	kSYSER_CORE_SQUIRRER,			//< 起動中のSquirrelスクリプトにエラーが発生

	//Collision
	kSYSER_CLS_MEMORYLEAK,			//< ゲーム終了時削除されていない当たり判定オブジェクトが存在する

	kSYSER_VAL						//< システムエラー数
};

//! システムエラー情報
struct S_SystemError
{
	dlSTRING message;
	dlBOOL	forced_End_Flg;
};

const S_SystemError SystemError_A[kSYSER_VAL] = 
{
	//FrameWork
	{"CodeNo : 000\nSystem : FrameWork\nKind : Injustieced State\n[Run]",				dlTRUE},
	
	//Utility
	{"CodeNo : 100\nSystem : Utility\nKind : NotFound\n[libFontRender.dll]",			dlTRUE},
	{"CodeNo : 101\nSystem : Utility\nKind : NotFound\n[libImageRender.dll]",			dlTRUE},
	{"CodeNo : 102\nSystem : Utility\nKind : NotFound\n[libAudioController.dll]",		dlTRUE},
	{"CodeNo : 103\nSystem : Utility\nKind : NotFound\n[libNPlayer.dll]",				dlTRUE},
	{"CodeNo : 104\nSystem : Utility\nKind : NotFound\n[libRenderCore]",				dlTRUE},
	{"CodeNo : 105\nSystem : Utility\nKind : NotFound\n[libMovieRender.dll]",			dlTRUE},
	{"CodeNo : 106\nSystem : Utility\nKind : NotFound\n[libDataArchive.dll]",			dlTRUE},
	{"CodeNo : 107\nSystem : Utility\nKind : Injustieced Arg\n[C_DL2DFrameWork-Utility-GetRandom]",	dlFALSE},

	//Input
	{"CodeNo : 200\nSystem : Input\nKind : Injustieced Call\n[C_DL2DFrameWork-INPUT-Initialize]",								dlTRUE},
	{"CodeNo : 201\nSystem : Input\nKind : Injustieced State\n[C_DL2DFrameWork-INPUT-BeginPushCondition]\n<Already Setting>",	dlTRUE},
	{"CodeNo : 202\nSystem : Input\nKind : Injustieced Arg\n[C_DL2DFrameWork-INPUT-BeginPushCondition]\n<Seting No OverFlow>",	dlTRUE},
	{"CodeNo : 203\nSystem : Input\nKind : Injustieced Func\n[C_DL2DFrameWork-INPUT-EndPushCondition]\n<Ref Again>",				dlTRUE},
	{"CodeNo : 204\nSystem : Input\nKind : Injustieced Func\n[C_DL2DFrameWork-INPUT-EndPushCondition]\n<Add None>",				dlTRUE},
	{"CodeNo : 205\nSystem : Input\nKind : Injustieced State\n[C_DL2DFrameWork-INPUT-SetCondition",								dlTRUE},
	{"CodeNo : 206\nSystem : Input\nKind : Injustieced State\n[C_DL2DFrameWork-INPUT-IsValidCondition]\n<Setting>",				dlTRUE},
	{"CodeNo : 207\nSystem : Input\nKind : Injustieced State\n[C_DL2DFrameWork-INPUT-IsValidCondition]\n<OverFlow>",				dlTRUE},
	{"CodeNo : 208\nSystem : Input\nKind : Injustieced Arg\n[C_DL2DFrameWork-INPUT-_GetCondition]",								dlTRUE},
	{"CodeNo : 209\nSystem : Input\nKind : Injustieced Arg\n[C_DL2DFrameWork-INPUT-_CreateCondition]",							dlTRUE},
	{"CodeNo : 210\nSystem : Input\nKind : Injustieced Arg\n[C_DL2DFrameWork-INPUT-_AddSamePriorityCallback]",					dlTRUE},

	//Timer
	{"CodeNo : 300\nSystem : Timer\nKind : Injustieced Arg\n[C_DL2DFrameWork-TIMER-CreateNewTimer]",		dlTRUE},
	{"CodeNo : 301\nSystem : Timer\nKind : NotFound\n[C_DL2DFrameWork-TIMER-DeleteTimer]",				dlTRUE},
	{"CodeNo : 302\nSystem : Timer\nKind : NotFound\n[C_DL2DFrameWork-TIMER-InitializeTimer]",			dlTRUE},
	{"CodeNo : 303\nSystem : Timer\nKind : NotFound\n[C_DL2DFrameWork-TIMER-GetFrameTime]",				dlTRUE},
	{"CodeNo : 304\nSystem : Timer\nKind : NotFound\n[C_DL2DFrameWork-TIMER-GetProgressTime]",			dlTRUE},
	{"CodeNo : 305\nSystem : Timer\nKind : NotFound\n[C_DL2DFrameWork-TIMER-GetFrameVal]",				dlTRUE},
	{"CodeNo : 306\nSystem : Timer\nKind : Injustieced Arg\n[C_DL2DFrameWork-TIMER-CreateFuncTimer]",	dlTRUE},

	//Render
	{"CodeNo : 400\nSystem : Render\nKind : MemoryLeak\n[C_DL2DFrameWork-RENDER-Terminate]",		dlTRUE},

	//Image
	{"CodeNo : 500\nSystem : Render\nKind : Failed Func\n[C_DL2DFrameWork-IMAGE-CreateImage]",								dlFALSE},

	//Button
	{"CodeNo : 600\nSystem : Render\nKind : Injustieced State\n[C_DL2DFrameWork-BUTTON-CreateButtonImage]\n<Already LoadImage>",	dlFALSE},
	{"CodeNo : 601\nSystem : Render\nKind : Injustieced State\n[C_DL2DFrameWork-BUTTON-CreateButtonImage]\n<Already LoadImage>",	dlFALSE},

	//Node
	{"CodeNo : 700\nSystem : Render\nKind : MemoryLeak\n[C_DL2DFrameWork-NODE-Terminate]",		dlTRUE},

	//Core
	{"CodeNo : 800\nSystem : Core\nKind : Script\n[C_DL2DFrameWork-CORE-RunSquirrel]",	dlFALSE},
	{"CodeNo : 801\nSystem : Core\nKind : Script\n[C_DL2DFrameWork-CORE-_ProcessingSquirrel]",	dlFALSE},

	//Collision
	{"CodeNo : 901\nSystem : Cls\nKind : MemoryLeak\n[C_DL2DFrameWork-CLS-Terminate]",		dlTRUE},
};

void SystemError(dlS32 error_No , const dlSTRING& plus_Str = "");
}

#endif