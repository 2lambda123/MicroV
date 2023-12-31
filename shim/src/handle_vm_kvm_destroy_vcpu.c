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

#include <detect_hypervisor.h>
#include <g_mut_hndl.h>
#include <mv_constants.h>
#include <mv_hypercall.h>
#include <mv_types.h>
#include <platform.h>
#include <shim_vcpu_t.h>

/**
 * <!-- description -->
 *   @brief Handles the execution of kvm_create_vcpu.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_vcpu the VCPU to destroy
 */
void
handle_vm_kvm_destroy_vcpu(struct shim_vcpu_t *const pmut_vcpu) NOEXCEPT
{
    platform_expects(MV_INVALID_HANDLE != g_mut_hndl);
    platform_expects(NULL != pmut_vcpu);

    if (detect_hypervisor()) {
        return;
    }

    platform_expects(MV_STATUS_SUCCESS == mv_vs_op_destroy_vs(g_mut_hndl, pmut_vcpu->vsid));
    platform_expects(MV_STATUS_SUCCESS == mv_vp_op_destroy_vp(g_mut_hndl, pmut_vcpu->vpid));
}
