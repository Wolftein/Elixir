// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2016-2020 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the Apache License, Version 2.0.
//
// See <https://opensource.org/licenses/Apache-2.0>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Foundation/Controller/Elixir-Controller.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   DATA   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Factory
{
    static Memory::Detour s_Detour_1;
    static Memory::Detour s_Detour_2;
    static Memory::Detour s_Detour_3;
    static uint32_t     * s_Address_1;
    static uint32_t     * s_Address_2;
    static uint32_t       s_Address_3;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Factory
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _Reader_Length(uint32_t Address)
    {
        return * (uint32_t *) (Address + 0x3C);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _Reader_Peek(uint32_t Address)
    {
        return static_cast<uint8_t *>((* (SAFEARRAY **) (Address + 0x34))->pvData);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void _Writer_Push(uint32_t Value)
    {
        * (_Reader_Peek(* s_Address_2) + _Reader_Length(* s_Address_2)) = Value & 0xFF;

        * (uint32_t *) (* s_Address_2 + 0x3C) = _Reader_Length(* s_Address_2) + 1;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void _Writer_Push(const char * Buffer, uint32_t Count)
    {
        for (int i = 0; i < Count; ++i)
        {
            _Writer_Push(Buffer[i]);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _I_08(const uint8_t * Data, uint32_t Position)
    {
        return static_cast<uint8_t>(* (Data + Position) & 0xFF);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _I_16(const uint8_t * Data, uint32_t Position)
    {
        return static_cast<uint16_t>((_I_08(Data, Position + 1) << 8) | _I_08(Data, Position));
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _I_32(const uint8_t * Data, uint32_t Position)
    {
        return static_cast<uint16_t>((_I_16(Data, Position + 2) << 16) | _I_16(Data, Position));
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t _Parse_Role(uint32_t Code)
    {
        switch (Code)
        {
        case 1:
        case 2:
        case 3:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17:
            return 2;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 16:
            return 1;
        case 15:
        case 23:
            return 3;
        }
        return 0;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uint32_t _Parse_Color(uint32_t Role)
    {
        switch (Role)
        {
        case 1:
            return 0xFFFF0000;
        case 2:
            return 0xFF0000FF;
        case 3:
            return 0xFF606060;
        }
        return 0xFFFFFFFF;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Mode(bool Inventory)
    {
        Core::Update_Mode(Inventory);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Use(uint16_t Slot, bool Key)
    {
        if (Key)
        {
            _Writer_Push(0x1D);
        }
        else
        {
            _Writer_Push(0x1E);
        }
        _Writer_Push(Slot);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Cast(uint16_t Slot, bool Cursor)
    {
        ((void (__stdcall *)(uint32_t)) s_Address_3)(Slot);

        if (Cursor)
        {
            _Writer_Push(0x1B);
            _Writer_Push(0x01);
        }
        else
        {
            Core::Update_Clickable(true);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Click(uint32_t X, uint32_t Y, Core::Attack Type)
    {
        _Writer_Push(0x22);
        _Writer_Push(X);
        _Writer_Push(Y - 1);
        _Writer_Push(Type == Core::Attack::Spell ? 0x1 : 0x11);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Recv(uint8_t Header, uint8_t * Data, uint32_t Length)
    {
        switch (Header)
        {
        case 0x04:
            Core::Update_Possession(0);
            Core::Destroy();
            break;
        case 0x16:
            Core::Update_Stamina(_I_16(Data, 0));
            break;
        case 0x17:
            Core::Update_Energy(_I_16(Data, 0));
            break;
        case 0x18:
            Core::Update_Energy(_I_16(Data, 0));
            Core::Update_Stamina(_I_16(Data, 2));
            break;
        case 0x19:
            Core::Update_Health(_I_16(Data, 0));
            Core::Update_Stamina(_I_16(Data, 2));
            break;
        case 0x1A:
            Core::Update_Health(_I_16(Data, 0));
            break;
        case 0x1B:
            Core::Update_Gold(_I_32(Data, 0));
            break;
        case 0x1C:
            Core::Update_Experience(_I_32(Data, 0));
            break;
        case 0x1E:
            Core::Update_Area(_I_08(Data, 4), _I_08(Data, 5));
            break;
        case 0x1F:
            Core::Update_Entity_Position(Core::Get_Possession(), _I_08(Data, 0), _I_08(Data, 1));
            break;
        case 0x2A:
            if (auto zEntity = Core::Get_Possession(); zEntity)
            {
                zEntity->Owned = false;
            }

            Core::Update_Possession(_I_16(Data, 0));

            if (auto zEntity = Core::Get_Possession(); zEntity)
            {
                zEntity->Owned = true;
            }
            break;
        case 0x2B:
        {
            auto zEntity = Core::Create_Entity(_I_16(Data, 0), _I_08(Data, 7), _I_08(Data, 8));

            wchar_t zBuffer[128];
            std::mbstowcs(zBuffer, reinterpret_cast<char *>(Data + 0x15), _I_16(Data, 0x13));
            Core::Update_Entity_Name(zEntity, std::wstring_view(zBuffer, _I_16(Data, 0x13)));
            //Trace(L"%s %d", zEntity->Name, _I_08(Data, 0x15 + _I_16(Data, 0x13)));

            zEntity->Role = _Parse_Role(_I_08(Data, 0x15 + _I_16(Data, 0x13)));
            zEntity->Color = _Parse_Color(zEntity->Role);
        }
            break;
        case 0x2C:
            Core::Destroy_Entity(_I_16(Data, 0));
            break;
        case 0x2D:
        {
            if (auto zEntity = Core::Find_Entity(_I_16(Data, 0)); zEntity)
            {
                Core::Update_Entity_Position(zEntity, _I_08(Data, 2), _I_08(Data, 3));
            }
        }
            break;
        case 0x31:
            Core::Create_Object(_I_16(Data, 2), _I_08(Data, 0), _I_08(Data, 1));
            break;
        case 0x32:
            Core::Destroy_Object(_I_08(Data, 0), _I_08(Data, 1));
            break;
        case 0x33:
            break;
        case 0x39:
            Core::Update_Area(_I_08(Data, 0), _I_08(Data, 1));
            break;
        case 0x3D:
            Core::Update_Health_Maximum(_I_16(Data, 0));
            Core::Update_Health(_I_16(Data, 2));
            Core::Update_Energy_Maximum(_I_16(Data, 4));
            Core::Update_Energy(_I_16(Data, 6));
            Core::Update_Stamina_Maximum(_I_16(Data, 8));
            Core::Update_Stamina(_I_16(Data, 10));
            Core::Update_Gold(_I_32(Data, 12));
            Core::Update_Level(_I_08(Data, 16));
            Core::Update_Experience_Maximum(_I_32(Data, 17));
            Core::Update_Experience(_I_32(Data, 21));
            break;
        case 0x3F:
            Core::Update_Item(_I_08(Data, 0), _I_16(Data, _I_16(Data, 1) + 6), _I_16(Data, _I_16(Data, 1) + 3));
            break;
        case 0x41:
            Core::Update_Spell(_I_08(Data, 0), _I_16(Data, 1));
            break;
        case 0x4F:
            Core::Update_Hunger_Maximum(_I_08(Data, 0));
            Core::Update_Hunger(_I_08(Data, 1));
            Core::Update_Thirst_Maximum(_I_08(Data, 2));
            Core::Update_Thirst(_I_08(Data, 3));
            break;
        default:
            //Trace_Message(L"<R>", Header, Data, Length);
            break;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Send(uint8_t Header, uint8_t * Data, uint32_t Length)
    {
        switch (Header)
        {
        case 0x07:
            Core::Update_Entity_Position(Core::Get_Possession(), (Core::Direction) _I_08(Data, 0));
            break;
        case 0x18:
            Core::Update_Cooldown(Core::Action::Cast, ::GetTickCount());
            break;
        case 0x19:
            Controller::Caster::Set_Aim_Target(_I_08(Data, 0), _I_08(Data, 1), true);
            break;
        case 0x1D:
        case 0x1E:
            Core::Update_Cooldown(Core::Action::Use, ::GetTickCount());
            break;
        case 0x22:
            Core::Update_Cooldown(Core::Action::Click, ::GetTickCount());
            break;
        case 0xFF:
            * (uint32_t *) (s_Address_2 + 0x3C) = 0;
            break;
        default:
            break;
        }
        Trace_Message(L"<S>", Header, Data, Length);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Tick()
    {
        Controller::On_Tick();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Recv()
    {
        uint32_t zLength = _Reader_Length(* s_Address_1), zSecond = 0, zThird = 0;

        uint8_t zData[8192];
        std::memcpy(zData, _Reader_Peek(* s_Address_1), zLength);

        while (zLength > 0)
        {
            __asm CALL s_Detour_2.Destination

            zSecond = zLength - _Reader_Length(* s_Address_1);
            zLength = zLength - zSecond;

            On_Recv(* (zData + zThird), zData + zThird + 1, zSecond - 1);

            zThird += zSecond;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Send()
    {
        if (* s_Address_2 && _Reader_Length(* s_Address_2))
        {
            On_Send(* _Reader_Peek(* s_Address_2), _Reader_Peek(* s_Address_2) + 1, _Reader_Length(* s_Address_2) - 1);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    __declspec(naked) void __stdcall On_Hook_Tick_Trampoline()
    {
        __asm PUSHAD
        __asm PUSHFD
        __asm CALL On_Hook_Tick
        __asm POPFD
        __asm POPAD
        __asm JMP s_Detour_1.Destination
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    __declspec(naked) void __stdcall On_Hook_Recv_Trampoline()
    {
        __asm PUSHAD
        __asm PUSHFD
        __asm CALL On_Hook_Recv
        __asm POPFD
        __asm POPAD
        __asm JMP s_Detour_2.Destination
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    __declspec(naked) void __stdcall On_Hook_Send_Trampoline()
    {
        __asm PUSHAD
        __asm PUSHFD
        __asm CALL On_Hook_Send
        __asm POPFD
        __asm POPAD
        __asm JMP s_Detour_3.Destination
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Game_Attach()
    {
        constexpr const char * PATTERN_2
            = "B9 ? ? ? ? FF 15 ? ? ? ? 38 45 AC 75 11 C7 45 ? ? ? ? ? E8 ? ? ? ? E9 ? ? ? ? C7 45 ? ? ? ? ? B9 ? ? ? ? FF 15";
        constexpr const char * PATTERN_3
            = "8B 4D D8 68 ? ? ? ? 68 ? ? ? ? 51 50 FF D6 8B 45 D8 8D 4D E8 51 8B 4D E4 8B 10 51 50 FF 52 64";
        constexpr const char * PATTERN_4
            = "FF 15 ? ? ? ? A1 ? ? ? ? 8B ? ? ? ? ? 8D 4D E4 50 51 FF D6 8B 55 E4 8D 45 EC 50 B9 ? ? ? ? 8B 1A FF 15";
        constexpr const char * PATTERN_5
            = "E8 ? ? ? ? 68 ? ? ? ? EB 0A 8D 4D DC FF 15 ? ? ? ? C3 C3 8B 4D E0 64 89 0D 00 00 00 00";
        constexpr const char * PATTERN_6
            = "0F 8E ? ? ? ? 85 C9 74 5B 66 83 39 02 75 55 8B 55 08 33 C0 8A 42 3C 8D 72 3C 8B 51 1C";
        constexpr const char * PATTERN_7
            = "8B 7D 08 57 8B 07 FF 90 24 03 00 00 8D 4D B8 50 51 FF 15 ? ? ? ? 8B F0 8D 45 B0 50 56 8B 16 FF 92 90 00 00 00";

        uintptr_t zModule = (uintptr_t) ::GetModuleHandle(NULL);

        uintptr_t zAddress_1 = (uintptr_t) ::GetProcAddress(::LoadLibrary("MSVBVM60"), "rtcDoEvents") + 0x07;
        uintptr_t zAddress_2 = Memory::Find(zModule, PATTERN_2, true);
        uintptr_t zAddress_3 = Memory::Find(zModule, PATTERN_3, true);
        uintptr_t zAddress_4 = Memory::Find(zModule, PATTERN_5, false);
        uintptr_t zAddress_5 = Memory::Find(zModule, PATTERN_6, false);
        uintptr_t zAddress_6 = Memory::Find(zModule, PATTERN_7, false);


        s_Address_1 = * reinterpret_cast<uint32_t **>(zAddress_2 + 0x5D);
        s_Address_2 = s_Address_1 + 1;
        s_Address_3 = Memory::Find(zModule, PATTERN_4, true);

        Memory::Create_Detour(zAddress_1, (uintptr_t) & On_Hook_Tick_Trampoline, s_Detour_1);
        Memory::Create_Detour(zAddress_2, (uintptr_t) & On_Hook_Recv_Trampoline, s_Detour_2);
        Memory::Create_Detour(zAddress_3, (uintptr_t) & On_Hook_Send_Trampoline, s_Detour_3);

        Memory::Write_Opcode_Nop(zAddress_4, 0x05);
        Memory::Write_Opcode_Jump(zAddress_5, zAddress_6);

        Trace(L"%X %X %X %X %X %X %X %X", zAddress_2, zAddress_3,
            s_Address_1, s_Address_2, s_Address_3, zAddress_4, zAddress_5, zAddress_6);

        Controller::Potion::Set_Blue_Type(0x2187);
        Controller::Potion::Set_Red_Type(0x2189);

        Controller::On_Load(SETTING_NAME);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Game_Detach()
    {
        Controller::On_Save(SETTING_NAME);

        Memory::Remove_Detour(s_Detour_1);
        Memory::Remove_Detour(s_Detour_2);
        Memory::Remove_Detour(s_Detour_3);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    extern "C" bool __stdcall DllMain(uint32_t, uint32_t Reason, uint32_t)
    {
        switch (Reason)
        {
        case DLL_PROCESS_ATTACH:
            Factory::On_Game_Attach();
            break;
        case DLL_PROCESS_DETACH:
            Factory::On_Game_Detach();
            break;
        default:
            break;
        }
        return true;
    }
}