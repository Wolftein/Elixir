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

#include "Foundation/Controller/Elixir-Item.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   DATA   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Controller::Item
{
    static uint32_t s_Action_Cooldown = 200;
    static uint32_t s_Action_Delay    = 300;
    static uint32_t s_Red_Key         = 0;
    static uint32_t s_Red_Type        = 0;
    static uint32_t s_Red_Minimum     = 25;
    static uint32_t s_Red_Threshold   = 80;
    static uint32_t s_Blue_Key        = 0;
    static uint32_t s_Blue_Type       = 0;
    static uint32_t s_Blue_Minimum    = 200;
    static uint32_t s_Blue_Threshold  = 15;
    static uint16_t s_Food_Location   = 0;
    static uint32_t s_Food_Minimum    = 90;
    static uint16_t s_Drink_Location  = 0;
    static uint32_t s_Drink_Minimum   = 90;
    static bool     s_Drink_Red            = false;
    static bool     s_Drink_Red_Emergency  = false;
    static bool     s_Drink_Blue           = false;
    static bool     s_Drink_Blue_Emergency = false;
    static bool     s_Food                 = false;
    static uint32_t s_Food_Last            = 0;
    static bool     s_Drink                = false;
    static uint32_t s_Drink_Last           = 0;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Controller::Item
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool On_Action(uint32_t Time, uint32_t Type, bool Key)
    {
        if (const uint32_t zLocation = Core::Get_Item(Type); zLocation != 0)
        {
            if (Key)
            {
                return Core::Do_Use(zLocation, false, !Core::Is_Inventory());
            }
            else if (Core::Is_Inventory())
            {
                return Core::Do_Use(zLocation, false, false);
            }
            else
            {
                Core::Do_Mode(true);
            }
            return false;
        }
        return true;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool On_Action(uint32_t Time, uint32_t Location)
    {
        if (const uint32_t zItem = Core::Get_Item_Type(Location); zItem != 0)
        {
            if (Core::Is_Inventory())
            {
                return Core::Do_Use(Location, false, true);
            }
            else
            {
                Core::Do_Mode(true);
            }
            return false;
        }
        return true;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Action_Cooldown(uint32_t Cooldown)
    {
        s_Action_Cooldown = Cooldown;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Action_Delay(uint32_t Delay)
    {
        s_Action_Delay = Delay;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Red_Key(uint32_t Key)
    {
        s_Red_Key = Key;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Red_Type(uint32_t Type)
    {
        s_Red_Type = Type;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Red_Minimum(uint32_t Minimum)
    {
        s_Red_Minimum = Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Red_Threshold(uint32_t Threshold)
    {
        s_Red_Threshold = Threshold;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Blue_Key(uint32_t Key)
    {
        s_Blue_Key = Key;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Blue_Type(uint32_t Type)
    {
        s_Blue_Type = Type;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Blue_Minimum(uint32_t Minimum)
    {
        s_Blue_Minimum = Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Blue_Threshold(uint32_t Threshold)
    {
        s_Blue_Threshold = Threshold;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Food_Location(uint16_t Location)
    {
        s_Food_Location = Location;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Food_Minimum(uint32_t Minimum)
    {
        s_Food_Minimum = Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Drink_Location(uint16_t Location)
    {
        s_Drink_Location = Location;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Set_Drink_Minimum(uint32_t Minimum)
    {
        s_Drink_Minimum = Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Action_Cooldown()
    {
        return s_Action_Cooldown;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Action_Delay()
    {
        return s_Action_Delay;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Red_Key()
    {
        return s_Red_Key;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Red_Type()
    {
        return s_Red_Type;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Red_Minimum()
    {
        return s_Red_Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Red_Threshold()
    {
        return s_Red_Threshold;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Blue_Key()
    {
        return s_Blue_Key;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Blue_Type()
    {
        return s_Blue_Type;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Blue_Minimum()
    {
        return s_Blue_Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Blue_Threshold()
    {
        return s_Blue_Threshold;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint16_t Get_Food_Location()
    {
        return s_Food_Location;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Food_Minimum()
    {
        return s_Food_Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint16_t Get_Drink_Location()
    {
        return s_Drink_Location;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t Get_Drink_Minimum()
    {
        return s_Drink_Minimum;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Module_Load(HANDLE File)
    {
        ::ReadFile(File, & s_Action_Cooldown, sizeof(s_Action_Cooldown), nullptr, nullptr);
        ::ReadFile(File, & s_Action_Delay, sizeof(s_Action_Delay), nullptr, nullptr);
        ::ReadFile(File, & s_Red_Key, sizeof(s_Red_Key), nullptr, nullptr);
        ::ReadFile(File, & s_Red_Minimum, sizeof(s_Red_Minimum), nullptr, nullptr);
        ::ReadFile(File, & s_Red_Threshold, sizeof(s_Red_Threshold), nullptr, nullptr);
        ::ReadFile(File, & s_Blue_Key, sizeof(s_Blue_Key), nullptr, nullptr);
        ::ReadFile(File, & s_Blue_Minimum, sizeof(s_Blue_Minimum), nullptr, nullptr);
        ::ReadFile(File, & s_Blue_Threshold, sizeof(s_Blue_Threshold), nullptr, nullptr);
        ::ReadFile(File, & s_Food_Location, sizeof(s_Food_Location), nullptr, nullptr);
        ::ReadFile(File, & s_Food_Minimum, sizeof(s_Food_Minimum), nullptr, nullptr);
        ::ReadFile(File, & s_Drink_Location, sizeof(s_Drink_Location), nullptr, nullptr);
        ::ReadFile(File, & s_Drink_Minimum, sizeof(s_Drink_Minimum), nullptr, nullptr);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Module_Save(HANDLE File)
    {
        ::WriteFile(File, & s_Action_Cooldown, sizeof(s_Action_Cooldown), nullptr, nullptr);
        ::WriteFile(File, & s_Action_Delay, sizeof(s_Action_Delay), nullptr, nullptr);
        ::WriteFile(File, & s_Red_Key, sizeof(s_Red_Key), nullptr, nullptr);
        ::WriteFile(File, & s_Red_Minimum, sizeof(s_Red_Minimum), nullptr, nullptr);
        ::WriteFile(File, & s_Red_Threshold, sizeof(s_Red_Threshold), nullptr, nullptr);
        ::WriteFile(File, & s_Blue_Key, sizeof(s_Blue_Key), nullptr, nullptr);
        ::WriteFile(File, & s_Blue_Minimum, sizeof(s_Blue_Minimum), nullptr, nullptr);
        ::WriteFile(File, & s_Blue_Threshold, sizeof(s_Blue_Threshold), nullptr, nullptr);
        ::WriteFile(File, & s_Food_Location, sizeof(s_Food_Location), nullptr, nullptr);
        ::WriteFile(File, & s_Food_Minimum, sizeof(s_Food_Minimum), nullptr, nullptr);
        ::WriteFile(File, & s_Drink_Location, sizeof(s_Drink_Location), nullptr, nullptr);
        ::WriteFile(File, & s_Drink_Minimum, sizeof(s_Drink_Minimum), nullptr, nullptr);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bool On_Module_Tick(uint32_t Time)
    {
        if (Core::Is_Alive() && Core::Is_Allowed(Core::Action::Use, s_Action_Cooldown))
        {
            if (Application::Is_Pressed(s_Red_Key))
            {
                s_Drink_Red = false;
                return On_Action(Time, s_Red_Type, false);
            }
            else if (Application::Is_Pressed(s_Blue_Key))
            {
                s_Drink_Blue = false;
                return On_Action(Time, s_Blue_Type, false);
            }
            else
            {
                if (s_Drink_Red || s_Drink_Blue || s_Food || s_Drink)
                {
                    s_Drink_Red  = s_Drink_Red  && (Core::Get_Health() < Core::Get_Health_Maximum());
                    s_Drink_Blue = s_Drink_Blue && (Core::Get_Energy() < Core::Get_Energy_Maximum());
                    s_Food       = s_Food  && (Core::Get_Hunger() < Core::Get_Hunger_Maximum());
                    s_Drink      = s_Drink && (Core::Get_Thirst() < Core::Get_Thirst_Maximum());

                    if (s_Drink_Red)
                    {
                        return On_Action(Time, s_Red_Type, s_Drink_Red_Emergency);
                    }
                    else if (s_Drink_Blue)
                    {
                        return On_Action(Time, s_Blue_Type, s_Drink_Blue_Emergency);
                    }
                    else if (s_Food)
                    {
                        return On_Action(Time, s_Food_Location);
                    }
                    else if (s_Drink)
                    {
                        return On_Action(Time, s_Drink_Location);
                    }
                }
                else
                {
                    if (Core::Get_Health() < (s_Red_Threshold * Core::Get_Health_Maximum()) / 100)
                    {
                        s_Drink_Red = true;
                        s_Drink_Red_Emergency = true;
                        return true;
                    }
                    else if (Core::Get_Energy() < (s_Blue_Threshold * Core::Get_Energy_Maximum()) / 100)
                    {
                        s_Drink_Red = true;
                        s_Drink_Red_Emergency = true;
                        return true;
                    }
                    else if (Core::Get_Health_Maximum() - Core::Get_Health() >= s_Red_Minimum)
                    {
                        s_Drink_Blue = true;
                        s_Drink_Blue_Emergency = false;
                        return true;
                    }
                    else if (Core::Get_Energy_Maximum() - Core::Get_Energy() >= s_Blue_Minimum)
                    {
                        s_Drink_Blue = true;
                        s_Drink_Blue_Emergency = false;
                        return true;
                    }
                    else if (Core::Get_Hunger_Maximum() - Core::Get_Hunger() >= s_Food_Minimum)
                    {
                        s_Food = true;
                        return true;
                    }
                    else if (Core::Get_Thirst_Maximum() - Core::Get_Thirst() >= s_Drink_Minimum)
                    {
                        s_Drink = true;
                        return true;
                    }
                }
            }
        }
        return true;
    }
}