/****************************************************************************/
/* DL_2DFrameWorkCore.h														*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKCORE_H_
#define	DL_2DFRAMEWORKCORE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/
namespace DL
{

typedef dlCALLBACK<void (void)> RENDER_CALLBACK;

//! 2Dゲーム用フレームワーク(システム)
class C_DL2DFrameWorkCore
{
public:
	void	Initialize	(void);
	void	Terminate	(void);
	dlBOOL	CheckWait	(void);
	void	Render		(void);

	void SetRenderCallback			(const RENDER_CALLBACK& render_Callback);
	void SetRenderDefaultCallback	(void);

private:
	void	_LoadDLL		(void);
	dlBOOL	_LoadLibrary	(const dlSTRING& library_File_Name);
	void	_Render			(void);

private:
	ACS_B_MEB(private , _window_Active_Flg , ActiveFlg);	//< 現在ウィンドウがアクティブかどうか
	ACS_MEB(private , dlS32 , _wait_Frame , SlowTime);		//< 何フレームに1度動くか
	dlS32 _wait_Count;										//< カウンター用
	RENDER_CALLBACK _render_Callback;						//< 描画用コールバックアドレス

#ifdef WIN32
	//! DirectXのデバイス
	ACS_G_MEB(private , C_DirectXDevice* , _dx_Device_CP , DirectXDevice);
	std::list<HMODULE>	_load_DLL_List;						//< ロードしたDLLのリスト
#endif
};

}

#endif
