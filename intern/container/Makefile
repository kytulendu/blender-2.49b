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
# container main makefile.
#

include nan_definitions.mk

LIBNAME = container
SOURCEDIR = intern/$(LIBNAME)
DIR = $(OCGDIR)/$(SOURCEDIR)
DIRS = intern
#not yet TESTDIRS = test
 
include nan_subdirs.mk

install: all debug
	@[ -d $(NAN_CONTAINER) ] || mkdir $(NAN_CONTAINER)
	@[ -d $(NAN_CONTAINER)/include ] || mkdir $(NAN_CONTAINER)/include
	@[ -d $(NAN_CONTAINER)/lib ] || mkdir $(NAN_CONTAINER)/lib
	@[ -d $(NAN_CONTAINER)/lib/debug ] || mkdir $(NAN_CONTAINER)/lib/debug
	@../tools/cpifdiff.sh $(DIR)/libcontainer.a $(NAN_CONTAINER)/lib/
	@../tools/cpifdiff.sh $(DIR)/debug/libcontainer.a $(NAN_CONTAINER)/lib/debug
	@../tools/cpifdiff.sh *.h $(NAN_CONTAINER)/include/

