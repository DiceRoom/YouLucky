/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include "DL_2DFrameWorkText.h"
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include <FrameWork/Render/DL_2DFrameWorkRender.h>
#include "DL_TextNode.h"

namespace DL
{

//============================================================================
//! ������
void C_DL2DFrameWorkText::Initialize(dlU16 window_W_Size , dlU16 window_H_Size)
{
#ifdef WIN32
	FontController::sharedInstance() -> setDirectXDevice(C_DL2DFrameWork::CORE -> GetDirectXDevice() -> GetDevice());
#endif
	FontController::sharedInstance() -> setWindowSize(window_W_Size , window_H_Size);
}

//============================================================================
//! �e�L�X�g�̍쐬
NODE_HANDLE C_DL2DFrameWorkText::CreateText(dlS32 font_Size, dlS32 max_Char_Val, dlS32 max_Line_Val, dlS32 depth, dlBOOL virtual_Flip_Flg, const dlSTRING& font_Path)
{
	C_TextNode* text_CP = C_DL2DFrameWork::RENDER -> _Add<C_TextNode>(depth , virtual_Flip_Flg);
	text_CP -> CreateTextField(S_IntVec2(font_Size * max_Char_Val , font_Size * max_Line_Val) , font_Path);
	text_CP -> SetFontSize(font_Size);
	++ _text_Val;
	return text_CP -> GetHandle();
}

//============================================================================
//! �e�L�X�g�̍폜
dlBOOL C_DL2DFrameWorkText::DeleteText(NODE_HANDLE handle)
{
	if(C_DL2DFrameWork::RENDER -> _Erase(handle))
	{
		-- _text_Val;
		return dlTRUE;
	}
	return dlFALSE;
}

//============================================================================
//! �g�p���Ă��镶���̃t�B�[���h�T�C�Y�̎擾
dlBOOL C_DL2DFrameWorkText::GetStringSize(NODE_HANDLE handle , S_IntVec2& out_Size_S) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	out_Size_S = static_cast<C_TextNode*>(node_CP) -> GetStringSize();

	return dlTRUE; 
}

//============================================================================
//! �g�p���Ă��镶���̃t�B�[���h�T�C�Y�̎擾
dlBOOL C_DL2DFrameWorkText::GetStringSize(NODE_HANDLE handle , S_Vector2& out_Size_S) const
{
	S_IntVec2 size_S;
	if(!GetStringSize(handle , size_S)){return dlFALSE;}

	out_Size_S.x = static_cast<dlF32>(size_S.x);
	out_Size_S.y = static_cast<dlF32>(size_S.y);
	return dlTRUE;
}

//============================================================================
//! �w��e�L�X�g���A�j���[�V���������ǂ���
dlBOOL C_DL2DFrameWorkText::IsAnimation(NODE_HANDLE handle , dlBOOL& animation_Flg) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	animation_Flg = static_cast<C_TextNode*>(node_CP) -> IsAnimation();

	return dlTRUE;
}

//============================================================================
//! �ʒu�̕ύX
dlBOOL C_DL2DFrameWorkText::SetPosition(DL::NODE_HANDLE handle , const S_IntVec2& pos_S) const
{
	return C_DL2DFrameWork::RENDER -> _SetPosition(handle , pos_S);
}

//============================================================================
//! ��ʒu�̕ύX
dlBOOL C_DL2DFrameWorkText::SetOrigin(NODE_HANDLE handle , const S_Vector2& origin_S) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	dlBOOL flip_Flg;
	if(!C_DL2DFrameWork::RENDER -> _IsVirtualFlip(handle , flip_Flg))
	{
		return dlFALSE;
	}

	static_cast<C_TextNode*>(node_CP) -> SetOrigin(flip_Flg ? S_Vector2(origin_S.x , 1.f - origin_S.y) : origin_S);

	return dlTRUE;
}

//============================================================================
//! �F�̕ύX
dlBOOL C_DL2DFrameWorkText::SetColor(DL::NODE_HANDLE handle , const S_Color& color_S) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetColor(color_S);

	return dlTRUE;
}

//============================================================================
//! �t�H���g�T�C�Y�̕ύX
dlBOOL C_DL2DFrameWorkText::SetFontSize(NODE_HANDLE handle , dlS32 font_Size) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetFontSize(font_Size);

	return dlTRUE;
}

//============================================================================
//! �[�x�̕ύX
dlBOOL C_DL2DFrameWorkText::SetDepth(NODE_HANDLE handle , dlS32 depth) const
{
	return C_DL2DFrameWork::RENDER -> _ChangeDepth(handle , depth);
}

//============================================================================
//! �\��/��\���̕ύX
dlBOOL C_DL2DFrameWorkText::SetValidFlg(NODE_HANDLE handle , dlBOOL flg) const
{
	return C_DL2DFrameWork::RENDER -> _SetValidFlg(handle , flg);
}

//============================================================================
//! �e�L�X�g�̕ύX
dlBOOL C_DL2DFrameWorkText::SetText(DL::NODE_HANDLE handle , const dlSTRING& text_Str) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetText(text_Str);

	return dlTRUE;
}

//============================================================================
//! �ꕶ�����Ԃɏo��A�j���[�V�����Ńe�L�X�g�̕ύX
dlBOOL C_DL2DFrameWorkText::SetSimpleAnimationText(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame) const
{
	//���Ԑݒ肪0�ȉ��̏ꍇ
	if(to_Next_Frame <= 0)
	{
		return SetText(handle , text_Str);
	}

	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetText(text_Str);
	static_cast<C_TextNode*>(node_CP) -> SetSimpleAnimation(to_Next_Frame / 60.f);

	return dlTRUE;
}

//============================================================================
//! ������ɂ�[���Əo�Ă���A�j���[�V�����Ńe�L�X�g�̕ύX
dlBOOL C_DL2DFrameWorkText::SetDivisionAnimationText(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame) const
{
	//���Ԑݒ肪0�ȉ��̏ꍇ
	if(to_Next_Frame <= 0)
	{
		return SetText(handle , text_Str);
	}

	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetText(text_Str);
	static_cast<C_TextNode*>(node_CP) -> SetDivisionAnimation(to_Next_Frame / 60.f);

	return dlTRUE;
}

//============================================================================
//! �X�P�[���A�j���[�V�����Ńe�L�X�g�̕ύX
dlBOOL C_DL2DFrameWorkText::SetScaleAnimationText(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame , dlF32 animation_Per , TimeCurveType time_Curve) const
{
	//���Ԑݒ肪0�ȉ��̏ꍇ
	if(to_Next_Frame <= 0)
	{
		return SetText(handle , text_Str);
	}

	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetText(text_Str);
	static_cast<C_TextNode*>(node_CP) -> SetScaleAnimation(to_Next_Frame / 60.f , animation_Per , time_Curve);

	return dlTRUE;
}

//============================================================================
//! �t�F�[�h�A�j���[�V�����Ńe�L�X�g�̕ύX
dlBOOL C_DL2DFrameWorkText::SetFadeAnimationText(NODE_HANDLE handle , const dlSTRING& text_Str , dlF32 to_Next_Frame , dlF32 animation_Per) const
{
	//���Ԑݒ肪0�ȉ��̏ꍇ
	if(to_Next_Frame <= 0)
	{
		return SetText(handle , text_Str);
	}

	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	
	if(node_CP == 0 || node_CP -> GetNodeType() != kTEXT_NODE){return dlFALSE;}

	static_cast<C_TextNode*>(node_CP) -> SetText(text_Str);
	static_cast<C_TextNode*>(node_CP) -> SetFadeAnimation(to_Next_Frame / 60.f , animation_Per);

	return dlTRUE;
}

}