/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkSound.h"
#include <DL_2DFrameWork.h>
#ifdef WIN32
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>
#endif

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkSound::Initialize(void)
{
#ifdef _WIN32
	AudioController::sharedInstance() -> setWindowHandler(C_DL2DFrameWork::WINDOW -> GetWindowHandle());
	AudioController::sharedInstance() -> setSoundPlayer(kAudioPlayerTypeOpenAL);
	AudioController::sharedInstance() -> setBackgroundMusicPlayer(kAudioPlayerTypeDirectSound);
#else
	AudioController::sharedInstance() -> setSoundPlayer(kAudioPlayerTypeOpenAL);
	AudioController::sharedInstance() -> setBackgroundMusicPlayer(kAudioPlayerTypeOpenAL);
#endif

	_bgm_Master_Volume = 1.f;
	_se_Master_Volume = 1.f;
}

//============================================================================
//! �X�V����
void C_DL2DFrameWorkSound::Update(void)
{

}

//============================================================================
//! �I������
void C_DL2DFrameWorkSound::Terminate(void)
{
	AudioController::sharedInstance() -> release();
}

//============================================================================
//! �t�@�C���̃��[�h
void C_DL2DFrameWorkSound::LoadSoundFile(const dlSTRING& file_Path)
{
	_load_Cmp_File_Path = file_Path;
	AudioController::sharedInstance() -> setCompoundFile(file_Path.c_str());
}

//============================================================================
//! BGM�̍Đ�
void C_DL2DFrameWorkSound::PlayBGM(const dlSTRING& bgm_Name , dlF32 fade_Time)
{
	AudioController::sharedInstance() -> backgroundMusicOpenFromName(bgm_Name .c_str());
	AudioController::sharedInstance() -> backgroundMusicSetVolume(_bgm_Master_Volume);
	AudioController::sharedInstance() -> backgroundMusicPlay(fade_Time);
}

//============================================================================
//! BGM�̒�~
void C_DL2DFrameWorkSound::StopBGM(dlF32 fade_Time)
{
	if(AudioController::sharedInstance() -> backgroundMusic().isValid())
	{
		AudioController::sharedInstance() -> backgroundMusicStop(fade_Time);
	}
}

//============================================================================
//! BGM�̈ꎞ��~
void C_DL2DFrameWorkSound::PauseBGM(dlF32 fade_Time , dlBOOL pause_Flg)
{
	AudioController::AudioPointer audio = AudioController::sharedInstance() -> backgroundMusic();
	if(audio.isValid())
	{
		audio -> setPause(pause_Flg , fade_Time);
	}
}

//============================================================================
//! SE�̍Đ�
dlBOOL C_DL2DFrameWorkSound::PlaySE(const dlSTRING& se_Name , dlF32 volume , dlS32 loop_Val)
{
	AudioController::SoundPointer sound = AudioController::sharedInstance() -> soundOpenFromName(se_Name.c_str());
	if(sound.isValid())
	{
		sound -> play();
		sound -> setVolume(_se_Master_Volume * volume);

		if(loop_Val > 0)
		{
			sound -> setRepeatCount(loop_Val);
		}

		return dlTRUE;
	}
	return dlFALSE;
}

//============================================================================
//! ���s�[�g�ʒu�ݒ�
void C_DL2DFrameWorkSound::SetBGMRepeatPosition(dlF32 repeat_Pos)
{
	AudioController::AudioPointer audio = AudioController::sharedInstance() -> backgroundMusic();
	if(audio.isValid())
	{
		audio -> setRepeatPos(repeat_Pos);
	}
}

//============================================================================
//! BGM�̃}�X�^�[�{�����[���̐ݒ�
void C_DL2DFrameWorkSound::SetBGMMasterVolume(dlF32 master_Vol)
{
	_bgm_Master_Volume = master_Vol;
	AudioController::sharedInstance() -> backgroundMusicSetVolume(_bgm_Master_Volume);
}

}