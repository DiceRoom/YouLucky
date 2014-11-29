/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_ImageNode.h"

//���̃t���[�����[�N���g�p����ꍇ��FPS��
const dlS32 FPS = 60;

namespace DL
{

//============================================================================
//! ������
void C_ImageNode::Initialize(void)
{
	SetNodeType(kIMAGE_NODE);
	_offset_Pos_S.x = 100;
	_rotate = 0.f;
}

//============================================================================
//! �I������
void C_ImageNode::Terminate(void)
{
	if(_image.isValid())
	{
		if(_image -> isBlur())
		{
			_image -> endBlur(dlTRUE);
		}
		_image.release();
	}
}

//============================================================================
//! �C���[�W�̃��[�h
dlBOOL C_ImageNode::LoadImagePath(const dlSTRING &image_Path)
{
	_load_Image_Name = image_Path;

	//���łɃ��[�h����Ă���ꍇ�͈�x������s��
	if(_image.isValid()){_image.release();}

	_image = ImageController::sharedInstance() -> createImageFromFile(image_Path.c_str(), kImageRenderType2D);

	return (_image.isValid());
}

//============================================================================
//! �C���[�W�̃��[�h
dlBOOL C_ImageNode::LoadCmpImage(const dlSTRING &cmp_File_Name , const dlSTRING &image_Name)
{
	_load_Image_Name = image_Name;

	//���łɃ��[�h����Ă���ꍇ�͈�x������s��
	dlBOOL width_Flip = dlFALSE;
	dlBOOL height_Flip = dlFALSE;

	if(_image.isValid())
	{
		width_Flip = _image -> isFlippedWidth();
		height_Flip = _image -> isFlippedHeight();
		_image.release();
	}

#ifdef _DEBUG
	dlU32 current_Size = ImageController::sharedInstance() -> textureByte();
#endif

	ImageController::sharedInstance() -> setCompoundFile(cmp_File_Name.c_str());
	_image = ImageController::sharedInstance() -> createImageFromName(image_Name.c_str(), kImageRenderType2D);

#ifdef _DEBUG
	if(current_Size != ImageController::sharedInstance() -> textureByte())
	{
		DLPrintf("�v���t�F�b�`�ς݂Ŗ����C���[�W�����[�h���܂���\nCmpPath [%s]\nImageName [%s]\n\n" , cmp_File_Name.c_str() , image_Name.c_str());
	}
#endif

	if(_image.isValid())
	{
		_image -> setFlipped(width_Flip , height_Flip);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�|�C���^�̒��ڂ̐ݒ�
void C_ImageNode::SetDirectImage(const ImageController::ImagePointer& image)
{
	if(_image.isValid())
	{
		_image.release();
	}

	_image = image;
}

//============================================================================
//! �C���[�W�|�C���^����R�s�[����
void C_ImageNode::CopyImage(const ImageController::ImagePointer& image)
{
	if(_image.isValid())
	{
		_image.release();
	}

	_image = image -> copyImage();
}

//============================================================================
//! �A�j���[�V�����̕ύX
dlBOOL C_ImageNode::ChangeAnimation(const dlSTRING &motion_Name , dlS32 loop_Val , dlS32 start_Frame)
{
	//�A�j���[�V�����L��
	if(!_image.isValid() || motion_Name.length() == 0 || !_image -> containImageAnimation(motion_Name.c_str()))
	{
		return dlFALSE;
	}

	//���[�V�����o�^(���������킹��)
	const dlBOOL check = _image -> isFlippedWidth();
	_image -> setPauseImageAnimation(dlFALSE);
	_image -> clearNextImageAnimation();
	_image -> startImageAnimation(motion_Name.c_str() , loop_Val , 1 , start_Frame);
	_image -> setFlipped(check , false);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�A�j���[�V�����̒�~
dlBOOL C_ImageNode::StopImageAnimation(void)
{
	if(_image.isValid())
	{
		_image -> stopImageAnimation();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �A�j���[�V�����̒�~
dlBOOL C_ImageNode::StopAnimation(void)
{
	if(_image.isValid())
	{
		_image -> stopAnimation();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �ʒu�̐ݒ�
void C_ImageNode::SetPosition(const S_Vector2 &pos_S)
{
	if(_image.isValid())
	{
		_image -> setPos(floor(pos_S.x) , floor(pos_S.y) , _image -> z());
	}
}

//============================================================================
//! �C���[�W�T�C�Y�̐ݒ�
dlBOOL C_ImageNode::SetSize(dlF32 width , dlF32 height)
{
	if(_image.isValid())
	{
		//�����C���[�W�T�C�Y��0�����̏ꍇ�͕ύX���Ȃ�
		if(width < 0)
		{
			width = static_cast<dlF32>(_image -> width());
		}
		if(height < 0)
		{
			height = static_cast<dlF32>(_image -> height());
		}

		_image -> setSize(width , height);
		return dlTRUE;
	}

	return dlFALSE;
}


//============================================================================
//! �X�P�[�����O�l�̐ݒ�
dlBOOL C_ImageNode::SetScale(dlF32 scale)
{
	if(_image.isValid())
	{
		_image -> setScale(scale);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �X�P�[�����O�l�̐ݒ�
dlBOOL C_ImageNode::SetRotate(dlF32 rotate)
{
	if(_image.isValid())
	{
		_rotate = rotate;
		_image -> setRotate(rotate);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �����x�̐ݒ�
dlBOOL C_ImageNode::SetAlpha(dlF32 alpha)
{
	if(_image.isValid())
	{
		_image -> setAlpha(alpha);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �摜�̔��]�ݒ�
dlBOOL C_ImageNode::SetFlip(dlBOOL width_Flg , dlBOOL height_Flg)
{
	if(_image.isValid())
	{
		_image -> setFlipped(width_Flg , height_Flg);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! ��_�̈ʒu�ݒ�
dlBOOL C_ImageNode::SetOrigin(const S_Vector2& origin_S)
{
	_origin_S = origin_S;
	if(_image.isValid())
	{
		_image -> setOriginPos(origin_S.x , origin_S.y);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �A�j���[�V�����|�[�Y�ݒ�
dlBOOL C_ImageNode::SetPause(dlBOOL pause_Flg)
{
	if(_image.isValid())
	{
		_image -> setPauseImageAnimation(pause_Flg);
		_image -> setPauseAnimation(pause_Flg);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�T�C�Y�ύX���ɃX�P�[���𖳎����邩�ǂ���
dlBOOL C_ImageNode::SetScaleIgnoreAspect(dlBOOL ignore_Flg)
{
	if(_image.isValid())
	{
		_image -> setImageScaleIgnoreAspect(ignore_Flg);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�擾
dlBOOL C_ImageNode::GetImage(ImageController::ImagePointer& out_Image) const
{
	if(_image.isValid())
	{
		out_Image = _image;
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�ʒu�擾
dlBOOL C_ImageNode::GetImagePosition(S_Vector2& out_Pos_S) const
{
	if(_image.isValid())
	{
		out_Pos_S.x = _image -> x();
		out_Pos_S.y = _image -> y();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�T�C�Y�̎擾
dlBOOL C_ImageNode::GetSize(S_Vector2& out_Size_S) const
{
	if(_image.isValid())
	{	
		out_Size_S = S_Vector2(_image -> width() , _image -> height());
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �X�P�[���̎擾
dlBOOL C_ImageNode::GetScale(dlF32& out_Scale) const
{
	if(_image.isValid())
	{	
		out_Scale = _image -> scale();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�T�C�Y�̎擾
dlBOOL C_ImageNode::GetImageSize(S_Vector2& out_Size_S)	const
{
	if(_image.isValid())
	{	
		out_Size_S = S_Vector2(_image -> imageWidth() , _image -> imageHeight());
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �����x�̎擾
dlBOOL C_ImageNode::GetAlpha(dlF32& out_Alpha) const
{
	if(_image.isValid())
	{
		out_Alpha = _image -> alpha();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W���]�`�F�b�N(��)
dlBOOL C_ImageNode::IsFlip(dlBOOL& out_Width_Flip_Flg , dlBOOL& out_Height_Flip_Flg) const
{
	if(_image.isValid())
	{
		out_Width_Flip_Flg = _image -> isFlippedWidth();
		out_Height_Flip_Flg = _image -> isFlippedHeight();
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! �C���[�W�����[�h�ς݂��ǂ���
dlBOOL C_ImageNode::IsValid(void) const
{
	return _image.isValid();
}

//============================================================================
//! �C���[�Wcmp�ɐݒ肳��Ă���I�t�Z�b�g�l�̎擾
dlBOOL C_ImageNode::GetImageOffset(S_Vector2& out_Offset_S , dlBOOL flip_Flg) const
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(flip_Flg)
	{
		out_Offset_S = S_Vector2(_image -> offsetLX() , _image -> offsetLY());
	}
	else
	{
		out_Offset_S = S_Vector2(_image -> offsetX() , _image -> offsetY());
	}
	
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̓_�ŕt��
dlBOOL C_ImageNode::Blink(dlS32 frame , dlS32 loop)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}
	
	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	dlF32 set_Time = static_cast<dlF32>(frame) / FPS / 2;

	_image -> setAlpha(1);
	_image -> beginAnimation(kParameterAnimationTypeAlpha , kTimeCurveTypeLinear);
	_image -> setAlpha(0);
	_image -> updateAnimation(set_Time);
	
	const dlS32 val = loop - 1;
	for(dlS32 cnt = 0 ; cnt < val ; ++ cnt)
	{
		_image -> setAlpha(1);
		_image -> updateAnimation(set_Time);
		_image -> setAlpha(0);
		_image -> updateAnimation(set_Time);
	}

	_image -> setAlpha(1);
	_image -> endAnimation(set_Time);
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̃t�F�[�h�t��
dlBOOL C_ImageNode::Fade(dlS32 frame , dlF32 init_Alpha , dlF32 end_Alpha)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}
	
	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> setAlpha(init_Alpha);
	_image -> beginAnimation(kParameterAnimationTypeAlpha , kTimeCurveTypeLinear);
	_image -> setAlpha(end_Alpha);
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);

	return dlTRUE;
}

//============================================================================
//! �u���[���|����
dlBOOL C_ImageNode::Blur(dlF32 retain , dlS32 division , dlF32 scale , const S_Vector2& vector_S , dlF32 alpha)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}
	
	_image -> beginBlur(retain , division);

	if(scale != 1.f)
	{
		_image -> setBlurScale(scale);
	}
	if(vector_S != S_Vector2::ZERO)
	{
		_image -> setBlurVector(vector_S.x , vector_S.y);
	}
	if(alpha != 1.f)
	{
		_image -> setBlurAlpha(alpha);
	}

	return dlTRUE;
}

//============================================================================
//! �u���[�̒�~
dlBOOL C_ImageNode::EndBlur(dlBOOL force_Stop_Flg)
{
	if(!_image.isValid() || !_image -> isBlur())
	{
		return dlFALSE;
	}
	
	_image -> endBlur(force_Stop_Flg);
	return dlTRUE;
}

//============================================================================
//! �ړ��A�j���[�V�����t��
dlBOOL C_ImageNode::MoveAnimation(dlS32 frame , const S_Vector2& move_Pos_S , const S_Vector2& begin_Pos_S)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> setPos(begin_Pos_S.x , begin_Pos_S.y , _image -> z());
	_image -> beginAnimation(kParameterAnimationTypePosition , kTimeCurveTypeLinear);
	_image -> setPos(move_Pos_S.x , move_Pos_S.y , _image -> z());
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);

	return dlTRUE;
}

//============================================================================
//! �ړ��A�j���[�V�����t��
dlBOOL C_ImageNode::MoveAnimation(dlS32 frame , const S_Vector2& move_Pos_S)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> beginAnimation(kParameterAnimationTypePosition , kTimeCurveTypeLinear);
	_image -> setPos(move_Pos_S.x , move_Pos_S.y , _image -> z());
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̊g�k�A�j���[�V�����t��
dlBOOL C_ImageNode::ScaleAnimation(dlS32 frame , dlF32 end_Scale , dlF32 init_Scale)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> setScale(init_Scale);
	_image -> beginAnimation(kParameterAnimationTypeScale , kTimeCurveTypeLinear);
	_image -> setScale(end_Scale);
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);
	
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̊g�k�A�j���[�V�����t��
dlBOOL C_ImageNode::ScaleAnimation(dlS32 frame , dlF32 end_Scale)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> beginAnimation(kParameterAnimationTypeScale , kTimeCurveTypeLinear);
	_image -> setScale(end_Scale);
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);
	
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̉�]�A�j���[�V�����t��
dlBOOL C_ImageNode::RotateAnimation(dlS32 frame , dlF32 end_Rotate , dlF32 init_Rotate)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> setRotate(init_Rotate);
	_image -> beginAnimation(kParameterAnimationTypeRotate , kTimeCurveTypeLinear);
	_image -> setRotate(end_Rotate);
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);
	
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̉�]�A�j���[�V�����t��
dlBOOL C_ImageNode::RotateAnimation(dlS32 frame , dlF32 end_Rotate)
{
	if(!_image.isValid())
	{
		return dlFALSE;
	}

	if(!_image -> isFinishedAnimation()){_image -> stopAnimation();}

	_image -> beginAnimation(kParameterAnimationTypeRotate , kTimeCurveTypeLinear);
	_image -> setRotate(end_Rotate);
	_image -> endAnimation(static_cast<dlF32>(frame) / FPS);
	
	return dlTRUE;
}

//============================================================================
//! �u���[�I�t�Z�b�g
void C_ImageNode::SetBlurOffset(const S_Vector2& offset_S)
{
	if(_image.isValid())
	{
		_image -> setBlurOffsetData(offset_S.x , offset_S.y);
	}
}

//============================================================================
//! �`��
void C_ImageNode::Render(void)
{
	if(_image.isValid())
	{
		_image -> render();
	}
}

}