# $Id: CMakeLists.txt 20238 2009-05-17 12:25:06Z ben2610 $
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

IF(WITH_GAMEENGINE)
  ADD_SUBDIRECTORY(qhull)
  ADD_SUBDIRECTORY(solid)
ENDIF(WITH_GAMEENGINE)

IF(WITH_BULLET)
  ADD_SUBDIRECTORY(bullet2)
ENDIF(WITH_BULLET)

IF(WITH_INTERNATIONAL)
  ADD_SUBDIRECTORY(bFTGL)
ENDIF(WITH_INTERNATIONAL)

IF(WITH_VERSE)
  ADD_SUBDIRECTORY(verse)
ENDIF(WITH_VERSE)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
  ADD_SUBDIRECTORY(binreloc)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

ADD_SUBDIRECTORY(glew)

IF(WITH_OPENJPEG)
  ADD_SUBDIRECTORY(libopenjpeg)
ENDIF(WITH_OPENJPEG)
