/****************************************************************************/
/* DL_2DFrameWorkSystemErrorInc.h											*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKSYSTEMERRORINC_H_
#define	DL_2DFRAMEWORKSYSTEMERRORINC_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/

/****************************************************************************/
/////////////////////////////////// �^��` ///////////////////////////////////
/****************************************************************************/

namespace DL
{

/****************************************************************************/
/* �^																		*/
/****************************************************************************/

//! �V�X�e���G���[�ԍ�
enum E_SystemError
{
	//FrameWork
	kSYSER_INJ_C_DL2DFrameWork_INIT = 0,		//< �t���[�����[�N�̏��������s���Ă��Ȃ�

	//Utility
	kSYSER_NF_LIBFONT,			//< libFontRender������
	kSYSER_NF_LIBIMAGE,			//< libImageRender������
	kSYSER_NF_LIBAUDIO,			//< libAudioController������
	kSYSER_NF_LIBNOVEL,			//< libNovelPlayer������
	kSYSER_NF_LIBRENDERCORE,	//< libRenderCore������
	kSYSER_NF_LIBMOVIE,			//< libMovieRender������
	kSYSER_NF_LIBDATAARCHIVE,	//< libDataArchive������
	kSYSER_INJ_RANDOM_ARG,		//< �����_���擾���̈��������̐�
	
	//Input
	kSYSER_INJ_IC_INIT,				//< INPUT�����̏��������s���ɌĂяo���ꂽ
	kSYSER_INJ_IC_ALREADY_SETTING,	//< INPUT���������ɓr���Ȃ̂ɊJ�n���߂���΂ꂽ
	kSYSER_INJ_IC_ARG_OVERFLOW,		//< �ݒ���J�n���悤�Ƃ���INPUT�����̔ԍ����ő�l�𒴂��Ă���
	kSYSER_INJ_IC_RE_REF,			//< INPUT�����̐ݒ肪�I����Ēǉ����������̃`�F�b�N���ɈႤ��������ēx�Q�Ƃ��ꂽ
	kSYSER_INJ_IC_ADD_NONE,			//< INPUT�����̐ݒ肪�I����Ēǉ����������̃`�F�b�N���Ɉ�����������o����Ȃ������ꍇ
	kSYSER_IC_NOT_BEGIN_SETTING,	//< INPUT�����ݒ肪�J�n����Ă��Ȃ���ԂŁA�����̒ǉ����s�����Ƃ���
	kSYSER_IC_STILL_BEGIN_CHECKED,	//< INPUT�����ݒ肪�J�n����Ă����ԂŁA�����̃`�F�b�N�����悤�Ƃ���
	kSYSER_INJ_IC_CHECK_OVERFLOW,	//< �ݒ�ς݂�INPUT�����̃`�F�b�N�����悤�Ƃ������̔ԍ����ő�l�𒴂��Ă���
	kSYSER_INJ_IC_GET_CONDITION,	//< �擾���悤�Ƃ���INPUT������KEY,POV,STICK�̂�����ł��Ȃ�
	kSYSER_INJ_IC_CREATE_CONDITION,	//< �쐬���悤�Ƃ���INPUT������KEY,POV,STICK�̂�����ł��Ȃ�
	kSYSER_SAME_CALLBACK_PRIORITY,	//< ����ԍ��̗D�揇�ʂ̃R�[���o�b�N���w�肳�ꂽ

	//Timer
	kSYSER_INJ_TMR_COLLIDE_HANDLE,	//< �^�C�}�[�쐬���ɍ�낤�Ƃ����n���h�������ɑ��݂���
	kSYSER_TMR_NF_HANDLE0,			//< �^�C�}�[�폜���A�w��n���h�������݂��Ȃ�
	kSYSER_TMR_NF_HANDLE1,			//< �^�C�}�[���������A�w��n���h�������݂��Ȃ�
	kSYSER_TMR_NF_HANDLE2,			//< �w��^�C�}�[�̑O��t���[������̌o�ߎ��Ԃ��擾���A�w��n���h�������݂��Ȃ�
	kSYSER_TMR_NF_HANDLE3,			//< �^�C�}�[�o�ߎ��Ԏ擾���A�w��n���h�������݂��Ȃ�
	kSYSER_TMR_NF_HANDLE4,			//< �^�C�}�[�t���[�����擾���A�w��n���h�������݂��Ȃ�
	kSYSER_INJ_UNDER_ZERO,			//< �֐��^�C�}�[�쐬���ɂO�ȉ����ݒ肳�ꂽ

	//Render
	kSYSER_RND_MEMORYLEAK,			//< �Q�[���I�����폜����Ă��Ȃ��m�[�h�����݂���

	//Image
	kSYSER_IMG_LOAD_FAILED,			//< �C���[�W�̃��[�h�Ɏ��s

	//Button
	kSYSER_BT_ALREADY_LOAD_IMAGE,	//< �{�^���Ɋ��ɃC���[�W�����[�h����Ă����Ԃōă��[�h
	kSYSER_BT_NF_BT_HANDLE0,		//< �{�^���C���[�W�쐬���A����n���h�������݂��Ȃ�

	//Node
	kSYSER_NODE_MEMORYLEAK,			//< �Q�[���I�����폜����Ă��Ȃ��m�[�h�����݂���

	//Core
	kSYSER_CORE_SQUIRRER_INIT,		//< Squirrel�̋N���Ɏ��s
	kSYSER_CORE_SQUIRRER,			//< �N������Squirrel�X�N���v�g�ɃG���[������

	//Collision
	kSYSER_CLS_MEMORYLEAK,			//< �Q�[���I�����폜����Ă��Ȃ������蔻��I�u�W�F�N�g�����݂���

	kSYSER_VAL						//< �V�X�e���G���[��
};

//! �V�X�e���G���[���
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