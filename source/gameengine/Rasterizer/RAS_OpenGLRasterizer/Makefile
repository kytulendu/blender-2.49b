#
# $Id: Makefile 20094 2009-05-07 09:13:01Z ben2610 $
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
# Bounce make to subdirectories.
#

LIBNAME = OpenGLrasterizer
DIR = $(OCGDIR)/gameengine/$(LIBNAME)

include nan_compile.mk

CCFLAGS += $(LEVEL_1_CPP_WARNINGS)

CPPFLAGS += -I$(NAN_GLEW)/include
CPPFLAGS += -I$(OPENGL_HEADERS)
CPPFLAGS += -I$(NAN_STRING)/include    
CPPFLAGS += -I$(NAN_MOTO)/include
CPPFLAGS += -I../../../kernel/gen_system
CPPFLAGS += -I../../../blender/gpu
CPPFLAGS += -I../../../blender/makesdna
CPPFLAGS += -I../../../blender/blenlib
CPPFLAGS += -I../../../blender/blenkernel
CPPFLAGS += -I../../BlenderRoutines
CPPFLAGS += -I../../Ketsji
CPPFLAGS += -I../../SceneGraph
CPPFLAGS += -I..
CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include

ifeq ($(OS),darwin)
	CPPFLAGS += -fpascal-strings
endif

