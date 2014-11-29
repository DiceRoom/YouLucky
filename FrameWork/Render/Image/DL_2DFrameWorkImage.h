/****************************************************************************/
/* DL_2DFrameWorkImage.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKIMAGE_H_
#define	DL_2DFRAMEWORKIMAGE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "DL_ImageNode.h"
#ifndef WIN32
#include <FrameWork/Render/DL_2DFrameWorkRender.h>
#endif

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

//!2Dゲーム用フレームワーク(描画関連)
class C_DL2DFrameWorkImage
{
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkImage	(void):_image_Val(0){};
	~C_DL2DFrameWorkImage	(void){};
	C_DL2DFrameWorkImage	(const C_DL2DFrameWorkImage&){};

public:
	void Initialize				(dlU16 window_W_Size , dlU16 window_H_Size);
	void Terminate				(void);

	NODE_HANDLE CreateImage				(dlS32 depth , dlBOOL filp_Flg);
	NODE_HANDLE CreateImage				(dlS32 depth , const ImageController::ImagePointer &image , dlBOOL flip_Flg);
	NODE_HANDLE CreateImage				(const dlSTRING& image_Path , dlS32 depth , dlBOOL filp_Flg);
	dlBOOL		LoadCmpImage			(NODE_HANDLE handle , const dlSTRING& cmp_Name , const dlSTRING& image_Name);
	dlBOOL		DeleteImage				(NODE_HANDLE handle);
	dlBOOL		IsCmpInImageAnimation	(const dlSTRING& cmp_File_Path , const dlSTRING& image_Name , const dlSTRING& animation_Name) const;
	
	
	//イメージ操作(設定系)
	dlBOOL		ChangeAnimation		(NODE_HANDLE handle , const dlSTRING& motion_Name , dlS32 loop_Val = 0 , dlS32 start_Frame = 0) const;
	template <typename ITERATOR_TYPE>
	dlBOOL		ChangeAnimation		(NODE_HANDLE handle , ITERATOR_TYPE begin_Itr , ITERATOR_TYPE end_Itr , dlS32 end_Loop_Val = 0) const;
	dlBOOL		PushAnimation		(NODE_HANDLE handle , const dlSTRING& push_Motion_Name , dlS32 loop_Val = 0);
	dlBOOL		StopImageAnimation	(NODE_HANDLE handle) const;
	dlBOOL		SetDepth			(NODE_HANDLE handle , dlS32 depth);
	dlBOOL		SetImagePointer		(NODE_HANDLE handle , const ImageController::ImagePointer& image) const;
	dlBOOL		SetPosition			(NODE_HANDLE handle , const S_Vector2& pos_S) const;
	dlBOOL		SetSize				(NODE_HANDLE handle , dlF32 width , dlF32 height) const;
	dlBOOL		SetScale			(NODE_HANDLE handle , dlF32 scale) const;
	dlBOOL		SetRotate			(NODE_HANDLE handle , dlF32 rotate) const;
	dlBOOL		SetAlpha			(NODE_HANDLE handle , dlF32 alpha) const;
	dlBOOL		SetCurrentAnimFrame	(NODE_HANDLE handle , dlS32 set_Frame) const;
	dlBOOL		SetFlip				(NODE_HANDLE handle , dlBOOL width_Flg , dlBOOL height_Flg) const;
	dlBOOL		SetOrigin			(NODE_HANDLE handle , const S_Vector2& origin_S) const;
	dlBOOL		SetPause			(NODE_HANDLE handle , dlBOOL pause_Flg) const;
	dlBOOL		SetScaleIgnoreAspect(NODE_HANDLE handle , dlBOOL ignore_Flg) const;
	dlBOOL		SetValidFlg			(NODE_HANDLE handle , dlBOOL valid_Flg) const;

	void		SetAllPauseAnimation(dlBOOL pause_Flg);

	//イメージ操作(取得系)
	dlBOOL		GetImagePointer			(NODE_HANDLE handle , ImageController::ImagePointer& out_Pointer)	const;
	dlBOOL		GetPosition				(NODE_HANDLE handle , S_Vector2& out_Pos_S)		const;
	dlBOOL		GetImageOffset			(NODE_HANDLE handle , S_Vector2& out_Pos_S , dlBOOL flip_Flg)		const;
	dlBOOL		GetSize					(NODE_HANDLE handle , S_Vector2& out_Size_S)	const;
	dlBOOL		GetScale				(NODE_HANDLE handle , dlF32& out_Scale)			const;
	dlBOOL		GetImageSize			(NODE_HANDLE handle , S_Vector2& out_Size_S)	const;
	dlBOOL		GetRotate				(NODE_HANDLE handle , dlF32& out_Rotate)		const;
	dlBOOL		GetAlpha				(NODE_HANDLE handle , dlF32& out_Alpha)			const;
	dlBOOL		GetCurrentAnimFrame		(NODE_HANDLE handle , dlS32& out_Frame)			const;
	dlBOOL		GetCurrentAnimMaxFrame	(NODE_HANDLE handle , dlS32& out_Frame)			const;
	dlBOOL		GetCurrentAnimImage		(NODE_HANDLE handle , dlS32& out_Frame)			const;
	dlBOOL		GetCurrentAnimMaxImage	(NODE_HANDLE handle , dlS32& out_Frame)			const;
	dlBOOL		GetCurrentImageName		(NODE_HANDLE handle , dlSTRING& image_Name)		const;
	dlBOOL		IsFlip					(NODE_HANDLE handle , dlBOOL& out_Width_Flip_Flg , dlBOOL& out_Height_Flip_Flg) const;
	dlBOOL		IsAnimation				(NODE_HANDLE handle , dlBOOL& out_Flg)			const;
	dlBOOL		IsImageAnimation		(NODE_HANDLE handle , dlBOOL& out_Flg)			const;
	dlBOOL		IsValidImage			(NODE_HANDLE handle , dlBOOL& out_Flg)			const;
	dlBOOL		IsValidFlg				(NODE_HANDLE handle , dlBOOL& out_Flg)			const;

	//イメージ効果プリセット
	dlBOOL Blink			(NODE_HANDLE handle , dlS32 frame , dlS32 loop = 0);
	dlBOOL Fade				(NODE_HANDLE handle , dlS32 frame , dlF32 init_Alpha , dlF32 end_Alpha);
	dlBOOL Blur				(NODE_HANDLE handle , dlF32 retain , dlS32 division , dlF32 scale = 1.f , const S_Vector2& vector_S = DL::S_Vector2::ZERO , dlF32 alpha = 1.f);
	dlBOOL EndBlur			(NODE_HANDLE handle , dlBOOL force_Stop_Flg = dlFALSE);
	dlBOOL FadeIn			(NODE_HANDLE handle , dlS32 frame , dlF32 end_Alpha = 1.f);
	dlBOOL FadeOut			(NODE_HANDLE handle , dlS32 frame , dlF32 end_Alpha = 0.f);
	dlBOOL ScaleAnimation	(NODE_HANDLE handle , dlS32 frame , dlF32 end_Scale);
	dlBOOL ScaleAnimation	(NODE_HANDLE handle , dlS32 frame , dlF32 end_Scale , dlF32 init_Scale);
	dlBOOL MoveAnimation	(NODE_HANDLE handle , dlS32 frame , const S_Vector2& move_Pos_S , const S_Vector2& begin_Pos_S);
	dlBOOL MoveAnimation	(NODE_HANDLE handle , dlS32 frame , const S_Vector2& move_Pos_S);
	dlBOOL RotateAnimation	(NODE_HANDLE handle , dlS32 frame , dlF32 end_Rotate , dlF32 init_Rotate);
	dlBOOL RotateAnimation	(NODE_HANDLE handle , dlS32 frame , dlF32 end_Rotate);

private:
	ACS_G_MEB(private , dlU32 , _image_Val , ImageVal);			//< イメージ数
};

//============================================================================
//! 連続アニメーションの変更
template <typename ITERATOR_TYPE>
dlBOOL C_DL2DFrameWorkImage::ChangeAnimation(NODE_HANDLE handle , ITERATOR_TYPE begin_Itr , ITERATOR_TYPE end_Itr , dlS32 end_Loop_Val) const
{

    C_RenderCoreNode* image_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);

	if(image_CP == 0 || image_CP -> GetNodeType() != kIMAGE_NODE){return dlFALSE;}
	
	return static_cast<C_ImageNode*>(image_CP) -> SetContinueAnimation(begin_Itr , end_Itr , end_Loop_Val);
}


}

#endif
