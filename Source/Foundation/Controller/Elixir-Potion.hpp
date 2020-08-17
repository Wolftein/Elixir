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

namespace Elixir::Controller::Potion
{
    // (Missing Documentation)
    void Set_Action_Cooldown(uint32_t Cooldown);

    // (Missing Documentation)
    void Set_Action_Delay(uint32_t Delay);

    // (Missing Documentation)
    void Set_Red_Key(uint32_t Key);

    // (Missing Documentation)
    void Set_Red_Type(uint32_t Type);

    // (Missing Documentation)
    void Set_Red_Minimum(uint32_t Minimum);

    // (Missing Documentation)
    void Set_Red_Threshold(uint32_t Threshold);

    // (Missing Documentation)
    void Set_Blue_Key(uint32_t Key);

    // (Missing Documentation)
    void Set_Blue_Type(uint32_t Type);

    // (Missing Documentation)
    void Set_Blue_Minimum(uint32_t Minimum);

    // (Missing Documentation)
    void Set_Blue_Threshold(uint32_t Threshold);

    // (Missing Documentation)
    uint32_t Get_Action_Cooldown();

    // (Missing Documentation)
    uint32_t Get_Action_Delay();

    // (Missing Documentation)
    uint32_t Get_Red_Key();

    // (Missing Documentation)
    uint32_t Get_Red_Type();

    // (Missing Documentation)
    uint32_t Get_Red_Minimum();

    // (Missing Documentation)
    uint32_t Get_Red_Threshold();

    // (Missing Documentation)
    uint32_t Get_Blue_Key();

    // (Missing Documentation)
    uint32_t Get_Blue_Type();

    // (Missing Documentation)
    uint32_t Get_Blue_Minimum();

    // (Missing Documentation)
    uint32_t Get_Blue_Threshold();

    // (Missing Documentation)
    void On_Module_Load(HANDLE File);

    // (Missing Documentation)
    void On_Module_Save(HANDLE File);

    // (Missing Documentation)
    bool On_Module_Tick(uint32_t Time);
}