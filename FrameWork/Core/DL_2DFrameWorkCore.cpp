/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkCore.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Render/DL_2DFrameWorkRender.h>
#ifdef WIN32
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>
#endif

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkCore::Initialize(void)
{
#ifdef WIN32
	_dx_Device_CP = dlNEW C_DirectXDevice();
	_dx_Device_CP -> CreateDevice(C_DL2DFrameWork::WINDOW -> GetWindowHandle());
	_dx_Device_CP -> SetDeviceLostCallback(dlCALLBACK<void (void)>(C_DL2DFrameWork::DeviceLostCallback));
#endif
	_wait_Frame = 0;
	_wait_Count = 0;
	_window_Active_Flg = dlTRUE;

#ifdef WIN32
	SetRenderDefaultCallback();
	_LoadDLL();
#endif
}

//============================================================================
//! �I������
void C_DL2DFrameWorkCore::Terminate(void)
{
#ifdef WIN32
	dlDELETE _dx_Device_CP;

	//���[�h�������W���[�������
	ItrLoop(std::list<HMODULE> , _load_DLL_List , itr)
	{
		FreeLibrary((*itr));
	}
#endif
}

//============================================================================
//! �҂�
dlBOOL C_DL2DFrameWorkCore::CheckWait(void)
{
	if(_wait_Frame == 0){return dlFALSE;}

	++ _wait_Count;

	if(_wait_Count >= _wait_Frame)
	{
		_wait_Count = 0;
		return dlFALSE;
	}

	return dlTRUE;
}


//============================================================================
//! �`�揈��
void C_DL2DFrameWorkCore::Render(void)
{
	_render_Callback();
}

//============================================================================
//! �`��R�[���o�b�N
void C_DL2DFrameWorkCore::SetRenderCallback(const RENDER_CALLBACK& render_Callback)
{
	_render_Callback = render_Callback;
}

//============================================================================
//! �`��R�[���o�b�N��W���ɖ߂�(����)
void C_DL2DFrameWorkCore::SetRenderDefaultCallback(void)
{
	_render_Callback = RENDER_CALLBACK(this , &C_DL2DFrameWorkCore::_Render);
}

//============================================================================
//! ������
void C_DL2DFrameWorkCore::_LoadDLL(void)
{
#ifdef WIN32
	//�ʒu�ύX
	TCHAR oldPath[4096];
	GetCurrentDirectory(4096, oldPath);
	SetCurrentDirectory("DLL");

	//�e��R���g���[���[�̃��[�h
	if(!_LoadLibrary("libFontRender.dll"))		{SystemError(kSYSER_NF_LIBFONT);}
	if(!_LoadLibrary("libImageRender.dll"))		{SystemError(kSYSER_NF_LIBIMAGE);}
	if(!_LoadLibrary("libAudioController.dll"))	{SystemError(kSYSER_NF_LIBAUDIO);}
	if(!_LoadLibrary("libNPlayer.dll"))			{SystemError(kSYSER_NF_LIBNOVEL);}
	if(!_LoadLibrary("libRenderCore.dll"))		{SystemError(kSYSER_NF_LIBRENDERCORE);}
	if(!_LoadLibrary("libMovieRender.dll"))		{SystemError(kSYSER_NF_LIBMOVIE);}
	if(!_LoadLibrary("libDataArchive.dll"))		{SystemError(kSYSER_NF_LIBDATAARCHIVE);}

	SetCurrentDirectory(oldPath);
#endif
}

//============================================================================
//! ���C�u�����̃��[�h
dlBOOL C_DL2DFrameWorkCore::_LoadLibrary(const dlSTRING& library_File_Name)
{
#ifdef WIN32
	HMODULE module = ::LoadLibrary(library_File_Name.c_str());
	const dlBOOL success_Flg = (module != 0);
	
	if(success_Flg)
	{
		_load_DLL_List.push_back(module);
	}

	return success_Flg;
#else
    return true;
#endif
}

//============================================================================
//! �f�t�H���g�̕`�揈��
void C_DL2DFrameWorkCore::_Render(void)
{
#ifdef WIN32
	_dx_Device_CP -> PrepareRender();
	ImageController::sharedInstance() -> nextFrame();
	NPlayerController::sharedInstance() -> render();
	C_DL2DFrameWork::RENDER -> Render();
	_dx_Device_CP -> FinishRender();
#endif
}

}