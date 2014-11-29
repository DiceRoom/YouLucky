/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include "DL_2DFrameWorkDrawPrimitive.h"
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include <FrameWork/Render/DL_2DFrameWorkRender.h>
#include "DL_PrimitiveCircleNode.h"
#include "DL_PrimitiveLineNode.h"
#include "DL_PrimitiveBoxNode.h"
#include "DL_PrimitivePolygonNode.h"
#include "DL_PrimitiveRayNode.h"

namespace DL
{

//============================================================================
//! 初期化
void C_DL2DFrameWorkDrawPrimitive::Initialize(void)
{
#ifdef WIN32
	C_PrimitiveCoreNode::SetDevice(C_DL2DFrameWork::CORE -> GetDirectXDevice());
#endif
}

//============================================================================
//! プリミティブ描画を作る上で共通処理をテンプレート処理化
template<class PRIMITIVE_CLASS_NAME>
PRIMITIVE_CLASS_NAME* C_DL2DFrameWorkDrawPrimitive::GetPrimitive(const S_Vector2& pos_S , const S_Color& color_S , dlS32 depth , dlBOOL virtual_Flip_Flg)
{
	PRIMITIVE_CLASS_NAME* primitive_CP = C_DL2DFrameWork::RENDER -> _Add<PRIMITIVE_CLASS_NAME>(depth , virtual_Flip_Flg);
	C_DL2DFrameWork::RENDER -> _SetPosition(primitive_CP -> GetHandle() , pos_S);
	primitive_CP -> SetColor(color_S);
	return primitive_CP;
}

//============================================================================
//! 円描画の登録
NODE_HANDLE C_DL2DFrameWorkDrawPrimitive::CreateCircle(const S_Vector2&	pos_S,
													   dlF32			radius,
													   const S_Color&	color_S,
													   dlS32			depth,
													   dlBOOL			virtual_Flip_Flg)
{
	C_PrimitiveCircleNode* circle_CP = GetPrimitive<C_PrimitiveCircleNode>(pos_S , color_S , depth , virtual_Flip_Flg);
	circle_CP -> SetFlipFlg(virtual_Flip_Flg);
	circle_CP -> SetCircleInfo(S_Circle(radius));

	++ _primitive_Val;
	return circle_CP -> GetHandle();
}

//============================================================================
//! 線描画の登録
NODE_HANDLE C_DL2DFrameWorkDrawPrimitive::CreateLine(const S_Vector2&	pos_S,
													 const S_Vector2&	line_S,
													 const S_Color&		color_S,
													 dlS32				depth,
													 dlBOOL				virtual_Flip_Flg)
{
	C_PrimitiveLineNode* line_CP = GetPrimitive<C_PrimitiveLineNode>(pos_S , color_S , depth , virtual_Flip_Flg);
	line_CP -> SetFlipFlg(virtual_Flip_Flg);

	S_2DLine set_Line_S;
	set_Line_S.vec_S = (virtual_Flip_Flg) ? S_Vector2(line_S.x , -line_S.y) : line_S;
	line_CP -> SetLineInfo(set_Line_S);

	++ _primitive_Val;
	return line_CP -> GetHandle();
}

//============================================================================
//! 箱描画の登録
NODE_HANDLE C_DL2DFrameWorkDrawPrimitive::CreateBox(const S_Vector2&	pos_S,
													const S_Vector2&	size_S,
													const S_Color&		color_S,
													const S_Vector2&	origin_S,
													const S_Vector2&	rotate_Origin_S,
													dlF32				degree,
													dlS32				depth,
													dlBOOL				virtual_Flip_Flg)
{
	C_PrimitiveBoxNode* box_CP = GetPrimitive<C_PrimitiveBoxNode>(pos_S , color_S , depth , virtual_Flip_Flg);
	box_CP -> SetPrimitiveType(kPRIMITIVE_BOX);
	box_CP -> SetFlipFlg(virtual_Flip_Flg);

	//反転処理
	if(virtual_Flip_Flg)
	{
		box_CP -> SetDegree(360.f - degree);
		box_CP -> SetOrigin(S_Vector2(origin_S.x , 1.f - origin_S.y));
		box_CP -> SetRotateOrigin(S_Vector2(rotate_Origin_S.x , 1.f - rotate_Origin_S.y));	
	}
	else
	{
		box_CP -> SetDegree(degree);
		box_CP -> SetOrigin(origin_S);
		box_CP -> SetRotateOrigin(rotate_Origin_S);		
	}

	box_CP -> SetBoxInfo(S_2DBox(size_S));

	++ _primitive_Val;
	return box_CP -> GetHandle();
}

//============================================================================
//! ポリゴン描画の登録(鈍角があるものは未対応)
NODE_HANDLE C_DL2DFrameWorkDrawPrimitive::CreatePolygon(const S_Vector2&				pos_S,
														const std::vector<S_Vector2>&	vertex_List,
														const S_Color&					color_S,
														dlS32							depth,
														dlBOOL							virtual_Flip_Flg)
{
	C_PrimitivePolygonNode* polygon_CP = GetPrimitive<C_PrimitivePolygonNode>(pos_S , color_S , depth , virtual_Flip_Flg);
	polygon_CP -> SetFlipFlg(virtual_Flip_Flg);

	S_2DPolygon pol_S = {vertex_List};
	if(virtual_Flip_Flg)
	{
		ItrLoopDef(std::vector<S_Vector2> , pol_S.vertex_Array , itr)
		{itr -> y = - itr -> y;}
	}
	
	polygon_CP -> SetPolygonInfo(pol_S);

	++ _primitive_Val;
	return polygon_CP -> GetHandle();
}

//============================================================================
//! レイ描画の登録
//
NODE_HANDLE C_DL2DFrameWorkDrawPrimitive::CreateRay(const S_Vector2&				pos_S,
													dlF32							origin,
													dlF32							degree,
													dlF32							radius,
													dlF32							half_Length,
													dlF32							width,
													const S_Color&					color_S,
													dlS32							depth,
													dlBOOL							virtual_Flip_Flg)
{
	C_PrimitiveRayNode* ray_CP = GetPrimitive<C_PrimitiveRayNode>(pos_S , color_S , depth , virtual_Flip_Flg);
	ray_CP -> SetFlipFlg(virtual_Flip_Flg);

	ray_CP -> SetDegree((virtual_Flip_Flg) ? 360.0f - degree : degree);
	ray_CP -> SetWidth(width);
	ray_CP -> SetRadius(radius);
	ray_CP -> SetOrigin(origin);
	ray_CP -> SetHalfLength(half_Length);

	++ _primitive_Val;
	return ray_CP -> GetHandle();
}

//============================================================================
//! 登録描画プリミティブの削除
dlBOOL C_DL2DFrameWorkDrawPrimitive::DeletePrimitive(DL::NODE_HANDLE handle)
{
	if(C_DL2DFrameWork::RENDER -> _Erase(handle))
	{
		-- _primitive_Val;
		return dlTRUE;
	}
	return dlFALSE;
}

//============================================================================
//! 位置の変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetPosition(NODE_HANDLE handle , const S_Vector2& pos_S)
{
	return C_DL2DFrameWork::RENDER -> _SetPosition(handle , pos_S);
}

//============================================================================
//! 回転度の変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetRotate(NODE_HANDLE handle , dlF32 degree)
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	if(node_CP == 0 || node_CP -> GetNodeType() != kPRIMITIVE_NODE)
	{
		return dlFALSE;
	}

	E_PrimitiveType type = static_cast<C_PrimitiveCoreNode*>(node_CP) -> GetPrimitiveType();
	if(type == kPRIMITIVE_BOX)
	{
		static_cast<C_PrimitiveBoxNode*>(node_CP) -> SetDegree(degree);
		return dlTRUE;
	}

	return dlFALSE;
}

//============================================================================
//! 深度の変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetDepth(NODE_HANDLE handle , dlS32 depth)
{
	return C_DL2DFrameWork::RENDER -> _ChangeDepth(handle , depth);
}

//============================================================================
//! 表示/非表示の変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetValidFlg(NODE_HANDLE handle , dlBOOL flg)
{
	return C_DL2DFrameWork::RENDER -> _SetValidFlg(handle , flg);
}

//============================================================================
//! プリミティブの色変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetColor(NODE_HANDLE handle , const S_Color& color_S)
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	if(node_CP == 0 || node_CP -> GetNodeType() != kPRIMITIVE_NODE)
	{
		return dlFALSE;
	}

	static_cast<C_PrimitiveCoreNode*>(node_CP) -> SetColor(color_S);

	return dlTRUE;
}

//============================================================================
//! プリミティブの基準点変更
dlBOOL C_DL2DFrameWorkDrawPrimitive::SetOrigin(NODE_HANDLE handle , const S_Vector2& origin_S , const S_Vector2& rotate_Origin_S)
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	if(node_CP == 0 || node_CP -> GetNodeType() != kPRIMITIVE_NODE)
	{
		return dlFALSE;
	}

	C_PrimitiveCoreNode* primitive_CP = static_cast<C_PrimitiveCoreNode*>(node_CP);

	dlBOOL flip_Flg;
	C_DL2DFrameWork::RENDER -> _IsVirtualFlip(handle , flip_Flg);

	if(flip_Flg)
	{
		primitive_CP -> SetOrigin(S_Vector2(origin_S.x , 1.f - origin_S.y));
		primitive_CP -> SetRotateOrigin(S_Vector2(rotate_Origin_S.x , 1.f - rotate_Origin_S.y));
	}
	else
	{
		primitive_CP -> SetOrigin(origin_S);
		primitive_CP -> SetRotateOrigin(rotate_Origin_S);
	}

	return dlTRUE;
}

//============================================================================
//! 有効状態かの取得
dlBOOL C_DL2DFrameWorkDrawPrimitive::IsValidFlg(NODE_HANDLE handle , dlBOOL& out_Flg) const
{
	C_RenderCoreNode* node_CP = C_DL2DFrameWork::RENDER -> _GetNodeAddress(handle);
	if(node_CP == 0 || node_CP -> GetNodeType() != kPRIMITIVE_NODE)
	{
		return dlFALSE;
	}

	out_Flg = node_CP -> IsValidFlg();
	return dlTRUE;
}

}