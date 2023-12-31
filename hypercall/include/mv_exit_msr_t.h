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

#ifndef MV_EXIT_MSR_T_HPP
#define MV_EXIT_MSR_T_HPP

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#pragma pack(push, 1)

/** @brief The mv_exit_mmio_t defines a read access */
#define MV_EXIT_MMIO_READ ((uint64_t)0x0000000000000001)
/** @brief The mv_exit_mmio_t defines a write access */
#define MV_EXIT_MMIO_WRITE ((uint64_t)0x0000000000000002)
/** @brief The mv_exit_mmio_t defines an execute access */
#define MV_EXIT_MMIO_EXECUTE ((uint64_t)0x0000000000000004)

    /**
     * <!-- description -->
     *   @brief See mv_vs_op_run for more details
     */
    struct mv_exit_mmio_t
    {
        /** @brief stores the GPA of the MMIO access */
        uint64_t gpa;
        /** @brief stores the MV_EXIT_MMIO flags */
        uint64_t flags;
    };

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
