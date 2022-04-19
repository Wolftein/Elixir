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

#include "Foundation/Kernel/Elixir-Core.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir::Memory
{
    //
    // A Detour is a trampoline function for re-routing other function(s).
    //
    struct Detour
    {
        uintptr_t Source, Destination;
    };

    //
    // Find an address given a byte-code pattern.
    //
    // \return the address where the byte-code pattern matches or \ref nullptr if wasn't found
    //
    uintptr_t Find(uintptr_t Module, const char * Pattern, bool Backtrace = false);

    //
    // Find an address given a byte-code pattern.
    //
    // \return the address where the byte-code pattern matches or \ref nullptr if wasn't found
    //
    uintptr_t Find(uintptr_t Address, uintptr_t Limit, const char * Pattern, bool Backtrace = false);

    //
    // Creates a \see TDetour.
    //
    // \param Address     the detour's old address
    // \param Destination the detour's new address
    // \param Detour      the detour
    //
    void Create_Detour(uintptr_t Address, uintptr_t Destination, Detour & Detour);

    //
    // Remove a \see TDetour.
    //
    // \param Detour the detour
    //
    void Remove_Detour(Detour & Detour);

    //
    // Write any opcode.
    //
    // \param Address the opcode's address
    // \param Opcode  the opcode
    // \param Length  the opcode's size (in bytes)
    // \param Count   the opcode's count
    //
    void Write_Opcode(uintptr_t Address, const uint8_t * Opcode, uint32_t Length, uint32_t Count = 1);

    //
    // Write '0x90' opcode.
    //
    // \param Address the opcode's address
    // \param Count   the opcode's count
    //
    // \see Write_Opcode
    //
    void Write_Opcode_Nop(uintptr_t Address, uint32_t Count);

    //
    // Write '0xE8' opcode.
    //
    // \param Address     the opcode's address
    // \param Destination the opcode's destination address
    //
    // \see Write_Opcode
    //
    void Write_Opcode_Call(uintptr_t Address, uintptr_t Destination);

    //
    // Write '0xE9' opcode.
    //
    // \param Address     the opcode's address
    // \param Destination the opcode's destination address
    //
    // \see Write_Opcode
    //
    void Write_Opcode_Jump(uintptr_t Address, uintptr_t Destination);

    //
    // Write '0xC2' or '0xC3' opcode.
    //
    // \param Address the opcode's address
    // \param Count   the opcode's count
    //
    // \see Write_Opcode
    //
    void Write_Opcode_Ret(uintptr_t Address, uintptr_t Count);
}