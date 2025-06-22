bin_PROGRAMS = tutorial01_intel_vulkan

SHARED_SOURCES = OperatingSystem.cpp Tools.cpp VulkanCommon.cpp \
								 VulkanFunctions.cpp

#####
# Start of Tutorial01.cpp
#####
tutorial01_intel_vulkan_SOURCES = $(SHARED_SOURCES) \
																		 Tutorial01.cpp \
																		 tutorial01_main.cpp

tutorial01_intel_vulkan_CPPFLAGS = -Werror -Wall -pedantic \
																			-Wno-enum-constexpr-conversion \
																			-I$(abs_top_srcdir)/include
if LINUX
tutorial01_intel_vulkan_CPPFLAGS += -DVK_USE_PLATFORM_XLIB_KHR
tutorial01_intel_vulkan_LDADD = -lvulkan -lX11 -lrt -lm
endif


tutorial01_intel_vulkan_LDFLAGS = -pthread
