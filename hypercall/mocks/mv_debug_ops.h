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

#ifndef MOCKS_MV_DEBUG_OPS_HPP
#define MOCKS_MV_DEBUG_OPS_HPP

#include <mv_types.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /** @brief stores whether or not mv_debug_op_out executed */
    extern int32_t g_mut_mv_debug_op_out_executed;

    /**
     * <!-- description -->
     *   @brief This hypercall tells MicroV to output reg0 and reg1 to the
     *     console device MicroV is currently using for debugging. The purpose
     *     of this hypercall is to provide a simple means for debugging issues
     *     with the guest and can be used by a VM from both userspace and the
     *     kernel, even when the operating system is not fully bootstrapped or
     *     is in a failure state.
     *
     * <!-- inputs/outputs -->
     *   @param val1 The first value to output to MicroV's console
     *   @param val2 The second value to output to MicroV's console
     */
    static inline void
    mv_debug_op_out(uint64_t const val1, uint64_t const val2) NOEXCEPT
    {
        g_mut_mv_debug_op_out_executed = 1;
        printf("0x%" PRIx64 " 0x%" PRIx64 "\n", val1, val2);
    }

#ifdef __cplusplus
}
#endif

#endif
