/****************************************************************************/
/* DL_PrimitiveRayNode.h													*/
/****************************************************************************/
#ifndef DL_PRIMITIVERAYNODE_H_
#define	DL_PRIMITIVERAYNODE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "DL_PrimitiveCoreNode.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! レイプリミティブ描画基礎ノード
class C_PrimitiveRayNode : public C_PrimitiveCoreNode
{
private:
	void _Render(void);

private:
	ACS_S_MEB(private , dlF32 , _width , Width);
	ACS_S_MEB(private , dlF32 , _radius , Radius);
	ACS_S_MEB(private , dlF32 , _origin , Origin);
	ACS_S_MEB(private , dlF32 , _half_Length , HalfLength);
	ACS_S_MEB(private , dlF32 , _degree , Degree);
};

}

#endif
