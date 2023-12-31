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

#ifndef TLS_INITIALIZE_HPP
#define TLS_INITIALIZE_HPP

#include <bf_syscall_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/errc_type.hpp>

namespace microv
{
    /// <!-- description -->
    ///   @brief Initializes the Thread Local Storage (TLS).
    ///
    /// <!-- inputs/outputs -->
    ///   @param mut_tls the tls_t to use
    ///   @param sys the bf_syscall_t to use
    ///   @param page_pool the page_pool_t to use
    ///   @param intrinsic the intrinsic_t to use
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     and friends otherwise
    ///
    [[nodiscard]] constexpr auto
    tls_initialize(
        tls_t &mut_tls,
        syscall::bf_syscall_t const &sys,
        page_pool_t const &page_pool,
        intrinsic_t const &intrinsic) noexcept -> bsl::errc_type
    {
        bsl::discard(page_pool);
        bsl::discard(intrinsic);

        mut_tls.ppid = sys.bf_tls_ppid();
        mut_tls.online_pps = sys.bf_tls_online_pps();

        mut_tls.active_vmid = hypercall::MV_INVALID_ID;
        mut_tls.active_vpid = hypercall::MV_INVALID_ID;
        mut_tls.active_vsid = hypercall::MV_INVALID_ID;

        mut_tls.parent_vmid = hypercall::MV_INVALID_ID;
        mut_tls.parent_vpid = hypercall::MV_INVALID_ID;
        mut_tls.parent_vsid = hypercall::MV_INVALID_ID;

        return bsl::errc_success;
    }
}

#endif
