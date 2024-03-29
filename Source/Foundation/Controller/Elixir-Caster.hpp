// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2016-2021 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Foundation/Core/Elixir-Character.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Controller::Caster
{
    // -=(Undocumented)=-
    void Set_Action_Cooldown(uint32_t Cooldown);

    // -=(Undocumented)=-
    void Set_Action_Delay(uint32_t Delay);

    // -=(Undocumented)=-
    void Set_Aim_Odds(uint32_t Odds);

    // -=(Undocumented)=-
    void Set_Aim_Key(uint32_t ID, uint32_t Key);

    // -=(Undocumented)=-
    void Set_Aim_Location(uint32_t ID, uint16_t Location);

    // -=(Undocumented)=-
    void Set_Aim_Macro(uint32_t ID, bool Macro);

    // -=(Undocumented)=-
    void Set_Aim_Self(uint32_t ID, bool Self);

    // -=(Undocumented)=-
    bool Set_Aim_Target(uint16_t X, uint16_t Y, bool Upward);

    // -=(Undocumented)=-
    void Set_Remove_Text(bool Active);

    // -=(Undocumented)=-
    bool Get_Remove_Text();

    // -=(Undocumented)=-
    uint32_t Get_Action_Cooldown();

    // -=(Undocumented)=-
    uint32_t Get_Action_Delay();

    // -=(Undocumented)=-
    uint32_t Get_Aim_Odds();

    // -=(Undocumented)=-
    uint32_t Get_Aim_Key(uint32_t ID);

    // -=(Undocumented)=-
    uint16_t Get_Aim_Location(uint32_t ID);

    // -=(Undocumented)=-
    bool Get_Aim_Macro(uint32_t ID);

    // -=(Undocumented)=-
    bool Get_Aim_Self(uint32_t ID);

    // -=(Undocumented)=-
    uint16_t Get_Aim_Target();

    // -=(Undocumented)=-
    void On_Module_Load(HANDLE File);

    // -=(Undocumented)=-
    void On_Module_Save(HANDLE File);

    // -=(Undocumented)=-
    bool On_Module_Tick(uint32_t Time);
}