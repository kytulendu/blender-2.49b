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
# The Original Code is Copyright (C) 2008 by The Blender Foundation
# All rights reserved.
#

SET(INC ./include ${WINTAB_INC})
ADD_DEFINITIONS(-DWITH_BINRELOC)
FILE(GLOB SRC *.c)

BLENDERLIB(extern_binreloc "${SRC}" "${INC}")
#, libtype=['core','player'], priority = [25,15] ) 
