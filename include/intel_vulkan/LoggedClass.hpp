////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Directed Acyclic Graph Scheduler
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////
#ifndef INTEL_VULKAN_LOGGEDCLASS_HPP
#define INTEL_VULKAN_LOGGEDCLASS_HPP

#include "intel_vulkan/Logging.h"

namespace intel_vulkan {
/**
 * @brief A class that sets up stderror and stdout loggers for a derived
 *        class.
 *
 * If you inherit from this class you will get a logger added to logging
 * for specific instance of this class.
 *
 * @tparam DerivedType Used in RTTI for an instance of \tref DerivedType.
 */
template <typename DerivedType> class LoggedClass {
public:
    /**
     * @brief ctor
     *
     * @param[in] d An instance of \tref DerivedType used to generate a
     *              \ref LogTag.
     * @param[in] cout_level The level at which to log to std::cout.
     * @param[in] cerr_level The level at which to log to std::cerr.
     */
    explicit LoggedClass(
            const DerivedType& derived,
            boost::log::trivial::severity_level cout_level = INTEL_VULKAN_INFO,
            boost::log::trivial::severity_level cerr_level =
                    INTEL_VULKAN_ERROR)
            : LOG_TAG(Logging::logTagForThis(derived)) {
        Logging::addStdCoutLogger(LOG_TAG, cout_level);
        Logging::addStdCerrLogger(LOG_TAG, cerr_level);
    }

    /**
     * @brief dtor
     */
    virtual ~LoggedClass() {}

protected:
    LogTag LOG_TAG;

private:
    LoggedClass(const LoggedClass& other) = delete;
    LoggedClass& operator=(const LoggedClass& rhs) = delete;
    LoggedClass(LoggedClass&& rhs) = delete;
    LoggedClass& operator=(LoggedClass&& rhs) = delete;
};
}  // namespace intel_vulkan
#endif
