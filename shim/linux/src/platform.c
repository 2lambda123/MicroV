/* SPDX-License-Identifier: SPDX-License-Identifier: GPL-2.0 OR MIT */

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

#include <asm/io.h>
#include <debug.h>
#include <linux/cpu.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/smp.h>
#include <linux/unistd.h>
#include <linux/vmalloc.h>
#include <platform.h>
#include <types.h>
#include <work_on_cpu_callback_args.h>

/**
 * <!-- description -->
 *   @brief If test is false, a contract violation has occurred. This
 *     should be used to assert preconditions that if not meet, would
 *     result in undefined behavior. These should not be tested by a
 *     unit test, meaning they are contract violations. These asserts
 *     are simply there as a sanity check during a debug build.
 *
 * <!-- inputs/outputs -->
 *   @param test the contract to check
 */
void
platform_expects(int const test) NOEXCEPT
{
    BUG_ON(!test);
}

/**
 * <!-- description -->
 *   @brief If test is false, a contract violation has occurred. This
 *     should be used to assert postconditions that if not meet, would
 *     result in undefined behavior. These should not be tested by a
 *     unit test, meaning they are contract violations. These asserts
 *     are simply there as a sanity check during a debug build.
 *
 * <!-- inputs/outputs -->
 *   @param test the contract to check
 */
void
platform_ensures(int const test) NOEXCEPT
{
    BUG_ON(!test);
}

/**
 * <!-- description -->
 *   @brief This function allocates read/write virtual memory from the
 *     kernel. This memory is not physically contiguous. The resulting
 *     pointer is at least 4k aligned, so use this function sparingly
 *     as it will always allocate at least one page. Use platform_free()
 *     to release this memory.
 *
 *   @note This function must zero the allocated memory
 *
 * <!-- inputs/outputs -->
 *   @param size the number of bytes to allocate
 *   @return Returns a pointer to the newly allocated memory on success.
 *     Returns a nullptr on failure.
 */
NODISCARD void *
platform_alloc(uint64_t const size) NOEXCEPT
{
    void *ret;
    platform_expects(0 != size);

    ret = vmalloc(size);
    if (((void *)0) == ret) {
        bferror("vmalloc failed");
        return ((void *)0);
    }

    return memset(ret, 0, size);
}

/**
 * <!-- description -->
 *   @brief This function frees memory previously allocated using the
 *     platform_alloc() function.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_ptr the pointer returned by platform_alloc(). If ptr is
 *     passed a nullptr, it will be ignored. Attempting to free memory
 *     more than once results in UB.
 *   @param size the number of bytes that were allocated. Note that this
 *     may or may not be ignored depending on the platform.
 */
void
platform_free(void *const pmut_ptr, uint64_t const size) NOEXCEPT
{
    (void)size;

    if (((void *)0) != pmut_ptr) {
        vfree(pmut_ptr);
    }
}

/**
 * <!-- description -->
 *   @brief Given a virtual address, this function returns the virtual
 *     address's physical address. Returns ((void *)0) if the conversion failed.
 *
 * <!-- inputs/outputs -->
 *   @param virt the virtual address to convert to a physical address
 *   @return Given a virtual address, this function returns the virtual
 *     address's physical address. Returns ((void *)0) if the conversion failed.
 */
NODISCARD uintptr_t
platform_virt_to_phys(void const *const virt) NOEXCEPT
{
    uintptr_t ret;

    if (is_vmalloc_addr(virt)) {
        ret = page_to_phys(vmalloc_to_page(virt));
    }
    else {
        ret = virt_to_phys((void *)virt);
    }

    return ret;
}

/**
 * <!-- description -->
 *   @brief Sets "num" bytes in the memory pointed to by "ptr" to "val".
 *     If the provided parameters are valid, returns 0, otherwise
 *     returns SHIM_FAILURE.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_ptr a pointer to the memory to set
 *   @param val the value to set each byte to
 *   @param num the number of bytes in "pmut_ptr" to set to "val".
 */
void
platform_memset(
    void *const pmut_ptr, uint8_t const val, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_ptr);
    memset(pmut_ptr, val, num);
}

/**
 * <!-- description -->
 *   @brief Copies "num" bytes from "src" to "pmut_dst". If "src" or "pmut_dst" are
 *     ((void *)0), returns SHIM_FAILURE, otherwise returns 0.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_dst a pointer to the memory to copy to
 *   @param src a pointer to the memory to copy from
 *   @param num the number of bytes to copy
 */
void
platform_memcpy(
    void *const pmut_dst, void const *const src, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_dst);
    platform_expects(((void *)0) != src);

    memcpy(pmut_dst, src, num);
}

/**
 * <!-- description -->
 *   @brief Locks the pages within a memory region starting at
 *     "pmut_ptr" and continuing for "num" bytes. Once locked, the
 *     memory is guaranteed to never be paged out to disk.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_ptr a pointer to the memory to lock
 *   @param num the number of bytes to lock.
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
platform_mlock(void *const pmut_ptr, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_ptr);
    platform_expects(((uint64_t)0) != num);

    /// TODO:
    /// - This needs to be implemented. For now, we use such small amounts
    ///   of memory that this is not a problem, but in the future it
    ///   will be.
    ///
    /// - Making a call to a syscall from the kernel will not work. On
    ///   newer kernels, pin_user_pages() seems like a good option, but
    ///   that API was just added and is not available for Ubuntu 20.04.
    ///
    /// - get_user_pages() is likely the way that this will have to be
    ///   implemented. This is what the IOMMU code uses, and it has to
    ///   do something similar here. Either way, I do not see this being
    ///   and easy function to implement.
    ///

    return SHIM_SUCCESS;
}

/**
 * <!-- description -->
 *   @brief Unlocks the pages within a memory region starting at
 *     "pmut_ptr" and continuing for "num" bytes. Once unlocked, the
 *     memory is allowed to be paged out to disk.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_ptr a pointer to the memory to unlock
 *   @param num the number of bytes to unlock.
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
platform_munlock(void *const pmut_ptr, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_ptr);
    platform_expects(((uint64_t)0) != num);

    /// TODO:
    /// - This needs to be implemented. For now, we use such small amounts
    ///   of memory that this is not a problem, but in the future it
    ///   will be.
    ///
    /// - Making a call to a syscall from the kernel will not work. On
    ///   newer kernels, pin_user_pages() seems like a good option, but
    ///   that API was just added and is not available for Ubuntu 20.04.
    ///
    /// - get_user_pages() is likely the way that this will have to be
    ///   implemented. This is what the IOMMU code uses, and it has to
    ///   do something similar here. Either way, I do not see this being
    ///   and easy function to implement.
    ///

    return SHIM_SUCCESS;
}

/**
 * <!-- description -->
 *   @brief Copies "num" bytes from "src" to "pmut_dst". Returns
 *     SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_dst a pointer to the memory to copy to
 *   @param src a pointer to the memory to copy from
 *   @param num the number of bytes to copy
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
platform_copy_from_user(
    void *const pmut_dst, void const *const src, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_dst);
    platform_expects(((void *)0) != src);

    return (int64_t)copy_from_user(pmut_dst, src, num);
}

/**
 * <!-- description -->
 *   @brief Copies "num" bytes from "src" to "pmut_dst". Returns
 *     SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_dst a pointer to the memory to copy to
 *   @param src a pointer to the memory to copy from
 *   @param num the number of bytes to copy
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
platform_copy_to_user(
    void *const pmut_dst, void const *const src, uint64_t const num) NOEXCEPT
{
    platform_expects(((void *)0) != pmut_dst);
    platform_expects(((void *)0) != src);

    return (int64_t)copy_to_user(pmut_dst, src, num);
}

/**
 * <!-- description -->
 *   @brief Returns the total number of online CPUs (i.e. PPs)
 *
 * <!-- inputs/outputs -->
 *   @return Returns the total number of online CPUs (i.e. PPs)
 */
NODISCARD uint32_t
platform_num_online_cpus(void) NOEXCEPT
{
    return num_online_cpus();
}

/**
 * <!-- description -->
 *   @brief Returns the current CPU (i.e. PP)
 *
 * <!-- inputs/outputs -->
 *   @return Returns the current CPU (i.e. PP)
 */
NODISCARD uint32_t
platform_current_cpu(void) NOEXCEPT
{
    return (uint32_t)raw_smp_processor_id();
}

/**
 * <!-- description -->
 *   @brief This function is called when the user calls platform_on_each_cpu.
 *     On each iteration of the CPU, this function calls the user provided
 *     callback with the signature that we perfer.
 *
 * <!-- inputs/outputs -->
 *   @param arg stores the params needed to execute the callback
 */
NODISCARD static long
work_on_cpu_callback(void *const arg) NOEXCEPT
{
    struct work_on_cpu_callback_args *args =
        ((struct work_on_cpu_callback_args *)arg);

    args->ret = args->func(args->cpu);
    return 0;
}

/**
 * <!-- description -->
 *   @brief Calls the user provided callback on each CPU in forward order.
 *     If each callback returns 0, this function returns 0, otherwise this
 *     function returns a non-0 value, even if all callbacks succeed except
 *     for one. If an error occurs, it is possible that this function will
 *     continue to execute the remaining callbacks until all callbacks have
 *     been called (depends on the platform).
 *
 * <!-- inputs/outputs -->
 *   @param pmut_func the function to call on each cpu
 *   @return If each callback returns 0, this function returns 0, otherwise
 *     this function returns a non-0 value
 */
NODISCARD static int64_t
platform_on_each_cpu_forward(platform_per_cpu_func const pmut_func) NOEXCEPT
{
    uint32_t cpu;

    get_online_cpus();
    for (cpu = 0; cpu < platform_num_online_cpus(); ++cpu) {
        struct work_on_cpu_callback_args args = {pmut_func, cpu, 0, 0};

        work_on_cpu(cpu, work_on_cpu_callback, &args);
        if (args.ret) {
            bferror("platform_per_cpu_func failed");
            goto work_on_cpu_callback_failed;
        }
    }

    put_online_cpus();
    return SHIM_SUCCESS;

work_on_cpu_callback_failed:
    put_online_cpus();
    return SHIM_FAILURE;
}

/**
 * <!-- description -->
 *   @brief Calls the user provided callback on each CPU in reverse order.
 *     If each callback returns 0, this function returns 0, otherwise this
 *     function returns a non-0 value, even if all callbacks succeed except
 *     for one. If an error occurs, it is possible that this function will
 *     continue to execute the remaining callbacks until all callbacks have
 *     been called (depends on the platform).
 *
 * <!-- inputs/outputs -->
 *   @param pmut_func the function to call on each cpu
 *   @return If each callback returns 0, this function returns 0, otherwise
 *     this function returns a non-0 value
 */
NODISCARD static int64_t
platform_on_each_cpu_reverse(platform_per_cpu_func const pmut_func) NOEXCEPT
{
    uint32_t cpu;

    get_online_cpus();
    for (cpu = platform_num_online_cpus(); cpu > 0; --cpu) {
        struct work_on_cpu_callback_args args = {pmut_func, cpu - 1, 0, 0};

        work_on_cpu(cpu - 1, work_on_cpu_callback, &args);
        if (args.ret) {
            bferror("platform_per_cpu_func failed");
            goto work_on_cpu_callback_failed;
        }
    }

    put_online_cpus();
    return SHIM_SUCCESS;

work_on_cpu_callback_failed:
    put_online_cpus();
    return SHIM_FAILURE;
}

/**
 * <!-- description -->
 *   @brief Calls the user provided callback on each CPU. If each callback
 *     returns 0, this function returns 0, otherwise this function returns
 *     a non-0 value, even if all callbacks succeed except for one. If an
 *     error occurs, it is possible that this function will continue to
 *     execute the remaining callbacks until all callbacks have been called
 *     (depends on the platform).
 *
 * <!-- inputs/outputs -->
 *   @param pmut_func the function to call on each cpu
 *   @param order sets the order the CPUs are called
 *   @return SHIM_SUCCESS on success, SHIM_FAILURE on failure.
 */
NODISCARD int64_t
platform_on_each_cpu(
    platform_per_cpu_func const pmut_func, uint32_t const order) NOEXCEPT
{
    int64_t ret;

    if (PLATFORM_FORWARD == order) {
        ret = platform_on_each_cpu_forward(pmut_func);
    }
    else {
        ret = platform_on_each_cpu_reverse(pmut_func);
    }

    return ret;
}

/**
 * <!-- description -->
 *   @brief Initializes a mutex lock. This must be called before a
 *     mutex can be used.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_mutex the mutex to lock
 */
void
platform_mutex_init(platform_mutex *const pmut_mutex) NOEXCEPT
{
    mutex_init(pmut_mutex);
}

/**
 * <!-- description -->
 *   @brief Destroys a mutex object. This must be called to free resources
 *     allocated from platform_mutex_init.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_mutex the mutex to destroy
 */
void
platform_mutex_destroy(platform_mutex *const pmut_mutex) NOEXCEPT
{
    mutex_destroy(pmut_mutex);
}

/**
 * <!-- description -->
 *   @brief Locks a mutex object. The mutex object must be initialized
 *     using platform_mutex_init before it is used.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_mutex the mutex to lock
 */
void
platform_mutex_lock(platform_mutex *const pmut_mutex) NOEXCEPT
{
    mutex_lock(pmut_mutex);
}

/**
 * <!-- description -->
 *   @brief Unlocks a mutex object. The mutex object must be initialized
 *     using platform_mutex_init before it is used.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_mutex the mutex to unlock
 */
void
platform_mutex_unlock(platform_mutex *const pmut_mutex) NOEXCEPT
{
    mutex_unlock(pmut_mutex);
}
