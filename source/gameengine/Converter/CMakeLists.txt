# $Id: CMakeLists.txt 19485 2009-03-31 22:34:34Z gsrb3d $
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

SET(INC
  .
  ../../../source/kernel/gen_system
  ../../../intern/string
  ../../../intern/guardedalloc
  ../../../source/gameengine/Rasterizer/RAS_OpenGLRasterizer
  ../../../intern/bmfont
  ../../../intern/SoundSystem
  ../../../intern/SoundSystem/include
  ../../../intern/SoundSystem/openal
  ../../../intern/SoundSystem/dummy
  ../../../intern/SoundSystem/intern
  ../../../source/gameengine/Converter
  ../../../source/gameengine/BlenderRoutines
  ../../../source/blender/imbuf
  ../../../intern/moto/include
  ../../../source/gameengine/Ketsji
  ../../../source/gameengine/Ketsji/KXNetwork
  ../../../source/blender/blenlib
  ../../../source/blender/blenkernel
  ../../../source/blender
  ../../../source/blender/include
  ../../../source/blender/makesdna
  ../../../source/gameengine/Rasterizer
  ../../../source/gameengine/Rasterizer/RAS_OpenGLRasterizer
  ../../../source/gameengine/GameLogic
  ../../../source/gameengine/Expressions
  ../../../source/gameengine/Network
  ../../../source/gameengine/SceneGraph
  ../../../source/gameengine/Physics/common
  ../../../source/gameengine/Physics/Bullet
  ../../../source/gameengine/Physics/BlOde
  ../../../source/gameengine/Physics/Dummy
  ../../../source/gameengine/Physics/Sumo
  ../../../source/gameengine/Physics/Sumo/Fuzzics/include
  ../../../source/gameengine/Network/LoopBackNetwork
  ../../../source/blender/misc
  ../../../source/blender/blenloader
  ../../../source/blender/gpu
  ../../../extern/bullet2/src
  ../../../extern/solid
  ${PYTHON_INC}
)

BLENDERLIB(bf_converter "${SRC}" "${INC}")
#env.BlenderLib ( 'bf_converter', sources, Split(incs), [], libtype=['game','player'], priority=[5,70] )
