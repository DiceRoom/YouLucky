/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkTimer.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Node/DL_2DFrameWorkNode.h>

namespace DL
{

//! ���[�J�[�m�[�h(�V�[���̍X�V)
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
//! ������
void C_DL2DFrameWorkTimer::Initialize(void)
{
	C_TimerUpdateNode* node_CP = C_DL2DFrameWork::NODE -> CreateNode<C_TimerUpdateNode>(kSYSTEM_FRONT_LINE , kSYS_NODE_PRI_TIMER , &_update_Node_Handle , dlTRUE);
	node_CP -> SetTimerAddress(this);
	_func_Timer_Delete_Flg = dlFALSE;
}
	
//============================================================================
//! �I������
void C_DL2DFrameWorkTimer::Terminate(void)
{
	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
}

//============================================================================
//! �V�����^�C�}�[��ǉ�����
void C_DL2DFrameWorkTimer::CreateNewTimer(dlS32 timer_Handle)
{
	//�����`�F�b�N
	if(_timer_Map.find(timer_Handle) != _timer_Map.end())
	{
		SystemError(kSYSER_INJ_TMR_COLLIDE_HANDLE);
	}
	
	//�V�K�쐬
	S_Timer new_Timer_S;
	_timer_Map.insert(std::pair<dlS32 , S_Timer>(timer_Handle , new_Timer_S));
	InitializeTimer(timer_Handle);
}

//============================================================================
//! �^�C�}�[�̍폜
void C_DL2DFrameWorkTimer::DeleteTimer(dlS32 timer_Handle)
{
	//�`�F�b�N
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	
	//������Ζ���
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE0);
	}
	
	_timer_Map.erase(find_Itr);
}

//============================================================================
//! �S�Ẵ^�C�}�[���폜
void C_DL2DFrameWorkTimer::DeleteAllTimer(void)
{
	_timer_Map.clear();
}

//============================================================================
//! �^�C�}�[�̏�����
void C_DL2DFrameWorkTimer::InitializeTimer(dlS32 timer_Handle)
{
	//�`�F�b�N
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
//! ���̂P�t���[���ԂɌo�߂������Ԃ��擾
dlF64 C_DL2DFrameWorkTimer::GetFrameTime(dlS32 timer_Handle)
{
	//�`�F�b�N
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE2);
	}

	return find_Itr -> second.progress_Time;
}

//============================================================================
//! �쐬������o�߂������Ԃ����߂�(�~���b�E�E�E�H)
dlU64 C_DL2DFrameWorkTimer::GetProgressTime(dlS32 timer_Handle)
{
	//�`�F�b�N
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE3);
	}

	return find_Itr -> second.begingame_After_Progress_Time;
}

//============================================================================
//! �쐬�����牽�t���[���o�߂�����
dlU64 C_DL2DFrameWorkTimer::GetFrameVal(dlS32 timer_Handle)
{
	//�`�F�b�N
	std::map<dlS32 , S_Timer>::iterator find_Itr = _timer_Map.find(timer_Handle);
	if(find_Itr == _timer_Map.end())
	{
		SystemError(kSYSER_TMR_NF_HANDLE4);
	}

	return find_Itr -> second.frame_Count;
}

//============================================================================
//! ��莞�Ԍo�߂������ɌĂ΂��R�[���o�b�N�֐���ݒ�
void C_DL2DFrameWorkTimer::CreateFuncTimer(dlS32 wait_Time , const TIMER_CALLBACK& timer_Callback)
{
	//�[���ȉ��͐ݒ�s�\
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
//! �S�ẴR�[���o�b�N�^�C�}�[���폜
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
//! ��莞�Ԍo�߂������ɌĂ΂��R�[���o�b�N�֐����̐����擾
size_t C_DL2DFrameWorkTimer::GetFuncTimerVal(void) const
{
	return _func_List.size();
}

//============================================================================
//! ���Ԍv���X�V
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

	//�t�@���N�V�����p
	if(_func_Timer_Delete_Flg)
	{
		_func_Timer_Delete_Flg = dlFALSE;
		_func_Stack_List.clear();
		_func_List.clear();
		return;
	}

	/*�쐬���ꂽ�֐��Q��ǉ�*/
	ItrLoopDef(std::vector<S_FuncTimer> , _func_Stack_List , itr)
	{
		_func_List.push_back((*itr));
	}
	_func_Stack_List.clear();

	/*���s*/
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

	//�t�@���N�V�����p
	if(_func_Timer_Delete_Flg)
	{
		_func_Timer_Delete_Flg = dlFALSE;
		_func_Stack_List.clear();
		_func_List.clear();
		return;
	}
}

}