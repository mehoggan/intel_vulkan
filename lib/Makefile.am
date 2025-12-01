lib_LTLIBRARIES = libintel_vulkan.la

libintel_vulkan_la_CPPFLAGS = -Werror -Wall -pedantic \
		-I$(abs_top_srcdir)/include

libintel_vulkan_la_SOURCES = ./LoggerHelpers.cpp \
															./Logging.cpp \
															./OperatingSystem.cpp \
															./Tools.cpp \
															./Tutorial01.cpp \
															./Tutorial02.cpp \
															./Tutorial03.cpp \
															./VulkanCommon.cpp \
															./VulkanFunctions.cpp

libintel_vulkan_la_LIBADD = -lboost_log -lboost_system -lboost_thread \
														$(VULKAN_LIBS) $(X11_LIBS)

libintel_vulkan_la_LDFLAGS = -pthread
