#
# $Id: Makefile 16952 2008-10-06 19:57:42Z sirdude $
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
# elbeem intern Makefile
#

LIBNAME = elbeem
DIR = $(OCGDIR)/intern/$(LIBNAME)

include nan_compile.mk

unexport NAN_QUIET

CCFLAGS += $(LEVEL_2_CPP_WARNINGS)

ifeq ($(WITH_BF_OPENMP),true)
   CPPFLAGS += -DPARALLEL
endif

CPPFLAGS += -DNOGUI -DELBEEM_BLENDER
CPPFLAGS += -I.
CPPFLAGS += -I../extern
CPPFLAGS += $(NAN_SDLCFLAGS)
CPPFLAGS += -I$(NAN_PNG)/include
CPPFLAGS += -I$(NAN_PNG)/include/libpng

# zlib
ifeq ($(OS),$(findstring $(OS), "solaris windows"))
    CPPFLAGS += -I$(NAN_ZLIB)/include
endif
