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

#ifndef INTRINSIC_HPP
#define INTRINSIC_HPP

#include <gs_t.hpp>
#include <intrinsic_cpuid_impl.hpp>
#include <intrinsic_xrstr_impl.hpp>
#include <intrinsic_xsave_impl.hpp>
#include <tls_t.hpp>

#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/safe_integral.hpp>

namespace microv
{
    /// @class microv::intrinsic_t
    ///
    /// <!-- description -->
    ///   @brief Provides raw access to intrinsics.
    ///
    class intrinsic_t final
    {
    public:
        /// <!-- description -->
        ///   @brief Executes the CPUID instruction given the provided
        ///     EAX and ECX and returns the results.
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_rax the index used by CPUID, returns resulting rax
        ///   @param mut_rbx returns resulting rbx
        ///   @param mut_rcx the subindex used by CPUID, returns the resulting rcx
        ///   @param mut_rdx returns resulting rdx
        ///
        static constexpr void
        cpuid(
            bsl::safe_u64 &mut_rax,
            bsl::safe_u64 &mut_rbx,
            bsl::safe_u64 &mut_rcx,
            bsl::safe_u64 &mut_rdx) noexcept
        {
            intrinsic_cpuid_impl(mut_rax.data(), mut_rbx.data(), mut_rcx.data(), mut_rdx.data());
        }

        /// <!-- description -->
        ///   @brief Executes the XSAVE instruction given the provided address
        ///     to the xsave region.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pmut_xsave a pointer to the xsave region to use
        ///
        static constexpr void
        xsave(void *const pmut_xsave) noexcept
        {
            intrinsic_xsave_impl(pmut_xsave);
        }

        /// <!-- description -->
        ///   @brief Executes the XRSTOR instruction given the provided address
        ///     to the xsave region.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pmut_xsave a pointer to the xsave region to use
        ///
        static constexpr void
        xrstr(void *const pmut_xsave) noexcept
        {
            intrinsic_xrstr_impl(pmut_xsave);
        }
    };
}

#endif
