/****************************************************************************/
/* DL_ImageNode.h															*/
/****************************************************************************/
#ifndef DL_IMAGENODE_H_
#define	DL_IMAGENODE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../DL_RenderCoreNode.h"

/****************************************************************************/
/////////////////////////////////// �^��` ///////////////////////////////////
/****************************************************************************/

namespace DL
{

//! �C���[�W�m�[�h
class C_ImageNode : public C_RenderCoreNode
{
public:
	void Initialize				(void);
	void Terminate				(void);

	dlBOOL	LoadImagePath		(const dlSTRING &image_Path);
	dlBOOL	LoadCmpImage		(const dlSTRING &cmp_File_Name , const dlSTRING &image_Name);
	void	SetDirectImage		(const ImageController::ImagePointer& image);
	void	CopyImage			(const ImageController::ImagePointer& image);
	dlBOOL	ChangeAnimation		(const dlSTRING &motion_Name , dlS32 loop_Val = 0 , dlS32 start_Frame = 0);
	template <typename ITERATOR_TYPE>
	dlBOOL	SetContinueAnimation	(ITERATOR_TYPE begin_Itr , ITERATOR_TYPE end_Itr , dlS32 end_Loop_Val = -1);
	dlBOOL	StopImageAnimation	(void);
	dlBOOL	StopAnimation		(void);

	//�ݒ�n
	void	SetPosition			(const S_Vector2& pos_S);
	dlBOOL	SetSize				(dlF32 width , dlF32 height);
	dlBOOL	SetScale			(dlF32 scale);
	dlBOOL	SetRotate			(dlF32 rotate);
	dlBOOL	SetAlpha			(dlF32 alpha);
	dlBOOL	SetFlip				(dlBOOL width_Flg , dlBOOL height_Flg);
	dlBOOL	SetOrigin			(const S_Vector2& origin_S);
	dlBOOL	SetPause			(dlBOOL pause_Flg);
	dlBOOL	SetScaleIgnoreAspect(dlBOOL ignore_Flg);
	
	//�擾�n
	dlBOOL GetImage			(ImageController::ImagePointer& out_Image) const;
	dlBOOL GetImagePosition	(S_Vector2& out_Pos_S)	const;
	dlBOOL GetSize			(S_Vector2& out_Size_S)	const;
	dlBOOL GetScale			(dlF32& out_Scale)		const;
	dlBOOL GetImageSize		(S_Vector2& out_Size_S)	const;
	dlBOOL GetAlpha			(dlF32& out_Alpha)		const;
	dlBOOL IsFlip			(dlBOOL& out_Width_Flip_Flg , dlBOOL& out_Height_Flip_Flg) const;
	dlBOOL IsValid			(void) const;
	dlBOOL GetImageOffset	(S_Vector2& out_Offset_S , dlBOOL flip_Flg) const;

	dlBOOL Blink			(dlS32 frame , dlS32 loop = 0);
	dlBOOL Fade				(dlS32 frame , dlF32 init_Alpha , dlF32 end_Alpha);
	dlBOOL Blur				(dlF32 retain , dlS32 division , dlF32 scale , const S_Vector2& vector_S , dlF32 alpha);
	dlBOOL EndBlur			(dlBOOL force_Stop_Flg);
	dlBOOL MoveAnimation	(dlS32 frame , const S_Vector2& move_Pos_S , const S_Vector2& begin_Pos_S);
	dlBOOL MoveAnimation	(dlS32 frame , const S_Vector2& move_Pos_S);
	dlBOOL ScaleAnimation	(dlS32 frame , dlF32 end_Scale , dlF32 init_Scale);
	dlBOOL ScaleAnimation	(dlS32 frame , dlF32 end_Scale);
	dlBOOL RotateAnimation	(dlS32 frame , dlF32 init_Rotate , dlF32 end_Rotate);
	dlBOOL RotateAnimation	(dlS32 frame , dlF32 init_Rotate);

	void SetBlurOffset(const S_Vector2& offset_S);
	void Render(void);

private:
	ACS_MEB(private , dlSTRING , _load_Image_Name , ImageName);		//< ���[�h�t�@�C����
	ImageController::ImagePointer _image;							//< �C���[�W�R���g���[���[
	ACS_MEB(private , DL::S_Vector2 , _offset_Pos_S , OffsetPos);	//< �I�t�Z�b�g�ʒu
	ACS_G_MEB(private , DL::S_Vector2 , _origin_S , Origin);		//< ��{�ʒu
	ACS_G_MEB(private , dlF32 , _rotate , Rotate);					//< ��]�֘A�̎擾
};

//============================================================================
//! �A���A�j���[�V�����̐ݒ�
template <typename ITERATOR_TYPE>
dlBOOL C_ImageNode::SetContinueAnimation(ITERATOR_TYPE begin_Itr , ITERATOR_TYPE end_Itr , dlS32 end_Loop_Val)
{
	std::vector<dlSTRING> motion_List;
	while(begin_Itr != end_Itr)
	{
		motion_List.push_back((*begin_Itr));
		++ begin_Itr;
	}

	//���[�V�������Q�ȏ�Ȃ��Ɩ���
	const size_t motion_Val = motion_List.size() - 1;
	if(motion_Val < 0)
	{
		return dlFALSE;
	}
	else if(motion_Val == 0)
	{
		ChangeAnimation(motion_List[0] , end_Loop_Val);
		return dlTRUE;
	}

	//�S���[�V�����`�F�b�N
	ConstItrLoop(std::vector<dlSTRING> , motion_List , itr)
	{
		if(!_image -> containImageAnimation((*itr).c_str()))
		{
			return dlFALSE;
		}
	}

	//�ŏ��̃��[�V�����ݒ�
	ChangeAnimation(motion_List[0] , 0);

	//�q��
	for(size_t cnt = 1 ; cnt < motion_Val ; ++ cnt)
	{
		_image -> pushNextImageAnimation(motion_List[cnt].c_str());
	}

	//���X�g
	_image -> pushNextImageAnimation(motion_List[motion_Val].c_str() , end_Loop_Val);

	return dlTRUE;
}


}

#endif
