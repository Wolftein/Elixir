// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2016-2020 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Foundation/Controller/Elixir-Controller.hpp"
#include <imgui_ui.h>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   DATA   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Controller::UI
{
    bool    s_Radar        = true;
    bool    s_Radar_Type_0 = true;
    bool    s_Radar_Type_1 = true;
    bool    s_Radar_Type_2 = true;
    bool    s_Radar_Type_3 = true;
    bool    s_Radar_Type_4 = true;
    int32_t s_Radar_Zoom   = 4;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Controller::UI // TODO this is temporally
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    static bool s_Menu_Active = true;

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void _Window_Render_Radar()
    {
        auto POINT_SCALE = (float) s_Radar_Zoom;
        auto POINT_SCALE_HALF = (float) s_Radar_Zoom / 2;

        ImGui::SetNextWindowSize(ImVec2(50 * POINT_SCALE, 50 * POINT_SCALE));

        if (ImGui::Begin("Radar", & s_Radar, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
        {
            auto zCanvas = ImGui::GetWindowDrawList();
            auto zPosition = ImGui::GetWindowPos();

            if (auto zPlayer = Core::Get_Possession(); zPlayer != nullptr)
            {
                if (s_Radar_Type_4)
                {
                    Core::Find_Object(
                        [POINT_SCALE, POINT_SCALE_HALF, zPosition, zPlayer, zCanvas](const Core::Object & Target)
                        {
                            uint32_t zX = Target.X - (zPlayer->X - 25);
                            uint32_t zY = Target.Y - (zPlayer->Y - 25);

                            zCanvas->AddRect(
                                ImVec2(zPosition.x + zX * POINT_SCALE, zPosition.y + zY * POINT_SCALE),
                                ImVec2(zPosition.x + zX * POINT_SCALE + POINT_SCALE,
                                    zPosition.y + zY * POINT_SCALE + POINT_SCALE),
                                ImColor(139, 69, 19, 255));

                            return false;
                        });
                }

                Core::Find_Entity(
                    [POINT_SCALE, POINT_SCALE_HALF, zPosition, zPlayer, zCanvas](const Core::Entity & Target)
                    {
                        ImColor zColor;
                        uint32_t zX = Target.X - (zPlayer->X - 25);
                        uint32_t zY = Target.Y - (zPlayer->Y - 25);

                        switch (Target.Role)
                        {
                        case 0:
                            if (!s_Radar_Type_0)
                            {
                                return false;
                            }
                            zColor = ImColor(Target.Color);
                            break;
                        case 1:
                            if (!s_Radar_Type_1)
                            {
                                return false;
                            }
                            zColor = ImColor(Target.Color);
                            break;
                        case 2:
                            if (!s_Radar_Type_2)
                            {
                                return false;
                            }
                            zColor = ImColor(Target.Color);
                            break;
                        case 3:
                            if (!s_Radar_Type_3)
                            {
                                return false;
                            }
                            zColor = ImColor(Target.Color);
                            break;
                        default:
                            zColor = ImColor(Target.Color);
                            break;
                        }

                        if (zPlayer->ID == Target.ID)
                        {
                            zColor = ImColor(255, 255, 0, 255);
                            zCanvas->AddCircleFilled(
                                ImVec2(
                                    zPosition.x + 25 * POINT_SCALE + POINT_SCALE_HALF,
                                    zPosition.y + 25 * POINT_SCALE + POINT_SCALE_HALF), POINT_SCALE_HALF,
                                zColor);
                        }
                        else
                        {
                            if (Target.ID == Controller::Caster::Get_Aim_Target())
                            {
                                zCanvas->AddTriangleFilled(
                                    ImVec2(zPosition.x + zX * POINT_SCALE + POINT_SCALE_HALF,
                                        zPosition.y + zY * POINT_SCALE + POINT_SCALE_HALF),
                                    ImVec2(zPosition.x + zX * POINT_SCALE,
                                        zPosition.y + zY * POINT_SCALE + POINT_SCALE),
                                    ImVec2(zPosition.x + zX * POINT_SCALE + POINT_SCALE,
                                        zPosition.y + zY * POINT_SCALE + POINT_SCALE), zColor);
                            }
                            else
                            {
                                zCanvas->AddCircleFilled(
                                    ImVec2(
                                        zPosition.x + zX * POINT_SCALE + POINT_SCALE_HALF,
                                        zPosition.y + zY * POINT_SCALE + POINT_SCALE_HALF), POINT_SCALE_HALF,
                                    zColor);
                            }
                        }
                        return false;
                    });

                zCanvas->AddRect(
                    ImVec2(zPosition.x + (25 - 8) * POINT_SCALE, zPosition.y + (25 - 6) * POINT_SCALE),
                    ImVec2(zPosition.x + (25 + 9) * POINT_SCALE, zPosition.y + (25 + 7) * POINT_SCALE),
                    ImColor(255, 255, 0, 255), 1.0f);

                const ImVec2 zArea1 = ImGui::GetWindowContentRegionMin() + ImVec2(zPosition.x, zPosition.y);
                const ImVec2 zArea2 = ImGui::GetWindowContentRegionMax() + ImVec2(zPosition.x, zPosition.y);

                if (ImGui::IsMouseHoveringRect(zArea1, zArea2))
                {
                    const ImVec2 zMouse = ImGui::GetMousePos();

                    int32_t zLocalX = (int) ((zMouse.x - zPosition.x) / POINT_SCALE);
                    int32_t zLocalY = (int) ((zMouse.y - zPosition.y) / POINT_SCALE);
                    int32_t zTargetX = zLocalX + (zPlayer->X - 25);
                    int32_t zTargetY = zLocalY + (zPlayer->Y - 25);

                    auto zObject = Core::Find_Object([zTargetX, zTargetY](const Core::Object & Object)
                    {
                        return Object.X == zTargetX && Object.Y == zTargetY;
                    });

                    auto zEntity = Core::Find_Entity([zTargetX, zTargetY](const Core::Entity & Entity)
                    {
                        return Entity.X == zTargetX && Entity.Y == zTargetY;
                    });

                    if (zObject != nullptr || zEntity != nullptr)
                    {
                        ImGui::BeginTooltip();
                        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                        if (zObject)
                        {
                            ImGui::Text("%d", zObject->ID);
                        }
                        if (zEntity)
                        {
                            ImGui::Text("%ls", zEntity->Name);
                        }
                        ImGui::PopTextWrapPos();
                        ImGui::EndTooltip();
                    }
                }
            }
        }
        ImGui::End();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void _Window_Render_Menu()
    {
        ImGui::SetNextWindowSize(ImVec2(415, 315));
        ImGui::Begin("Elixir", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
        {
            static int32_t s_Type = 1;

            {
                ImGui::Columns(2);
                ImGui::SetColumnOffset(1, 115.f);

                s_Type = (ImGui::Button("Radar", ImVec2(100.f, 20.f))) ? 1 : s_Type;
                s_Type = (ImGui::Button("Pociones", ImVec2(100.f, 20.f))) ? 2 : s_Type;
                s_Type = (ImGui::Button("Magias", ImVec2(100.f, 20.f))) ? 3 : s_Type;
                s_Type = (ImGui::Button("Cazador", ImVec2(100.f, 20.f))) ? 4 : s_Type;

                ImGui::SetCursorPosY(260);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

                if (ImGui::Button("Guardar", ImVec2(100.f, 20.f)))
                {
                    Controller::On_Save(SETTING_NAME);
                }
                if (ImGui::Button("Salir", ImVec2(100.f, 20.f)))
                {
                    ::ExitProcess(0);
                }
                ImGui::NextColumn();
            }

            switch (s_Type)
            {
            case 1:
                ImGui::Checkbox("Activado", & s_Radar);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::SliderInt("Escalado", & s_Radar_Zoom, 1, 20);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                ImGui::Checkbox("Mostrar NPC", & s_Radar_Type_0);
                ImGui::Checkbox("Mostrar Ciudadanos", & s_Radar_Type_1);
                ImGui::Checkbox("Mostrar Criminales", & s_Radar_Type_2);
                ImGui::Checkbox("Mostrar Neutrales", & s_Radar_Type_3);
                ImGui::Checkbox("Mostrar Objetos", & s_Radar_Type_4);
                break;
            case 2:
            {
                int32_t zCooldown = Controller::Potion::Get_Action_Cooldown();
                int32_t zDelay = Controller::Potion::Get_Action_Delay();

                if (ImGui::SliderInt("Cooldown", & zCooldown, 1, 1000))
                {
                    Controller::Potion::Set_Action_Cooldown(zCooldown);
                }

                if (ImGui::SliderInt("Delay", & zDelay, 1, 1000))
                {
                    Controller::Potion::Set_Action_Delay(zDelay);
                }

                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

                int32_t zBind1 = Controller::Potion::Get_Red_Key();
                int32_t zBind2 = Controller::Potion::Get_Blue_Key();
                int32_t zPriority1 = Controller::Potion::Get_Red_Threshold();
                int32_t zPriority2 = Controller::Potion::Get_Blue_Threshold();
                int32_t zMinimum1 = Controller::Potion::Get_Red_Minimum();
                int32_t zMinimum2 = Controller::Potion::Get_Blue_Minimum();

                if (ImGui::Hotkey("Rojas (Macro)", & zBind1))
                {
                    Controller::Potion::Set_Red_Key(zBind1);
                }
                if (ImGui::SliderInt("Rojas  (Emergencia)", & zPriority1, 0, 100, "%d%%"))
                {
                    Controller::Potion::Set_Red_Threshold(zPriority1);
                }
                if (ImGui::SliderInt("Rojas  (Minimo)", & zMinimum1, 1, 750))
                {
                    Controller::Potion::Set_Red_Minimum(zMinimum1);
                }
                if (ImGui::Hotkey("Azules (Macro)", & zBind2))
                {
                    Controller::Potion::Set_Blue_Key(zBind2);
                }
                if (ImGui::SliderInt("Azules (Emergencia)", & zPriority2, 0, 100, "%d%%"))
                {
                    Controller::Potion::Set_Blue_Threshold(zPriority2);
                }
                if (ImGui::SliderInt("Azules (Minimo)", & zMinimum2, 1, 4000))
                {
                    Controller::Potion::Set_Blue_Minimum(zMinimum2);
                }
            }
                break;
            case 3:
            {
                int32_t zCooldown = Controller::Caster::Get_Action_Cooldown();
                int32_t zDelay = Controller::Caster::Get_Action_Delay();
                int32_t zProbability = Controller::Caster::Get_Aim_Odds();

                if (ImGui::SliderInt("Cooldown", & zCooldown, 1, 1000))
                {
                    Controller::Caster::Set_Action_Cooldown(zCooldown);
                }
                if (ImGui::SliderInt("Delay", & zDelay, 1, 1000))
                {
                    Controller::Caster::Set_Action_Delay(zDelay);
                }
                if (ImGui::SliderInt("Probabilidad", & zProbability, 0, 100))
                {
                    Controller::Caster::Set_Aim_Odds(zProbability);
                }

                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

                bool zAim1 = Controller::Caster::Get_Aim_Macro(0);
                bool zAim2 = Controller::Caster::Get_Aim_Macro(1);
                bool zAim3 = Controller::Caster::Get_Aim_Macro(2);
                bool zAim4 = Controller::Caster::Get_Aim_Macro(3);
                bool zAim5 = Controller::Caster::Get_Aim_Macro(4);
                bool zSelf1 = Controller::Caster::Get_Aim_Self(0);
                bool zSelf2 = Controller::Caster::Get_Aim_Self(1);
                bool zSelf3 = Controller::Caster::Get_Aim_Self(2);
                bool zSelf4 = Controller::Caster::Get_Aim_Self(3);
                bool zSelf5 = Controller::Caster::Get_Aim_Self(4);
                int32_t zBind1 = Controller::Caster::Get_Aim_Key(0);
                int32_t zBind2 = Controller::Caster::Get_Aim_Key(1);
                int32_t zBind3 = Controller::Caster::Get_Aim_Key(2);
                int32_t zBind4 = Controller::Caster::Get_Aim_Key(3);
                int32_t zBind5 = Controller::Caster::Get_Aim_Key(4);
                int32_t zLoct1 = Controller::Caster::Get_Aim_Location(0);
                int32_t zLoct2 = Controller::Caster::Get_Aim_Location(1);
                int32_t zLoct3 = Controller::Caster::Get_Aim_Location(2);
                int32_t zLoct4 = Controller::Caster::Get_Aim_Location(3);
                int32_t zLoct5 = Controller::Caster::Get_Aim_Location(4);

                if (ImGui::Checkbox("##Self_1", & zSelf1))
                {
                    Controller::Caster::Set_Aim_Self(0, zSelf1);
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("##Auto_1", & zAim1))
                {
                    Controller::Caster::Set_Aim_Macro(0, zAim1);
                }
                ImGui::SameLine();
                if (ImGui::Hotkey("Magia 1 (Key)", & zBind1))
                {
                    Controller::Caster::Set_Aim_Key(0, zBind1);
                }
                if (ImGui::SliderInt("##Spell_1", & zLoct1, 1, 20))
                {
                    Controller::Caster::Set_Aim_Location(0, zLoct1);
                }

                if (ImGui::Checkbox("##Self_2", & zSelf2))
                {
                    Controller::Caster::Set_Aim_Self(1, zSelf2);
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("##Auto_2", & zAim2))
                {
                    Controller::Caster::Set_Aim_Macro(1, zAim2);
                }
                ImGui::SameLine();
                if (ImGui::Hotkey("Magia 2 (Key)", & zBind2))
                {
                    Controller::Caster::Set_Aim_Key(1, zBind2);
                }
                if (ImGui::SliderInt("##Spell_2", & zLoct2, 1, 20))
                {
                    Controller::Caster::Set_Aim_Location(1, zLoct2);
                }

                if (ImGui::Checkbox("##Self_3", & zSelf3))
                {
                    Controller::Caster::Set_Aim_Self(2, zSelf3);
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("##Auto_3", & zAim3))
                {
                    Controller::Caster::Set_Aim_Macro(2, zAim3);
                }
                ImGui::SameLine();
                if (ImGui::Hotkey("Magia 3 (Key)", & zBind3))
                {
                    Controller::Caster::Set_Aim_Key(2, zBind3);
                }
                if (ImGui::SliderInt("##Spell_3", & zLoct3, 1, 20))
                {
                    Controller::Caster::Set_Aim_Location(2, zLoct3);
                }

                if (ImGui::Checkbox("##Self_4", & zSelf4))
                {
                    Controller::Caster::Set_Aim_Self(3, zSelf4);
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("##Auto_4", & zAim4))
                {
                    Controller::Caster::Set_Aim_Macro(3, zAim4);
                }
                ImGui::SameLine();
                if (ImGui::Hotkey("Magia 4 (Key)", & zBind4))
                {
                    Controller::Caster::Set_Aim_Key(3, zBind4);
                }
                if (ImGui::SliderInt("##Spell_4", & zLoct4, 1, 20))
                {
                    Controller::Caster::Set_Aim_Location(3, zLoct4);
                }

                if (ImGui::Checkbox("##Self_5", & zSelf5))
                {
                    Controller::Caster::Set_Aim_Self(4, zSelf5);
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("##Auto_5", & zAim5))
                {
                    Controller::Caster::Set_Aim_Macro(4, zAim5);
                }
                ImGui::SameLine();
                if (ImGui::Hotkey("Magia 5 (Key)", & zBind5))
                {
                    Controller::Caster::Set_Aim_Key(4, zBind5);
                }
                if (ImGui::SliderInt("##Spell_5", & zLoct5, 1, 20))
                {
                    Controller::Caster::Set_Aim_Location(4, zLoct5);
                }
            }
                break;
            case 4:
            {
                int32_t zCooldown = Controller::Ranger::Get_Action_Cooldown();
                int32_t zDelay = Controller::Ranger::Get_Action_Delay();
                int32_t zProbability = Controller::Ranger::Get_Aim_Odds();

                if (ImGui::SliderInt("Cooldown", & zCooldown, 1, 1000))
                {
                    Controller::Ranger::Set_Action_Cooldown(zCooldown);
                }
                if (ImGui::SliderInt("Delay", & zDelay, 1, 1000))
                {
                    Controller::Ranger::Set_Action_Delay(zDelay);
                }
                if (ImGui::SliderInt("Probabilidad", & zProbability, 0, 100))
                {
                    Controller::Ranger::Set_Aim_Odds(zProbability);
                }

                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

                int32_t zBind = Controller::Ranger::Get_Aim_Key();
                int32_t zLoct = Controller::Ranger::Get_Aim_Location();

                if (ImGui::Hotkey("Key", & zBind))
                {
                    Controller::Ranger::Set_Aim_Key(zBind);
                }
                if (ImGui::SliderInt("##Location", & zLoct, 1, 20))
                {
                    Controller::Ranger::Set_Aim_Location(zLoct);
                }
            }
                break;
            }
        }
        ImGui::Columns(1);
        ImGui::End();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void _Window_Render()
    {
        if (s_Menu_Active)
        {
            _Window_Render_Menu();

            if (s_Radar)
            {
                _Window_Render_Radar();
            }
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    DWORD __stdcall _Window_Thread(LPVOID)
    {
        if (!ImGui_ImplWin32_Init())
        {
            return 0;
        }

        char szBuffer[MAX_PATH];
        GetWindowsDirectoryA(szBuffer, MAX_PATH);
        ImGui::GetIO().Fonts->AddFontFromFileTTF((std::string(szBuffer) + "\\Fonts\\Tahoma.ttf").c_str(), 12.0f);

#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
#define WORD(v) ImVec4(0.860f, 0.930f, 0.890f, v)

        auto & style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = WORD(0.78f);
        style.Colors[ImGuiCol_TextDisabled] = WORD(0.28f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
        style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
        style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
        style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
        style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
        style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
        style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
        style.Colors[ImGuiCol_Header] = MED(0.76f);
        style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
        style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
        style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
        style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
        style.Colors[ImGuiCol_PlotLines] = WORD(0.63f);
        style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = WORD(0.63f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);

        style.WindowPadding = ImVec2(6, 4);
        style.WindowRounding = 0.0f;
        style.FrameRounding = 3.0f;
        style.IndentSpacing = 6.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 16.0f;
        style.GrabMinSize = 20.0f;
        style.GrabRounding = 2.0f;

        style.WindowTitleAlign.x = 0.50f;

        style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
        style.FrameBorderSize = 0.0f;
        style.WindowBorderSize = 1.0f;

        ImGui_ImplWin32_Loop(_Window_Render);
        return 1;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Module_Load(HANDLE File)
    {
        {
            ::CreateThread(NULL, NULL, _Window_Thread, NULL, NULL, NULL);
        }

        ::ReadFile(File, & s_Radar, sizeof(s_Radar), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Zoom, sizeof(s_Radar_Zoom), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Type_0, sizeof(s_Radar_Type_0), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Type_1, sizeof(s_Radar_Type_1), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Type_2, sizeof(s_Radar_Type_2), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Type_3, sizeof(s_Radar_Type_3), nullptr, nullptr);
        ::ReadFile(File, & s_Radar_Type_4, sizeof(s_Radar_Type_4), nullptr, nullptr);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Module_Save(HANDLE File)
    {
        ::WriteFile(File, & s_Radar, sizeof(s_Radar), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Zoom, sizeof(s_Radar_Zoom), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Type_0, sizeof(s_Radar_Type_0), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Type_1, sizeof(s_Radar_Type_1), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Type_2, sizeof(s_Radar_Type_2), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Type_3, sizeof(s_Radar_Type_3), nullptr, nullptr);
        ::WriteFile(File, & s_Radar_Type_4, sizeof(s_Radar_Type_4), nullptr, nullptr);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool On_Module_Tick(uint32_t Time)
    {
        static uint32_t s_Tick = 0;

        if (Application::Is_Focused() && Time - s_Tick >= 350)
        {
            if (Application::Is_Pressed(VK_INSERT))
            {
                s_Menu_Active = !s_Menu_Active;
                s_Tick = Time;
            }
        }
        return true;
    }
}