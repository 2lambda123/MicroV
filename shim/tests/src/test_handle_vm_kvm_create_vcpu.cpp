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

#include "../../include/handle_vm_kvm_create_vcpu.h"

#include <helpers.hpp>
#include <shim_vcpu_t.h>
#include <shim_vm_t.h>

#include <bsl/convert.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/ut.hpp>

namespace shim
{
    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        init_tests();
        constexpr auto handle{&handle_vm_kvm_create_vcpu};

        bsl::ut_scenario{"success"} = []() noexcept {
            bsl::ut_given{} = [&]() noexcept {
                shim_vm_t mut_vm{};
                shim_vcpu_t *pmut_mut_vcpu{};
                constexpr auto vpid{23_u16};
                constexpr auto vsid{42_u16};
                bsl::ut_when{} = [&]() noexcept {
                    g_mut_mv_vp_op_create_vp = vpid.get();
                    g_mut_mv_vs_op_create_vs = vsid.get();
                    bsl::ut_then{} = [&]() noexcept {
                        bsl::ut_check(SHIM_SUCCESS == handle(&mut_vm, &pmut_mut_vcpu));
                        bsl::ut_check(vpid == pmut_mut_vcpu->vpid);
                        bsl::ut_check(vsid == pmut_mut_vcpu->vsid);
                    };
                };
            };
        };

        bsl::ut_scenario{"hypervisor not detected"} = []() noexcept {
            bsl::ut_given{} = [&]() noexcept {
                shim_vm_t mut_vm{};
                shim_vcpu_t *pmut_mut_vcpu{};
                bsl::ut_when{} = [&]() noexcept {
                    g_mut_hypervisor_detected = false;
                    bsl::ut_then{} = [&]() noexcept {
                        bsl::ut_check(SHIM_FAILURE == handle(&mut_vm, &pmut_mut_vcpu));
                    };
                    bsl::ut_cleanup{} = [&]() noexcept {
                        g_mut_hypervisor_detected = true;
                    };
                };
            };
        };

        bsl::ut_scenario{"mv_vp_op_create_vp fails"} = []() noexcept {
            bsl::ut_given{} = [&]() noexcept {
                shim_vm_t mut_vm{};
                shim_vcpu_t *pmut_mut_vcpu{};
                bsl::ut_when{} = [&]() noexcept {
                    g_mut_mv_vp_op_create_vp = MV_INVALID_ID;
                    bsl::ut_then{} = [&]() noexcept {
                        bsl::ut_check(SHIM_FAILURE == handle(&mut_vm, &pmut_mut_vcpu));
                    };
                    bsl::ut_cleanup{} = [&]() noexcept {
                        g_mut_mv_vp_op_create_vp = {};
                    };
                };
            };
        };

        bsl::ut_scenario{"mv_vs_op_create_vs fails"} = []() noexcept {
            bsl::ut_given{} = [&]() noexcept {
                shim_vm_t mut_vm{};
                shim_vcpu_t *pmut_mut_vcpu{};
                bsl::ut_when{} = [&]() noexcept {
                    g_mut_mv_vs_op_create_vs = MV_INVALID_ID;
                    bsl::ut_then{} = [&]() noexcept {
                        bsl::ut_check(SHIM_FAILURE == handle(&mut_vm, &pmut_mut_vcpu));
                    };
                    bsl::ut_cleanup{} = [&]() noexcept {
                        g_mut_mv_vs_op_create_vs = {};
                    };
                };
            };
        };

        bsl::ut_scenario{"out of vms"} = []() noexcept {
            bsl::ut_given{} = [&]() noexcept {
                shim_vm_t mut_vm{};
                shim_vcpu_t *pmut_mut_vcpu{};
                bsl::ut_when{} = [&]() noexcept {
                    bsl::ut_then{} = [&]() noexcept {
                        bsl::ut_check(SHIM_SUCCESS == handle(&mut_vm, &pmut_mut_vcpu));
                        bsl::ut_check(SHIM_SUCCESS == handle(&mut_vm, &pmut_mut_vcpu));
                        bsl::ut_check(SHIM_FAILURE == handle(&mut_vm, &pmut_mut_vcpu));
                    };
                };
            };
        };

        return fini_tests();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    bsl::enable_color();
    return shim::tests();
}
