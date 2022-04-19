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

#include "Foundation/Core/Elixir-Executor.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Core
{
    // -=(Undocumented)=-
    uint32_t Get_Energy();

    // -=(Undocumented)=-
    uint32_t Get_Energy_Maximum();

    // -=(Undocumented)=-
    uint32_t Get_Experience();

    // -=(Undocumented)=-
    uint32_t Get_Experience_Maximum();

    // -=(Undocumented)=-
    uint32_t Get_Gold();

    // -=(Undocumented)=-
    uint32_t Get_Health();

    // -=(Undocumented)=-
    uint32_t Get_Health_Maximum();

    // -=(Undocumented)=-
    uint32_t Get_Hunger();

    // -=(Undocumented)=-
    uint32_t Get_Hunger_Maximum();

    // -=(Undocumented)=-
    uint32_t Get_Level();

    // -=(Undocumented)=-
    Entity * Get_Possession();

    // -=(Undocumented)=-
    uint32_t Get_Stamina();

    // -=(Undocumented)=-
    uint32_t Get_Stamina_Maximum();

    // -=(Undocumented)=-
    uint32_t Get_Thirst();

    // -=(Undocumented)=-
    uint32_t Get_Thirst_Maximum();

    // -=(Undocumented)=-
    uint16_t Get_Item(uint16_t Type);

    // -=(Undocumented)=-
    uint16_t Get_Item(uint16_t Type, uint16_t Type_2);

    // -=(Undocumented)=-
    uint16_t Get_Item_Type(uint8_t Position);

    // -=(Undocumented)=-
    uint32_t Get_Item_Quantity(uint8_t Position);

    // -=(Undocumented)=-
    uint16_t Get_Spell(uint8_t Position);

    // -=(Undocumented)=-
    uint16_t Get_Spell_Selected();

    // -=(Undocumented)=-
    void Update_Energy(uint32_t Energy);

    // -=(Undocumented)=-
    void Update_Energy_Maximum(uint32_t Energy);

    // -=(Undocumented)=-
    void Update_Experience(uint32_t Experience);

    // -=(Undocumented)=-
    void Update_Experience_Maximum(uint32_t Experience);

    // -=(Undocumented)=-
    void Update_Gold(uint32_t Gold);

    // -=(Undocumented)=-
    void Update_Health(uint32_t Health);

    // -=(Undocumented)=-
    void Update_Health_Maximum(uint32_t Health);

    // -=(Undocumented)=-
    void Update_Hunger(uint32_t Hunger);

    // -=(Undocumented)=-
    void Update_Hunger_Maximum(uint32_t Hunger);

    // -=(Undocumented)=-
    void Update_Level(uint32_t Level);

    // -=(Undocumented)=-
    void Update_Possession(uint32_t Possession);

    // -=(Undocumented)=-
    void Update_Stamina(uint32_t Stamina);

    // -=(Undocumented)=-
    void Update_Stamina_Maximum(uint32_t Stamina);

    // -=(Undocumented)=-
    void Update_Thirst(uint32_t Thirst);

    // -=(Undocumented)=-
    void Update_Thirst_Maximum(uint32_t Thirst);

    // -=(Undocumented)=-
    void Update_Mode(bool Inventory);

    // -=(Undocumented)=-
    void Update_Item(uint16_t Position, uint16_t Type, uint32_t Quantity);

    // -=(Undocumented)=-
    void Update_Item_Position(uint16_t Source, uint16_t Destination);

    // -=(Undocumented)=-
    void Update_Spell(uint16_t Position, uint16_t Type);

    // -=(Undocumented)=-
    void Update_Spell_Slot(uint16_t Source, uint16_t Destination);

    // -=(Undocumented)=-
    void Update_Spell_Selected(uint16_t Spell);

    // -=(Undocumented)=-
    void Update_Cooldown(Action Type, uint32_t Time);

    // -=(Undocumented)=-
    void Update_Clickable(bool Clickeable);

    // -=(Undocumented)=-
    bool Is_Alive();

    // -=(Undocumented)=-
    bool Is_Allowed(Action Type, uint32_t Delay);

    // -=(Undocumented)=-
    bool Is_Range(Entity * Other);

    // -=(Undocumented)=-
    bool Is_Inventory();

    // -=(Undocumented)=-
    bool Is_Clickable();

    // -=(Undocumented)=-
    bool Do_Mode(bool Inventory);

    // -=(Undocumented)=-
    bool Do_Use(uint32_t Slot, bool Cursor, bool Key);

    // -=(Undocumented)=-
    bool Do_Cast(uint32_t Slot, bool Cursor);

    // -=(Undocumented)=-
    bool Do_Click(uint32_t X, uint32_t Y, Attack Type);

    // -=(Undocumented)=-
    bool Do_Rotate(Direction Heading);
}