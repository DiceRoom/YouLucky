/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_PrimitiveRayNode.h"

namespace DL
{

//============================================================================
//! レイ描画
void C_PrimitiveRayNode::_Render(void)
{
#ifdef WIN32
	const S_Vector2 pos_S = GetPosition();
	const S_Color color_S = GetColor();

	//レイの長さ取得
	const dlF32 ray_Length = _width + _radius * 1.73205080756887729352f;
	//基準点の移動量取得
	const dlF32 ray_Origin = ray_Length * _origin;
	//頂点設定
	S_RHW_Vertex vertex_SA[9] = {
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) }
	};

	//先端部を除いた矩形設定
	vertex_SA[0].x = vertex_SA[5].x = -ray_Origin;
	vertex_SA[0].y = vertex_SA[1].y = -_half_Length;
	vertex_SA[1].x = vertex_SA[2].x = vertex_SA[0].x + _width;
	vertex_SA[5].y = vertex_SA[2].y = _half_Length;
	//先端部設定
	vertex_SA[6].x = vertex_SA[8].x = vertex_SA[1].x;
	vertex_SA[6].y = -_radius;
	vertex_SA[8].y =  _radius;
	vertex_SA[7].x = vertex_SA[0].x + ray_Length;

	//回転処理
	if(_degree)
	{
		dlF32 sin_Value = DL::MATH::Sin(DL::MATH::DegToRad(_degree));
		dlF32 cos_Value = DL::MATH::Cos(DL::MATH::DegToRad(_degree));
		for(dlS32 i = 0 ; i < 9 ; ++ i)
		{
			if(i == 3 || i == 4)
				continue;

			S_Vector2 turn_S(
				vertex_SA[i].x * cos_Value - vertex_SA[i].y * sin_Value,
				vertex_SA[i].x * sin_Value + vertex_SA[i].y * cos_Value
			);

			vertex_SA[i].x = turn_S.x + pos_S.x;
			vertex_SA[i].y = turn_S.y + pos_S.y;
		}
	}
	else
	{
		//回転していない場合はそのまま移動
		for(dlS32 i = 0 ; i < 9 ; ++ i)
		{
			vertex_SA[i].x += pos_S.x;
			vertex_SA[i].y += pos_S.y;
		}
	}

	// 3, 4頂点はそれぞれ 0, 2頂点と同じ位置
	//              [6]
	//   [0/3]--[ 1 ]|＼
	//     |  ＼  |  |  [7]
	//   [ 5 ]--[2/4]|／
	//              [8]
	vertex_SA[3] = vertex_SA[0];
	vertex_SA[4] = vertex_SA[2];

	//頂点ストリーム宣言設定
	_GetDevice() -> GetDevice() -> SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	//ポリゴンの描画
	_GetDevice() -> GetDevice() -> DrawPrimitiveUP(D3DPT_TRIANGLELIST , 3 , vertex_SA , sizeof(S_RHW_Vertex));
#endif
}

}