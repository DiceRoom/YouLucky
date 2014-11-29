/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include <FrameWork/Core/DL_2DFrameWorkCore.h>
#include "DL_PrimitiveCoreNode.h"

namespace DL
{

C_DirectXDevice* C_PrimitiveCoreNode::_dx_Device_CP = 0;

//============================================================================
//! �R���X�g���N�^
C_PrimitiveCoreNode::C_PrimitiveCoreNode(void)
{
	SetNodeType(kPRIMITIVE_NODE);
}

//============================================================================
//! �`��
void C_PrimitiveCoreNode::Render(void)
{
#ifdef WIN32
	//�����_�����O�X�e�[�^�X�̕ێ�
	DWORD stack1 , stack2;
	LPDIRECT3DDEVICE9 device = C_DL2DFrameWork::CORE -> GetDirectXDevice() -> GetDevice();
	device -> GetRenderState(D3DRS_SRCBLEND , &stack1);
	device -> GetRenderState(D3DRS_DESTBLEND , &stack2);

	//�����_�����O�X�e�[�^�X�̕ύX
	device -> SetRenderState(D3DRS_SRCBLEND , D3DBLEND_SRCALPHA);
	device -> SetRenderState(D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA);

	_Render();

	//�����_�����O�X�e�[�^�X�̕ύX
	device -> SetRenderState(D3DRS_SRCBLEND , stack1);
	device -> SetRenderState(D3DRS_DESTBLEND , stack2);
#endif
}

//============================================================================
//! DirectXDevice�̐ݒ�
void C_PrimitiveCoreNode::SetDevice(C_DirectXDevice* device_CP)
{
	_dx_Device_CP = device_CP;
}

//============================================================================
//! DirectXDevice�̎擾
C_DirectXDevice* C_PrimitiveCoreNode::_GetDevice(void)
{
	return _dx_Device_CP;
}

}
