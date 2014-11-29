/****************************************************************************/
/* DL_TextNode.h	s														*/
/****************************************************************************/
#ifndef DL_TEXTNODE_H_
#define	DL_TEXTNODE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../DL_RenderCoreNode.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! �e�L�X�g�m�[�h
class C_TextNode : public C_RenderCoreNode
{
public:
	void	Initialize			(void);
	void	Terminate			(void);

	void	CreateTextField		(const S_IntVec2 &size_S , const dlSTRING &font_Name);
	void	SetPosition			(const S_Vector2 &pos_S);
	void	SetText				(const dlSTRING& set_Str);
	void	SetColor			(const S_Color &color_S);
	void	SetFontSize			(dlS32 font_Size);
	void	SetOrigin			(const S_Vector2& origin_S);
	dlBOOL	IsAnimation			(void) const;
	
	//�A�j���[�V�����֘A(�A�j���[�V�������͈ʒu�̕ύX�͕s�\)
	void	SetSimpleAnimation	(dlF32 to_Next_Time);
	void	SetDivisionAnimation(dlF32 to_Next_Time);
	void	SetScaleAnimation	(dlF32 to_Next_Time , dlF32 animation_Time , TimeCurveType time_Curve);
	void	SetFadeAnimation	(dlF32 to_Next_Time , dlF32 animation_Time);

	void	Render				(void);

private:
	void	_Refresh			(void);
	void	_CheckSize			(void);
	
private:
	S_Vector2	_pos_S;		//< �ʒu
	TextView*	_view;		//< �e�L�X�g�r���[�N���X
	dlSTRING	_text;		//< �ݒ肷��e�L�X�g
	S_Vector2	_origin_S;	//< ��ʒu����

	ACS_G_MEB(private , S_IntVec2 , _string_Size_S , StringSize);
};

}

#endif
