#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
//#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui_internal.h"
#include "imgui_impl_win32.h"

namespace ImGui {
	bool Hotkey(const char * label, int * k, const ImVec2 & size_arg = ImVec2(0, 0));
}