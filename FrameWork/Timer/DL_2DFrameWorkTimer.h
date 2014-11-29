/****************************************************************************/
/* DL_2DFrameWorkTimer.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKTIMER_H_
#define	DL_2DFRAMEWORKTIMER_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../../../Library/Utility/DL_OSTime.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

typedef dlCALLBACK<void (void)> TIMER_CALLBACK;

//! タイマー用
struct S_Timer
{
	timev old_Time_S;						//< 前回の時間保持用
	dlF64 progress_Time;					//< 前回のフレームから経過した時間
	dlU64 begingame_After_Progress_Time;	//< フレームワークが起動してから経過した時間(ミリ秒)
	dlU64 frame_Count;						//< フレーム単位で何回経過しているか
};

//! 2Dゲーム用フレームワーク(タイマー)
class C_DL2DFrameWorkTimer
{
friend class C_DL2DFrameWork;
private:
	//! Funcタイマー用
	struct S_FuncTimer
	{
		dlS32 result_Time;
		TIMER_CALLBACK timer_Callback;
	};

	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkTimer(void){}
	~C_DL2DFrameWorkTimer(void){}
	C_DL2DFrameWorkTimer(const C_DL2DFrameWorkTimer &){}


public:
	void Initialize				(void);
	void Terminate				(void);

	void	CreateNewTimer		(dlS32 timer_Handle);
	void	DeleteTimer			(dlS32 timer_Handle);
	void	DeleteAllTimer		(void);

	void	InitializeTimer		(dlS32 timer_Handle);
	dlF64	GetFrameTime		(dlS32 timer_Handle);
	dlU64	GetProgressTime		(dlS32 timer_Handle);
	dlU64	GetFrameVal			(dlS32 timer_Handle);

	void	CreateFuncTimer		(dlS32 wait_Time , const TIMER_CALLBACK& timer_Callback);
	void	DeleteAllFuncTimer	(dlBOOL force_Delete_Flg = dlFALSE);
	size_t	GetFuncTimerVal		(void) const;

	void Update(void);

private:
	NODE_HANDLE					_update_Node_Handle;	//< 更新を掛けるノードのハンドル
	std::map<dlS32 , S_Timer>	_timer_Map;				//< タイマーのマップ
	std::vector<S_FuncTimer>	_func_List;				//< 一定時間経過後に呼び出す関数のリスト
	std::vector<S_FuncTimer>	_func_Stack_List;		//< 作成した直後に格納されるリスト
	dlBOOL						_func_Timer_Delete_Flg;	//< 削除フラグ
};

}

#endif
