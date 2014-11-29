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

//! 2D�Q�[���p�t���[�����[�N(���m�X�e�[�g�p�^�[��)
class C_DL2DFrameWork
{
public:
	//! ���݂̏�
	enum E_RunState
	{
		kSTATE_INITIALIZE = 0,		//< ������
		kSTATE_SYSTEM_WAIT,			//< �V�X�e���E�F�C�g
		kSTATE_UPDATE_INPUT,		//< ���͏��̍X�V
		kSTATE_UPDATE_NODE,			//< �m�[�h�X�V��(Update)
		kSTATE_REVISION_NODE,		//< �m�[�h�X�V��(Revision)
		kSTATE_FINISH_NODE,			//< �m�[�h�X�V��(Finish)
		kSTATE_RENDER,				//< �`�撆
		kSTATE_TERMINATE,			//< �I������
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

	//���̑�
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
    
	//�S�ăA�N�Z�X�\(���[�U�[�g�p�\�^)
public:
	static class C_DL2DFrameWorkCore*			CORE;			//< �R�A
	static class C_DL2DFrameWorkUtility*		UTILITY;		//< ���[�e�B���e�B
	static class C_DL2DFrameWorkNode*			NODE;			//< �m�[�h
	static class C_DL2DFrameWorkScene*			SCENE;			//< �V�[�����
	static class C_DL2DFrameWorkCollision*		CLS;			//< �����蔻����
#ifdef WIN32
	static class C_DL2DFrameWorkWindow*			WINDOW;			//< �E�B���h�E�֘A
	static class C_DL2DFrameWorkKeyboard*		KEYBOARD;		//< �L�[�{�[�h����
	static class C_DL2DFrameWorkMouse*			MOUSE;			//< �}�E�X����
	static class C_DL2DFrameWorkGamepad*		PAD;			//< �p�b�h����
#endif
	static class C_DL2DFrameWorkSound*			SOUND;			//< �����֘A
	static class C_DL2DFrameWorkTimer*			TIMER;			//< �^�C�}�[�֘A
	static class C_DL2DFrameWorkRender*			RENDER;			//< �`��֘A
	static class C_DL2DFrameWorkImage*			IMAGE;			//< �C���[�W
	static class C_DL2DFrameWorkText*			TEXT;			//< �e�L�X�g
	static class C_DL2DFrameWorkDrawPrimitive*	DRAW_PRIMITIVE;	//< �v���~�e�B�u�`��

private:
	static E_RunState _run_State;
};

typedef C_DL2DFrameWork FW;

}

#endif
