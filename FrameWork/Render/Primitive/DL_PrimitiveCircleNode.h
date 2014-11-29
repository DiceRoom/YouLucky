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

//! â~ÉvÉäÉ~ÉeÉBÉuï`âÊäÓëbÉmÅ[Éh
class C_PrimitiveCircleNode : public C_PrimitiveCoreNode
{
public:
	void SetCircleInfo(const S_Circle& circle_S);

private:
	void _Render(void);

private:
	dlS32 dummy;							//< âΩåÃÇ©Ç±ÇÃÉ_É~Å[Ç™ñ≥Ç¢Ç∆îºåaÇÃíÜêgÇ™èëÇ´ä∑ÇÌÇÈ

	static const dlS32 PRECISION = 18;		//< â~ÇÃï`âÊï™äÑêî
	S_Circle	_circle_S;					//< â~èÓïÒ
	S_Vector2	_vertex_A[PRECISION + 1];	//< â~ÇÃí∏ì_èÓïÒ
};

}

#endif
