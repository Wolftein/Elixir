// dear imgui: Platform Binding for Windows (standard windows API for 32 and 64 bits applications)
// This needs to be used along with a Renderer (e.g. DirectX11, OpenGL3, Vulkan..)

// Implemented features:
//  [X] Platform: Clipboard support (for Win32 this is actually part of core dear imgui)
//  [X] Platform: Mouse cursor shape and visibility. Disable with 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange'.
//  [X] Platform: Keyboard arrays indexed using VK_* Virtual Key Codes, e.g. ImGui::IsKeyPressed(VK_SPACE).
//  [X] Platform: Gamepad support. Enabled with 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad'.

#pragma once
#include "imgui.h"      // IMGUI_IMPL_API

IMGUI_IMPL_API bool     ImGui_ImplWin32_Init();
IMGUI_IMPL_API void     ImGui_ImplWin32_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplWin32_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplWin32_Loop(void ( * Trampoline)());

// Configuration
// - Disable gamepad support or linking with xinput.lib
#define IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
#define IMGUI_IMPL_WIN32_DISABLE_LINKING_XINPUT
