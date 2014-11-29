/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_2DFrameWorkUtility.h"
#include <DL_2DFrameWork.h>

namespace DL
{

namespace
{

#ifdef _WIN32
const std::map<dlCHAR , dlSTRING> DIK_NAME_MAP = boost::assign::map_list_of
(DIK_ESCAPE , "ESCAPE")
(DIK_1 , "1")
(DIK_2 , "2")
(DIK_3 , "3")
(DIK_4 , "4")
(DIK_5 , "5")
(DIK_6 , "6")
(DIK_7 , "7")
(DIK_8 , "8")
(DIK_9 , "9")
(DIK_0 , "0")
(DIK_MINUS , "MINUS")
(DIK_EQUALS , "EQUALS")
(DIK_BACK , "BACK")
(DIK_TAB , "TAB")
(DIK_Q , "Q")
(DIK_W , "W")
(DIK_E , "E")
(DIK_R , "R")
(DIK_T , "T")
(DIK_Y , "Y")
(DIK_U , "U")
(DIK_I , "I")
(DIK_O , "O")
(DIK_P , "P")
(DIK_LBRACKET , "LEFT_BRACKET")
(DIK_RBRACKET , "RIGHT_BRACKET")
(DIK_RETURN , "RETURN")
(DIK_LCONTROL , "LEFT_CONTROL")
(DIK_A , "A")
(DIK_S , "S")
(DIK_D , "D")
(DIK_F , "F")
(DIK_G , "G")
(DIK_H , "H")
(DIK_J , "J")
(DIK_K , "K")
(DIK_L , "L")
(DIK_SEMICOLON , "SEMICOLON")
(DIK_APOSTROPHE , "APOSTROPHE")
(DIK_GRAVE , "GRAVE")
(DIK_LSHIFT , "LEFT_SHIFT")
(DIK_BACKSLASH , "BACK_SLASH")
(DIK_Z , "Z")
(DIK_X , "X")
(DIK_C , "C")
(DIK_V , "V")
(DIK_B , "B")
(DIK_N , "N")
(DIK_M , "M")
(DIK_COMMA , "COMMA")
(DIK_PERIOD , "PERIOD")
(DIK_SLASH , "SLASH")
(DIK_RSHIFT , "RIGHT_SHIFT")
(DIK_MULTIPLY , "MULTIPLY")
(DIK_LMENU , "LEFT_MENU")
(DIK_SPACE , "SPACE")
(DIK_CAPITAL , "CAPITAL")
(DIK_F1 , "F1")
(DIK_F2 , "F2")
(DIK_F3 , "F3")
(DIK_F4 , "F4")
(DIK_F5 , "F5")
(DIK_F6 , "F6")
(DIK_F7 , "F7")
(DIK_F8 , "F8")
(DIK_F9 , "F9")
(DIK_F10 , "F10")
(DIK_NUMLOCK , "NUM_LOCK")
(DIK_SCROLL , "SCROLL")
(DIK_NUMPAD7 , "NUM_PAD7")
(DIK_NUMPAD8 , "NUM_PAD8")
(DIK_NUMPAD9 , "NUM_PAD9")
(DIK_SUBTRACT , "SUBTRACT")
(DIK_NUMPAD4 , "NUM_PAD4")
(DIK_NUMPAD5 , "NUM_PAD5")
(DIK_NUMPAD6 , "NUM_PAD6")
(DIK_ADD , "ADD")
(DIK_NUMPAD1 , "NUM_PAD1")
(DIK_NUMPAD2 , "NUM_PAD2")
(DIK_NUMPAD3 , "NUM_PAD3")
(DIK_NUMPAD0 , "NUM_PAD0")
(DIK_DECIMAL , "DECIMAL")
(DIK_OEM_102 , "OEM_102")
(DIK_F11 , "F11")
(DIK_F12 , "F12")
(DIK_F13 , "F13")
(DIK_F14 , "F14")
(DIK_F15 , "F15")
(DIK_KANA , "KANA")
(DIK_ABNT_C1 , "ABNT_C1")
(DIK_CONVERT , "CONVERT")
(DIK_NOCONVERT , "NO_CONVERT")
(DIK_YEN , "YEN")
(DIK_ABNT_C2 , "ABNT_C2")
(DIK_NUMPADEQUALS , "NUM_PADEQUALS")
(DIK_PREVTRACK , "PREVTRACK")
(DIK_AT , "AT")
(DIK_COLON , "COLON")
(DIK_UNDERLINE , "UNDER_LINE")
(DIK_KANJI , "KANJI")
(DIK_STOP , "STOP")
(DIK_AX , "AX")
(DIK_UNLABELED , "UN_LABELED")
(DIK_NEXTTRACK , "NEXT_TRACK")
(DIK_NUMPADENTER , "NUM_PADENTER")
(DIK_RCONTROL , "RIGHT_CONTROL")
(DIK_MUTE , "MUTE")
(DIK_CALCULATOR , "CALCULATOR")
(DIK_PLAYPAUSE , "PLAY_PAUSE")
(DIK_MEDIASTOP , "MEDIA_STOP")
(DIK_VOLUMEDOWN , "VOLUME_DOWN")
(DIK_VOLUMEUP , "VOLUME_UP")
(DIK_WEBHOME , "WEB_HOME")
(DIK_NUMPADCOMMA , "NUM_PADCOMMA")
(DIK_DIVIDE , "DIVIDE")
(DIK_SYSRQ , "SYSRQ")
(DIK_RMENU , "RIGHT_MENU")
(DIK_PAUSE , "PAUSE")
(DIK_HOME , "HOME")
(DIK_UP , "UP")
(DIK_PRIOR , "PAGE_UP")
(DIK_LEFT , "LEFT")
(DIK_RIGHT , "RIGHT")
(DIK_END , "END")
(DIK_DOWN , "DOWN")
(DIK_NEXT , "NEXT")
(DIK_INSERT , "INSERT")
(DIK_DELETE , "DELETE")
(DIK_LWIN , "LEFT_WIN")
(DIK_RWIN , "RIGHT_WIN")
(DIK_APPS , "APP_MENU")
(DIK_POWER , "POWER")
(DIK_SLEEP , "SLEEP")
(DIK_WAKE , "WAKE")
(DIK_WEBSEARCH , "WEB_SEARCH")
(DIK_WEBFAVORITES , "WEB_FAVORITES")
(DIK_WEBREFRESH , "WEB_REFRESH")
(DIK_WEBSTOP , "WEB_STOP")
(DIK_WEBFORWARD , "WEB_FORWARD")
(DIK_WEBBACK , "WEB_BACK")
(DIK_MYCOMPUTER , "MY_COMPUTER")
(DIK_MAIL , "MAIL")
(DIK_MEDIASELECT , "MEDIA_SELECT");

#endif

}

//============================================================================
//! 初期化
void C_DL2DFrameWorkUtility::Initialize(void)
{
	//ランダム初期化
	C_Random::Initialize();
}

//============================================================================
//! 終了処理
void C_DL2DFrameWorkUtility::Terminate(void)
{
}


//============================================================================
//! 0から指定した範囲無いの数値でランダム値を返す
dlS32 C_DL2DFrameWorkUtility::GetRandom(dlS32 random_Area) const
{
	if(random_Area <= 0)
	{
		SystemError(kSYSER_INJ_RANDOM_ARG);
		return -1;
	}

	return C_Random::GetRandom(random_Area);
}

//============================================================================
//! DIKキーから指定番号のキーコードの名前を取得
dlPCSTR C_DL2DFrameWorkUtility::GetDIKKeyName(dlU8 key_No) const
{
#ifdef _WIN32
	static const dlSTRING MISSING = "MISSING_NUMBER";
	const std::map<dlCHAR , dlSTRING>::const_iterator find_Itr = DIK_NAME_MAP.find(key_No);
	return ((find_Itr == DIK_NAME_MAP.end()) ? MISSING.c_str() : find_Itr -> second.c_str());
#else
	return "Not Win32";
#endif
}

//============================================================================
//! 指定数値から文字列を作成
dlSTRING C_DL2DFrameWorkUtility::TransNumberToString(dlS32 number , dlS32 figure /*= 0*/) const
{
	dlSTRING ret_Str = boost::lexical_cast<dlSTRING>(number);	
	for(dlS32 cnt = static_cast<dlS32>(ret_Str.length()) ; cnt < figure ; ++ cnt)
	{
		ret_Str = "0" + ret_Str;
	}
	return ret_Str;
}

}