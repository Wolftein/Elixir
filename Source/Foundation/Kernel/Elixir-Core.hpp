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

#include <algorithm>
#include <functional>
#include <mutex>
#include <vector>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <windows.h>
#include <psapi.h>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Elixir
{
    //
    // Get a random between Lower and Upper.
    //
    uint32_t Random(uint32_t Lower, uint32_t Upper);

    //
    // Trace a message (only if _ELIXIR_DEBUG_ is enabled).
    //
    template<typename... Args>
    void Trace(const wchar_t * Format, Args && ... Arguments)
    {
#ifdef    _ELIXIR_DEBUG_
        wchar_t zBuffer[4096] = { '[', 'E', 'l', 'i', 'x', 'i', 'r', ']', ' ' };

        ::_swprintf_c(& zBuffer[9], (sizeof(zBuffer) / sizeof(wchar_t)) - 9, Format, Arguments...);

        ::OutputDebugStringW(zBuffer);
#endif // _ELIXIR_DEBUG_
    }

    //
    // Trace a message (only if _ELIXIR_DEBUG_ is enabled).
    //
    void Trace_Message(const wchar_t * Header, uint32_t Handle, uint8_t * Message, uint32_t Count);

    //
    // Calculate the size of the given array.
    //
    // \note if the array is known at compile time, then it will be calculated at compile time.
    //
    template<typename Type, uint32_t Length>
    constexpr uint32_t Expr_Size(Type(&)[Length])
    {
        return Length;
    }

    //
    // Calculate the length of the given string.
    //
    // \note if the string is known at compile time, then it will be calculated at compile time.
    //
    template<typename Type>
    constexpr uint32_t Expr_Length(const Type Text)
    {
        return (* Text) ? 1u + Expr_Length(Text + 1u) : 0u;
    }

    //
    // Calculate a unique identifier (hash) for the given string.
    //
    // \note if the string is known at compile time, then it will be calculated at compile time.
    //
    template<typename Type>
    constexpr uint32_t Expr_Hash(const Type Text, uint32_t Length = UINT32_MAX)
    {
        return (Length && (* Text)) ? (Expr_Hash(Text + 1u, Length - 1u) * 33u) ^ (* Text & ~32u) : 5381u;
    }
}