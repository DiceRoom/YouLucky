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

//! �v���~�e�B�u���
enum E_PrimitiveType
{
	kPRIMITIVE_BOX,	//< ��
};
#ifndef WIN32
    class C_DirectXDevice;
#endif
//! �v���~�e�B�u�`���b�m�[�h
class C_PrimitiveCoreNode : public C_RenderCoreNode
{
public:
	//! �v���~�e�B�u�`��p�̒��_
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
	ACS_MEB(private , S_Vector2 , _pos_S , Position);						//< �ʒu
	static C_DirectXDevice* _dx_Device_CP;									//< DirectX�̃f�o�C�X
	ACS_MEB(private , DL::S_Color , _color_S , Color);						//< �F

	ACS_MEB(private , S_Vector2 , _origin_S , Origin);						//< ��ʒu���
	ACS_MEB(private , S_Vector2 , _rotate_Origin_S , RotateOrigin);			//< ��]��ʒu���
	ACS_B_MEB(private , _flip_Flg , FlipFlg);								//< �t���b�v�t���O
};

}

#endif
