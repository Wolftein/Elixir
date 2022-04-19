// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2016-2021 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Foundation/Core/Elixir-Chunk.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   DATA   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Core
{
    static uint32_t            s_Area_Min_X;
    static uint32_t            s_Area_Min_Y;
    static uint32_t            s_Area_Max_X;
    static uint32_t            s_Area_Max_Y;
    static std::vector<Object> s_Objects;
    static std::vector<Entity> s_Entities;
    static std::mutex          s_Entities_Lock;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Core
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool Check_Object(const Object & Object)
    {
#ifdef SETTING_AREA
        const uint32_t zX = Object.X;
        const uint32_t zY = Object.Y;

        return (zX < s_Area_Min_X || zY < s_Area_Min_Y || zX > s_Area_Max_X || zY > s_Area_Max_Y);
#else
        return false;
#endif
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool Check_Entity(const Entity & Entity)
    {
#ifdef SETTING_AREA
        const uint32_t zX = Entity.X;
        const uint32_t zY = Entity.Y;

        if (Entity.Owned)
        {
            return false;
        }
        return (zX < s_Area_Min_X || zY < s_Area_Min_Y || zX > s_Area_Max_X || zY > s_Area_Max_Y);
#else
        return false;
#endif
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Entity * Create_Entity(uint16_t ID, uint16_t X, uint16_t Y)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        return & s_Entities.emplace_back(Entity { ID, X, Y, 0, 0, L"?", L"", false, false });
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Entity * Find_Entity(uint16_t ID)
    {
        const auto zFilter = [ID](const Entity & Other)
        {
            return (Other.ID == ID);
        };
        return Find_Entity(zFilter);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Entity * Find_Entity(std::function<bool(const Entity &)> Filter)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        if (auto zIterator = std::find_if(s_Entities.begin(), s_Entities.end(), std::move(Filter)); zIterator != s_Entities.end())
        {
            return &* zIterator;
        }
        return nullptr;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Entity * Find_Entity(uint16_t X, uint16_t Y)
    {
        const auto zFilter = [X, Y](const Entity & Other)
        {
            return (Other.X == X && Other.Y == Y);
        };
        return Find_Entity(zFilter);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Update_Entity_Name(Entity * Entity, std::wstring_view Name)
    {
        auto zMarker = Name.find(L'<');

        if (zMarker != std::wstring_view::npos)
        {
            Name.copy(Entity->Name, zMarker - 1);
            Name.copy(Entity->Faction, Name.length() - zMarker - 2, zMarker + 1);
        }
        else
        {
            Name.copy(Entity->Name, Name.length());
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Update_Area(uint16_t X, uint16_t Y)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        s_Area_Min_X = max(0, (X / SETTING_AREA_X - 1) * SETTING_AREA_X);
        s_Area_Min_Y = max(0, (Y / SETTING_AREA_Y - 1) * SETTING_AREA_Y);
        s_Area_Max_X = min(100, s_Area_Min_X + (SETTING_AREA_X * 3) - 1);
        s_Area_Max_Y = min(100, s_Area_Min_Y + (SETTING_AREA_Y * 3) - 1);

        s_Objects.erase(
            std::remove_if(s_Objects.begin(), s_Objects.end(), Check_Object), s_Objects.end());
        s_Entities.erase(
            std::remove_if(s_Entities.begin(), s_Entities.end(), Check_Entity), s_Entities.end());
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Update_Entity_Position(Entity * Entity, Direction Heading)
    {
        switch (Heading)
        {
        case Direction::North:
            Update_Entity_Position(Entity, Entity->X, Entity->Y - 1);
            break;
        case Direction::South:
            Update_Entity_Position(Entity, Entity->X, Entity->Y + 1);
            break;
        case Direction::East:
            Update_Entity_Position(Entity, Entity->X + 1, Entity->Y);
            break;
        case Direction::West:
            Update_Entity_Position(Entity, Entity->X - 1, Entity->Y);
            break;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Update_Entity_Position(Entity * Entity, uint16_t X, uint16_t Y)
    {
        Entity->X = X;
        Entity->Y = Y;

        if (Check_Entity(* Entity))
        {
            Destroy_Entity(Entity->ID);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Destroy()
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        s_Objects.clear();

        s_Entities.clear();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Destroy_Entity(uint16_t ID)
    {
        const auto zFilter = [ID](const Entity & Other)
        {
            return (Other.ID == ID);
        };
        Destroy_Entity(zFilter);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Destroy_Entity(std::function<bool(const Entity &)> Filter)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        s_Entities.erase(std::remove_if(s_Entities.begin(), s_Entities.end(), std::move(Filter)), s_Entities.end());
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Create_Object(uint16_t ID, uint16_t X, uint16_t Y, uint32_t Stack)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        s_Objects.emplace_back(Object { ID, X, Y, Stack });
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Object * Find_Object(std::function<bool(const Object &)> Filter)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        if (auto zIterator = std::find_if(s_Objects.begin(), s_Objects.end(), std::move(Filter)); zIterator != s_Objects.end())
        {
            return &* zIterator;
        }
        return nullptr;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Object * Find_Object(uint16_t X, uint16_t Y)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        const auto zFilter = [X, Y](const Object & Other)
        {
            return (Other.X == X && Other.Y == Y);
        };

        if (const auto zIterator = std::find_if(s_Objects.begin(), s_Objects.end(), zFilter); zIterator != s_Objects.end())
        {
            return &* zIterator;
        }
        return nullptr;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Destroy_Object(uint16_t X, uint16_t Y)
    {
        const std::lock_guard<std::mutex> zLock(s_Entities_Lock);

        const auto zFilter = [X, Y](const Object & Other)
        {
            return (Other.X == X && Other.Y == Y);
        };
        s_Objects.erase(std::remove_if(s_Objects.begin(), s_Objects.end(), zFilter), s_Objects.end());
    }
}