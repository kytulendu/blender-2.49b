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

LIBNAME = ftfont
DIR = $(OCGDIR)/blender/ftfont

include nan_compile.mk

CFLAGS += $(LEVEL_1_C_WARNINGS)

#CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include
CPPFLAGS += -I../../makesdna
CPPFLAGS += -I../../blenkernel
CPPFLAGS += -I../../blenlib
CPPFLAGS += -I../../include
CPPFLAGS += -I$(NAN_FTGL)/include
CPPFLAGS += -I$(NAN_FTGL)/include/FTGL
CPPFLAGS += -I$(NAN_GETTEXT)/include
CPPFLAGS += -I$(NAN_FREETYPE)/include
CPPFLAGS += -I$(OPENGL_HEADERS)
ifeq ($(OS), windows)
  CPPFLAGS += -I$(NAN_ICONV)/include
  ifeq ($(FREE_WINDOWS), true)
    CPPFLAGS += -I$(NAN_FREETYPE)/include/freetype2
    CPPFLAGS += -DUSE_GETTEXT_DLL
  endif
else
  CPPFLAGS += -I$(NAN_FREETYPE)/include/freetype2
endif
CPPFLAGS += -I..
