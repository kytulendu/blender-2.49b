#
# $Id: Makefile 17883 2008-12-15 20:53:45Z hos $
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
# Makefile for GHOST game player

LIBNAME = ghost
DIR = $(OCGDIR)/gameengine/GamePlayer/ghost

include nan_compile.mk

CCFLAGS += $(LEVEL_1_CPP_WARNINGS)

# OpenGL header files
CPPFLAGS += -I$(NAN_GLEW)/include
CPPFLAGS += -I$(OPENGL_HEADERS)
CPPFLAGS += -I$(NAN_STRING)/include    
CPPFLAGS += -I$(NAN_BMFONT)/include
CPPFLAGS += -I$(NAN_SOUNDSYSTEM)/include
CPPFLAGS += -I$(NAN_GUARDEDALLOC)/include

CPPFLAGS += -I../../GamePlayer/common

# Game Engine includes
CPPFLAGS += -I../../Converter
CPPFLAGS += -I../../Expressions
CPPFLAGS += -I../../GameLogic
CPPFLAGS += -I../../Ketsji
CPPFLAGS += -I../../Ketsji/KXNetwork
CPPFLAGS += -I../../Network
CPPFLAGS += -I../../Network/LoopBackNetwork
CPPFLAGS += -I../../Rasterizer
CPPFLAGS += -I../../Rasterizer/RAS_OpenGLRasterizer
CPPFLAGS += -I../../SceneGraph

# Sumo
CPPFLAGS += -I$(SRCHOME)/gameengine/Physics/Sumo/include
CPPFLAGS += -I$(SRCHOME)/gameengine/Physics/Sumo/Fuzzics/include

CPPFLAGS += -I$(NAN_MOTO)/include

# Blender includes
CPPFLAGS += -I../../../blender/blenkernel
CPPFLAGS += -I../../../blender/blenlib
CPPFLAGS += -I../../../blender/blenloader
CPPFLAGS += -I../../../blender/imbuf
CPPFLAGS += -I../../../blender/makesdna
CPPFLAGS += -I../../../blender/readblenfile
CPPFLAGS += -I../../../blender/gpu

CPPFLAGS += -I../../../gameengine/BlenderRoutines

# kernel? GEN? stuff
CPPFLAGS += -I../../../kernel/gen_system
CPPFLAGS += -I../../../kernel/gen_messaging

CPPFLAGS += -I$(NAN_STRING)/include
CPPFLAGS += -I$(NAN_GHOST)/include
CPPFLAGS += -I$(NAN_PYTHON)/include/python$(NAN_PYTHON_VERSION)

ifeq ($(WITH_FFMPEG), true)
   CPPFLAGS += -DWITH_FFMPEG
endif
