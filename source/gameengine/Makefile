#
# $Id: Makefile 17298 2008-11-02 18:12:45Z ton $
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
# Bounces make to subdirectories.

include nan_definitions.mk

SOURCEDIR = source/gameengine
DIR = $(OCGDIR)/gameengine
DIRS = BlenderRoutines
DIRS += Converter
DIRS += Expressions GameLogic Ketsji Rasterizer SceneGraph
DIRS += Network Physics VideoTexture

ifeq ($(WITH_BF_BLENDERGAMEENGINE),true)
  DIRS += GamePlayer
endif

include nan_subdirs.mk
