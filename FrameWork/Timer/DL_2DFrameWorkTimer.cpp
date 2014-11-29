/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkTimer.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Node/DL_2DFrameWorkNode.h>

namespace DL
{

//! ワーカーノード(シーンの更新)
class C_TimerUpdateNode : public C_CoreNode
{
private:
	void _Update(void)
	{
		_timer_CP -> Update();
	};

private:
	ACS_PS_MEB(private , C_DL2DFrameWorkTimer* , _timer_CP , TimerAddress);
};


//============================================================================
//! 初期化
void C_DL2DFrameWorkTimer::Initialize(void)
{
	C_TimerUpdateNode* node_CP = C_DL2DFrameWork::NODE -> CreateNode<C_TimerUpdateNode>(kSYSTEM_FRONT_LINE , kSYS_NODE_PRI_TIMER , &_update_Node_Handle , dlTRUE);
	node_CP -> SetTimerAddress(this);
	_func_Timer_Delete_Flg = dlFALSE;
}
	
//============================================================================
//! 終了処理
void C_DL2DFrameWorkTimer::Terminate(void)
{
	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
}

//============================================================================
//! 新しいタイマーを追加する
void C_DL2DFrameWorkTimer::CreateNewTimer(dlS32 timer_Handle)
{
	//競合チェック
	if(_timer_Map.find(timer_Handle) != _timer_Map.end())
	{
		SystemError(kSYSER_INJ_TMR_COLLIDE_HANDLE);
	}
	
	//新規作成
	S_Timer new_Timer_S;
	_timer_Map.insert(std::pair<dlS32 , S_Timer>(timer_Handle , new_Timer_S));
	InitializeTimer(timer_Handle);
}

//============================================================================
//! タイマーの削除
void C_DL2DFrameWorkTimer::DeleteTimer(dlS32 timer_Handle)
{
	//チェック
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	
	//無ければ無視
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE0);
	}
	
	_timer_Map.erase(find_Itr);
}

//============================================================================
//! 全てのタイマーを削除
void C_DL2DFrameWorkTimer::DeleteAllTimer(void)
{
	_timer_Map.clear();
}

//============================================================================
//! タイマーの初期化
void C_DL2DFrameWorkTimer::InitializeTimer(dlS32 timer_Handle)
{
	//チェック
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE1);
	}

	find_Itr -> second.progress_Time = 0;
	find_Itr -> second.begingame_After_Progress_Time = 0;
	find_Itr -> second.frame_Count = 0;
	getNowTime(&find_Itr -> second.old_Time_S);
}

//============================================================================
//! この１フレーム間に経過した時間を取得
dlF64 C_DL2DFrameWorkTimer::GetFrameTime(dlS32 timer_Handle)
{
	//チェック
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE2);
	}

	return find_Itr -> second.progress_Time;
}

//============================================================================
//! 作成時から経過した時間を求める(ミリ秒・・・？)
dlU64 C_DL2DFrameWorkTimer::GetProgressTime(dlS32 timer_Handle)
{
	//チェック
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE3);
	}

	return find_Itr -> second.begingame_After_Progress_Time;
}

//============================================================================
//! 作成時から何フレーム経過したか
dlU64 C_DL2DFrameWorkTimer::GetFrameVal(dlS32 timer_Handle)
{
	//チェック
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE4);
	}

	return find_Itr -> second.frame_Count;
}

//============================================================================
//! 一定時間経過した時に呼ばれるコールバック関数を設定
void C_DL2DFrameWorkTimer::CreateFuncTimer(dlS32 wait_Time , const TIMER_CALLBACK& timer_Callback)
{
	//ゼロ以下は設定不可能
	if(wait_Time <= 0)
	{
		SystemError(kSYSER_INJ_UNDER_ZERO , "Setting Wait Time Under Zero");
	}

	S_FuncTimer info_S;
	info_S.timer_Callback = timer_Callback;
	info_S.result_Time = wait_Time;
	_func_Stack_List.push_back(info_S);
}

//============================================================================
//! 全てのコールバックタイマーを削除
void C_DL2DFrameWorkTimer::DeleteAllFuncTimer(dlBOOL force_Delete_Flg)
{
	if(force_Delete_Flg)
	{
		_func_Stack_List.clear();
		_func_List.clear();
	}
	else
	{
		_func_Timer_Delete_Flg = dlTRUE;
	}
}

//============================================================================
//! 一定時間経過した時に呼ばれるコールバック関数情報の数を取得
size_t C_DL2DFrameWorkTimer::GetFuncTimerVal(void) const
{
	return _func_List.size();
}

//============================================================================
//! 時間計測更新
void C_DL2DFrameWorkTimer::Update(void)
{
	timev current_Time_S;
	getNowTime(&current_Time_S);
	
	MapItrLoopDef(dlS32 , S_Timer , _timer_Map , itr)
	{
		itr -> second.progress_Time = (current_Time_S - itr -> second.old_Time_S).value();
		itr -> second.old_Time_S = current_Time_S;
		itr -> second.begingame_After_Progress_Time += static_cast<dlU64>(itr -> second.progress_Time * 1000);
		++ (itr -> second.frame_Count);
	}

	//ファンクション用
	if(_func_Timer_Delete_Flg)
	{
		_func_Timer_Delete_Flg = dlFALSE;
		_func_Stack_List.clear();
		_func_List.clear();
		return;
	}

	/*作成された関数群を追加*/
	ItrLoopDef(std::vector<S_FuncTimer> , _func_Stack_List , itr)
	{
		_func_List.push_back((*itr));
	}
	_func_Stack_List.clear();

	/*実行*/
	std::vector<S_FuncTimer>::iterator itr , end_Itr = _func_List.end();
	for(itr = _func_List.begin() ; itr != end_Itr ; )
	{
		-- (*itr).result_Time;
		if((*itr).result_Time <= 0)
		{
			(*itr).timer_Callback();

			itr = _func_List.erase(itr);
			if(_func_List.size() == 0)
			{
				break;
			}
			end_Itr = _func_List.end();
		}
		else
		{
			++ itr;
		}
	}

	//ファンクション用
	if(_func_Timer_Delete_Flg)
	{
		_func_Timer_Delete_Flg = dlFALSE;
		_func_Stack_List.clear();
		_func_List.clear();
		return;
	}
}

}