/****************************************************************************/
/* DL_2DFrameWorkCore.h														*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKCORE_H_
#define	DL_2DFRAMEWORKCORE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

typedef dlCALLBACK<void (void)> RENDER_CALLBACK;

//! 2D�Q�[���p�t���[�����[�N(�V�X�e��)
class C_DL2DFrameWorkCore
{
public:
	void	Initialize	(void);
	void	Terminate	(void);
	dlBOOL	CheckWait	(void);
	void	Render		(void);

	void SetRenderCallback			(const RENDER_CALLBACK& render_Callback);
	void SetRenderDefaultCallback	(void);

private:
	void	_LoadDLL		(void);
	dlBOOL	_LoadLibrary	(const dlSTRING& library_File_Name);
	void	_Render			(void);

private:
	ACS_B_MEB(private , _window_Active_Flg , ActiveFlg);	//< ���݃E�B���h�E���A�N�e�B�u���ǂ���
	ACS_MEB(private , dlS32 , _wait_Frame , SlowTime);		//< ���t���[����1�x������
	dlS32 _wait_Count;										//< �J�E���^�[�p
	RENDER_CALLBACK _render_Callback;						//< �`��p�R�[���o�b�N�A�h���X

#ifdef WIN32
	//! DirectX�̃f�o�C�X
	ACS_G_MEB(private , C_DirectXDevice* , _dx_Device_CP , DirectXDevice);
	std::list<HMODULE>	_load_DLL_List;						//< ���[�h����DLL�̃��X�g
#endif
};

}

#endif
