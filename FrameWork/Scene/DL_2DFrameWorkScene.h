/****************************************************************************/
/* DL_2DFrameWorkScene.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKSCENE_H_
#define	DL_2DFRAMEWORKSCENE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{
    class C_SceneUpdateNode;
//! フレームワーク(シーン)
class C_DL2DFrameWorkScene
{	
friend class C_DL2DFrameWork;
friend class C_SceneUpdateNode;
friend class C_DL2DFrameWorkCore;

private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkScene	(void){}
	~C_DL2DFrameWorkScene	(void){}
	C_DL2DFrameWorkScene	(const C_DL2DFrameWorkScene &){}

public:
	void Initialize	(void);
	void Termiante	(void);

	template <class SCENE_CLASS_NAME>
	SCENE_CLASS_NAME* AddScene		(const dlSTRING &scene_Name);
	void	DeleteAllScene			(void);
	void	JumpScene				(const dlSTRING &scene_Name);
	void	ReJump					(void);
	dlBOOL	IsAlreadySettingJump	(void) const;

	dlSTRING			GetCurrentSceneName	(void);
	class C_SceneBase*	GetScene			(const dlSTRING& scene_Name);
	void				SetSceneRelation	(const dlSTRING &parent_Name , const dlSTRING &child_Name);

	void SetSceneValidFlg	(dlBOOL flg);
	void ResetScene			(void);
	
	//ポーズ関連
	void SetPauseScene		(const dlSTRING &scene_Name);
	void BeginSystemPause	(const dlSTRING &scene_Name = "");
	void EndSystemPause		(const dlSTRING &scene_Name = "");

	void SetWaitTime(dlS32 wait_Time);

private:
	C_SceneUpdateNode* _GetSceneUpdateNode(void) const;

private:
	NODE_HANDLE				_update_Node_Handle;	//< シーンの更新を掛けるノードのハンドル
	class C_SceneManager*	_scene_Mng_CP;			//< シーンマネージャ
};

//============================================================================
//! シーンノードの追加
template <class SCENE_CLASS_NAME>
SCENE_CLASS_NAME* C_DL2DFrameWorkScene::AddScene(const dlSTRING& scene_Name)
{
	SCENE_CLASS_NAME* scene_CP = dlNEW SCENE_CLASS_NAME();
	_scene_Mng_CP -> SetObject(scene_CP , scene_Name);
	return scene_CP;
}


}

#endif