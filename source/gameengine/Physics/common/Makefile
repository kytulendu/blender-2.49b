#
# $Id: Makefile 15444 2008-07-05 17:05:05Z lukep $
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

LIBNAME = common
DIR = $(OCGDIR)/gameengine/blphys/$(LIBNAME)

include nan_compile.mk

CCFLAGS += $(LEVEL_1_CPP_WARNINGS)

CPPFLAGS += -I$(OPENGL_HEADERS)
CPPFLAGS += -I$(NAN_STRING)/include
CPPFLAGS += -I$(NAN_SOUNDSYSTEM)/include
CPPFLAGS += -I$(NAN_PYTHON)/include/python$(NAN_PYTHON_VERSION)

CPPFLAGS += -I$(NAN_FUZZICS)/include -I$(NAN_SUMO)/include -I$(NAN_MOTO)/include
CPPFLAGS += -I../../blender
# these two needed because of blenkernel
CPPFLAGS += -I../../blender/makesdna
CPPFLAGS += -I../../blender/include
CPPFLAGS += -I../../blender/blenlib
CPPFLAGS += -I../../blender/blenkernel
CPPFLAGS += -I../../blender/render/extern/include
CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include
CPPFLAGS += -I../Expressions -I../Rasterizer -I../GameLogic
CPPFLAGS += -I../Ketsji -I../BlenderRoutines -I../SceneGraph
CPPFLAGS += -I../../kernel/gen_system
CPPFLAGS += -I../Rasterizer/RAS_OpenGLRasterizer
CPPFLAGS += -I../Network -I../Ketsji/KXNetwork
CPPFLAGS += -I../Physics
CPPFLAGS += -I../Physics/Dummy
