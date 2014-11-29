/****************************************************************************/
/* DL_RenderCoreNode.h														*/
/****************************************************************************/
#ifndef DL_RENDERCORENODE_H_
#define	DL_RENDERCORENODE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../Node/DL_CoreNode.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! ï`âÊäÓëbÉmÅ[Éh
class C_RenderCoreNode : public C_CoreNode
{
public:
	C_RenderCoreNode(void){SetNodeType(kRENDER_CORE_NODE);};
	virtual ~C_RenderCoreNode(void){};
	virtual void Render(void) = 0;
	virtual void SetPosition(const S_Vector2&) = 0;
};

}

#endif
