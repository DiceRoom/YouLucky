/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_PrimitiveLineNode.h"

namespace DL
{

//============================================================================
//! ü•`‰æ
void C_PrimitiveLineNode::_Render(void)
{
#ifdef WIN32
	//’¸“_Ý’è
	const S_Vector2 pos_S = GetPosition();
	const S_Vector2 origin_S = GetOrigin();
	const S_Vector2 offset_S(-origin_S.x * _line_S.vec_S.x , -origin_S.y * _line_S.vec_S.y);
	const S_Color color_S = GetColor();
	S_RHW_Vertex vertex_SA[2] = {
		{
			pos_S.x + offset_S.x,
			pos_S.y + offset_S.y,
			0,
			1,
			S_Color::PackARGB(color_S)
		}, {
			pos_S.x + _line_S.vec_S.x + offset_S.x,
			pos_S.y + _line_S.vec_S.y + offset_S.y,
			0,
			1,
			S_Color::PackARGB(color_S)
		}
	};

	//’¸“_ƒXƒgƒŠ[ƒ€éŒ¾Ý’è
	_GetDevice() -> GetDevice() -> SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	//ƒ|ƒŠƒSƒ“‚Ì•`‰æ
	_GetDevice() -> GetDevice() -> DrawPrimitiveUP(D3DPT_LINELIST , 1 , vertex_SA , sizeof(S_RHW_Vertex));
#endif
}

}