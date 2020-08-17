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
    static uintptr_t      s_Memory_1;
    static uintptr_t      s_Memory_2;
    static uintptr_t      s_Memory_3;
    static uintptr_t      s_Memory_4;
    static uintptr_t      s_Memory_5;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Factory
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _Parse_Color(uint32_t R, uint32_t G, uint32_t B, uint32_t A = 0xFF)
    {
        return ((A & 0xFF) << 24) + ((B & 0xFF) << 16) + ((G & 0xFF) << 8) + (R & 0xFF);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _Parse_Role(uint32_t Color)
    {
        switch (Color)
        {
        case 0xFF000000:
            return 0;
        case 0xFF91FAB9:
        case 0xFF00FF00:
            return 1;
        case 0xFF801010:
        case 0xFFFF7D00:
            return 2;
        case 0xFF101080:
        case 0xFF0000FF:
            return 3;
        case 0xFF646464:
        case 0xFF808080:
            return 4;
        case 0xFF50B428:
            return 5;
        }

        Trace(L"[!] Unknown Color %X", Color);
        return 6;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<typename Type>
    auto _Parse(std::wstring_view Buffer, int32_t Position, wchar_t Delimiter = L',')
    {
        uint32_t zBegin = 0, zEnd = 0;

        while (zBegin < Buffer.length() && --Position >= 0)
        {
            zEnd = Buffer.find_first_of(Delimiter, zBegin);

            if (zEnd == std::wstring_view::npos || Position <= 0)
            {
                zEnd = (zEnd == std::wstring_view::npos) ? Buffer.length() : zEnd;
                break;
            }
            zBegin = zEnd + 1;
        }

        if constexpr (std::is_same<wchar_t, Type>::value)
        {
            return Position > 0 ? std::wstring_view() : Buffer.substr(zBegin, zEnd - zBegin);
        }
        else if constexpr (std::is_floating_point_v<Type>)
        {
            return Position > 0 ? 0 : (Type) std::wcstof(& Buffer[zBegin], nullptr);
        }
        else
        {
            return Position > 0 ? 0 : (Type) std::wcstoull(& Buffer[zBegin], nullptr, 10);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    auto _Net_Decode(std::wstring_view Message)
    {
        if (Message.length() < 2)
        {
            return std::wstring();
        }

        std::wstring zBuffer(Message.data(), Message.length() - 1);

        for (uint32_t zID = 0, zKey = Message[Message.length() - 1] ^0x2F; zID < zBuffer.length(); ++zID)
        {
            zBuffer[zID] ^= zKey;
        }
        return zBuffer;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<typename... Args>
    void _Net_Handle(bool Remote, const wchar_t * Format, Args && ... Arguments)
    {
        wchar_t zBuffer[1024] = { '\0' };

        ::_swprintf_c(zBuffer, (sizeof(zBuffer) / sizeof(wchar_t)), Format, Arguments...);

        BSTR zMessage = ::SysAllocString(zBuffer);
        {
            if (Remote)
            {
                ((void (__stdcall *)(BSTR, uint32_t)) (s_Detour_3.Destination))(zMessage, 0);
            }
            else
            {
                ((void (__stdcall *)(BSTR)) (s_Detour_2.Destination))(zMessage);
            }
        }
        ::SysFreeString(zMessage);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    template<typename... Args>
    void _Net_Modify(const wchar_t * Format, BSTR * Message, Args && ... Arguments)
    {
        wchar_t zBuffer[1024] = { '\0' };

        ::_swprintf_c(zBuffer, (sizeof(zBuffer) / sizeof(wchar_t)), Format, Arguments...);

        ::SysReAllocString(Message, zBuffer);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Mode(bool Inventory)
    {
        if (Inventory)
        {
            ((void (__stdcall *)(uint32_t)) (s_Memory_2))(* (uint32_t *) s_Memory_1);
        }
        else
        {
            ((void (__stdcall *)(uint32_t)) (s_Memory_3))(* (uint32_t *) s_Memory_1);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Use(uint16_t Slot, bool Key)
    {
        if (!Key)
        {
            _Net_Handle(true, L"9\xA7%d,0", Slot);
        }
        _Net_Handle(true, L"9\xA7%d,1", Slot);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Cast(uint16_t Slot, bool Cursor)
    {
        {
            Core::Update_Clickable(true);
        }

        if (Cursor)
        {
            _Net_Handle(false, L"T012");
        }
        _Net_Handle(true, L"25\xA7%d,1", Slot);
        _Net_Handle(true, L"28\xA72");
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Action_Click(uint32_t X, uint32_t Y, Core::Attack Type)
    {
        wchar_t zBuffer[256] = { L'\0' };

        if (Core::Entity * zEntity = Core::Find_Entity(X, Y); zEntity)
        {
            const bool zIsPossession = (zEntity == Core::Get_Possession());
            const bool zIsNamed = (zEntity->Role > 0);
            const bool zIsFaction = (wcslen(zEntity->Faction) > 0);

            if (zIsPossession)
            {
                ::wcscpy_s(zBuffer, L"_SELF_");
            }
            else if (zIsNamed)
            {
                ::wcscpy_s(zBuffer, zEntity->Name);
            }

            if (!zIsPossession && zIsFaction)
            {
                ::wcscat_s(zBuffer, L" <");
                ::wcscat_s(zBuffer, zEntity->Faction);
                ::wcscat_s(zBuffer, L">");
            }
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Tick()
    {
        Controller::On_Tick();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Recv(BSTR Message, BSTR * Dynamic)
    {
        switch (auto zData = Message + 0x07; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"ATURDOK"):
        {
            return;
        }
        case Expr_Hash(L"BANCOOK"):
        {
            return;
        }
        case Expr_Hash(L"CHRINFL"):
        {
            return;
        }
        case Expr_Hash(L"CHRINFO"):
        {
            return;
        }
        case Expr_Hash(L"CHRPNFL"):
        {
            return;
        }
        case Expr_Hash(L"CLANDET"):
        {
            return;
        }
        case Expr_Hash(L"DONLIST"):
        {
            return;
        }
        case Expr_Hash(L"DONINDV"):
        {
            return;
        }
        case Expr_Hash(L"GUILDNE"):
        {
            return;
        }
        case Expr_Hash(L"LEADERA"):
        {
            return;
        }
        case Expr_Hash(L"LEADERI"):
        {
            return;
        }
        case Expr_Hash(L"OPENHEL"):
        {
            return;
        }
        case Expr_Hash(L"PARADO1"):
        {
            return;
        }
        case Expr_Hash(L"PARADO2"):
        {
            return;
        }
        case Expr_Hash(L"PARADOK"):
        {
            return;
        }
        case Expr_Hash(L"PEACEDE"):
        {
            return;
        }
        case Expr_Hash(L"PEACEPR"):
        {
            return;
        }
        case Expr_Hash(L"PETICIO"):
        {
            return;
        }
        case Expr_Hash(L"SHOWFUN"):
        {
            return;
        }
        case Expr_Hash(L"TRANSOK"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x06; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"ACHIEA"):
        {
            return;
        }
        case Expr_Hash(L"ACHIEM"):
        {
            return;
        }
        case Expr_Hash(L"ACHIEV"):
        {
            return;
        }
        case Expr_Hash(L"LSTCRI"):
        {
            return;
        }
        case Expr_Hash(L"LOGGED"):
        {
            return;
        }
        case Expr_Hash(L"NESTUP"):
        {
            return;
        }
        case Expr_Hash(L"NSEGUE"):
        {
            return;
        }
        case Expr_Hash(L"SKILLS"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x05; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"HPBAR"):
        {
            return;
        }
        case Expr_Hash(L"FINAC"):
        {
            return;
        }
        case Expr_Hash(L"FINOK"):
        {
            Core::Update_Possession(0);
            return;
        }
        case Expr_Hash(L"GUIBO"):
        {
            return;
        }
        case Expr_Hash(L"ITORN"):
        {
            return;
        }
        case Expr_Hash(L"MATOR"):
        {
            return;
        }
        case Expr_Hash(L"MEDIT"):
        {
            return;
        }
        case Expr_Hash(L"MEDOK"):
        {
            return;
        }
        case Expr_Hash(L"MTORN"):
        {
            return;
        }
        case Expr_Hash(L"NOVER"):
        {
            return;
        }
        case Expr_Hash(L"SHOWT"):
        {
            return;
        }
        case Expr_Hash(L"STTOR"):
        {
            return;
        }
        case Expr_Hash(L"SUBVA"):
        {
            return;
        }
        case Expr_Hash(L"SURVE"):
        {
            return;
        }
        case Expr_Hash(L"SURVI"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x04; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"AREA"):
        {
            auto zContent = _Parse<wchar_t>(zData, 1, L'\x04');
            auto zChild = _Parse<wchar_t>(zContent, 2, L'\x03');

            for (uint32_t zIndex = 0, zCount = _Parse<uint32_t>(zContent, 1, L'\x03'); zIndex < zCount; ++zIndex)
            {
                const auto zBody = _Net_Decode(_Parse<wchar_t>(zChild, zIndex + 1, L'\x02'));

                auto zEntity = Core::Create_Entity(
                    _Parse<uint16_t>(zBody, 4), _Parse<uint16_t>(zBody, 5), _Parse<uint16_t>(zBody, 6));
                zEntity->Color = _Parse_Color(
                    _Parse<uint32_t>(zBody, 23), _Parse<uint32_t>(zBody, 24), _Parse<uint32_t>(zBody, 25));
                zEntity->Role = _Parse_Role(zEntity->Color);
                //zEntity->Friendly = (zEntity->Role == 5);
                zEntity->Dead = _Parse<uint32_t>(zBody, 13);

                Update_Entity_Name(zEntity, _Parse<wchar_t>(zBody, 10));

            }

            zContent = _Parse<wchar_t>(zData, 2, L'\x04');
            zChild = _Parse<wchar_t>(zContent, 2, L'\x03');

            for (uint32_t zIndex = 0, zCount = _Parse<uint32_t>(zContent, 1, L'\x03'); zIndex < zCount; ++zIndex)
            {
                const auto zBody = _Net_Decode(_Parse<wchar_t>(zChild, zIndex + 1, L'\x02'));

                auto zEntity = Core::Create_Entity(
                    _Parse<uint16_t>(zBody, 4), _Parse<uint16_t>(zBody, 5), _Parse<uint16_t>(zBody, 6));
                Update_Entity_Name(zEntity, _Parse<wchar_t>(zBody, 1));
            }
            return;
        }
        case Expr_Hash(L"ARED"):
        {
            const uint32_t zX1 = _Parse<uint16_t>(zData, 1, L'\x02');
            const uint32_t zX2 = _Parse<uint16_t>(zData, 2, L'\x02');
            const uint32_t zY1 = _Parse<uint16_t>(zData, 3, L'\x02');
            const uint32_t zY2 = _Parse<uint16_t>(zData, 4, L'\x02');

            Core::Destroy_Entity([zX1, zX2, zY1, zY2](const Core::Entity & Target)
            {
                return (Target.X >= zX1 && Target.X <= zX2 && Target.Y >= zY1 && Target.Y <= zY2);
            });
            return;
        }
        case Expr_Hash(L"CHAT"):
        {
            return;
        }
        case Expr_Hash(L"CONT"):
        {
            return;
        }
        case Expr_Hash(L"CRAF"):
        {
            return;
        }
        case Expr_Hash(L"EHYS"):
        {
            Core::Update_Hunger_Maximum(_Parse<uint32_t>(zData, 1));
            Core::Update_Hunger(_Parse<uint32_t>(zData, 2));
            Core::Update_Thirst_Maximum(_Parse<uint32_t>(zData, 3));
            Core::Update_Thirst(_Parse<uint32_t>(zData, 4));
            return;
        }
        case Expr_Hash(L"ETIM"):
        {
            return;
        }
        case Expr_Hash(L"FARV"):
        {
            return;
        }
        case Expr_Hash(L"FARQ"):
        {
            return;
        }
        case Expr_Hash(L"FMSG"):
        {
            return;
        }
        case Expr_Hash(L"HRNO"):
        {
            return;
        }
        case Expr_Hash(L"LACC"):
        {
            return;
        }
        case Expr_Hash(L"LMSG"):
        {
            return;
        }
        case Expr_Hash(L"MACC"):
        {
            return;
        }
        case Expr_Hash(L"MALM"):
        {
            return;
        }
        case Expr_Hash(L"MARO"):
        {
            return;
        }
        case Expr_Hash(L"MAUM"):
        {
            return;
        }
        case Expr_Hash(L"MBOM"):
        {
            return;
        }
        case Expr_Hash(L"MCAR"):
        {
            return;
        }
        case Expr_Hash(L"MFOR"):
        {
            return;
        }
        case Expr_Hash(L"MINI"):
        {
            return;
        }
        case Expr_Hash(L"MISS"):
        {
            return;
        }
        case Expr_Hash(L"MRNK"):
        {
            return;
        }
        case Expr_Hash(L"MSOS"):
        {
            return;
        }
        case Expr_Hash(L"NENE"):
        {
            return;
        }
        case Expr_Hash(L"NPCI"):
        {
            return;
        }
        case Expr_Hash(L"NPCO"):
        {
            return;
        }
        case Expr_Hash(L"NPCZ"):
        {
            return;
        }
        case Expr_Hash(L"NOBL"):
        {
            return;
        }
        case Expr_Hash(L"PONG"):
        {
            return;
        }
        case Expr_Hash(L"PREM"):
        {
            return;
        }
        case Expr_Hash(L"PTSA"):
        {
            return;
        }
        case Expr_Hash(L"PTSH"):
        {
            return;
        }
        case Expr_Hash(L"PTSD"):
        {
            return;
        }
        case Expr_Hash(L"QTDL"):
        {
            return;
        }
        case Expr_Hash(L"RANK"):
        {
            return;
        }
        case Expr_Hash(L"RSOS"):
        {
            return;
        }
        case Expr_Hash(L"SUNI"):
        {
            return;
        }
        case Expr_Hash(L"TIME"):
        {
            return;
        }
        case Expr_Hash(L"VTIM"):
        {
            return;
        }
        case Expr_Hash(L"XACC"):
        {
            return;
        }
        case Expr_Hash(L"ZLSM"):
        {
            return;
        }
        case Expr_Hash(L"ZLST"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x03; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"822"):
        {
            return;
        }
        case Expr_Hash(L"500"):
        {
            return;
        }
        case Expr_Hash(L"ALB"):
        {
            return;
        }
        case Expr_Hash(L"ALC"):
        {
            return;
        }
        case Expr_Hash(L"ALT"):
        {
            return;
        }
        case Expr_Hash(L"ALZ"):
        {
            return;
        }
        case Expr_Hash(L"ATI"):
        {
            return;
        }
        case Expr_Hash(L"ATR"):
        {
            return;
        }
        case Expr_Hash(L"AUR"):
        {
            return;
        }
        case Expr_Hash(L"AUT"):
        {
            return;
        }
        case Expr_Hash(L"AYM"):
        {
            return;
        }
        case Expr_Hash(L"BKW"):
        {
            return;
        }
        case Expr_Hash(L"CBB"):
        {
            return;
        }
        case Expr_Hash(L"CBO"):
        {
            return;
        }
        case Expr_Hash(L"CDI"):
        {
            return;
        }
        case Expr_Hash(L"CFX"):
        {
            return;
        }
        case Expr_Hash(L"CHK"):
        {
            return;
        }
        case Expr_Hash(L"CKE"):
        {
            return;
        }
        case Expr_Hash(L"CKI"):
        {
            return;
        }
        case Expr_Hash(L"CNT"):
        {
            return;
        }
        case Expr_Hash(L"CRF"):
        {
            return;
        }
        case Expr_Hash(L"CSI"):
        {
            Core::Update_Item(_Parse<uint16_t>(zData, 1), _Parse<uint32_t>(zData, 2), _Parse<uint32_t>(zData, 4));
            return;
        }
        case Expr_Hash(L"DND"):
        {
            return;
        }
        case Expr_Hash(L"DNE"):
        {
            return;
        }
        case Expr_Hash(L"DNV"):
        {
            for (uint32_t zID = 1; zID <= 36; ++zID)
            {
                if (auto zBody = _Parse<wchar_t>(zData, zID, L'\x03'); !zBody.empty())
                {
                    Core::Update_Item(
                        _Parse<uint32_t>(zBody, 1, L'\x02'),
                        _Parse<uint32_t>(zBody, 2, L'\x02'),
                        _Parse<uint32_t>(zBody, 4, L'\x02'));
                }
            }
            return;
        }
        case Expr_Hash(L"DOK"):
        {
            return;
        }
        case Expr_Hash(L"DSE"):
        {
            return;
        }
        case Expr_Hash(L"DSI"):
        {
            Core::Update_Item(_Parse<uint16_t>(zData, 1), _Parse<uint32_t>(zData, 6), _Parse<uint32_t>(zData, 4));
            return;
        }
        case Expr_Hash(L"DSS"):
        {
            return;
        }
        case Expr_Hash(L"ERR"):
        {
            return;
        }
        case Expr_Hash(L"ERT"):
        {
            return;
        }
        case Expr_Hash(L"ERZ"):
        {
            return;
        }
        case Expr_Hash(L"EST"):
        {
            Core::Update_Health_Maximum(_Parse<uint32_t>(zData, 2));
            Core::Update_Health(_Parse<uint32_t>(zData, 3));
            Core::Update_Energy_Maximum(_Parse<uint32_t>(zData, 4));
            Core::Update_Energy(_Parse<uint32_t>(zData, 5));
            Core::Update_Stamina_Maximum(_Parse<uint32_t>(zData, 6));
            Core::Update_Stamina(_Parse<uint32_t>(zData, 7));
            Core::Update_Hunger_Maximum(_Parse<uint32_t>(zData, 8));
            Core::Update_Hunger(_Parse<uint32_t>(zData, 9));
            Core::Update_Thirst_Maximum(_Parse<uint32_t>(zData, 10));
            Core::Update_Thirst(_Parse<uint32_t>(zData, 11));
            Core::Update_Gold(_Parse<uint32_t>(zData, 12));
            Core::Update_Level(_Parse<uint32_t>(zData, 13));
            Core::Update_Experience_Maximum(_Parse<uint32_t>(zData, 14));
            Core::Update_Experience(_Parse<uint32_t>(zData, 15));

            return;
        }
        case Expr_Hash(L"EWT"):
        {
            return;
        }
        case Expr_Hash(L"GOD"):
        {
            return;
        }
        case Expr_Hash(L"LAH"):
        {
            return;
        }
        case Expr_Hash(L"LAR"):
        {
            return;
        }
        case Expr_Hash(L"LAS"):
        {
            return;
        }
        case Expr_Hash(L"LAQ"):
        {
            return;
        }
        case Expr_Hash(L"LAZ"):
        {
            return;
        }
        case Expr_Hash(L"LLU"):
        {
            return;
        }
        case Expr_Hash(L"LÑM"):
        {
            return;
        }
        case Expr_Hash(L"MJR"):
        {
            return;
        }
        case Expr_Hash(L"NOC"):
        {
            return;
        }
        case Expr_Hash(L"OBR"):
        {
            return;
        }
        case Expr_Hash(L"PEL"):
        {
            return;
        }
        case Expr_Hash(L"PFL"):
        {
            return;
        }
        case Expr_Hash(L"PLC"):
        {
            return;
        }
        case Expr_Hash(L"PLM"):
        {
            return;
        }
        case Expr_Hash(L"PLR"):
        {
            return;
        }
        case Expr_Hash(L"POD"):
        {
            return;
        }
        case Expr_Hash(L"POW"):
        {
            return;
        }
        case Expr_Hash(L"POP"):
        {
            return;
        }
        case Expr_Hash(L"PRM"):
        {
            return;
        }
        case Expr_Hash(L"PTY"):
        {
            return;
        }
        case Expr_Hash(L"QDL"):
        {
            return;
        }
        case Expr_Hash(L"SBA"):
        {
            return;
        }
        case Expr_Hash(L"SBG"):
        {
            return;
        }
        case Expr_Hash(L"SBO"):
        {
            return;
        }
        case Expr_Hash(L"SEA"):
        {
            return;
        }
        case Expr_Hash(L"SHS"):
        {
            return;
        }
        case Expr_Hash(L"SHW"):
        {
            for (uint32_t zID = 0, zLength = _Parse<uint32_t>(zData, 1, L'~'); zID < zLength; ++zID)
            {
                if (auto zBody = _Parse<wchar_t>(zData, zID + 2, L'~'); !zBody.empty())
                {
                    Core::Update_Spell(zID + 1, _Parse<uint32_t>(_Parse<wchar_t>(zData, zID + 2, L'~'), 1));
                }
            }
            return;
        }
        case Expr_Hash(L"SPL"):
        {
            return;
        }
        case Expr_Hash(L"T01"):
        {
            switch (_Parse<uint32_t>(zData, 1))
            {
            case 0x02:
                Core::Update_Clickable(true);
                break;
            }
            return;
        }
        case Expr_Hash(L"TXC"):
        {
            return;
        }
        case Expr_Hash(L"TXT"):
        {
            return;
        }
        case Expr_Hash(L"UMP"):
        {
            return;
        }
        case Expr_Hash(L"VAL"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x02; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"41"):
        {
            return;
        }
        case Expr_Hash(L"51"):
        {
            return;
        }
        case Expr_Hash(L"67"):
        {
            ::Beep(350, 1000);
            return;
        }
        case Expr_Hash(L"77"):
        {
            return;
        }
        case Expr_Hash(L"||"):
        {
            return;
        }
        case Expr_Hash(L"BO"):
        {
            return;
        }
        case Expr_Hash(L"BP"):
        {
            Core::Destroy_Entity(_Parse<uint16_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"BQ"):
        {
            return;
        }
        case Expr_Hash(L"C|"):
        {
            return;
        }
        case Expr_Hash(L"CC"):
        {
            auto zBody = _Net_Decode(zData);

            auto zEntity = Core::Create_Entity(
                _Parse<uint16_t>(zBody, 4), _Parse<uint16_t>(zBody, 5), _Parse<uint16_t>(zBody, 6));
            zEntity->Color = _Parse_Color(
                _Parse<uint32_t>(zBody, 22), _Parse<uint32_t>(zBody, 23), _Parse<uint32_t>(zBody, 24));
            zEntity->Role = _Parse_Role(zEntity->Color);
            //zEntity->Friendly = (zEntity->Role == 5);
            zEntity->Dead = _Parse<uint32_t>(zBody, 13);

            Update_Entity_Name(zEntity, _Parse<wchar_t>(zBody, 10));
            return;
        }
        case Expr_Hash(L"CM"):
        {
            Core::Destroy();
            return;
        }
        case Expr_Hash(L"CP"):
        {
            Core::Find_Entity(_Parse<uint32_t>(zData, 1))->Dead = _Parse<uint32_t>(zData, 11);
            return;
        }
        case Expr_Hash(L"DA"):
        {
            return;
        }
        case Expr_Hash(L"FO"):
        {
            return;
        }
        case Expr_Hash(L"G|"):
        {
            return;
        }
        case Expr_Hash(L"GL"):
        {
            return;
        }
        case Expr_Hash(L"GM"):
        {
            return;
        }
        case Expr_Hash(L"GW"):
        {
            return;
        }
        case Expr_Hash(L"HO"):
        {
            return;
        }
        case Expr_Hash(L"IN"):
        {
            return;
        }
        case Expr_Hash(L"IP"):
        {
            Core::Update_Possession(_Parse<uint32_t>(zData, 1));
            {
                Core::Get_Possession()->Owned = true;
            }
            return;
        }
        case Expr_Hash(L"IU"):
        {
            return;
        }
        case Expr_Hash(L"LB"):
        {
            return;
        }
        case Expr_Hash(L"M0"):
        {
            return;
        }
        case Expr_Hash(L"MP"):
        {
            return;
        }
        case Expr_Hash(L"ON"):
        {
            return;
        }
        case Expr_Hash(L"P|"):
        {
            return;
        }
        case Expr_Hash(L"PU"):
        {
            Core::Update_Entity_Position(Core::Get_Possession(), _Parse<uint32_t>(zData, 1),
                _Parse<uint32_t>(zData, 2));
            return;
        }
        case Expr_Hash(L"SS"):
        {
            return;
        }
        case Expr_Hash(L"TM"):
        {
            return;
        }
        case Expr_Hash(L"TW"):
        {
            return;
        }
        case Expr_Hash(L"XS"):
        {
            return;
        }
        case Expr_Hash(L"ZP"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x01; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"\x2B"):
        {
            return;
        }
        case Expr_Hash(L"\xAA"):
        {
            return;
        }
        case Expr_Hash(L"0"):
        {
            auto zEntity = Core::Find_Entity(_Parse<uint32_t>(zData, 1, 0xC8));

            if (zEntity != nullptr)
            {
                Core::Update_Entity_Position(
                    zEntity, _Parse<uint32_t>(zData, 2, 0xC8), _Parse<uint32_t>(zData, 3, 0xC8));
            }
            return;
        }
        case Expr_Hash(L"A"):
        {
            Core::Update_Health(_Parse<uint32_t>(zData, 1));
            Core::Update_Health_Maximum(_Parse<uint32_t>(zData, 2));
            return;
        }
        case Expr_Hash(L"B"):
        {
            Core::Update_Energy(_Parse<uint32_t>(zData, 1));
            Core::Update_Energy_Maximum(_Parse<uint32_t>(zData, 2));
            return;
        }
        case Expr_Hash(L"C"):
        {
            Core::Update_Gold(_Parse<uint32_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"D"):
        {
            Core::Update_Stamina(_Parse<uint32_t>(zData, 1));
            Core::Update_Stamina_Maximum(_Parse<uint32_t>(zData, 2));
            return;
        }
        case Expr_Hash(L"F"):
        {
            return;
        }
        case Expr_Hash(L"G"):
        {
            Core::Update_Health(_Parse<uint32_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"H"):
        {
            Core::Update_Energy(_Parse<uint32_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"I"):
        {
            Core::Update_Experience(_Parse<uint32_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"J"):
        {
            Core::Update_Stamina(_Parse<uint32_t>(zData, 1));
            return;
        }
        case Expr_Hash(L"N"):
        {
            return;
        }
        case Expr_Hash(L"U"):
        {
            return;
        }
        }

        Trace(L"<R> = %s", Message);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void __stdcall On_Hook_Send(BSTR Message, BSTR * Dynamic)
    {
        Trace(L"<S> = %s", Message);

        switch (auto zData = Message + 0x04; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"106\xA7"):
        {
            return;
        }
        case Expr_Hash(L"109\xA7"):
        {
            return;
        }
        case Expr_Hash(L"112\xA7"):
        {
            return;
        }
        case Expr_Hash(L"113\xA7"):
        {
            return;
        }
        case Expr_Hash(L"114\xA7"):
        {
            Core::Update_Spell_Position(_Parse<uint32_t>(zData, 1), _Parse<uint32_t>(zData, 2));
            return;
        }
        case Expr_Hash(L"134\xA7"):
        {
            return;
        }
        case Expr_Hash(L"152\xA7"):
        {
            return;
        }
        case Expr_Hash(L"171\xA7"):
        {
            Core::Update_Mode(!Core::Is_Inventory());
            return;
        }
        case Expr_Hash(L"173\xA7"):
        {
            return;
        }
        case Expr_Hash(L"190\xA7"):
        {
            return;
        }
        case Expr_Hash(L"287\xA7"):
        {
            return;
        }
        case Expr_Hash(L"294\xA7"):
        {
            return;
        }
        case Expr_Hash(L"526\xA7"):
        {
            Core::Update_Mode(!Core::Is_Inventory());
            return;
        }
        case Expr_Hash(L"527\xA7"):
        {
            return;
        }
        case Expr_Hash(L"534\xA7"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x03; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"17\xA7"):
        {
            return;
        }
        case Expr_Hash(L"23\xA7"):
        {
            return;
        }
        case Expr_Hash(L"25\xA7"):
        {
            return;
        }
        case Expr_Hash(L"26\xA7"):
        {
            Controller::Caster::Set_Aim_Target(_Parse<uint32_t>(zData, 1), _Parse<uint32_t>(zData, 2), true);
            return;
        }
        case Expr_Hash(L"27\xA7"):
        {
            return;
        }
        case Expr_Hash(L"28\xA7"):
        {
            Core::Update_Cooldown(Core::Action::Cast, ::GetTickCount());
            return;
        }
        case Expr_Hash(L"32\xA7"):
        {
            return;
        }
        case Expr_Hash(L"36\xA7"):
        {
            return;
        }
        case Expr_Hash(L"87\xA7"):
        {
            {
                Core::Update_Clickable(false);
            }
            Controller::Caster::Set_Aim_Target(_Parse<uint32_t>(zData, 1), _Parse<uint32_t>(zData, 2), true);
            return;
        }
        case Expr_Hash(L"92\xA7"):
        {
            return;
        }
        case Expr_Hash(L"93\xA7"):
        {
            return;
        }
        case Expr_Hash(L"96\xA7"):
        {
            return;
        }
        case Expr_Hash(L"108"):
        {
            return;
        }
        case Expr_Hash(L"174"):
        {
            return;
        }
        case Expr_Hash(L"196"):
        {
            return;
        }
        case Expr_Hash(L"213"):
        {
            return;
        }
        case Expr_Hash(L"262"):
        {
            return;
        }
        case Expr_Hash(L"263"):
        {
            return;
        }
        case Expr_Hash(L"288"):
        {
            return;
        }
        case Expr_Hash(L"309"):
        {
            return;
        }
        }
        switch (auto zData = Message + 0x02; Expr_Hash(Message, zData - Message))
        {
        case Expr_Hash(L"4\xA7"):
        {
            return;
        }
        case Expr_Hash(L"9\xA7"):
        {
            Core::Update_Cooldown(Core::Action::Use, ::GetTickCount());
            return;
        }
        case Expr_Hash(L"10"):
        {
            return;
        }
        case Expr_Hash(L"11"):
        {
            return;
        }
        case Expr_Hash(L"15"):
        {
            return;
        }
        case Expr_Hash(L"16"):
        {
            return;
        }
        case Expr_Hash(L"22"):
        {
            return;
        }
        case Expr_Hash(L"97"):
        {
            return;
        }
        case Expr_Hash(L"98"):
        {
            return;
        }
        }

        if (::SysStringLen(Message) < 2)
        {
            switch (auto zData = Message + 1; Expr_Hash(Message, zData - Message))
            {
            case Expr_Hash(L"0"):
            {
                Core::Update_Entity_Position(Core::Get_Possession(), Core::Direction::North);
                return;
            }
            case Expr_Hash(L"1"):
            {
                Core::Update_Entity_Position(Core::Get_Possession(), Core::Direction::South);
                return;
            }
            case Expr_Hash(L"2"):
            {
                Core::Update_Entity_Position(Core::Get_Possession(), Core::Direction::East);
                return;
            }
            case Expr_Hash(L"3"):
            {
                Core::Update_Entity_Position(Core::Get_Possession(), Core::Direction::West);
                return;
            }
            case Expr_Hash(L"8"):
            {
                return;
            }
            }
        }

        Trace(L"<S> = %s", Message);
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
        __asm LEA  EAX, DWORD PTR[ESP + 0x28]
        __asm PUSH EAX
        __asm PUSH DWORD PTR[ESP + 0x2C]
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
        __asm LEA  EAX, DWORD PTR[ESP + 0x28]
        __asm PUSH EAX
        __asm PUSH DWORD PTR[ESP + 0x2C]
        __asm CALL On_Hook_Send
        __asm POPFD
        __asm POPAD
        __asm JMP s_Detour_3.Destination
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void On_Game_Attach()
    {
        constexpr const char * PATTERN_2 = "6A 00 6A 1C 8B ? ? ? ? ? 8B 08 8B ? ? ? ? ? 8B 02 8B 10";
        constexpr const char * PATTERN_3 = "66 3D 10 27 ? ? ? ? ? ? 7E 09 66 ? ? ? ? ? ? ? ? 8D 55 80 8D 4D B0 BB";
        constexpr const char * PATTERN_4 = "68 ? ? ? ? 68 ? ? ? ? FF 15 ? ? ? ? C7 85 ? ? ? ? ? ? ? ? EB 0A C7 85 ? ? ? ? ? ? ? ? 6A 00";
        constexpr const char * PATTERN_5 = "FF 15 ? ? ? ? 83 EC 10 B9 ? ? ? ? 8B D4 B8 00 00 A0 42 68 06 00 01 80";
        constexpr const char * PATTERN_6 = "8D 4D D4 FF 15 ? ? ? ? 66 ? ? ? ? ? ? ? B8 00 00 E0 43 75 05 B8";
        constexpr const char * PATTERN_7 = "8B 45 C0 8B ? ? ? ? ? 8B 4D E4 51 8A 04 C2 50 FF 15 ? ? ? ? 8B D0 8D 4D E0 FF D6 50 FF D7";
        constexpr const char * PATTERN_8 = "8B ? ? ? ? ? 50 52 FF D3 8B D0 8D 4D B0 FF D6 50 FF D7 8B D0 8D 4D AC FF D6 50 68 ? ? ? ? FF D7 8B D0 8D 4D A8";

        uintptr_t zModule = (uintptr_t) ::GetModuleHandle(NULL);

        uintptr_t zAddress_1 = (uintptr_t) ::GetProcAddress(::LoadLibrary("MSVBVM60"), "rtcDoEvents") + 0x07;
        uintptr_t zAddress_2 = Memory::Find(zModule, PATTERN_2, true);
        uintptr_t zAddress_3 = Memory::Find(zModule, PATTERN_3, true);

        Memory::Create_Detour(zAddress_1, (uintptr_t) & On_Hook_Tick_Trampoline, s_Detour_1);
        Memory::Create_Detour(zAddress_2, (uintptr_t) & On_Hook_Recv_Trampoline, s_Detour_2);
        Memory::Create_Detour(zAddress_3, (uintptr_t) & On_Hook_Send_Trampoline, s_Detour_3);

        s_Memory_1 = Memory::Find(zModule, PATTERN_4, false);
        s_Memory_1 = * (uint32_t *) (s_Memory_1 + 1);
        s_Memory_2 = Memory::Find(zModule, PATTERN_5, true);
        s_Memory_3 = Memory::Find(zModule, PATTERN_6, true);
        s_Memory_4 = Memory::Find(zModule, PATTERN_7, true);
        s_Memory_5 = Memory::Find(zModule, PATTERN_8, false);
        s_Memory_5 = * (uint32_t *) (s_Memory_5 + 2);

        Controller::On_Load(SETTING_NAME);

        /* TODO: REMOVE */
        Controller::Potion::Set_Red_Type(542);
        Controller::Potion::Set_Blue_Type(541);
        Core::Update_Mode(true);
        //Core::Robot::Set_Action_Emulation(true); // this was removed from code, because it was too powerfull to open source it
        /* TODO: REMOVE */

        Trace(L"Initialised [0x%X] [0x%X] [0x%X] [0x%X] [0x%X] [0x%X] [0x%X] [0x%X]",
            zAddress_1, zAddress_2, zAddress_3, s_Memory_1, s_Memory_2, s_Memory_3, s_Memory_4, s_Memory_5);
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