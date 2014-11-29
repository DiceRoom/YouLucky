/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkScene.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Node/DL_2DFrameWorkNode.h>

namespace DL
{

//! ���[�J�[�m�[�h(�V�[���̍X�V)
class C_SceneUpdateNode : public C_CoreNode
{
public:
	C_SceneUpdateNode(void):_wait_Time(0){}

private:
	void _Update(void)
	{
		//�ҋ@���Ԃ�����ꍇ
		if(_wait_Time > 0)
		{
			-- _wait_Time;
			return;
		}

		_scene_CP -> Update();
	};

private:
	ACS_PS_MEB(private , C_SceneManager* , _scene_CP , SceneAddress);
	ACS_S_MEB(private , dlS32 , _wait_Time , WaitTime);
};


//============================================================================
//! ������
void C_DL2DFrameWorkScene::Initialize(void)
{
	_scene_Mng_CP = dlNEW C_SceneManager();
	C_SceneUpdateNode* node_CP = C_DL2DFrameWork::NODE -> CreateNode<C_SceneUpdateNode>(kSYSTEM_FRONT_LINE , kSYS_NODE_PRI_SCENE , &_update_Node_Handle , dlTRUE);
	node_CP -> SetSceneAddress(_scene_Mng_CP);
}

//============================================================================
//! �I������
void C_DL2DFrameWorkScene::Termiante(void)
{
	dlDELETE _scene_Mng_CP;
	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
}

//============================================================================
//! �S�ẴV�[�����폜
void C_DL2DFrameWorkScene::DeleteAllScene(void)
{
	dlDELETE _scene_Mng_CP;
	_scene_Mng_CP = dlNEW C_SceneManager();
	C_SceneUpdateNode* node_CP = static_cast<C_SceneUpdateNode*>(C_DL2DFrameWork::NODE -> GetNode(_update_Node_Handle));
	node_CP -> SetSceneAddress(_scene_Mng_CP);
}

//============================================================================
//! �V�[���̃W�����v
void C_DL2DFrameWorkScene::JumpScene(const dlSTRING &scene_Name)
{
	_scene_Mng_CP -> SetJumpScene(scene_Name);
}

//============================================================================
//! �����V�[���ɍăW�����v
void C_DL2DFrameWorkScene::ReJump(void)
{
	_scene_Mng_CP -> ReJump();
}

//============================================================================
//! ���ɃW�����v���߂����s����Ă��邩�̃`�F�b�N
dlBOOL C_DL2DFrameWorkScene::IsAlreadySettingJump(void) const
{
	return (_scene_Mng_CP -> GetJumpSceneName().length() != 0);
}

//============================================================================
//!	�V�[���̃A�h���X�̎擾
C_SceneBase* C_DL2DFrameWorkScene::GetScene(const dlSTRING& scene_Name)
{
	return _scene_Mng_CP -> GetSceneAddress(scene_Name);
}

//============================================================================
//! �V�[���̐e�q�֘A�t��
void C_DL2DFrameWorkScene::SetSceneRelation(const dlSTRING &parent_Name , const dlSTRING &child_Name)
{
	_scene_Mng_CP -> SetRelations(parent_Name , child_Name);
}

//============================================================================
//! �V�[���̗L�������̐؂�ւ�
void C_DL2DFrameWorkScene::SetSceneValidFlg(dlBOOL flg)
{
	_GetSceneUpdateNode() -> SetValidFlg(flg);
}

//============================================================================
//! �V�[���𖢎�����Ԃɂ���
void C_DL2DFrameWorkScene::ResetScene(void)
{
	_scene_Mng_CP -> ResetScene();
}

//============================================================================
//! ���ݎ��s���̃V�[����
dlSTRING C_DL2DFrameWorkScene::GetCurrentSceneName(void)
{
	return _scene_Mng_CP -> GetSceneName();
}

//============================================================================
//! �w�肵���V�[���̎��s�s�\��ԂɕύX
void C_DL2DFrameWorkScene::SetPauseScene(const dlSTRING &scene_Name)
{
	C_SceneBase *scene_CP = _scene_Mng_CP -> GetSceneAddress(scene_Name);
	if(scene_CP == 0){return;}
	scene_CP -> Pause();
}

//============================================================================
//! �w�肵�����O�̃V�[������V�X�e���|�[�Y���|����
void C_DL2DFrameWorkScene::BeginSystemPause(const dlSTRING &scene_Name)
{
	if(scene_Name.length() != 0)
	{
		C_SceneBase *scene_CP = _scene_Mng_CP -> GetSceneAddress(scene_Name);
		_scene_Mng_CP -> SetAllScenePause(scene_CP);
	}
	else
	{
		_scene_Mng_CP -> SetAllScenePause();
	}
}

//============================================================================
//! �w�肵�����O�̃V�[������V�X�e���|�[�Y����������
void C_DL2DFrameWorkScene::EndSystemPause(const dlSTRING &scene_Name)
{
	if(scene_Name.length() != 0)
	{
		C_SceneBase *scene_CP = _scene_Mng_CP -> GetSceneAddress(scene_Name);
		_scene_Mng_CP -> SetAllScenePauseCancel(scene_CP);
	}
	else
	{
		_scene_Mng_CP -> SetAllScenePauseCancel();
	}
}

//============================================================================
//! �w�莞�Ԃ̊Ԃ����A�V�[�������s���Ȃ�
void C_DL2DFrameWorkScene::SetWaitTime(dlS32 wait_Time)
{
	_GetSceneUpdateNode() -> SetWaitTime(wait_Time);
}

//============================================================================
//! �V�[���̍X�V�m�[�h�̎擾
C_SceneUpdateNode* C_DL2DFrameWorkScene::_GetSceneUpdateNode(void) const
{
	return static_cast<C_SceneUpdateNode*>(C_DL2DFrameWork::NODE -> GetNode(_update_Node_Handle));
}

}