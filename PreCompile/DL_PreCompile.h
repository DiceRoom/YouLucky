/****************************************************************************/
/* DL_PreCompile.h															*/
/****************************************************************************/
#ifndef DL_FRAMEWORK_PRECOMPIL_H_
#define	DL_FRAMEWORK_PRECOMPIL_H_

/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include "../../Library/Common/DL_Common.h"

//ライブラリ
#include "../../Library/Math/DL_Math.h"
#include "../../Library/Random/DL_Random.h"
#include "../../Library/Scene/DL_SceneManager.h"
#include "../../Library/Collision/DL_CollisionManager.h"
#ifdef WIN32
#include "../../Library/Window/DL_Window.h"
#include "../../Library/DirectXDevice/DL_DirectXDevice.h"
#include "../../Library/DirectXInput/DL_DirectXKeyboardDevice.h"
#include "../../Library/DirectXInput/DL_DirectXMouseDevice.h"
#include "../../Library/DirectXInput/DL_DirectXPadDevice.h"
#endif

//山下ライブラリ
#include "../Controller/DL_RenderCore.h"
#include "../Controller/DL_AudioController.h"
#include "../Controller/DL_FontController.h"
#include "../Controller/DL_ImageController.h"
#include "../Controller/DL_TextView.h"
#include "../Controller/DL_MovieController.h"
#include "../Controller/DL_NPlayerController.h"
#include "../Controller/DL_PostEffectController.h"

#endif