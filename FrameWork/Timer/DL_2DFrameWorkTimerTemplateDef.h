/****************************************************************************/
/* 2DFrameWorkTimerTemplateDef.h											*/
/****************************************************************************/
#ifndef DL_INCLUDE_BY_FRAMEWORK_TIMER_H_
#	error このファイルはインクルードできません
#endif

namespace DL
{

//============================================================================
//! 一定時間経過した時に呼ばれるコールバック関数を設定
template <class CLASS_NAME>
void C_DL2DFrameWorkTimer::CreateFuncTimer(dlS32 wait_Time , CLASS_NAME* class_CP , void (CLASS_NAME::*func_P)(dlS32) , dlS32 variable)
{
	//ゼロ以下は設定不可能
	if(wait_Time <= 0)
	{
		SystemError(kSYSER_INJ_UNDER_ZERO , "Setting Wait Time Under Zero");
	}

	S_FuncTimer info_S;
	info_S.callback_TP = dlNEW T_CallBack<CLASS_NAME>();
	static_cast<T_CallBack<CLASS_NAME>*>(info_S.callback_TP) -> SetAction(func_P , class_CP , variable);
	info_S.result_Time = wait_Time;
	_func_Stack_List.push_back(info_S);
}

template <class CLASS_NAME>
void C_DL2DFrameWorkTimer::CreateFuncTimer(dlS32 wait_Time , CLASS_NAME* class_CP , void (CLASS_NAME::*func_P)(void))
{
	//ゼロ以下は設定不可能
	if(wait_Time <= 0)
	{
		SystemError(kSYSER_INJ_UNDER_ZERO , "Setting Wait Time Under Zero");
	}

	S_FuncTimer info_S;
	info_S.callback_TP = dlNEW T_CallBack<CLASS_NAME>();
	static_cast<T_CallBack<CLASS_NAME>*>(info_S.callback_TP) -> SetAction(func_P , class_CP);
	info_S.result_Time = wait_Time;
	_func_Stack_List.push_back(info_S);
}

}