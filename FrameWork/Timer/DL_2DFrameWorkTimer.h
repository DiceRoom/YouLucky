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

//! �^�C�}�[�p
struct S_Timer
{
	timev old_Time_S;						//< �O��̎��ԕێ��p
	dlF64 progress_Time;					//< �O��̃t���[������o�߂�������
	dlU64 begingame_After_Progress_Time;	//< �t���[�����[�N���N�����Ă���o�߂�������(�~���b)
	dlU64 frame_Count;						//< �t���[���P�ʂŉ���o�߂��Ă��邩
};

//! 2D�Q�[���p�t���[�����[�N(�^�C�}�[)
class C_DL2DFrameWorkTimer
{
friend class C_DL2DFrameWork;
private:
	//! Func�^�C�}�[�p
	struct S_FuncTimer
	{
		dlS32 result_Time;
		TIMER_CALLBACK timer_Callback;
	};

	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
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
	NODE_HANDLE					_update_Node_Handle;	//< �X�V���|����m�[�h�̃n���h��
	std::map<dlS32 , S_Timer>	_timer_Map;				//< �^�C�}�[�̃}�b�v
	std::vector<S_FuncTimer>	_func_List;				//< ��莞�Ԍo�ߌ�ɌĂяo���֐��̃��X�g
	std::vector<S_FuncTimer>	_func_Stack_List;		//< �쐬��������Ɋi�[����郊�X�g
	dlBOOL						_func_Timer_Delete_Flg;	//< �폜�t���O
};

}

#endif
