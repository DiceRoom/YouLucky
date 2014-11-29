/****************************************************************************/
/* DL_2DFrameWorkText.h														*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKTEXT_H_
#define	DL_2DFRAMEWORKTEXT_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

class C_TextNode;

//!2D�Q�[���p�t���[�����[�N(�`��֘A)
class C_DL2DFrameWorkText
{
friend class C_DL2DFrameWork;
private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
	C_DL2DFrameWorkText	(void):_text_Val(0){}
	~C_DL2DFrameWorkText(void){}
	C_DL2DFrameWorkText	(const C_DL2DFrameWorkText &){}

public:
	void Initialize(dlU16 window_W_Size , dlU16 window_H_Size);
	void Terminate(void){};

	NODE_HANDLE CreateText(dlS32 font_Size , dlS32 max_Char_Val , dlS32 max_Line_Val , dlS32 depth , dlBOOL virtual_Flip_Flg , const dlSTRING& font_Path);
	dlBOOL		DeleteText(NODE_HANDLE handle);

	//�擾/�ݒ�n
	dlBOOL	GetStringSize	(NODE_HANDLE handle , S_IntVec2& out_Size_S)		const;
	dlBOOL	GetStringSize	(NODE_HANDLE handle , S_Vector2& out_Size_S)		const;
	dlBOOL	IsAnimation		(NODE_HANDLE handle , dlBOOL& animation_Flg)		const;
	dlBOOL	SetPosition		(NODE_HANDLE handle , const S_IntVec2& pos_S)		const;
	dlBOOL	SetOrigin		(NODE_HANDLE handle , const S_Vector2& origin_S)	const;
	dlBOOL	SetColor		(NODE_HANDLE handle , const S_Color& color_S)		const;
	dlBOOL	SetFontSize		(NODE_HANDLE handle , dlS32 font_Size)				const;
	dlBOOL	SetDepth		(NODE_HANDLE handle , dlS32 depth)					const;
	dlBOOL	SetValidFlg		(NODE_HANDLE handle , dlBOOL flg)					const;

	//�e�L�X�g�ݒ�n
	dlBOOL	SetText						(NODE_HANDLE handle , const dlSTRING& text_Str)	const;
	dlBOOL	SetSimpleAnimationText		(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame)		const;
	dlBOOL	SetDivisionAnimationText	(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame)		const;
	dlBOOL	SetScaleAnimationText		(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame , dlF32 animation_Per , TimeCurveType time_Curve) const;
	dlBOOL	SetFadeAnimationText		(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame , dlF32 animation_Per) const;

	
private:
	ACS_G_MEB(private , dlU32 , _text_Val , TextVal);
};

}

#endif
