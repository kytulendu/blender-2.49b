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
#
#

LIBNAME = blenpluginapi
DIR = $(OCGDIR)/blender/$(LIBNAME)

include nan_compile.mk

ifeq ($(OS),$(findstring $(OS), "beos darwin freebsd linux openbsd solaris"))
    CFLAGS += -shared
endif

CFLAGS += $(LEVEL_1_C_WARNINGS)

# path to our own external headerfiles. On win2k this needs to be
# longer, to avoid the util.h include problem
CPPFLAGS += -I..
CPPFLAGS += -I../..

# also do dna
CPPFLAGS += -I../../makesdna
# path to blenlib
CPPFLAGS += -I../../blenlib
# path to imbuf
CPPFLAGS += -I../../imbuf
CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include

