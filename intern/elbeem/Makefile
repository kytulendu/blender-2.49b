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
# Contributor(s): Hans Lambermont
#
# ***** END GPL LICENSE BLOCK *****
# elbeem main makefile.
#

include nan_definitions.mk

unexport NAN_QUIET

LIBNAME = elbeem
SOURCEDIR = intern/$(LIBNAME)
DIR = $(OCGDIR)/$(SOURCEDIR)
DIRS = intern
#not ready yet TESTDIRS = test

include nan_subdirs.mk

install: all debug
	@[ -d $(NAN_ELBEEM) ] || mkdir $(NAN_ELBEEM)
	@[ -d $(NAN_ELBEEM)/include ] || mkdir $(NAN_ELBEEM)/include
	@[ -d $(NAN_ELBEEM)/lib ] || mkdir $(NAN_ELBEEM)/lib
	@[ -d $(NAN_ELBEEM)/lib/debug ] || mkdir $(NAN_ELBEEM)/lib/debug
	@../tools/cpifdiff.sh $(DIR)/libelbeem.a $(NAN_ELBEEM)/lib/
	@../tools/cpifdiff.sh $(DIR)/debug/libelbeem.a $(NAN_ELBEEM)/lib/debug/
ifeq ($(OS),darwin)
	ranlib $(NAN_ELBEEM)/lib/libelbeem.a
	ranlib $(NAN_ELBEEM)/lib/debug/libelbeem.a
endif
	@../tools/cpifdiff.sh extern/*.h $(NAN_ELBEEM)/include/

