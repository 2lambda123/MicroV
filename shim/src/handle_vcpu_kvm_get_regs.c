/**
 * @copyright
 * Copyright (C) 2020 Assured Information Security, Inc.
 *
 * @copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * @copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <debug.h>
#include <detect_hypervisor.h>
#include <g_mut_hndl.h>
#include <kvm_regs.h>
#include <mv_constants.h>
#include <mv_hypercall.h>
#include <mv_rdl_t.h>
#include <mv_reg_t.h>
#include <mv_types.h>
#include <platform.h>
#include <shared_page_for_current_pp.h>
#include <shim_vcpu_t.h>

/** @brief stores the structure of the RDL we will send to MicroV */
static struct mv_rdl_t const g_reg_rdl = {
    .reg0 = ((uint64_t)0),
    .reg1 = ((uint64_t)0),
    .reg2 = ((uint64_t)0),
    .reg3 = ((uint64_t)0),
    .reg4 = ((uint64_t)0),
    .reg5 = ((uint64_t)0),
    .reg6 = ((uint64_t)0),
    .reg7 = ((uint64_t)0),
    .reserved1 = ((uint64_t)0),
    .reserved2 = ((uint64_t)0),
    .reserved3 = ((uint64_t)0),
    .num_entries = ((uint64_t)0),

    {
        {(uint64_t)mv_reg_t_rax, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rbx, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rcx, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rdx, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rsi, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rdi, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rsp, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rbp, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r8, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r9, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r10, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r11, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r12, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r13, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r14, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_r15, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rip, ((uint64_t)0)},
        {(uint64_t)mv_reg_t_rflags, ((uint64_t)0)},
    }};

/**
 * <!-- description -->
 *   @brief Handles the execution of kvm_get_regs.
 *
 * <!-- inputs/outputs -->
 *   @param vcpu arguments received from private data
 *   @param pmut_args the arguments provided by userspace
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
handle_vcpu_kvm_get_regs(
    struct shim_vcpu_t const *const vcpu, struct kvm_regs *const pmut_args) NOEXCEPT
{
    uint64_t mut_i;

    struct mv_rdl_t *pmut_mut_rdl;
    struct mv_rdl_entry_t const *mut_src_entry;
    struct mv_rdl_entry_t *pmut_mut_dst_entry;

    platform_expects(MV_INVALID_HANDLE != g_mut_hndl);
    platform_expects(NULL != vcpu);
    platform_expects(NULL != pmut_args);

    if (detect_hypervisor()) {
        bferror("The shim is not running in a VM. Did you forget to start MicroV?");
        return SHIM_FAILURE;
    }

    pmut_mut_rdl = (struct mv_rdl_t *)shared_page_for_current_pp();
    platform_expects(NULL != pmut_mut_rdl);

    pmut_mut_rdl->num_entries = ((uint64_t)0);
    while (1) {
        platform_expects(pmut_mut_rdl->num_entries < MV_RDL_MAX_ENTRIES);

        mut_src_entry = &g_reg_rdl.entries[pmut_mut_rdl->num_entries];
        pmut_mut_dst_entry = &pmut_mut_rdl->entries[pmut_mut_rdl->num_entries];

        if (((uint64_t)0) == mut_src_entry->reg) {
            break;
        }

        pmut_mut_dst_entry->reg = mut_src_entry->reg;
        ++pmut_mut_rdl->num_entries;
    }

    if (mv_vs_op_reg_get_list(g_mut_hndl, vcpu->vsid)) {
        bferror("mv_vs_op_reg_get_list failed");
        return SHIM_FAILURE;
    }

    if (pmut_mut_rdl->num_entries >= MV_RDL_MAX_ENTRIES) {
        bferror("the RDL's num_entries is no longer valid");
        return SHIM_FAILURE;
    }

    for (mut_i = ((uint64_t)0); mut_i < pmut_mut_rdl->num_entries; ++mut_i) {
        mut_src_entry = &pmut_mut_rdl->entries[mut_i];

        switch ((int32_t)mut_src_entry->reg) {
            case mv_reg_t_rax: {
                pmut_args->rax = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rbx: {
                pmut_args->rbx = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rcx: {
                pmut_args->rcx = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rdx: {
                pmut_args->rdx = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rsi: {
                pmut_args->rsi = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rdi: {
                pmut_args->rdi = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rsp: {
                pmut_args->rsp = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rbp: {
                pmut_args->rbp = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r8: {
                pmut_args->r8 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r9: {
                pmut_args->r9 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r10: {
                pmut_args->r10 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r11: {
                pmut_args->r11 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r12: {
                pmut_args->r12 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r13: {
                pmut_args->r13 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r14: {
                pmut_args->r14 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_r15: {
                pmut_args->r15 = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rip: {
                pmut_args->rip = mut_src_entry->val;
                continue;
            }

            case mv_reg_t_rflags: {
                pmut_args->rflags = mut_src_entry->val;
                continue;
            }

            default: {
                break;
            }
        }

        if (((uint64_t)0) != mut_src_entry->reg) {
            bferror("unknown mv_reg_t returned by MicroV");
            return SHIM_FAILURE;
        }

        bferror("MicroV returned a num_entries that does not match the shim's");
        return SHIM_FAILURE;
    }

    return SHIM_SUCCESS;
}
