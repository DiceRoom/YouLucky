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
//! �t���[�����[�N(�V�[��)
class C_DL2DFrameWorkScene
{	
friend class C_DL2DFrameWork;
friend class C_SceneUpdateNode;
friend class C_DL2DFrameWorkCore;

private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
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
	
	//�|�[�Y�֘A
	void SetPauseScene		(const dlSTRING &scene_Name);
	void BeginSystemPause	(const dlSTRING &scene_Name = "");
	void EndSystemPause		(const dlSTRING &scene_Name = "");

	void SetWaitTime(dlS32 wait_Time);

private:
	C_SceneUpdateNode* _GetSceneUpdateNode(void) const;

private:
	NODE_HANDLE				_update_Node_Handle;	//< �V�[���̍X�V���|����m�[�h�̃n���h��
	class C_SceneManager*	_scene_Mng_CP;			//< �V�[���}�l�[�W��
};

//============================================================================
//! �V�[���m�[�h�̒ǉ�
template <class SCENE_CLASS_NAME>
SCENE_CLASS_NAME* C_DL2DFrameWorkScene::AddScene(const dlSTRING& scene_Name)
{
	SCENE_CLASS_NAME* scene_CP = dlNEW SCENE_CLASS_NAME();
	_scene_Mng_CP -> SetObject(scene_CP , scene_Name);
	return scene_CP;
}


}

#endif