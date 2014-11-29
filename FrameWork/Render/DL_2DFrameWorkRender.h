/****************************************************************************/
/* DL_2DFrameWorkRenderManager.h											*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKRENDERMANAGER_H_
#define	DL_2DFRAMEWORKRENDERMANAGER_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

class C_RenderCoreNode;
class C_DL2DFrameWork;
class C_DL2DFrameWorkDrawPrimitive;
class C_DL2DFrameWorkText;
class C_DL2DFrameWorkImage;
class C_RenderUpdateNode;

//!2D�Q�[���p�t���[�����[�N(�`��֘A)
class C_DL2DFrameWorkRender
{
friend class C_DL2DFrameWork;
friend class C_DL2DFrameWorkDrawPrimitive;
friend class C_DL2DFrameWorkText;
friend class C_DL2DFrameWorkImage;
friend class C_RenderUpdateNode;
public:
	//! �O���b�h�̐ݒ�
	enum E_DrawGridState
	{
		kGRID_NONE,		//< �O���b�h�\�����Ȃ�
		kGRID_FIX,		//< �J�����̈ʒu�Ɉˑ����Ȃ��O���b�h�\��
		kGRID_FREE,		//< �J�����̈ʒu�Ɉˑ�����O���b�h�\��
	};

private:
	//! �`��m�[�h���
	struct S_RenderNodeInfo
	{
		C_RenderCoreNode*	node_CP;				//< �m�[�h�A�h���X
		dlBOOL				virtual_Flip_Flg;		//< �^�����]���Ă��邩�ǂ���
		dlBOOL				camera_Influence_Flg;	//< �J�����̈ʒu�ɉe�����邩�ǂ���
		S_Vector2			pos_S;					//< �ʒu
	};
	
private:
	//�R���X�g���N�^�A�R�s�[�R���X�g���N�^�A�f�X�g���N�^�̋֎~
	C_DL2DFrameWorkRender	(void){};
	~C_DL2DFrameWorkRender	(void){};
	C_DL2DFrameWorkRender	(const C_DL2DFrameWorkRender &){};

public:
	void Initialize	(void);
	void Terminate	(void);

	void	Render					(void);
	void	SetVirtualCameraPos		(const S_Vector2& pos_S);
	dlU32	GetRenderNodeVal		(void) const;
	dlS32	GetRenderKind			(NODE_HANDLE handle) const;
	void	SetCameraInfluenceFlg	(NODE_HANDLE handle , dlBOOL flg);
	void	ValidGrid				(dlS32 state , const S_IntVec2& depth_S , const S_Vector2& split_Size_S , const S_Color& width_Line_Color_S , const S_Color& height_Line_Color_S);
	void	InValidGrid				(void);

private:
	template<class RENDER_NODE> RENDER_NODE* _Add(dlS32 depth , dlBOOL virtual_Flip_Flg);
	dlBOOL	_Erase			(NODE_HANDLE handle);
	void	_ReservateErase	(NODE_HANDLE handle);

	dlBOOL	_IsValidFlg	(NODE_HANDLE handle , dlBOOL& flg) const;
	dlBOOL	_SetValidFlg(NODE_HANDLE handle , dlBOOL flg);
	dlBOOL	_SetPosition(NODE_HANDLE handle , const S_Vector2& pos_S);
	dlBOOL	_ChangeDepth(NODE_HANDLE handle , dlS32 depth);

	void	_ResetPosition		(void);
	void	_ResetGridPosition	(void);
	void	_EraseReservation	(void);

	C_RenderCoreNode*	_GetNodeAddress	(NODE_HANDLE handle) const;
	dlBOOL				_GetPosition	(NODE_HANDLE handle , S_Vector2& out_Pos_S);
	dlBOOL				_IsVirtualFlip	(NODE_HANDLE handle , dlBOOL& flip_Flg);

	void		_InsertNode			(C_RenderCoreNode* node_CP , dlBOOL virtual_Flip_Flg);
	NODE_HANDLE	_GetUseAbletHandle	(void);
	void		_GetImageHandleList	(std::vector<NODE_HANDLE>& out_List);
	S_Vector2	_GetYFlipPosition	(const S_Vector2& pos_S , dlBOOL camera_Influence_Flg) const;

private:
	NODE_HANDLE					_update_Node_Handle;							//< �X�V�n���h��
	std::list<S_RenderNodeInfo> _render_Info_List;								//< �`�惊�X�g(�\�[�g�ς�)
	std::list<NODE_HANDLE>		_erase_List;									//< ���̃t���[���͕`�悵�Ă���폜���������p�̃��X�g
	struct S_GridInfo*			_grid_Info_SP;									//< �O���b�h���
	dlBOOL						_change_Virtual_Camera_Flg;						//< �^���J�����̈ʒu���ύX���ꂽ
	ACS_G_MEB(private , S_Vector2 , _virtual_Camera_Pos_S , VirtualCameraPos);	//< �^���J�����ʒu
};

//============================================================================
//! �`�惊�X�g�֒ǉ�
template<class RENDER_NODE>
RENDER_NODE* C_DL2DFrameWorkRender::_Add(dlS32 depth , dlBOOL virtual_Flip_Flg)
{
	RENDER_NODE* new_CP = dlNEW RENDER_NODE();
	NODE_HANDLE handle = _GetUseAbletHandle();
	
	//�����ݒ�
	new_CP -> SetHandle(handle);
	new_CP -> SetPriority(depth);

	//������
	new_CP -> Initialize();

	//���X�g�ɓ����
	_InsertNode(new_CP , virtual_Flip_Flg);

	return new_CP;
}

}

#endif