/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkGamepad.h"
#include <DL_2DFrameWork.h>
#include <FrameWork/Window/DL_2DFrameWorkWindow.h>

#ifdef WIN32
#include <rpc.h>
#pragma comment (lib, "rpcrt4.lib")
#endif

namespace DL
{

//============================================================================
//! 初期化
void C_DL2DFrameWorkGamepad::Initialize(void)
{
	_gamepad_Device_CP = dlNEW C_DirectXPadDevice();
	_gamepad_Device_CP -> CreateDevice(C_DL2DFrameWork::WINDOW -> GetWindowHandle());
}

//============================================================================
//! 初期化
void C_DL2DFrameWorkGamepad::Terminate(void)
{
	dlDELETE _gamepad_Device_CP;
}

//============================================================================
//! 接続されているゲームパッドの本数を取得
dlU32 C_DL2DFrameWorkGamepad::GetConnectGamePadVal(void) const
{
	return _gamepad_Device_CP -> GetConnectGamePadVal();
}

//============================================================================
//! 接続されているゲームパッドのうちどのパッドが有効状態か(何らかのキー、POV、アナログ値がPRS状態)
void C_DL2DFrameWorkGamepad::GetValidPrsGamePadNoList(std::list<dlU32>& out_List) const
{
	const dlU32 pad_Val = _gamepad_Device_CP -> GetConnectGamePadVal();
	for(dlU32 cnt = 0 ; cnt < pad_Val ; ++ cnt)
	{
		if(_gamepad_Device_CP -> IsValidSome(cnt)){out_List.push_back(cnt);}
	}
}

//============================================================================
//! 指定ゲームパッド番号の物で押されているキーボタンを取得
void C_DL2DFrameWorkGamepad::GetValidPadKeyList(dlU32 gamepad_No , std::vector<C_DirectXPadDeviceDefinition::S_KeyInfo>& out_List) const
{
	_gamepad_Device_CP -> GetValidKeyList(gamepad_No , out_List);
}

//============================================================================
//! 指定ゲームパッド番号の物で押されているPOVボタンの情報を取得
void C_DL2DFrameWorkGamepad::GetValidPadPovList(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_PovInfo> &out_List) const
{
	_gamepad_Device_CP -> GetValidPovList(gamepad_Index , out_List);
}

//============================================================================
//! 指定ゲームパッド番号の物で押されているスティックの情報を取得
void C_DL2DFrameWorkGamepad::GetValidPadStickList(dlU32 gamepad_Index , std::vector<C_DirectXPadDeviceDefinition::S_StickInfo> &out_List) const
{
	_gamepad_Device_CP -> GetValidStickList(gamepad_Index , out_List);
}


//============================================================================
//! ジョイスティックの情報を取得
dlBOOL C_DL2DFrameWorkGamepad::GetPadDeviceInfomation(dlU32 gamepad_Index , S_PadDeviceInfomation& out_Info_S) const
{
	if(_gamepad_Device_CP -> GetConnectGamePadVal() <= gamepad_Index){return dlFALSE;}

	LPDIRECTINPUTDEVICE8 device = _gamepad_Device_CP -> GetGamepadDevice(gamepad_Index);
	DIDEVICEINSTANCE device_Info;
	device_Info.dwSize = sizeof(DIDEVICEINSTANCE);
	device -> GetDeviceInfo(&device_Info);

	//種類名の取得
	out_Info_S.product_Name = device_Info.tszProductName;
	
	//ユニーク名の取得
	dlU8* unique_Name = NULL;
	UuidToString(&device_Info.guidInstance , &unique_Name);
	out_Info_S.unique_Name = boost::lexical_cast<dlSTRING>(unique_Name);
	RpcStringFree(&unique_Name);

	//ニュートラル値の取得
	_gamepad_Device_CP -> GetGamepadNeutralList(gamepad_Index , out_Info_S.neutral_List);

	return dlTRUE;
}

//============================================================================
//! デバイスのアクティブ変更
void C_DL2DFrameWorkGamepad::SetActive(dlBOOL window_Active_Flg)
{
	_gamepad_Device_CP -> SetUpdateFlg(window_Active_Flg);
}

//============================================================================
//! ウィンドウのアクティブ変更
dlBOOL C_DL2DFrameWorkGamepad::IsWaitPeriod(void) const
{
	return _gamepad_Device_CP -> IsWaitPeriod();
}

//============================================================================
//! 指定キーが押されているか
dlBOOL C_DL2DFrameWorkGamepad::IsPrsKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kPRS , key_No);
}

//============================================================================
//! 指定キーが押された瞬間か
dlBOOL C_DL2DFrameWorkGamepad::IsTrgKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kTRG , key_No);
}

//============================================================================
//! 指定キーが離された瞬間か
dlBOOL C_DL2DFrameWorkGamepad::IsRlsKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kRLS , key_No);
}

//============================================================================
//! 指定キーがリピート状態か
dlBOOL C_DL2DFrameWorkGamepad::IsRepeatKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kREPEAT , key_No);
}

//============================================================================
//! 指定キーがダブルクリックされたか
dlBOOL C_DL2DFrameWorkGamepad::IsDoubleClickKey(dlU8 key_No) const
{
	return _gamepad_Device_CP -> IsButton(DL::kDOUBLE_CLICK , key_No);
}

//============================================================================
//! 指定キーチェック
dlBOOL C_DL2DFrameWorkGamepad::IsKey(dlU8 key_No , dlS32 state) const
{
	return _gamepad_Device_CP -> IsButton(state , key_No);
}

}