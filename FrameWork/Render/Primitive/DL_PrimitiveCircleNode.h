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

//! �~�v���~�e�B�u�`���b�m�[�h
class C_PrimitiveCircleNode : public C_PrimitiveCoreNode
{
public:
	void SetCircleInfo(const S_Circle& circle_S);

private:
	void _Render(void);

private:
	dlS32 dummy;							//< ���̂����̃_�~�[�������Ɣ��a�̒��g�����������

	static const dlS32 PRECISION = 18;		//< �~�̕`�敪����
	S_Circle	_circle_S;					//< �~���
	S_Vector2	_vertex_A[PRECISION + 1];	//< �~�̒��_���
};

}

#endif
