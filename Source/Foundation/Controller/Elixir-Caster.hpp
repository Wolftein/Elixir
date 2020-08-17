// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2016-2020 by Agustin Alvarez. All rights reserved.
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
    // (Missing Documentation)
    void Set_Action_Cooldown(uint32_t Cooldown);

    // (Missing Documentation)
    void Set_Action_Delay(uint32_t Delay);

    // (Missing Documentation)
    void Set_Aim_Odds(uint32_t Odds);

    // (Missing Documentation)
    void Set_Aim_Key(uint32_t ID, uint32_t Key);

    // (Missing Documentation)
    void Set_Aim_Location(uint32_t ID, uint16_t Location);

    // (Missing Documentation)
    void Set_Aim_Macro(uint32_t ID, bool Macro);

    // (Missing Documentation)
    void Set_Aim_Self(uint32_t ID, bool Self);

    // (Missing Documentation)
    bool Set_Aim_Target(uint16_t X, uint16_t Y, bool Upward);

    // (Missing Documentation)
    uint32_t Get_Action_Cooldown();

    // (Missing Documentation)
    uint32_t Get_Action_Delay();

    // (Missing Documentation)
    uint32_t Get_Aim_Odds();

    // (Missing Documentation)
    uint32_t Get_Aim_Key(uint32_t ID);

    // (Missing Documentation)
    uint16_t Get_Aim_Location(uint32_t ID);

    // (Missing Documentation)
    bool Get_Aim_Macro(uint32_t ID);

    // (Missing Documentation)
    bool Get_Aim_Self(uint32_t ID);

    // (Missing Documentation)
    uint16_t Get_Aim_Target();

    // (Missing Documentation)
    void On_Module_Load(HANDLE File);

    // (Missing Documentation)
    void On_Module_Save(HANDLE File);

    // (Missing Documentation)
    bool On_Module_Tick(uint32_t Time);
}