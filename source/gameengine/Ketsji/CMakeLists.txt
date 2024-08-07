# $Id: CMakeLists.txt 20007 2009-04-30 12:45:13Z campbellbarton $
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
# The Original Code is Copyright (C) 2006, Blender Foundation
# All rights reserved.
#
# The Original Code is: all of this file.
#
# Contributor(s): Jacques Beaurain.
#
# ***** END GPL LICENSE BLOCK *****

FILE(GLOB SRC *.cpp)
SET(SRC 
  ${SRC}
  ../../../source/blender/python/api2_2x/Mathutils.c
  ../../../source/blender/python/api2_2x/Geometry.c
  ../../../source/blender/python/api2_2x/constant.c
  ../../../source/blender/python/api2_2x/euler.c
  ../../../source/blender/python/api2_2x/matrix.c
  ../../../source/blender/python/api2_2x/quat.c
  ../../../source/blender/python/api2_2x/vector.c
  ../../../source/blender/python/api2_2x/bpy_internal_import.c
  ../../../source/blender/python/api2_2x/BGL.c
)

SET(INC
  .
  ../../../source/kernel/gen_system
  ../../../intern/string
  ../../../intern/guardedalloc
  ../../../source/gameengine/Rasterizer/RAS_OpenGLRasterizer 
  ../../../intern/bmfont
  ../../../source/gameengine/Converter
  ../../../source/blender/imbuf
  ../../../intern/ghost/include
  ../../../intern/moto/include
  ../../../source/gameengine/Ketsji 
  ../../../source/blender/blenlib
  ../../../source/blender/blenkernel
  ../../../source/blender/python/api2_2x
  ../../../source/blender 
  ../../../source/blender/include
  ../../../source/blender/makesdna 
  ../../../source/gameengine/Rasterizer 
  ../../../source/gameengine/GameLogic
  ../../../source/gameengine/Expressions 
  ../../../source/gameengine/Ketsji/KXNetwork
  ../../../source/gameengine/Network
  ../../../source/gameengine/SceneGraph 
  ../../../source/gameengine/Physics/common
  ../../../source/gameengine/Physics/Bullet 
  ../../../source/gameengine/Physics/Sumo
  ../../../source/gameengine/Physics/Sumo/Fuzzics/include 
  ../../../source/gameengine/Network/LoopBackNetwork
  ../../../intern/SoundSystem
  ../../../source/blender/misc 
  ../../../source/blender/blenloader
  ../../../source/blender/gpu
  ../../../extern/bullet2/src
  ../../../extern/solid
  ../../../extern/glew/include
  ${PYTHON_INC}
  ${SDL_INC}
)

BLENDERLIB(bf_ketsji "${SRC}" "${INC}")
#env.BlenderLib ( 'bf_ketsji', sources, Split(incs), [], libtype=['game','player'], priority=[25, 72], compileflags = cflags )
