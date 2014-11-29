/****************************************************************************/
/* DL_2DFrameWorkKeyboard.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKKEYBOARD_H_
#define	DL_2DFRAMEWORKKEYBOARD_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

//! 2Dゲーム用フレームワーク(キーボード)
class C_DL2DFrameWorkKeyboard
{	
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkKeyboard	(void){}
	~C_DL2DFrameWorkKeyboard(void){}
	C_DL2DFrameWorkKeyboard	(const C_DL2DFrameWorkKeyboard &){}

public:
	void	Initialize				(void);
	void	Terminate				(void);

	dlBOOL	IsPrsKey				(dlU8 key_No) const;
	dlBOOL	IsTrgKey				(dlU8 key_No) const;
	dlBOOL	IsRlsKey				(dlU8 key_No) const;
	dlBOOL	IsRepeatKey				(dlU8 key_No) const;
	dlBOOL	IsDoubleClickKey		(dlU8 key_No) const;
	dlBOOL	IsKey					(dlU8 key_No , dlS32 state) const;

	void	GetPrsKeyboardKeyList	(std::list<dlU8>& out_List) const;
	void	SetActive				(dlBOOL window_Active_Flg);

private:
	class C_DirectXKeyboardDevice*	_keyboard_Device_CP;	//< キーボードデバイス
};

}

#endif
