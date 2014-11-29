/****************************************************************************/
/* DL_2DFrameWorkMouse.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKMOUSE_H_
#define	DL_2DFRAMEWORKMOUSE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

//!2Dゲーム用フレームワーク(マウス)
class C_DL2DFrameWorkMouse
{	
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkMouse	(void){}
	~C_DL2DFrameWorkMouse	(void){}
	C_DL2DFrameWorkMouse	(const C_DL2DFrameWorkMouse &){}

public:
	void	Initialize	(void);
	void	Terminate	(void);

	dlBOOL	IsPrsLMouse			(void)	const;
	dlBOOL	IsTrgLMouse			(void)	const;
	dlBOOL	IsRlsLMouse			(void)	const;
	dlBOOL	IsRepeatLMouse		(void)	const;
	dlBOOL	IsDoubleClickLMouse	(void)	const;
	dlBOOL	IsLMouse			(dlS32 state) const;

	dlBOOL	IsPrsRMouse			(void)	const;
	dlBOOL	IsTrgRMouse			(void)	const;
	dlBOOL	IsRlsRMouse			(void)	const;
	dlBOOL	IsRepeatRMouse		(void)	const;
	dlBOOL	IsDoubleClickRMouse	(void)	const;
	dlBOOL	IsRMouse			(dlS32 state) const;

	dlBOOL	IsPrsCMouse			(void)	const;
	dlBOOL	IsTrgCMouse			(void)	const;
	dlBOOL	IsRlsCMouse			(void)	const;
	dlBOOL	IsRepeatCMouse		(void)	const;
	dlBOOL	IsDoubleClickCMouse	(void)	const;
	dlBOOL	IsCMouse			(dlS32 state) const;

	dlBOOL	IsMouseKey			(dlS32 key_No , dlS32 state)	const;
	dlBOOL	GetMouseWheelMove	(dlS32& out_Move)				const;
	dlBOOL	GetMousePos			(S_IntVec2& out_Pos_S)			const;

	void SetActive(dlBOOL window_Active_Flg);

private:
	class C_DirectXMouseDevice*	_mouse_Device_CP;	//< マウスデバイス
};

}

#endif
