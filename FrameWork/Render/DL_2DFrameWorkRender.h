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

//!2Dゲーム用フレームワーク(描画関連)
class C_DL2DFrameWorkRender
{
friend class C_DL2DFrameWork;
friend class C_DL2DFrameWorkDrawPrimitive;
friend class C_DL2DFrameWorkText;
friend class C_DL2DFrameWorkImage;
friend class C_RenderUpdateNode;
public:
	//! グリッドの設定
	enum E_DrawGridState
	{
		kGRID_NONE,		//< グリッド表示しない
		kGRID_FIX,		//< カメラの位置に依存しないグリッド表示
		kGRID_FREE,		//< カメラの位置に依存するグリッド表示
	};

private:
	//! 描画ノード情報
	struct S_RenderNodeInfo
	{
		C_RenderCoreNode*	node_CP;				//< ノードアドレス
		dlBOOL				virtual_Flip_Flg;		//< 疑似反転しているかどうか
		dlBOOL				camera_Influence_Flg;	//< カメラの位置に影響するかどうか
		S_Vector2			pos_S;					//< 位置
	};
	
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
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
	NODE_HANDLE					_update_Node_Handle;							//< 更新ハンドル
	std::list<S_RenderNodeInfo> _render_Info_List;								//< 描画リスト(ソート済み)
	std::list<NODE_HANDLE>		_erase_List;									//< このフレームは描画してから削除したい時用のリスト
	struct S_GridInfo*			_grid_Info_SP;									//< グリッド情報
	dlBOOL						_change_Virtual_Camera_Flg;						//< 疑似カメラの位置が変更された
	ACS_G_MEB(private , S_Vector2 , _virtual_Camera_Pos_S , VirtualCameraPos);	//< 疑似カメラ位置
};

//============================================================================
//! 描画リストへ追加
template<class RENDER_NODE>
RENDER_NODE* C_DL2DFrameWorkRender::_Add(dlS32 depth , dlBOOL virtual_Flip_Flg)
{
	RENDER_NODE* new_CP = dlNEW RENDER_NODE();
	NODE_HANDLE handle = _GetUseAbletHandle();
	
	//初期設定
	new_CP -> SetHandle(handle);
	new_CP -> SetPriority(depth);

	//初期化
	new_CP -> Initialize();

	//リストに入れる
	_InsertNode(new_CP , virtual_Flip_Flg);

	return new_CP;
}

}

#endif