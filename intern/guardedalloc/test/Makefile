#
# $Id: Makefile 14444 2008-04-16 22:40:48Z hos $
#
# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
# All rights reserved.
#
# The Original Code is: all of this file.
#
# Contributor(s): none yet.
#
# ***** END GPL LICENSE BLOCK *****
# Test the guarded memory module
#

LIBNAME = guardedalloc
SOURCEDIR = intern/$(LIBNAME)/test
DIR = $(OCGDIR)/$(SOURCEDIR)
DIRS = simpletest

include nan_subdirs.mk

include nan_compile.mk
include nan_link.mk

TESTLIBS  = $(OCGDIR)/intern/$(LIBNAME)/$(DEBUG_DIR)lib$(LIBNAME).a

all debug::
	@echo "****> linking $@ in $(SOURCEDIR)"
	$(CC) $(LDFLAGS) -o $(DIR)/$(DEBUG_DIR)memtest $(DIR)/memtest.o $(TESTLIBS)

clean::
	$(RM) $(DIR)/memtest $(DIR)/debug/memtest

test:: $(DIR)/memtest
	$(DIR)/memtest $(NAN_TEST_VERBOSITY)

