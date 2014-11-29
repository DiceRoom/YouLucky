/****************************************************************************/
/* DL_2DFrameWorkWindow.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKWINDOW_H_
#define	DL_2DFRAMEWORKWINDOW_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/

namespace DL
{

//! ウィンドウ管理
class C_DL2DFrameWorkWindow
{
friend class C_DL2DFrameWork;
public:
	//! コールバックの種類
	enum E_CallBackKind
	{
		kCALLBACK_FRAMEWORK	= (1 << 1),		//< フレームワークが行うコールバック
		kCALLBACK_LIBRARY	= (1 << 2),		//< ライブラリが行うコールバック
		kCALLBACK_OTHER		= (1 << 3),		//< その他コールバック
	};

	//! コールバックの返り値の種類
	enum E_ReturnCallBack
	{
		kNOT_PROC				= 0,
		
		kONLY_FRAMEWORK			= kCALLBACK_LIBRARY,
		kONLY_LIBRARY			= kCALLBACK_LIBRARY,
		kONLY_OTHER				= kCALLBACK_OTHER,

		kFRAMEWORK_AND_LIBRARY	= kCALLBACK_FRAMEWORK | kCALLBACK_LIBRARY,
		kFRAMEWORK_AND_OTHER	= kCALLBACK_FRAMEWORK | kCALLBACK_OTHER,
		kLIBRARY_AND_OTHER		= kCALLBACK_LIBRARY | kCALLBACK_OTHER,

		kALL_PROC				= kCALLBACK_FRAMEWORK | kCALLBACK_LIBRARY | kCALLBACK_OTHER,
	};

	typedef dlCALLBACK<dlBOOL (void)>										C_CloseWindowCallback;
	typedef dlCALLBACK<E_ReturnCallBack (HWND , dlU32 , WPARAM , LPARAM)>	C_MessageCallback;

private:
	C_DL2DFrameWorkWindow	(void){};
	~C_DL2DFrameWorkWindow	(void){};
	C_DL2DFrameWorkWindow	(const C_DL2DFrameWorkWindow &){};

public:
	void	Initialize				(dlU16 wnd_W_Size , dlU16 wnd_H_Size , const dlSTRING& wnd_Name , void (*game_Proc_P)(void));
	void	Terminate				(void);
	dlU32	DispDialog				(const dlSTRING& title , const dlSTRING& text , dlU32 type = MB_OK);
	void	AddCallBack				(dlS32 priority , C_MessageCallback callback_Proc_P);
	void	EraseCallBack			(dlS32 priority);
	void	SetCloseWindowCallback	(const C_CloseWindowCallback& close_Callback);

	HWND	GetWindowHandle	(void) const;

	void		SetWindowPosition(const S_IntVec2& pos_S);
	S_IntVec2	GetWindowPosition(void) const;

private:
	ACS_MEB(private , S_IntVec2 , _window_Size_Int32_S , WindowIntSize);	//< ウィンドウサイズ(dlINT32)
	ACS_MEB(private , S_Vector2 , _window_Size_S , WindowSize);				//< ウィンドウサイズ(dlF32)
	std::map<dlS32 , C_MessageCallback>	_callback_Proc_Map;						//< メッセージが飛んできたときに対応するコールバック関数マップ
};

}

#endif
