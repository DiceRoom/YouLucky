/****************************************************************************/
/* PrimitiveCircleNode.h													*/
/****************************************************************************/
#ifndef DL_PRIMITIVECIRCLENODE_H_
#define	DL_PRIMITIVECIRCLENODE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "DL_PrimitiveCoreNode.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! 円プリミティブ描画基礎ノード
class C_PrimitiveCircleNode : public C_PrimitiveCoreNode
{
public:
	void SetCircleInfo(const S_Circle& circle_S);

private:
	void _Render(void);

private:
	dlS32 dummy;							//< 何故かこのダミーが無いと半径の中身が書き換わる

	static const dlS32 PRECISION = 18;		//< 円の描画分割数
	S_Circle	_circle_S;					//< 円情報
	S_Vector2	_vertex_A[PRECISION + 1];	//< 円の頂点情報
};

}

#endif
