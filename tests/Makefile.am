if HAVE_GTEST
TESTS = vertex_types_test
check_PROGRAMS = vertex_types_test

vertex_types_test_SOURCES = ./VertexTypesTest.cpp
vertex_types_test_CPPFLAGS = -Werror -Wall -pedantic \
		-I$(abs_top_srcdir)/include $(GTEST_CFLAGS) $(GLM_CFLAGS)
vertex_types_test_LDADD = $(GTEST_LIBS)
vertex_types_test_LDFLAGS = -pthread
endif

CLEANFILES = *.o
