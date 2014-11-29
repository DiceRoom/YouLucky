/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkScene.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Node/DL_2DFrameWorkNode.h>

namespace DL
{

//! ワーカーノード(シーンの更新)
class C_SceneUpdateNode : public C_CoreNode
{
public:
	C_SceneUpdateNode(void):_wait_Time(0){}

private:
	void _Update(void)
	{
		//待機時間がある場合
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
//! 初期化
void C_DL2DFrameWorkScene::Initialize(void)
{
	_scene_Mng_CP = dlNEW C_SceneManager();
	C_SceneUpdateNode* node_CP = C_DL2DFrameWork::NODE -> CreateNode<C_SceneUpdateNode>(kSYSTEM_FRONT_LINE , kSYS_NODE_PRI_SCENE , &_update_Node_Handle , dlTRUE);
	node_CP -> SetSceneAddress(_scene_Mng_CP);
}

//============================================================================
//! 終了処理
void C_DL2DFrameWorkScene::Termiante(void)
{
	dlDELETE _scene_Mng_CP;
	C_DL2DFrameWork::NODE -> DeleteNode(_update_Node_Handle);
}

//============================================================================
//! 全てのシーンを削除
void C_DL2DFrameWorkScene::DeleteAllScene(void)
{
	dlDELETE _scene_Mng_CP;
	_scene_Mng_CP = dlNEW C_SceneManager();
	C_SceneUpdateNode* node_CP = static_cast<C_SceneUpdateNode*>(C_DL2DFrameWork::NODE -> GetNode(_update_Node_Handle));
	node_CP -> SetSceneAddress(_scene_Mng_CP);
}

//============================================================================
//! シーンのジャンプ
void C_DL2DFrameWorkScene::JumpScene(const dlSTRING &scene_Name)
{
	_scene_Mng_CP -> SetJumpScene(scene_Name);
}

//============================================================================
//! 同じシーンに再ジャンプ
void C_DL2DFrameWorkScene::ReJump(void)
{
	_scene_Mng_CP -> ReJump();
}

//============================================================================
//! 既にジャンプ命令が発行されているかのチェック
dlBOOL C_DL2DFrameWorkScene::IsAlreadySettingJump(void) const
{
	return (_scene_Mng_CP -> GetJumpSceneName().length() != 0);
}

//============================================================================
//!	シーンのアドレスの取得
C_SceneBase* C_DL2DFrameWorkScene::GetScene(const dlSTRING& scene_Name)
{
	return _scene_Mng_CP -> GetSceneAddress(scene_Name);
}

//============================================================================
//! シーンの親子関連付け
void C_DL2DFrameWorkScene::SetSceneRelation(const dlSTRING &parent_Name , const dlSTRING &child_Name)
{
	_scene_Mng_CP -> SetRelations(parent_Name , child_Name);
}

//============================================================================
//! シーンの有効無効の切り替え
void C_DL2DFrameWorkScene::SetSceneValidFlg(dlBOOL flg)
{
	_GetSceneUpdateNode() -> SetValidFlg(flg);
}

//============================================================================
//! シーンを未実効状態にする
void C_DL2DFrameWorkScene::ResetScene(void)
{
	_scene_Mng_CP -> ResetScene();
}

//============================================================================
//! 現在実行中のシーン名
dlSTRING C_DL2DFrameWorkScene::GetCurrentSceneName(void)
{
	return _scene_Mng_CP -> GetSceneName();
}

//============================================================================
//! 指定したシーンの実行不可能状態に変更
void C_DL2DFrameWorkScene::SetPauseScene(const dlSTRING &scene_Name)
{
	C_SceneBase *scene_CP = _scene_Mng_CP -> GetSceneAddress(scene_Name);
	if(scene_CP == 0){return;}
	scene_CP -> Pause();
}

//============================================================================
//! 指定した名前のシーンからシステムポーズを掛ける
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
//! 指定した名前のシーンからシステムポーズを解除する
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
//! 指定時間の間だけ、シーンを実行しない
void C_DL2DFrameWorkScene::SetWaitTime(dlS32 wait_Time)
{
	_GetSceneUpdateNode() -> SetWaitTime(wait_Time);
}

//============================================================================
//! シーンの更新ノードの取得
C_SceneUpdateNode* C_DL2DFrameWorkScene::_GetSceneUpdateNode(void) const
{
	return static_cast<C_SceneUpdateNode*>(C_DL2DFrameWork::NODE -> GetNode(_update_Node_Handle));
}

}