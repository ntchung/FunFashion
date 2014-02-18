// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <assert.h>
#endif

#include <GLES2/gl2.h>

#include "platform/DebugLog.h"
#include "platform/FileUtils.h"

#include "utils/FairyMacros.h"
#include "utils/DynamicArray.h"
#include "utils/Array.h"
#include "utils/List.h"
#include "utils/SharedObject.h"
#include "utils/MemoryPool.h"
#include "utils/ObjectsPool.h"
#include "utils/GameState.h"
#include "utils/String.h"
#include "utils/Stream.h"
#include "utils/MemoryStream.h"
#include "utils/StreamReader.h"

#include "FairyTypes.h"
#include "Resources.h"
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"
#include "FairyHeart.h"
#include "FairyCore.h"

#include "gui/GUI.h"

#endif // __STDAFX_H__
