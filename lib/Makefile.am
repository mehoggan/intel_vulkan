lib_LTLIBRARIES = libautotools_mvp.la

libautotools_mvp_la_CPPFLAGS = -Werror -Wall -pedantic \
		-I$(abs_top_srcdir)/include

libautotools_mvp_la_SOURCES = ./LoggerHelpers.cpp \
															./Logging.cpp \
															./OperatingSystem.cpp \
															./Tools.cpp \
															./Tutorial01.cpp \
															./Tutorial02.cpp \
															./VulkanCommon.cpp \
															./VulkanFunctions.cpp

libautotools_mvp_la_LIBADD = -lboost_log -lboost_system -lboost_thread

libautotools_mvp_la_LDFLAGS = -uuid -Wl,-ld_classic -pthread
