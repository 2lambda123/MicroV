/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef MV_RUN_T_HPP
#define MV_RUN_T_HPP

#include <bsl/array.hpp>
#include <bsl/convert.hpp>
#include <bsl/safe_integral.hpp>

#pragma pack(push, 1)

namespace hypercall
{
    /// @brief defines the max number of entires in the MDL
    constexpr auto MV_RUN_MAX_RESERVED{0x1000_u64};

    /// <!-- description -->
    ///   @brief TODO
    ///
    struct mv_run_t final
    {
        /// @brief reserved
        bsl::array<bsl::uint8, MV_RUN_MAX_RESERVED.get()> reserved;
    };
}

#pragma pack(pop)

#endif
