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

namespace Elixir::Controller::Ranger
{
    // -=(Undocumented)=-
    void Set_Action_Cooldown(uint32_t Cooldown);

    // -=(Undocumented)=-
    void Set_Action_Delay(uint32_t Delay);

    // -=(Undocumented)=-
    void Set_Aim_Odds(uint32_t Odds);

    // -=(Undocumented)=-
    void Set_Aim_Key(uint32_t Key);

    // -=(Undocumented)=-
    void Set_Aim_Location(uint16_t Location);

    // -=(Undocumented)=-
    uint32_t Get_Action_Cooldown();

    // -=(Undocumented)=-
    uint32_t Get_Action_Delay();

    // -=(Undocumented)=-
    uint32_t Get_Aim_Odds();

    // -=(Undocumented)=-
    uint32_t Get_Aim_Key();

    // -=(Undocumented)=-
    uint16_t Get_Aim_Location();

    // -=(Undocumented)=-
    void On_Module_Load(HANDLE File);

    // -=(Undocumented)=-
    void On_Module_Save(HANDLE File);

    // -=(Undocumented)=-
    bool On_Module_Tick(uint32_t Time);
}