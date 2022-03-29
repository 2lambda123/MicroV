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

#ifndef SHARED_PAGE_FOR_CURRENT_PP_H
#define SHARED_PAGE_FOR_CURRENT_PP_H

#include <mv_types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * <!-- description -->
     *   @brief Returns the shared page for the current PP. Note that this
     *     cannot be called until shim_init has completed.
     *     When done using the shared page, the caller must call
     *     release_shared_page_for_current_pp().
     *
     * <!-- inputs/outputs -->
     *   @return  Returns the shared page for the current PP
     */
    NODISCARD void *shared_page_for_current_pp(void) NOEXCEPT;

    /**
     * <!-- description -->
     *   @brief Releases the shared page. Note that this
     *     cannot be called until shim_init has completed.
     */
    void release_shared_page_for_current_pp(void * user_data) NOEXCEPT;

    void shared_page_for_curent_pp__before_mv_op(void *user_data) NOEXCEPT;
    void shared_page_for_curent_pp__after_mv_op(void *user_data) NOEXCEPT;


#ifdef __cplusplus
}
#endif

#endif
