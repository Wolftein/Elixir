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

#include "Foundation/Kernel/Elixir-Memory.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Memory
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uintptr_t Disassemble(uintptr_t Address, uintptr_t Least)
    {
        static const char zMethod[]
            = "\x60\xFC\x33\xD2\x8B\x74\x24\x24\x8B\xEC\x68\x1C\xF7\x97\x10\x68"
              "\x80\x67\x1C\xF7\x68\x18\x97\x38\x17\x68\x18\xB7\x1C\x10\x68\x17"
              "\x2C\x30\x17\x68\x17\x30\x17\x18\x68\x47\xF5\x15\xF7\x68\x48\x37"
              "\x10\x4C\x68\xF7\xE7\x2C\x27\x68\x87\x60\xAC\xF7\x68\x52\x1C\x12"
              "\x1C\x68\x1C\x87\x10\x7C\x68\x1C\x70\x1C\x20\x68\x2B\x60\x67\x47"
              "\x68\x11\x10\x21\x20\x68\x25\x16\x12\x40\x68\x22\x20\x87\x82\x68"
              "\x20\x12\x20\x47\x68\x19\x14\x10\x13\x68\x13\x10\x27\x18\x68\x60"
              "\x82\x85\x28\x68\x45\x40\x12\x15\x68\xC7\xA0\x16\x50\x68\x12\x18"
              "\x19\x28\x68\x12\x18\x40\xF2\x68\x27\x41\x15\x19\x68\x11\xF0\xF0"
              "\x50\xB9\x10\x47\x12\x15\x51\x68\x47\x12\x15\x11\x68\x12\x15\x11"
              "\x10\x68\x15\x11\x10\x47\xB8\x15\x20\x47\x12\x50\x50\x68\x10\x1A"
              "\x47\x12\x80\xC1\x10\x51\x80\xE9\x20\x51\x33\xC9\x49\x41\x8B\xFC"
              "\xAC\x8A\xF8\x8A\x27\x47\xC0\xEC\x04\x2A\xC4\x73\xF6\x8A\x47\xFF"
              "\x24\x0F\x3C\x0C\x75\x03\x5A\xF7\xD2\x42\x3C\x00\x74\x42\x3C\x01"
              "\x74\xDB\x83\xC7\x51\x3C\x0A\x74\xD7\x8B\x7D\x24\x42\x3C\x02\x74"
              "\x2F\x3C\x07\x74\x33\x3C\x0B\x0F\x84\x7E\x00\x00\x00\x42\x3C\x03"
              "\x74\x1E\x3C\x08\x74\x22\x42\x3C\x04\x74\x15\x42\x42\x60\xB0\x66"
              "\xF2\xAE\x61\x75\x02\x4A\x4A\x3C\x09\x74\x0D\x2C\x05\x74\x6C\x42"
              "\x8B\xE5\x89\x54\x24\x1C\x61\xC3\xAC\x8A\xE0\xC0\xE8\x07\x72\x12"
              "\x74\x14\x80\xC2\x04\x60\xB0\x67\xF2\xAE\x61\x75\x09\x80\xEA\x03"
              "\xFE\xC8\x75\xDC\x42\x40\x80\xE4\x07\x60\xB0\x67\xF2\xAE\x61\x74"
              "\x13\x80\xFC\x04\x74\x17\x80\xFC\x05\x75\xC5\xFE\xC8\x74\xC1\x80"
              "\xC2\x04\xEB\xBC\x66\x3D\x00\x06\x75\xB6\x42\xEB\xB2\x3C\x00\x75"
              "\xAE\xAC\x24\x07\x2C\x05\x75\xA7\x42\xEB\xE4\xF6\x06\x38\x75\xA8"
              "\xB0\x08\xD0\xEF\x14\x00\xE9\x72\xFF\xFF\xFF\x80\xEF\xA0\x80\xFF"
              "\x04\x73\x82\x60\xB0\x67\xF2\xAE\x61\x75\x02\x4A\x4A\x60\xB0\x66"
              "\xF2\xAE\x61\x0F\x84\x76\xFF\xFF\xFF\x0F\x85\x66\xFF\xFF\xFF";

        for (auto zAddress = Address, zLeast = Least; zAddress - Address < zLeast; Least = zAddress - Address)
        {
            zAddress += ((uint32_t (__cdecl *)(uintptr_t)) & zMethod)(zAddress);
        }
        return Least;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uintptr_t Find(uintptr_t Module, const char * Pattern, bool Backtrace)
    {
        MODULEINFO zModule { 0 };

        if (GetModuleInformation(GetCurrentProcess(), (HMODULE) Module, & zModule, sizeof(zModule)))
        {
            const auto zAddress = (uintptr_t) zModule.lpBaseOfDll;

            return Find(zAddress, zAddress + zModule.SizeOfImage, Pattern, Backtrace);
        }
        return 0;
    }


    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    uintptr_t Find(uintptr_t Address, uintptr_t Limit, const char * Pattern, bool Backtrace)
    {
#define GetByte(X) ((X[0] >= '0' && X[0] <= '9' ? (X[0] - '0') : ((X[0] & (~ 0x20)) - 'A' + 0xA)) << 4 | \
                    (X[1] >= '0' && X[1] <= '9' ? (X[1] - '0') : ((X[1] & (~ 0x20)) - 'A' + 0xA)))

        for (uintptr_t zAddress = Address; zAddress <= Limit; ++zAddress)
        {
            auto zMemory = (uint8_t *) zAddress;
            auto zFound = true;

            for (auto zPattern = Pattern; zFound && * zPattern != 0u; ++zMemory)
            {
                zFound &= (* zPattern == '?' || * zMemory == GetByte(zPattern));
                zPattern += (* zPattern == '?' ? 1 : 2);
                zPattern += (* zPattern != 0u ? 1 : 0);
            }

            if (zFound)
            {
                if (Backtrace)
                {
                    while (* (uint16_t *) (zAddress - 0x01) != 0xEC8B || * (uint8_t *) (zAddress - 0x02) != 0x55)
                    {
                        --zAddress;
                    }
                    return zAddress - 0x02;
                }
                return zAddress;
            }
        }
        return 0u;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Create_Detour(uintptr_t Address, uintptr_t Destination, Detour & Detour)
    {
        auto zRequirement = Disassemble(Address, 0x05);

        Detour.Destination = (uintptr_t) ::VirtualAlloc(
            nullptr, zRequirement + 0x05, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        ::RtlCopyMemory((void *) Detour.Destination, (void *) (Detour.Source = Address), zRequirement);

        // writes the jump from the original opcode to our redirect address and
        // writes the jump from our opcode to the original opcode
        Write_Opcode_Jump(Detour.Source, Destination);
        Write_Opcode_Jump(Detour.Destination + zRequirement, Address + zRequirement);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Remove_Detour(Detour & Detour)
    {
        if (Detour.Source != 0u && Detour.Destination != 0u)
        {
            Write_Opcode(Detour.Source, (uint8_t *) Detour.Destination, 0x05);

            ::VirtualFree((void *) Detour.Destination, 0, MEM_RELEASE);
        }
        ::RtlZeroMemory(& Detour, sizeof(Detour));
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Write_Opcode(uintptr_t Address, const uint8_t * Opcode, uint32_t Length, uint32_t Count)
    {
        ULONG zProtection;

        ::VirtualProtect((void *) Address, Length * Count, PAGE_EXECUTE_READWRITE, & zProtection);
        {
            for (uint32_t Index = 0u; Index < Count; ++Index)
            {
                ::RtlCopyMemory((void *) (Address + (Index * Length)), Opcode, Length);
            }
        }
        ::VirtualProtect((void *) Address, Length * Count, zProtection, & zProtection);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Write_Opcode_Nop(uintptr_t Address, uint32_t Count)
    {
        uint8_t zOpcode[] = {
            0x90
        };
        Write_Opcode(Address, zOpcode, sizeof(zOpcode), Count);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Write_Opcode_Call(uintptr_t Address, uintptr_t Destination)
    {
        uint8_t zOpcode[] = {
            0xE8,
            0x00,
            0x00,
            0x00,
            0x00
        };
        * ((uint32_t *) & zOpcode[0x01]) = Destination - Address - 0x05;

        Write_Opcode(Address, zOpcode, sizeof(zOpcode));
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Write_Opcode_Jump(uintptr_t Address, uintptr_t Destination)
    {
        uint8_t zOpcode[] = {
            0xE9,
            0x00,
            0x00,
            0x00,
            0x00
        };
        * ((uintptr_t *) & zOpcode[0x01]) = Destination - Address - 0x05;

        Write_Opcode(Address, zOpcode, sizeof(zOpcode));
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void Write_Opcode_Ret(uintptr_t Address, uintptr_t Count)
    {
        if (Count > 0)
        {
            uint8_t zOpcode[] = {
                0xC2
            };

            Write_Opcode(Address, zOpcode, sizeof(zOpcode));
        }
        else
        {
            uint8_t zOpcode[] = {
                0xC3,
                0x00,
                0x00
            };

            * ((uint16_t *) & zOpcode[0x01]) = Count * 2;

            Write_Opcode(Address, zOpcode, sizeof(zOpcode));
        }
    }
}