/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_PrimitiveCircleNode.h"

namespace DL
{

//============================================================================
//! �~�`��
void C_PrimitiveCircleNode::_Render(void)
{
#ifdef WIN32
	//���_�̐ݒ�
	S_RHW_Vertex vertex_SA[PRECISION + 1];
	const S_Vector2 pos_S = GetPosition();
	const S_Color color_S = GetColor();
	for(dlS32 cnt = 0 ; cnt < PRECISION ; ++ cnt)
	{
		vertex_SA[cnt].x = pos_S.x + _vertex_A[cnt].x * _circle_S.rad;
		vertex_SA[cnt].y = pos_S.y + _vertex_A[cnt].y * _circle_S.rad;
		vertex_SA[cnt].z = 0;
		vertex_SA[cnt].rhw = 1;
		vertex_SA[cnt].diffuse = S_Color::PackARGB(color_S);
	}
	vertex_SA[PRECISION] = vertex_SA[0];

	//���_�X�g���[���錾�ݒ�
	_GetDevice() -> GetDevice() -> SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	//�|���S���̕`��
	_GetDevice() -> GetDevice() -> DrawPrimitiveUP(D3DPT_TRIANGLEFAN , PRECISION - 1 , vertex_SA , sizeof(S_RHW_Vertex));
#endif
}

//============================================================================
//! �~���̐ݒ�
void C_PrimitiveCircleNode::SetCircleInfo(const S_Circle& circle_S)
{
	_circle_S = circle_S;

	//���������P������̊p�x
	const dlF32 draw_Angle = 360.f / PRECISION;

	for(dlS32 cnt = 0 ; cnt < PRECISION ; ++ cnt)
	{
		_vertex_A[cnt].x = MATH::Cos(MATH::DegToRad(draw_Angle * cnt));
		_vertex_A[cnt].y = MATH::Sin(MATH::DegToRad(draw_Angle * cnt));
	}
}

}