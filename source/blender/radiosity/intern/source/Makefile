#
# $Id: Makefile 16366 2008-09-04 20:51:28Z blendix $
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
# radiosity uses the render lib
#

LIBNAME = radiosity
DIR = $(OCGDIR)/blender/$(LIBNAME)

include nan_compile.mk

CFLAGS += $(LEVEL_1_C_WARNINGS)

CPPFLAGS += -I$(NAN_GLEW)/include
CPPFLAGS += -I$(OPENGL_HEADERS)

# not very neat....
CPPFLAGS += -I../../../blenkernel
CPPFLAGS += -I../../../blenlib
CPPFLAGS += -I../../../makesdna
CPPFLAGS += -I../../../imbuf
CPPFLAGS += -I../../../
CPPFLAGS += -I../../../blenloader
CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include

# first /include is my own includes, second are the external includes
# third is the external interface. there should be a nicer way to say this 
CPPFLAGS += -I../include -I../../../include -I../../extern/include
CPPFLAGS += -I../../../render/extern/include 
CPPFLAGS += -I../../../render/intern/include 
