// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
#pragma once
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <wrl/client.h>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

//Direct X Tex
#include "../DirectXTex/DirectXTex.h"

//ImGUI
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_win32.h"
#include "../ImGUI/imgui_impl_dx11.h"

// FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib,"fmod_vc.lib")

// DirectWrite
#include <d2d1_1.h>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

using namespace std;
using namespace DirectX;

// Device
#include "Framework/Device/Device.h"

#include "Types.h"

// Utility
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/tinyxml2.h"
#include "Framework/Utility/Audio.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/DirectWrite.h"


// Render
#include "Framework/Render/VertexLayOut.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"

// Math
#include "Framework/Math/MathUtility.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/Collider.h"
#include "Framework/Math/RectCollider.h"
#include "Framework/Math/CircleCollider.h"

// Camera
#include "Framework/Camera/Camera.h"

// Texture
#include "Framework/Texture/SRV.h"
#include "Framework/Texture/SamplerState.h"
#include "Framework/Texture/BlendState.h"
#include "Framework/Texture/StateManager.h"
#include "Framework/Texture/SRVManager.h"

// Animation
#include "Framework/Animation/Action.h"
#include "Framework/Utility/MyXML.h"

// BagicObj
#include "Object/BasicObject/Quad.h"
#include "Object/BasicObject/Sprite.h"
#include "Object/BasicObject/Effect.h"
#include "Object/BasicObject/EffectManager.h"

// UI
#include "Framework/Utility/Button.h"

// Bro_Potato
#include "Object/GameObject/Brotato/UI/Bro_BackGround.h"
#include "Object/GameObject/Brotato/UI/Bro_Resource.h"
#include "Object/GameObject/Brotato/UI/Bro_icon.h"


#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_Player_Gun.h"
#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_Player_RailGun.h"
#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_Player_SMG.h"

#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_Player_Bullet.h"
#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_player_Bullet_Rail.h"
#include "Object/GameObject/Brotato/Player/Player_Guns/Bro_Player_Bullet_SMG.h"


#include "Object/GameObject/Brotato/Player/Bro_Player.h"
#include "Object/GameObject/Brotato/Monster/Bro_Monster.h"

#include "Object/GameObject/Brotato/UI/Store_menu.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/Brotato/First_Scene.h"
#include "Scene/Brotato/BrotatoScene.h"
#include "Scene/Brotato/Brotato_Store.h"
#include "Scene/Brotato/Instancing_Test.h"
#include "Scene/SceneManager.h"

// Program
#include "Program/Program.h"

extern Vector2 mousePos;

using CallBack = std::function<void()>;