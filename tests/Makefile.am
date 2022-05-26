## Process this file with automake to produce Makefile.in

AM_CFLAGS =  -I$(top_builddir)/src @CHECK_CFLAGS@
AM_LDFLAGS = @CHECK_LIBS@

TESTS = check_array check_item check_cmd
check_PROGRAMS = check_array check_item check_cmd

check_array_SOURCES = check_array.c

check_item_SOURCES = check_item.c

check_cmd_SOURCES = check_cmd.c
