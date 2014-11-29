/****************************************************************************/
/* DL_2DFrameWorkSound.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKSOUND_H_
#define	DL_2DFRAMEWORKSOUND_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

///�������
struct S_MusicInfo
{
	///cmp�t�@�C���p�X
	dlSTRING cmp_File_Path;
	///���ʖ�
	dlSTRING music_Name;
};

//!2D�Q�[���p�t���[�����[�N(�����֘A)
class C_DL2DFrameWorkSound
{
friend class C_DL2DFrameWork;
private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
	C_DL2DFrameWorkSound(void){}
	~C_DL2DFrameWorkSound(void){}
	C_DL2DFrameWorkSound(const C_DL2DFrameWorkSound &){}

public:
	void		Initialize			(void);
	void		Update				(void);
	void		Terminate			(void);

	void		LoadSoundFile		(const dlSTRING& file_Path);
	void		PlayBGM				(const dlSTRING& bgm_Name , dlF32 fade_Time);
	void		StopBGM				(dlF32 fade_Time);
	void		PauseBGM			(dlF32 fade_Time , dlBOOL pause_Flg);
	void		ChangeBGMVolume		(dlF32 volume);
	dlBOOL		PlaySE				(const dlSTRING& se_Name, dlF32 volume , dlS32 loop_Val);
	void		SetBGMRepeatPosition(dlF32 repeat_Pos);

	void		SetBGMMasterVolume	(dlF32 master_Vol);

private:
	ACS_G_MEB(private , dlSTRING , _load_Cmp_File_Path , LoadFilePath);	//< ���݃��[�h���̃T�E���h�t�@�C���̃p�X
	ACS_G_MEB(private , dlF32 , _bgm_Master_Volume , BGMMasterVolume);	//< BGM�}�X�^�[�{�����[��
	ACS_MEB(private , dlF32 , _se_Master_Volume , SEMasterVolume);		//< SE�}�X�^�[�{�����[��
};

}

#endif
