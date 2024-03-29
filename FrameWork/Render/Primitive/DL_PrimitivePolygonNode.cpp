/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_PrimitivePolygonNode.h"

namespace DL
{

//============================================================================
//! ポリゴン描画
void C_PrimitivePolygonNode::_Render(void)
{
#ifdef WIN32
//	if(_polygon_S.vertex_Array.size() < 2)  return;

	//頂点設定
	const dlU32 vertex_Num = static_cast<dlU32>(_polygon_S.vertex_Array.size());
	std::vector<S_RHW_Vertex> vertex_SA(vertex_Num);

	const S_Vector2 pos_S = GetPosition();
	const S_Color color_S = GetColor();
	for(dlU32 cnt = 0 ; cnt < vertex_Num ; ++ cnt)
	{
		vertex_SA[cnt].x = pos_S.x + _polygon_S.vertex_Array[cnt].x;
		vertex_SA[cnt].y = pos_S.y + _polygon_S.vertex_Array[cnt].y;
		vertex_SA[cnt].z = 0;
		vertex_SA[cnt].diffuse = S_Color::PackARGB(color_S);
		vertex_SA[cnt].rhw = 1;
	}

	//頂点ストリーム宣言設定
	_GetDevice() -> GetDevice() -> SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	//ポリゴンの描画
	_GetDevice() -> GetDevice() -> DrawPrimitiveUP(D3DPT_TRIANGLEFAN , vertex_Num - 2 , &vertex_SA[0] , sizeof(S_RHW_Vertex));
#endif
}

}