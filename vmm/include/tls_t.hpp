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

#ifndef TLS_T_HPP
#define TLS_T_HPP

#include <bsl/convert.hpp>
#include <bsl/safe_integral.hpp>

namespace microv
{
    /// @class microv::tls_t
    ///
    /// <!-- description -->
    ///   @brief Defines MicroV's Thread Local Storage (TLS).
    ///
    struct tls_t final
    {
        /// @brief stores the ID of the PP associated with this TLS
        bsl::safe_u16 ppid;
        /// @brief stores the total number of online PPs
        bsl::safe_u16 online_pps;

        /// @brief stores the ID of the VM that is active on this PP
        bsl::safe_u16 active_vmid;
        /// @brief stores the ID of the VP that is active on this PP
        bsl::safe_u16 active_vpid;
        /// @brief stores the ID of the VS that is active on this PP
        bsl::safe_u16 active_vsid;

        /// @brief stores the ID of the parent VM
        bsl::safe_u16 parent_vmid;
        /// @brief stores the ID of the parent VP
        bsl::safe_u16 parent_vpid;
        /// @brief stores the ID of the parent VS
        bsl::safe_u16 parent_vsid;

        /// @brief tells the VMExit handler that we are in a vmcall
        bool handling_vmcall;
    };

    /// @brief defines the max size supported for the TLS block
    constexpr auto MAX_TLS_SIZE{HYPERVISOR_PAGE_SIZE};

    /// @brief ensure that the tls_t does not exceed the max supported size
    static_assert(!(sizeof(tls_t) > MAX_TLS_SIZE));
}

#endif
