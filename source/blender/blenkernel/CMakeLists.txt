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

FILE(GLOB SRC intern/*.c)

SET(INC 
  . ../../../intern/guardedalloc ../include ../blenlib ../makesdna
  ../python ../render/extern/include ../../../intern/decimation/extern
  ../imbuf ../avi ../../../intern/elbeem/extern ../../../intern/opennl/extern
  ../../../intern/iksolver/extern ../blenloader ../quicktime
  ../../../intern/bmfont ../../../extern/bullet2/src
  ../nodes ../../../extern/glew/include ../gpu
  ${SDL_INC}
  ${ZLIB_INC}
  ${PYTHON_INC}
)

IF(WITH_VERSE)
  ADD_DEFINITIONS(-DWITH_VERSE)
  SET(INC ${INC} ${VERSE_INC})
ENDIF(WITH_VERSE)

IF(WITH_OPENEXR)
  ADD_DEFINITIONS(-DWITH_OPENEXR)
ENDIF(WITH_OPENEXR)

IF(WITH_OPENJPEG)
  ADD_DEFINITIONS(-DWITH_OPENJPEG)
ENDIF(WITH_OPENJPEG)

IF(WITH_DDS)
  ADD_DEFINITIONS(-DWITH_DDS)
ENDIF(WITH_DDS)

IF(WITH_QUICKTIME)
  SET(INC ${INC} ${QUICKTIME_INC})
  ADD_DEFINITIONS(-DWITH_QUICKTIME)
ENDIF(WITH_QUICKTIME)

IF(WITH_FFMPEG)
  SET(INC ${INC} ${FFMPEG_INC})
  ADD_DEFINITIONS(-DWITH_FFMPEG)
ENDIF(WITH_FFMPEG)

IF(WITH_PLAYER)
  ADD_SUBDIRECTORY(bad_level_call_stubs)
ENDIF(WITH_PLAYER)

BLENDERLIB(bf_blenkernel "${SRC}" "${INC}")

IF(WITH_VERSE)
  ADD_DEPENDENCIES(bf_blenkernel mkprot verse)
ENDIF(WITH_VERSE)

IF(WITH_INTERNATIONAL)
   ADD_DEFINITIONS(-DWITH_FREETYPE2)
ENDIF(WITH_INTERNATIONAL)

IF(NOT WITH_ELBEEM)
  ADD_DEFINITIONS(-DDISABLE_ELBEEM)
ENDIF(NOT WITH_ELBEEM)
