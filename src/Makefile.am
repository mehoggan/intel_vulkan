bin_PROGRAMS = tutorial01_intel_vulkan tutorial02_intel_vulkan

#####
# Start of Tutorial01.cpp
#####
tutorial01_intel_vulkan_SOURCES = tutorial01_main.cpp \
																	LoggerHelpers.cpp \
																	Logging.cpp \
																	OperatingSystem.cpp \
																	VulkanFunctions.cpp \
																	Tutorial01.cpp
    

tutorial01_intel_vulkan_CPPFLAGS = -Werror -Wall -pedantic \
																	 -Wno-enum-constexpr-conversion \
																	 -I$(abs_top_srcdir)/include

if LINUX
tutorial01_intel_vulkan_CPPFLAGS += -DVK_USE_PLATFORM_XLIB_KHR
tutorial01_intel_vulkan_LDADD = -lboost_filesystem \
																-lboost_log \
																-lboost_system \
																-lboost_thread \
																-lvulkan \
																-lX11 \
																-lrt \
																-lm
endif

tutorial01_intel_vulkan_LDFLAGS = -pthread

#####
# Start of Tutorial02.cpp
#####
tutorial02_intel_vulkan_SOURCES = tutorial02_main.cpp \
																	LoggerHelpers.cpp \
																	Logging.cpp \
																	OperatingSystem.cpp \
																	VulkanFunctions.cpp \
																	Tutorial02.cpp
    

tutorial02_intel_vulkan_CPPFLAGS = -Werror -Wall -pedantic \
																	 -Wno-enum-constexpr-conversion \
																	 -I$(abs_top_srcdir)/include

if LINUX
tutorial02_intel_vulkan_CPPFLAGS += -DVK_USE_PLATFORM_XLIB_KHR
tutorial02_intel_vulkan_LDADD = -lboost_filesystem \
																-lboost_log \
																-lboost_system \
																-lboost_thread \
																-lvulkan \
																-lX11 \
																-lrt \
																-lm
endif

tutorial02_intel_vulkan_LDFLAGS = -pthread
