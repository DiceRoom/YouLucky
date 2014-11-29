/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_TextNode.h"

/****************************************************************************/
//////////////////////////// function Declaration ////////////////////////////
/****************************************************************************/
namespace DL
{

//============================================================================
//! 初期化
void C_TextNode::Initialize(void)
{
	_view = 0;
	SetNodeType(kTEXT_NODE);
}

//============================================================================
//! 終了処理
void C_TextNode::Terminate(void)
{
	if(_view != 0){dlDELETE _view;}
}

//============================================================================
//! 位置設定
void C_TextNode::SetPosition(const S_Vector2& pos_S)
{
	_pos_S = pos_S;

	if(!_view -> isPlayingAnimation())
	{
		_view -> setPos(static_cast<dlS32>(pos_S.x - (_string_Size_S.x * _origin_S.x)) , static_cast<dlS32>(pos_S.y - (_string_Size_S.y * _origin_S.y)));
	}
}

//============================================================================
//! テキストフィールドの作成
void C_TextNode::CreateTextField(const S_IntVec2 &size_S , const dlSTRING &font_Name)
{
	_view = dlNEW TextView(0 , 0 , size_S.x , size_S.y);
	_view -> setFont(font_Name.c_str());
}

//============================================================================
//! テキストの設定
void C_TextNode::SetText(const dlSTRING &set_Str)
{
	_text = set_Str;
	_Refresh();
}

//============================================================================
//! 色の設定
void C_TextNode::SetColor(const S_Color &color_S)
{
	_view -> setColor(S_Color::PackNonAlphaARGB(color_S));
	_view -> setAlpha(static_cast<dlF32>(color_S.a) / 255.f);
}

//============================================================================
//! フォントサイズの設定
void C_TextNode::SetFontSize(dlS32 font_Size)
{
	_view -> setFontSize(font_Size);
	_CheckSize();
	SetPosition(_pos_S);
}

//============================================================================
//! 基準位置の変更
void C_TextNode::SetOrigin(const S_Vector2& origin_S)
{
	_origin_S = origin_S;
	SetPosition(_pos_S);
}

//============================================================================
//! レンダリング
void C_TextNode::Render(void)
{
	if(_view != 0)
	{
		_view -> render();
	}
}

//============================================================================
//! アニメーション中か
dlBOOL C_TextNode::IsAnimation(void) const
{
	return _view -> isPlayingAnimation();
}

//============================================================================
//! 一文字順番に出るアニメーション付加
void C_TextNode::SetSimpleAnimation(dlF32 to_Next_Time)
{
	_view -> setAnimationType(kTextAnimationTypeSimple);
	_view -> startAnimation(to_Next_Time);
}

//============================================================================
//! 左からにゅーっと出てくるアニメーション付加
void C_TextNode::SetDivisionAnimation(dlF32 to_Next_Time)
{
	_view -> setAnimationType(kTextAnimationTypeDivision);
	_view -> startAnimation(to_Next_Time);
}

//============================================================================
//! スケールアニメーション付加
void C_TextNode::SetScaleAnimation(dlF32 to_Next_Time , dlF32 animation_Time , TimeCurveType time_Curve)
{
	_view -> setAnimationType(kTextAnimationTypeScale);
	_view -> setScaleAnimationType(time_Curve);

	if(animation_Time != 0)
	{
		_view -> setNextInfection(to_Next_Time / animation_Time);
	}

	//1文字に掛けるアニメーション時間
	_view -> startAnimation(animation_Time);
}

//============================================================================
//! フェードアニメーション付加
void C_TextNode::SetFadeAnimation(dlF32 to_Next_Time , dlF32 animation_Time)
{
	_view -> setAnimationType(kTextAnimationTypeFade);

	if(animation_Time != 0)
	{
		_view -> setNextInfection(to_Next_Time / animation_Time);
	}

	//1文字に掛けるアニメーション時間
	_view -> startAnimation(animation_Time);
}

//============================================================================
//! 情報の再設定
void C_TextNode::_Refresh(void)
{
	//アニメーション中はアニメーションを終了
	if(_view -> isPlayingAnimation())
	{
		_view -> finishAnimation();
	}

	_view -> setText(_text.c_str());
	_CheckSize();
	SetPosition(_pos_S);
}

//============================================================================
//! サイズのチェック
void C_TextNode::_CheckSize(void)
{
	_string_Size_S = S_IntVec2(_view -> stringWidth() , _view -> stringHeight());

	//何故かたまに負の数がくる・・・
	if(_string_Size_S.x < 0 || _string_Size_S.y < 0)
	{
		TextView view(0 , 0 , 1200 , 600);
		view.setText(_text.c_str());
		_string_Size_S = S_IntVec2(view.stringWidth() , view.stringHeight());
	}
}

}