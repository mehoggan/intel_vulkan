bin_PROGRAMS = tutorial01_runner tutorial02_runner

# Tutorial 01 Binary
tutorial01_runner_SOURCES = ./tutorial01_main.cpp
tutorial01_runner_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include
tutorial01_runner_LDADD = \
    $(abs_top_builddir)/lib/libintel_vulkan.la
tutorial01_runner_LDFLAGS = -pthread

# Tutorial 02 Binary
tutorial02_runner_SOURCES = ./tutorial02_main.cpp
tutorial02_runner_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include
tutorial02_runner_LDADD = \
    $(abs_top_builddir)/lib/libintel_vulkan.la
tutorial02_runner_LDFLAGS = -pthread

CLEANFILES = *.o
CLEANDIRS = .lib/
