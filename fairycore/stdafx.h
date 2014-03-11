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
#include <GLES2/gl2ext.h>
#include <math.h>
#include <string.h>

#include "platform/DebugLog.h"
#include "platform/FileUtils.h"

#include "maths/Mathf.h"
#include "maths/Color32.h"
#include "maths/Vector2f.h"
#include "maths/Vector3f.h"
#include "maths/Quaternion.h"
#include "maths/Matrix4x4.h"
#include "maths/Rectf.h"

#include "utils/FairyMacros.h"
#include "utils/PVRTPFXSemantics.h"
#include "utils/DynamicArray.h"
#include "utils/Array.h"
#include "utils/List.h"
#include "utils/SharedObject.h"
#include "utils/MemoryPool.h"
#include "utils/ObjectsPool.h"
#include "utils/GameState.h"
#include "utils/String.h"
#include "utils/ByteArray.h"
#include "utils/RecyclingMemory.h"
#include "utils/Stream.h"
#include "utils/MemoryStream.h"
#include "utils/StreamReader.h"
#include "utils/UIDGenerator.h"

#include "FairyTypes.h"
#include "Resources.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "VertexList.h"
#include "RenderState.h"
#include "RenderBatch.h"
#include "Renderer.h"
#include "Camera.h"
#include "FairyHeart.h"
#include "FairyCore.h"

#include "gui/GUI.h"

#endif // __STDAFX_H__
