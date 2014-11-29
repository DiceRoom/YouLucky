/****************************************************************************/
/* DL_2DFrameWorkCls.h														*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKCOLLISION_H_
#define	DL_2DFRAMEWORKCOLLISION_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../../../Library/Collision/2D/DL_2DBox.h"
#include "../../../Library/Collision/2D/DL_2DLine.h"
#include "../../../Library/Collision/2D/DL_Circle.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

//! 2Dゲーム用フレームワーク(当たり判定用)
class C_DL2DFrameWorkCollision
{
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkCollision(void){}
	~C_DL2DFrameWorkCollision(void){}
	C_DL2DFrameWorkCollision(const C_DL2DFrameWorkCollision&){}

public:
	void Initialize(void);
	void Terminate(void);

	void SetInitParameter(dlS32 division_Level , const S_Vector2& left_Up_Pos_S , const S_Vector2& right_Down_Pos_S);

	void			AddCollision(C_DLCls2DBase* cls_CP);
	C_DLCls2DBox*	AddCollision(const S_2DBox &box_S);
	C_DLCls2DLine*	AddCollision(const S_2DLine &line_S);
	C_DLClsCircle*	AddCollision(const S_Circle &circle_S);
	
	void	EraseCollision		(C_DLCls2DBase *erase_CP);
	dlBOOL	IsRegistCollision	(C_DLClsBase* cls_CP) const;
	void	DeleteCollision		(C_DLCls2DBase *erase_CP);
	
	dlU32 GetRegistCollisionVal(void);

private:
	void _SetCollision(C_DLCls2DBase *cls_CP);
	
private:
	NODE_HANDLE					_update_Node_Handle;		//< 当たり判定マネージャの更新を掛けるノードのハンドル
	NODE_HANDLE					_finish_Node_Handle;		//< 当たり判定マネージャの初期化を掛けるノードのハンドル
	class C_CollisionManager*	_cls_Mng_CP;				//< 当たり判定マネージャ
};

}

#endif
