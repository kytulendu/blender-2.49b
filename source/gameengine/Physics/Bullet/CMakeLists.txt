# $Id: CMakeLists.txt 20200 2009-05-14 13:47:08Z ben2610 $
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

SET(SRC CcdPhysicsEnvironment.cpp CcdPhysicsController.cpp CcdGraphicController.cpp)

SET(INC
  .
  ../common
  ../../../../extern/bullet2/src
  ../../../../extern/glew/include
  ../../../../intern/moto/include
  ../../../../intern/guardedalloc
  ../../../kernel/gen_system
  ../../../../intern/string
  ../../../../intern/SoundSystem 
  ../../Rasterizer
  ../../Ketsji
  ../../Expressions
  ../../GameLogic
  ../../SceneGraph
  ../../../../source/blender/makesdna
  ../../../../source/blender/blenlib
  ../../../../source/blender/blenkernel
  ${PYTHON_INC}
)

BLENDERLIB(bf_bullet "${SRC}" "${INC}")
#env.BlenderLib ( 'bf_bullet', Split(sources), Split(incs), [], libtype=['game','player'], priority=[15,90] )
