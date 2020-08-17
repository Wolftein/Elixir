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

#include "Foundation/Kernel/Elixir-Application.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Core
{
    //
    // Enumerates {@see Entity}'s click's mode.
    //
    enum class Attack
    {
        Bow, Spell
    };

    //
    // Enumerates {@see Entity}'s action.
    //
    enum class Action
    {
        Mode, Use, Cast, Click
    };

    //
    // Enumerates {@see Entity}'s direction.
    //
    enum class Direction
    {
        North = 0x01, East = 0x02, South = 0x03, West = 0x04
    };

    //
    // An entity is something that exists in the game world.
    //
    struct Entity
    {
        uint16_t ID;
        uint16_t X;
        uint16_t Y;
        uint32_t Role;
        uint32_t Color;
        wchar_t  Name[64];
        wchar_t  Faction[64];
        bool     Dead;
        bool     Owned;
    };

    //
    // An entity is something that exists in the game world.
    //
    struct Object
    {
        uint16_t ID;
        uint16_t X;
        uint16_t Y;
    };

    //
    // Create a new {@see Entity}.
    //
    // \param ID the entity's id
    // \param X  the entity's x coordinate
    // \param Y  the entity's y coordinate
    //
    Entity * Create_Entity(uint16_t ID, uint16_t X, uint16_t Y);

    //
    // Find an entity with the given id.
    //
    // \param ID the entity's id
    //
    // \return the entity with the given id, or nullptr
    //
    Entity * Find_Entity(uint16_t ID);

    //
    // Find an entity.
    //
    // \param Filter the filter of the search
    //
    // \return the entity that matches the given criteria, or nullptr
    //
    Entity * Find_Entity(std::function<bool(const Entity &)> Filter);

    //
    // Find an entity with the given coordinates.
    //
    // \param X  the entity's x coordinate
    // \param Y  the entity's y coordinate
    //
    // \return the entity with the given id, or nullptr
    //
    Entity * Find_Entity(uint16_t X, uint16_t Y);

    //
    // Update the area.
    //
    void Update_Area(uint16_t X, uint16_t Y);

    //
    // Update the name of the given {@see Entity}.
    //
    void Update_Entity_Name(Entity * Entity, std::wstring_view Name);

    //
    // Update the position of the given {@see Entity} by the given {@see Direction}.
    //
    void Update_Entity_Position(Entity * Entity, Direction Heading);

    //
    // Update the position of the given {@see Entity}.
    //
    void Update_Entity_Position(Entity * Entity, uint16_t X, uint16_t Y);

    //
    // Destroy all {@see Entity}s.
    //
    void Destroy();

    //
    // Destroy the entity with the given id.
    //
    // @param ID the entity's id
    //
    void Destroy_Entity(uint16_t ID);

    //
    // Destroy the entity with the given filter.
    //
    // @param ID the entity's id
    //
    void Destroy_Entity(std::function<bool(const Entity &)> Filter);

    //
    // Create a new object in the ground.
    //
    // \param ID the object's id
    // \param X  the object's x coordinate
    // \param Y  the object's y coordinate
    //
    void Create_Object(uint16_t ID, uint16_t X, uint16_t Y);

    //
    // Find an entity.
    //
    // \param Filter the filter of the search
    //
    // \return the entity that matches the given criteria, or nullptr
    //
    Object * Find_Object(std::function<bool(const Object &)> Filter);

    //
    // Destroy the entity with the given id.
    //
    // \param X  the object's x coordinate
    // \param Y  the object's y coordinate
    //
    void Destroy_Object(uint16_t X, uint16_t Y);
}