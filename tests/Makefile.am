## Process this file with automake to produce Makefile.in

TESTS = check_array
check_PROGRAMS = check_array
check_array_SOURCES =\
				check_array.c\
				$(top_builddir)/src/array.c
check_array_CFLAGS = -I../src @CHECK_CFLAGS@
check_array_LDADD = @CHECK_LIBS@

