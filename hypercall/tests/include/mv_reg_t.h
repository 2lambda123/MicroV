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

#ifndef MV_REG_T_H
#define MV_REG_T_H

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief stores the max value for a mv_reg_t */
#define MV_MAX_REG_T 2

#ifdef __cplusplus
    /**
     * <!-- description -->
     *   @brief Defines which register to use for certain hypercalls
     */
    enum mv_reg_t : int32_t
#else
/**
     * <!-- description -->
     *   @brief Defines which register to use for certain hypercalls
     */
enum mv_reg_t
#endif
    {
        /** @brief defines an unsupported register */
        mv_reg_t_unsupported = 0,
        /** @brief defines a dummy register */
        mv_reg_t_dummy = 1,
        /** @brief defines and invalid mv_reg_t */
        mv_reg_t_invalid = MV_MAX_REG_T,
    };

#ifdef __cplusplus
}
#endif

#endif
