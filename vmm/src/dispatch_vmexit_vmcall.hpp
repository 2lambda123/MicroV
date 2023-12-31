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

#ifndef DISPATCH_VMEXIT_VMCALL_HPP
#define DISPATCH_VMEXIT_VMCALL_HPP

#include <bf_syscall_t.hpp>
#include <dispatch_abi_helpers.hpp>
#include <dispatch_vmcall_mv_debug_op.hpp>
#include <dispatch_vmcall_mv_handle_op.hpp>
#include <dispatch_vmcall_mv_id_op.hpp>
#include <dispatch_vmcall_mv_pp_op.hpp>
#include <dispatch_vmcall_mv_vm_op.hpp>
#include <dispatch_vmcall_mv_vp_op.hpp>
#include <dispatch_vmcall_mv_vs_op.hpp>
#include <errc_types.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <mv_constants.hpp>
#include <page_pool_t.hpp>
#include <pp_pool_t.hpp>
#include <tls_t.hpp>
#include <vm_pool_t.hpp>
#include <vp_pool_t.hpp>
#include <vs_pool_t.hpp>

#include <bsl/convert.hpp>
#include <bsl/debug.hpp>
#include <bsl/discard.hpp>

namespace microv
{
    /// <!-- description -->
    ///   @brief Dispatches VMCALL VMExits.
    ///
    /// <!-- inputs/outputs -->
    ///   @param gs the gs_t to use
    ///   @param mut_tls the tls_t to use
    ///   @param mut_sys the bf_syscall_t to use
    ///   @param mut_page_pool the page_pool_t to use
    ///   @param intrinsic the intrinsic_t to use
    ///   @param mut_pp_pool the pp_pool_t to use
    ///   @param mut_vm_pool the vm_pool_t to use
    ///   @param mut_vp_pool the vp_pool_t to use
    ///   @param mut_vs_pool the vs_pool_t to use
    ///   @param vsid the ID of the VS that generated the VMExit
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     and friends otherwise
    ///
    [[nodiscard]] constexpr auto
    dispatch_vmexit_vmcall(
        gs_t const &gs,
        tls_t &mut_tls,
        syscall::bf_syscall_t &mut_sys,
        page_pool_t &mut_page_pool,
        intrinsic_t const &intrinsic,
        pp_pool_t &mut_pp_pool,
        vm_pool_t &mut_vm_pool,
        vp_pool_t &mut_vp_pool,
        vs_pool_t &mut_vs_pool,
        bsl::safe_u16 const &vsid) noexcept -> bsl::errc_type
    {
        mut_tls.handling_vmcall = true;

        switch (hypercall::mv_hypercall_opcode(get_reg_hypercall(mut_sys)).get()) {
            case hypercall::MV_ID_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_id_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_HANDLE_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_handle_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_DEBUG_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_debug_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_PP_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_pp_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_VM_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_vm_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_VP_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_vp_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            case hypercall::MV_VS_OP_VAL.get(): {
                auto const ret{dispatch_vmcall_mv_vs_op(
                    gs,
                    mut_tls,
                    mut_sys,
                    mut_page_pool,
                    intrinsic,
                    mut_pp_pool,
                    mut_vm_pool,
                    mut_vp_pool,
                    mut_vs_pool,
                    vsid)};

                if (bsl::unlikely(!ret)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                set_reg_return(mut_sys, hypercall::MV_STATUS_SUCCESS);
                return ret;
            }

            default: {
                break;
            }
        }

        return report_hypercall_unknown_unsupported(mut_sys);
    }
}

#endif
