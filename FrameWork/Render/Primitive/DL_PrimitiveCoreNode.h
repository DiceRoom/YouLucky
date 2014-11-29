/****************************************************************************/
/* DL_PrimitiveCoreNode.h													*/
/****************************************************************************/
#ifndef DL_PRIMITIVEBASECORE_H_
#define	DL_PRIMITIVEBASECORE_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../DL_RenderCoreNode.h"

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

//! プリミティブ種類
enum E_PrimitiveType
{
	kPRIMITIVE_BOX,	//< 箱
};
#ifndef WIN32
    class C_DirectXDevice;
#endif
//! プリミティブ描画基礎ノード
class C_PrimitiveCoreNode : public C_RenderCoreNode
{
public:
	//! プリミティブ描画用の頂点
	struct S_RHW_Vertex
	{
		dlF32    x;
		dlF32    y;
		dlF32    z;
		dlF32    rhw;
#ifdef WIN32
		D3DCOLOR diffuse;
#endif
	};
public:
	C_PrimitiveCoreNode			(void);
	virtual ~C_PrimitiveCoreNode(void){};

	void			Render		(void);
	static void		SetDevice	(C_DirectXDevice* device_CP);

protected:
	static C_DirectXDevice* _GetDevice(void);

private:
	virtual void _Render(void) = 0;

private:
	ACS_MEB(private , E_PrimitiveType , _primitive_Type , PrimitiveType);
	ACS_MEB(private , S_Vector2 , _pos_S , Position);						//< 位置
	static C_DirectXDevice* _dx_Device_CP;									//< DirectXのデバイス
	ACS_MEB(private , DL::S_Color , _color_S , Color);						//< 色

	ACS_MEB(private , S_Vector2 , _origin_S , Origin);						//< 基準位置情報
	ACS_MEB(private , S_Vector2 , _rotate_Origin_S , RotateOrigin);			//< 回転基準位置情報
	ACS_B_MEB(private , _flip_Flg , FlipFlg);								//< フリップフラグ
};

}

#endif
