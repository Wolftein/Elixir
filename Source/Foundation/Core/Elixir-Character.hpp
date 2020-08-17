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

#include "Foundation/Core/Elixir-Executor.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Core
{
    // (Missing Documentation)
    uint32_t Get_Energy();

    // (Missing Documentation)
    uint32_t Get_Energy_Maximum();

    // (Missing Documentation)
    uint32_t Get_Experience();

    // (Missing Documentation)
    uint32_t Get_Experience_Maximum();

    // (Missing Documentation)
    uint32_t Get_Gold();

    // (Missing Documentation)
    uint32_t Get_Health();

    // (Missing Documentation)
    uint32_t Get_Health_Maximum();

    // (Missing Documentation)
    uint32_t Get_Hunger();

    // (Missing Documentation)
    uint32_t Get_Hunger_Maximum();

    // (Missing Documentation)
    uint32_t Get_Level();

    // (Missing Documentation)
    Entity * Get_Possession();

    // (Missing Documentation)
    uint32_t Get_Stamina();

    // (Missing Documentation)
    uint32_t Get_Stamina_Maximum();

    // (Missing Documentation)
    uint32_t Get_Thirst();

    // (Missing Documentation)
    uint32_t Get_Thirst_Maximum();

    // (Missing Documentation)
    uint16_t Get_Item(uint16_t Type);

    // (Missing Documentation)
    uint16_t Get_Item_Type(uint8_t Position);

    // (Missing Documentation)
    uint32_t Get_Item_Quantity(uint8_t Position);

    // (Missing Documentation)
    uint16_t Get_Spell(uint8_t Position);

    // (Missing Documentation)
    uint16_t Get_Spell_Selected();

    // (Missing Documentation)
    void Update_Energy(uint32_t Energy);

    // (Missing Documentation)
    void Update_Energy_Maximum(uint32_t Energy);

    // (Missing Documentation)
    void Update_Experience(uint32_t Experience);

    // (Missing Documentation)
    void Update_Experience_Maximum(uint32_t Experience);

    // (Missing Documentation)
    void Update_Gold(uint32_t Gold);

    // (Missing Documentation)
    void Update_Health(uint32_t Health);

    // (Missing Documentation)
    void Update_Health_Maximum(uint32_t Health);

    // (Missing Documentation)
    void Update_Hunger(uint32_t Hunger);

    // (Missing Documentation)
    void Update_Hunger_Maximum(uint32_t Hunger);

    // (Missing Documentation)
    void Update_Level(uint32_t Level);

    // (Missing Documentation)
    void Update_Possession(uint32_t Possession);

    // (Missing Documentation)
    void Update_Stamina(uint32_t Stamina);

    // (Missing Documentation)
    void Update_Stamina_Maximum(uint32_t Stamina);

    // (Missing Documentation)
    void Update_Thirst(uint32_t Thirst);

    // (Missing Documentation)
    void Update_Thirst_Maximum(uint32_t Thirst);

    // (Missing Documentation)
    void Update_Mode(bool Inventory);

    // (Missing Documentation)
    void Update_Item(uint16_t Position, uint16_t Type, uint32_t Quantity);

    // (Missing Documentation)
    void Update_Item_Position(uint16_t Source, uint16_t Destination);

    // (Missing Documentation)
    void Update_Spell(uint16_t Position, uint16_t Type);

    // (Missing Documentation)
    void Update_Spell_Position(uint16_t Source, uint16_t Destination);

    // (Missing Documentation)
    void Update_Spell_Selected(uint16_t Spell);

    // (Missing Documentation)
    void Update_Cooldown(Action Type, uint32_t Time);

    // (Missing Documentation)
    void Update_Clickable(bool Clickeable);

    // (Missing Documentation)
    bool Is_Alive();

    // (Missing Documentation)
    bool Is_Allowed(Action Type, uint32_t Delay);

    // (Missing Documentation)
    bool Is_Range(Entity * Other);

    // (Missing Documentation)
    bool Is_Inventory();

    // (Missing Documentation)
    bool Is_Clickable();

    // (Missing Documentation)
    bool Do_Mode(bool Inventory);

    // (Missing Documentation)
    bool Do_Use(uint32_t Slot, bool Key);

    // (Missing Documentation)
    bool Do_Cast(uint32_t Slot, bool Cursor);

    // (Missing Documentation)
    bool Do_Click(uint32_t X, uint32_t Y, Attack Type);
}