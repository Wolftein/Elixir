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

namespace Elixir::Controller::Item
{
    // -=(Undocumented)=-
    void Set_Action_Cooldown(uint32_t Cooldown);

    // -=(Undocumented)=-
    void Set_Action_Delay(uint32_t Delay);

    // -=(Undocumented)=-
    void Set_Red_Key(uint32_t Key);

    // -=(Undocumented)=-
    void Set_Red_Type(uint32_t Type);

    // -=(Undocumented)=-
    void Set_Red_Minimum(uint32_t Minimum);

    // -=(Undocumented)=-
    void Set_Red_Threshold(uint32_t Threshold);

    // -=(Undocumented)=-
    void Set_Blue_Key(uint32_t Key);

    // -=(Undocumented)=-
    void Set_Blue_Type(uint32_t Type);

    // -=(Undocumented)=-
    void Set_Blue_Minimum(uint32_t Minimum);

    // -=(Undocumented)=-
    void Set_Blue_Threshold(uint32_t Threshold);

    // -=(Undocumented)=-
    void Set_Food_Location(uint16_t Location);

    // -=(Undocumented)=-
    void Set_Food_Minimum(uint32_t Minimum);

    // -=(Undocumented)=-
    void Set_Drink_Location(uint16_t Location);

    // -=(Undocumented)=-
    void Set_Drink_Minimum(uint32_t Minimum);

    // -=(Undocumented)=-
    uint32_t Get_Action_Cooldown();

    // -=(Undocumented)=-
    uint32_t Get_Action_Delay();

    // -=(Undocumented)=-
    uint32_t Get_Red_Key();

    // -=(Undocumented)=-
    uint32_t Get_Red_Type();

    // -=(Undocumented)=-
    uint32_t Get_Red_Minimum();

    // -=(Undocumented)=-
    uint32_t Get_Red_Threshold();

    // -=(Undocumented)=-
    uint32_t Get_Blue_Key();

    // -=(Undocumented)=-
    uint32_t Get_Blue_Type();

    // -=(Undocumented)=-
    uint32_t Get_Blue_Minimum();

    // -=(Undocumented)=-
    uint32_t Get_Blue_Threshold();

    // -=(Undocumented)=-
    uint16_t Get_Food_Location();

    // -=(Undocumented)=-
    uint32_t Get_Food_Minimum();

    // -=(Undocumented)=-
    uint16_t Get_Drink_Location();

    // -=(Undocumented)=-
    uint32_t Get_Drink_Minimum();

    // -=(Undocumented)=-
    void On_Module_Load(HANDLE File);

    // -=(Undocumented)=-
    void On_Module_Save(HANDLE File);

    // -=(Undocumented)=-
    bool On_Module_Tick(uint32_t Time);
}