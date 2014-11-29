/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include "DL_2DFrameWorkImage.h"
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include <FrameWork/Render/DL_2DFrameWorkRender.h>

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkImage::Initialize(dlU16 window_W_Size , dlU16 window_H_Size)
{
#ifdef WIN32
	ImageController::sharedInstance() -> setDirectXDevice(C_DL2DFrameWork::CORE -> GetDirectXDevice() -> GetDevice());
#endif
	ImageController::sharedInstance() -> setWindowSize(window_W_Size , window_H_Size);
	ImageController::sharedInstance() -> setFlipped(dlFALSE);
	ImageController::sharedInstance() -> setDepthTest(dlFALSE);
	ImageController::sharedInstance() -> setTimeType(kImageTimeTypeFrame);
}

//============================================================================
//! �I������
void C_DL2DFrameWorkImage::Terminate(void)
{
}

//============================================================================
//! �C���[�W�̍쐬
NODE_HANDLE C_DL2DFrameWorkImage::CreateImage(dlS32 depth , dlBOOL flip_Flg)
{
	C_ImageNode* image_CP = C_DL2DFrameWork::RENDER -> _Add<C_ImageNode>(depth , flip_Flg);
	++ _image_Val;
	return image_CP -> GetHandle();
}

//============================================================================
//! �C���[�W�쐬
DL::NODE_HANDLE C_DL2DFrameWorkImage::CreateImage(dlS32 depth , const ImageController::ImagePointer &image , dlBOOL flip_Flg)
{
	C_ImageNode* image_CP = C_DL2DFrameWork::RENDER -> _Add<C_ImageNode>(depth , flip_Flg);
	++ _image_Val;
	image_CP -> SetDirectImage(image);
	
	//�[��3D�̏ꍇ�͍�������_�Ƃ���
	if(flip_Flg)
	{
		//image_CP -> SetOrigin(S_Vector2(0.f , 1.f));
	}

	return image_CP -> GetHandle();
}

//============================================================================
//! �C���[�W�̍쐬
NODE_HANDLE C_DL2DFrameWorkImage::CreateImage(const dlSTRING& image_Path , dlS32 depth , dlBOOL flip_Flg)
{
	C_ImageNode* image_CP = C_DL2DFrameWork::RENDER -> _Add<C_ImageNode>(depth , flip_Flg);
	if(!image_CP -> LoadImagePath(image_Path))
	{
		SystemError(kSYSER_IMG_LOAD_FAILED , "ImagePath : " + image_Path);
	}

	//�[��3D�̏ꍇ�͍�������_�Ƃ���
	if(flip_Flg)
	{
		image_CP -> SetOrigin(S_Vector2(0.f , 1.f));
	}

	++ _image_Val;
	return image_CP -> GetHandle();
}

//============================================================================
//! �C���[�W�̍ă��[�h
dlBOOL C_DL2DFrameWorkImage::LoadCmpImage(NODE_HANDLE handle , const dlSTRING& cmp_Name , const dlSTRING& image_Name)
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(node_CP == 0 || node_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}

	C_ImageNode* image_CP = static_cast<C_ImageNode*>(node_CP);

	if(!image_CP -> LoadCmpImage(cmp_Name , image_Name))
	{
		SystemError(kSYSER_IMG_LOAD_FAILED , "ImageInfo : " + cmp_Name + "_" + image_Name);
		return dlFALSE;
	}

	dlBOOL flip_Flg;
	C_DL2DFrameWork::RENDER -> _IsVirtualFlip(handle , flip_Flg);
	//�[��3D�̏ꍇ�͍�������_�Ƃ���
	if(flip_Flg)
	{
		image_CP -> SetOrigin(S_Vector2(0.f , -1.f));
	}
	
	C_DL2DFrameWork::RENDER -> _SetPosition(image_CP -> GetHandle() , S_Vector2::ZERO);
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̍폜
dlBOOL C_DL2DFrameWorkImage::DeleteImage(NODE_HANDLE handle)
{
	if(C_DL2DFrameWork::RENDER -> _Erase(handle))
	{
		-- _image_Val;
		return dlTRUE;
	}
	return dlFALSE;
}

//============================================================================
//! �w��Cmp�t�@�C�����̃C���[�W�t�H���_�Ɏw��A�j���[�V���������邩�ǂ���
dlBOOL C_DL2DFrameWorkImage::IsCmpInImageAnimation(const dlSTRING& cmp_File_Path , const dlSTRING& image_Name , const dlSTRING& animation_Name) const
{
	C_ImageNode image_C;
	
	//cmp�t�@�C������image������
	if(!image_C.LoadCmpImage(cmp_File_Path , image_Name))
	{
		return dlFALSE;
	}

	//�A�j���[�V����������
	if(!image_C.ChangeAnimation(animation_Name))
	{
		return dlFALSE;
	}

	return dlTRUE;
}

//============================================================================
//! �A�j���[�V�����̕ύX
dlBOOL C_DL2DFrameWorkImage::ChangeAnimation(NODE_HANDLE handle , const dlSTRING &motion_Name , dlS32 loop_Val , dlS32 start_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}

	return static_cast<C_ImageNode*>(image_CP) -> ChangeAnimation(motion_Name , loop_Val , start_Frame);
}

//============================================================================
//! ���݂̃A�j���[�V�����X�^�b�N�Ƀ��[�V�����̒ǉ�
dlBOOL C_DL2DFrameWorkImage::PushAnimation(NODE_HANDLE handle , const dlSTRING& push_Motion_Name , dlS32 loop_Val)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	ImageController::ImagePointer image;
	static_cast<C_ImageNode*>(image_CP) -> GetImage(image);
	
	if(!image.isValid()){return dlFALSE;}
	
	image -> pushNextImageAnimation(push_Motion_Name.c_str() , loop_Val);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�A�j���[�V�����̒�~
dlBOOL C_DL2DFrameWorkImage::StopImageAnimation(NODE_HANDLE handle) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> StopImageAnimation();

	return dlTRUE;
}

//============================================================================
//! �[�x�̕ύX
dlBOOL C_DL2DFrameWorkImage::SetDepth(NODE_HANDLE handle , dlS32 depth)
{
	return C_DL2DFrameWork::RENDER -> _ChangeDepth(handle , depth);
}

//============================================================================
//! �C���[�W�|�C���^�̍쐬
dlBOOL C_DL2DFrameWorkImage::SetImagePointer(NODE_HANDLE handle , const ImageController::ImagePointer& image) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> CopyImage(image);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̈ʒu�ύX
dlBOOL C_DL2DFrameWorkImage::SetPosition(NODE_HANDLE handle , const S_Vector2 &pos_S) const
{
	//�I�t�Z�b�g�̈ʒu���l��
	DL::S_Vector2 offset_S;
	return C_DL2DFrameWork::RENDER -> _SetPosition(handle , pos_S + offset_S);
}

//============================================================================
//! �C���[�W�̃T�C�Y�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetSize(NODE_HANDLE handle , dlF32 width , dlF32 height) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> SetSize(width , height);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̊g�k�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetScale(NODE_HANDLE handle , dlF32 scale) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> SetScale(scale);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̉�]�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetRotate(NODE_HANDLE handle , dlF32 rotate) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> SetRotate(rotate);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̓��ߐݒ�
dlBOOL C_DL2DFrameWorkImage::SetAlpha(NODE_HANDLE handle , dlF32 alpha) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> SetAlpha(alpha);

	return dlTRUE;
}

//============================================================================
//! ���݂̃A�j���[�V�����̃t���[���ԍ���ݒ�
dlBOOL C_DL2DFrameWorkImage::SetCurrentAnimFrame(NODE_HANDLE handle , dlS32 set_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image)){return dlFALSE;}

	//�w�肷��C���[�W�̃A�j���[�V�����ԍ��𒴂��Ă����牽�����Ȃ�
	const dlPCSTR anim_Name = image -> currentImageAnimationName();
	const dlS32 anim_Val = image -> totalFrameImageAnimation(anim_Name);

	if(anim_Val < set_Frame){return dlFALSE;}

	image -> startImageAnimationAtFrame(anim_Name , image -> imageAnimationRepeatCount() , 1.f , set_Frame);
	
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̔��]�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetFlip(NODE_HANDLE handle , dlBOOL width_Flg , dlBOOL height_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	static_cast<C_ImageNode*>(image_CP) -> SetFlip(width_Flg , height_Flg);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̊�ʒu�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetOrigin(NODE_HANDLE handle , const S_Vector2& origin_S) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}

	//�㉺���]�`�F�b�N
	dlBOOL virtual_Flip_Flg;
	C_DL2DFrameWork::RENDER -> _IsVirtualFlip(handle , virtual_Flip_Flg);
	
	S_Vector2 set_Origin_S = (virtual_Flip_Flg) ? S_Vector2(origin_S.x , 1.f - origin_S.y) : origin_S;

	set_Origin_S *= -1;
	static_cast<C_ImageNode*>(image_CP) -> SetOrigin(set_Origin_S);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̃A�j���[�V�����|�[�Y�ݒ�
dlBOOL C_DL2DFrameWorkImage::SetPause(NODE_HANDLE handle , dlBOOL pause_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}

	static_cast<C_ImageNode*>(image_CP) -> SetPause(pause_Flg);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�T�C�Y�ύX���̃A�X�y�N�g��𖳎����邩
dlBOOL C_DL2DFrameWorkImage::SetScaleIgnoreAspect(NODE_HANDLE handle , dlBOOL ignore_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}

	static_cast<C_ImageNode*>(image_CP) -> SetScaleIgnoreAspect(ignore_Flg);

	return dlTRUE;
}

//============================================================================
//! �C���[�W�̕\��/��\���̐؂�ւ�
dlBOOL C_DL2DFrameWorkImage::SetValidFlg(NODE_HANDLE handle , dlBOOL valid_Flg) const
{
	return C_DL2DFrameWork::RENDER -> _SetValidFlg(handle , valid_Flg);
}

//============================================================================
//! �C���[�W�R���g���[���[���̃C���[�W�̑S�|�[�Y(�C���[�W�A�j���[�V����)�ݒ�
void C_DL2DFrameWorkImage::SetAllPauseAnimation(dlBOOL pause_Flg)
{
	std::vector<NODE_HANDLE> handle_List;
	C_DL2DFrameWork::RENDER -> _GetImageHandleList(handle_List);

	ItrLoopDef(std::vector<NODE_HANDLE> , handle_List , itr)
	{
		C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress((*itr));

		if(image_CP != 0)
		{
			static_cast<C_ImageNode*>(image_CP) -> SetPause(pause_Flg);
		}
	}
}

//============================================================================
//! �C���[�W�|�C���^�̎擾
dlBOOL C_DL2DFrameWorkImage::GetImagePointer(NODE_HANDLE handle , ImageController::ImagePointer& out_Pointer) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetImage(out_Pointer);
}

//============================================================================
//! �ʒu�̎擾
dlBOOL C_DL2DFrameWorkImage::GetPosition(NODE_HANDLE handle , S_Vector2& out_Pos_S)	const
{
	return C_DL2DFrameWork::RENDER -> _GetPosition(handle , out_Pos_S);
}

//============================================================================
//! �C���[�W�I�t�Z�b�g�̎擾
dlBOOL C_DL2DFrameWorkImage::GetImageOffset(NODE_HANDLE handle , S_Vector2& out_Pos_S , dlBOOL flip_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetImageOffset(out_Pos_S , flip_Flg);
}

//============================================================================
//! ���݂̃C���[�W�̃T�C�Y�̎擾
dlBOOL C_DL2DFrameWorkImage::GetSize(NODE_HANDLE handle , S_Vector2& out_Size_S) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetSize(out_Size_S);
}

//============================================================================
//! �g�嗦�̎擾
dlBOOL C_DL2DFrameWorkImage::GetScale(NODE_HANDLE handle , dlF32& out_Scale) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetScale(out_Scale);
}

//============================================================================
//! �C���[�W�T�C�Y�̎擾
dlBOOL C_DL2DFrameWorkImage::GetImageSize(NODE_HANDLE handle , S_Vector2& out_Size_S) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetImageSize(out_Size_S);
}

//============================================================================
//! ��]�l�̎擾
dlBOOL C_DL2DFrameWorkImage::GetRotate(NODE_HANDLE handle , dlF32& out_Rotate) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	out_Rotate = static_cast<C_ImageNode*>(image_CP) -> GetRotate();
	return dlTRUE;
}

//============================================================================
//! �C���[�W�����x�̎擾
dlBOOL C_DL2DFrameWorkImage::GetAlpha(NODE_HANDLE handle , dlF32& out_Alpha) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> GetAlpha(out_Alpha);
}

//============================================================================
//! ���݂̃A�j���[�V�����̃t���[���ԍ����擾
dlBOOL C_DL2DFrameWorkImage::GetCurrentAnimFrame(NODE_HANDLE handle , dlS32& out_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image))
	{
		return dlFALSE;
	}

	out_Frame = image -> imageAnimationNowFrameNo();
	return dlTRUE;
}

//============================================================================
//! ���݂̃A�j���[�V�����̍ŏI�t���[���ԍ����擾
dlBOOL C_DL2DFrameWorkImage::GetCurrentAnimMaxFrame(NODE_HANDLE handle , dlS32& out_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image))
	{
		return dlFALSE;
	}


	out_Frame = image -> totalFrameCurrentImageAnimation();
	return dlTRUE;
}

//============================================================================
//! ���݂̃A�j���[�V�����̃C���[�W�ԍ����擾
dlBOOL C_DL2DFrameWorkImage::GetCurrentAnimImage(NODE_HANDLE handle , dlS32& out_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image))
	{
		return dlFALSE;
	}

	out_Frame = image -> imageAnimationNowImageNo();
	return dlTRUE;
}

//============================================================================
//! ���݂̃A�j���[�V�����̍ŏI�t���[���ԍ����擾
dlBOOL C_DL2DFrameWorkImage::GetCurrentAnimMaxImage(NODE_HANDLE handle , dlS32& out_Frame) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image))
	{
		return dlFALSE;
	}


	out_Frame = image -> totalImageCurrentImageAnimation();
	return dlTRUE;
}

//============================================================================
//! ���݂̃C���[�W�����擾
dlBOOL C_DL2DFrameWorkImage::GetCurrentImageName(NODE_HANDLE handle , dlSTRING& image_Name) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image)){return dlFALSE;}

	image_Name = image -> isPlayingImageAnimationName();
	return dlTRUE;
}

//============================================================================
//! �C���[�W���]���̎擾
dlBOOL C_DL2DFrameWorkImage::IsFlip(NODE_HANDLE handle , dlBOOL& out_Width_Flip_Flg , dlBOOL& out_Height_Flip_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> IsFlip(out_Width_Flip_Flg , out_Height_Flip_Flg);
}

//============================================================================
//! �A�j���[�V��������
dlBOOL C_DL2DFrameWorkImage::IsAnimation(NODE_HANDLE handle , dlBOOL& out_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image)){return dlFALSE;}

	out_Flg = (!image -> isFinishedAnimation());

	return dlTRUE;
}

//============================================================================
//! �C���[�W�A�j���[�V��������
dlBOOL C_DL2DFrameWorkImage::IsImageAnimation(NODE_HANDLE handle , dlBOOL& out_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	ImageController::ImagePointer image;
	if(!static_cast<C_ImageNode*>(image_CP) -> GetImage(image)){return dlFALSE;}

	out_Flg = image -> isPlayingImageAnimation();
	return dlTRUE;
}

//============================================================================
//! �C���[�W���L�����ǂ���
dlBOOL C_DL2DFrameWorkImage::IsValidImage(NODE_HANDLE handle , dlBOOL& out_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	out_Flg = static_cast<C_ImageNode*>(image_CP) -> IsValid();
	return dlTRUE;
}

//============================================================================
//! �\������Ă��邩
dlBOOL C_DL2DFrameWorkImage::IsValidFlg(NODE_HANDLE handle , dlBOOL& out_Flg) const
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	out_Flg = image_CP -> IsValidFlg();
	return dlTRUE;
}

//============================================================================
//! �C���[�W�̓_�Őݒ�
dlBOOL C_DL2DFrameWorkImage::Blink(NODE_HANDLE handle , dlS32 frame , dlS32 loop)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> Blink(frame , loop);
}

//============================================================================
//! �C���[�W�̃t�F�[�h�C���ݒ�
dlBOOL C_DL2DFrameWorkImage::Fade(NODE_HANDLE handle , dlS32 frame , dlF32 init_Alpha , dlF32 end_Alpha)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> Fade(frame , init_Alpha , end_Alpha);
}

//============================================================================
//! �C���[�W�̃u���[�ݒ�
dlBOOL C_DL2DFrameWorkImage::Blur(NODE_HANDLE handle , dlF32 retain , dlS32 division , dlF32 scale , const S_Vector2& vector_S , dlF32 alpha)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> Blur(retain , division , scale , vector_S , alpha);
}

//============================================================================
//! �C���[�W�̃u���[�I��
dlBOOL C_DL2DFrameWorkImage::EndBlur(NODE_HANDLE handle , dlBOOL force_Stop_Flg)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> EndBlur(force_Stop_Flg);
}

//============================================================================
//! �C���[�W�̃t�F�[�h�C���ݒ�
dlBOOL C_DL2DFrameWorkImage::FadeIn(NODE_HANDLE handle , dlS32 frame , dlF32 end_Alpha)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> Fade(frame , 0.f , end_Alpha);
}

//============================================================================
//! �C���[�W�̃t�F�[�h�A�E�g�ݒ�
dlBOOL C_DL2DFrameWorkImage::FadeOut(NODE_HANDLE handle , dlS32 frame , dlF32 end_Alpha)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> Fade(frame , 1.f , end_Alpha);
}

//============================================================================
//! �g�k�A�j���[�V�����ݒ�
dlBOOL C_DL2DFrameWorkImage::ScaleAnimation(NODE_HANDLE handle , dlS32 frame , dlF32 end_Scale , dlF32 init_Scale)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> ScaleAnimation(frame , end_Scale , init_Scale);
}

//============================================================================
//! �g�k�A�j���[�V�����ݒ�
dlBOOL C_DL2DFrameWorkImage::ScaleAnimation(NODE_HANDLE handle , dlS32 frame , dlF32 end_Scale)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> ScaleAnimation(frame , end_Scale);
}

//============================================================================
//! �ړ��A�j���[�V�����ݒ�(2D�A�j���[�V�����̂�)
dlBOOL C_DL2DFrameWorkImage::MoveAnimation(NODE_HANDLE handle , dlS32 frame , const S_Vector2& move_Pos_S , const S_Vector2& begin_Pos_S)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> MoveAnimation(frame , move_Pos_S , begin_Pos_S);
}

//============================================================================
//! �ړ��A�j���[�V�����ݒ�(2D�A�j���[�V�����̂�)
dlBOOL C_DL2DFrameWorkImage::MoveAnimation(NODE_HANDLE handle , dlS32 frame , const S_Vector2& move_Pos_S)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> MoveAnimation(frame , move_Pos_S);
}

//============================================================================
//! ��]�A�j���[�V�����ݒ�
dlBOOL C_DL2DFrameWorkImage::RotateAnimation(NODE_HANDLE handle , dlS32 frame , dlF32 end_Rotate, dlF32 init_Rotate)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> RotateAnimation(frame , end_Rotate , init_Rotate);
}

//============================================================================
//! ��]�A�j���[�V�����ݒ�
dlBOOL C_DL2DFrameWorkImage::RotateAnimation(NODE_HANDLE handle , dlS32 frame , dlF32 end_Rotate)
{
	C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> RotateAnimation(frame , end_Rotate);
}

}