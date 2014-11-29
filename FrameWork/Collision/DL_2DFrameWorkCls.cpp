/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include <DL_2DFrameWork.h>
#include "DL_2DFrameWorkCls.h"
#include <FrameWork/Node/DL_2DFrameWorkNode.h>

namespace DL
{

//! ���[�J�[�m�[�h(�����蔻��}�l�[�W���̍X�V)
class C_ClsUpdateNode : public C_CoreNode
{
private:
	void _Revision(void)
	{
		_cls_CP -> Update();
	};

private:
	ACS_PS_MEB(private , C_CollisionManager* , _cls_CP , ClsAddress);
};

//! ���[�J�[�m�[�h(�����蔻��}�l�[�W���̏�����)
class C_ClsFinishNode : public C_CoreNode
{
private:
	void _Finish(void)
	{
		_cls_CP -> InitializeAllObject();
	};

private:
	ACS_PS_MEB(private , C_CollisionManager* , _cls_CP , ClsAddress);
};

//============================================================================
//! ������
void C_DL2DFrameWorkCollision::Initialize(void)
{
	_cls_Mng_CP = dlNEW C_CollisionManager();

	C_ClsUpdateNode* update_CP = C_DL2DFrameWork::NODE -> CreateNode<C_ClsUpdateNode>(kSYSTEM_FRONT_LINE , kSYS_NODE_PRI_CLS_UPDATE , &_update_Node_Handle , dlTRUE);
	update_CP -> SetClsAddress(_cls_Mng_CP);

	C_ClsFinishNode* finish_CP = C_DL2DFrameWork::NODE -> CreateNode<C_ClsFinishNode>(kSYSTEM_BACK_LINE , kSYS_NODE_PRI_CLS_UPDATE , &_finish_Node_Handle , dlTRUE);
	finish_CP -> SetClsAddress(_cls_Mng_CP);
}

//============================================================================
//! �I������
void C_DL2DFrameWorkCollision::Terminate(void)
{
	//�폜���I�u�W�F�N�g���c���Ă���΃G���[
	if(_cls_Mng_CP -> GetManagerCollisionVal() != 0)
	{
		SystemError(kSYSER_CLS_MEMORYLEAK);
	}

	dlDELETE _cls_Mng_CP;
	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
	C_DL2DFrameWork::NODE -> DeleteNode(_finish_Node_Handle);
}

//============================================================================
//! �G���h���[�U�[�����̏������A�[������Ă΂Ȃ��ƃG���[�ɂȂ�
void C_DL2DFrameWorkCollision::SetInitParameter(dlS32 division_Level , const S_Vector2& left_Up_Pos_S , const S_Vector2& right_Down_Pos_S)
{
	_cls_Mng_CP -> Initialize(division_Level , left_Up_Pos_S , right_Down_Pos_S);
}

//============================================================================
//! �S�Ă̓����蔻����J

//============================================================================
//! �����蔻����}�l�[�W���ɓo�^
void C_DL2DFrameWorkCollision::AddCollision(C_DLCls2DBase* cls_CP)
{
	_SetCollision(cls_CP);
}

//============================================================================
//! �������蔻����쐬���}�l�[�W���[�ɓo�^
C_DLCls2DBox *C_DL2DFrameWorkCollision::AddCollision(const S_2DBox &box_S)
{
	C_DLCls2DBox *box_CP = dlNEW C_DLCls2DBox();
	box_CP -> SetBox(box_S);

	_SetCollision(box_CP);
	
	return box_CP;
}

//============================================================================
//! �������蔻����쐬���}�l�[�W���[�ɓo�^
C_DLCls2DLine *C_DL2DFrameWorkCollision::AddCollision(const S_2DLine &line_S)
{
	C_DLCls2DLine *line_CP = dlNEW C_DLCls2DLine();
	line_CP -> SetLine(line_S);

	_SetCollision(line_CP);
	
	return line_CP;
}

//============================================================================
//! �~�����蔻����쐬���}�l�[�W���[�ɓo�^
C_DLClsCircle *C_DL2DFrameWorkCollision::AddCollision(const S_Circle &circle_S)
{
	C_DLClsCircle *circle_CP = dlNEW C_DLClsCircle();
	circle_CP -> SetCircle(circle_S);

	_SetCollision(circle_CP);

	return circle_CP;
}

//============================================================================
//! �}�l�[�W���ɓo�^����Ă��铖���蔻�������
void C_DL2DFrameWorkCollision::EraseCollision(C_DLCls2DBase *erase_CP)
{
	_cls_Mng_CP -> EraseCollision(erase_CP);
}

//============================================================================
//! �����蔻�肪�o�^����Ă��邩
dlBOOL C_DL2DFrameWorkCollision::IsRegistCollision(C_DLClsBase* cls_CP) const
{
	return (_cls_Mng_CP -> IsRegistCollision(cls_CP));
}

//============================================================================
//! �}�l�[�W���ɓo�^����Ă��铖���蔻����폜
void C_DL2DFrameWorkCollision::DeleteCollision(C_DLCls2DBase *erase_CP)
{
	EraseCollision(erase_CP);
	dlDELETE erase_CP;
}

//============================================================================
//! �}�l�[�W���ɓo�^����Ă��铖���蔻��̐��̎擾
dlU32 C_DL2DFrameWorkCollision::GetRegistCollisionVal(void)
{
	return static_cast<dlU32>(_cls_Mng_CP -> GetManagerCollisionVal());
}

//============================================================================
//! �����蔻����}�l�[�W���[�ɓo�^
void C_DL2DFrameWorkCollision::_SetCollision(C_DLCls2DBase *cls_CP)
{
	_cls_Mng_CP -> RegistCollision(cls_CP);
}

}