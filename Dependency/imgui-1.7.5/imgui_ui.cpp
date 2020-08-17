#include "imgui_ui.h"
#include <windows.h>

void getKeyName(UINT keycode, char * buffer, int size)
{
	if (keycode == VK_LBUTTON)
	{
		strcpy(buffer, "Left Button");
		return;
	} else if (keycode == VK_RBUTTON)
	{
		strcpy(buffer, "Right Button");
		return;
	} else if (keycode == VK_MBUTTON)
	{
		strcpy(buffer, "Middle Button");
		return;
	}else if (keycode == VK_XBUTTON1)
	{
		strcpy(buffer, "X1 Button");
		return;
	} else if (keycode == VK_XBUTTON2)
	{
		strcpy(buffer, "X2 Button");
		return;
	}


	LONG scancode = MapVirtualKey(keycode, MAPVK_VK_TO_VSC);

	// because MapVirtualKey strips the extended bit for some keys
	switch ((UINT)keycode)
	{
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
		case VK_PRIOR:
		case VK_NEXT:
		case VK_END:
		case VK_HOME:
		case VK_INSERT:
		case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK: scancode |= 0x100; break;
	}

	GetKeyNameText(scancode << 16, buffer, size);
}

bool ImGui::Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGui::Text(label);
	ImGui::SameLine();

	char szBuffer[512];
	getKeyName(* k, szBuffer, 512);
	ImGui::Text("[ %s ]", szBuffer);

	if (!ImGui::IsItemHovered())
		return false;

	ImGui::SetTooltip("Presiona una tecla");
	ImGuiIO& io = ImGui::GetIO();
	for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
		if (ImGui::IsKeyPressed(i))
		{
			* k = (i != VK_ESCAPE) ? i : 0;
		}
	}
	for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
		if (ImGui::IsMouseClicked(i))
		{
			switch (i)
			{
				case 0:
					*k = VK_LBUTTON;
					break;
				case 1:
					*k = VK_RBUTTON;
					break;
				case 2:
					*k = VK_MBUTTON;
					break;
				case 3:
					*k = VK_XBUTTON1;
					break;
				case 4:
					*k = VK_XBUTTON2;
					break;
			}
		}
	}
	return true;
}
