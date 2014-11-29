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

//! テキストノード
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
	
	//アニメーション関連(アニメーション中は位置の変更は不可能)
	void	SetSimpleAnimation	(dlF32 to_Next_Time);
	void	SetDivisionAnimation(dlF32 to_Next_Time);
	void	SetScaleAnimation	(dlF32 to_Next_Time , dlF32 animation_Time , TimeCurveType time_Curve);
	void	SetFadeAnimation	(dlF32 to_Next_Time , dlF32 animation_Time);

	void	Render				(void);

private:
	void	_Refresh			(void);
	void	_CheckSize			(void);
	
private:
	S_Vector2	_pos_S;		//< 位置
	TextView*	_view;		//< テキストビュークラス
	dlSTRING	_text;		//< 設定するテキスト
	S_Vector2	_origin_S;	//< 基準位置割合

	ACS_G_MEB(private , S_IntVec2 , _string_Size_S , StringSize);
};

}

#endif
