bin_PROGRAMS = tutorial01_runner tutorial02_runner tutorial03_runner

# Tutorial 01 Binary
tutorial01_runner_SOURCES = ./tutorial01_main.cpp
tutorial01_runner_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include
tutorial01_runner_LDADD = \
    $(abs_top_builddir)/lib/libintel_vulkan.la $(VULKAN_LIBS) $(X11_LIBS)
tutorial01_runner_LDFLAGS = -pthread

# Tutorial 02 Binary
tutorial02_runner_SOURCES = ./tutorial02_main.cpp
tutorial02_runner_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include
tutorial02_runner_LDADD = \
    $(abs_top_builddir)/lib/libintel_vulkan.la $(VULKAN_LIBS) $(X11_LIBS)
tutorial02_runner_LDFLAGS = -pthread

# Tutorial 03 Binary
tutorial03_runner_SOURCES = ./tutorial03_main.cpp
tutorial03_runner_CPPFLAGS = -Werror -Wall -pedantic \
    -I$(abs_top_srcdir)/include
tutorial03_runner_LDADD = \
    $(abs_top_builddir)/lib/libintel_vulkan.la $(VULKAN_LIBS) $(X11_LIBS)
tutorial03_runner_LDFLAGS = -pthread
pkgdatadir = $(bindir)

# --- Shader Copying Logic ---
tutorial03_vert = $(top_srcdir)/resources/03/Data/shader.vert.03.spv
tutorial03_frag = $(top_srcdir)/resources/03/Data/shader.frag.03.spv

all-local: $(tutorial03_vert) $(tutorial03_frag)
	cp $(tutorial03_vert) $(builddir)/shader.03.vert.spv
	cp $(tutorial03_frag) $(builddir)/shader.03.frag.spv

CLEANFILES = shader.03.vert.spv shader.03.frag.spv
