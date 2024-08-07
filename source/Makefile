#
# $Id: Makefile 20217 2009-05-15 18:21:27Z blendix $
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
# Top level makefile. Start looping through subdirs and link....
#

ifndef NANENV
    export NANENV := $(shell env | grep NAN_)
endif

include nan_definitions.mk

DIRS = creator blender kernel

ifneq ($(NAN_NO_KETSJI),true)
   DIRS += gameengine
endif

ifeq ($(OS),windows)
    DIRS += icons
endif

########## buildinfo kludge ###################
CPPFLAGS += -I../Physics/common
CPPFLAGS += -I../Physics/Dummy
ifdef NAN_BUILDINFO
    BUILDINFO_O = $(DIR)/$(DEBUG_DIR)buildinfo.o
    BUILDINFO_C = $(SRCHOME)/creator/buildinfo.c
    BUILD_DATE := $(shell date "+%Y-%m-%d")
    BUILD_TIME := $(shell date "+%H:%M:%S")
	BUILD_REV := $(shell svnversion)
endif

############# set pyplayerlib ##################


############# libraries ##################
# COMLIB COMmon LIBraries for all targets
# BPLIB Browser Plugin LIBraries
# SPLIB1 Standalone Player LIBraries (pre COMLIB)
# SPLIB Standalone Player LIBraries (post COMLIB)
# PULIB PUblisher LIBraries
# GRPLIB Gui and Render LIBraries for Publisher
# LLIBS dynamic system libraries
# SADD Static OpenGL libraries
# DADD Dynamic OpenGL libraries
# NSPLUGLIB PLUGin LIBraries for ns-style api
# PLUGAPPLIB libs that form the application to be plugged in
# Note: the order is important here

GRPLIB = $(OCGDIR)/creator/$(DEBUG_DIR)libcreator.a
GRPLIB += $(OCGDIR)/blender/src/$(DEBUG_DIR)libsrcpublisher.a
GRPLIB += $(NAN_BSP)/lib/$(DEBUG_DIR)libbsp.a
GRPLIB += $(NAN_BOOLOP)/lib/$(DEBUG_DIR)libboolop.a
GRPLIB += $(NAN_SOUNDSYSTEM)/lib/$(DEBUG_DIR)libSoundSystem.a
GRPLIB += $(NAN_GHOST)/lib/$(DEBUG_DIR)libghost.a
GRPLIB += $(NAN_STRING)/lib/$(DEBUG_DIR)libstring.a
GRPLIB += $(OCGDIR)/blender/render/$(DEBUG_DIR)librender.a
GRPLIB += $(OCGDIR)/blender/radiosity/$(DEBUG_DIR)libradiosity.a
GRPLIB += $(NAN_OPENNL)/lib/$(DEBUG_DIR)libopennl.a
GRPLIB += $(NAN_SUPERLU)/lib/$(DEBUG_DIR)libsuperlu.a
GRPLIB += $(OCGDIR)/blender/python/$(DEBUG_DIR)libpython.a

# nlin: the reason that some libraries appear more than once below is
# to handle circular dependencies in linking among libraries... some
# linkers (e.g. under Linux) need libs to be specified multiple times
# to properly resolve circular dependencies. ugly, but it works...
# the repeat entries could probably be trimmed down.
COMLIB = $(OCGDIR)/blender/blenkernel/$(DEBUG_DIR)libblenkernel.a
COMLIB += $(OCGDIR)/blender/blenloader/$(DEBUG_DIR)libblenloader.a
COMLIB += $(OCGDIR)/blender/blenpluginapi/$(DEBUG_DIR)libblenpluginapi.a
COMLIB += $(OCGDIR)/blender/nodes_shd/$(DEBUG_DIR)libnodes_shd.a
COMLIB += $(OCGDIR)/blender/nodes_cmp/$(DEBUG_DIR)libnodes_cmp.a
COMLIB += $(OCGDIR)/blender/nodes_tex/$(DEBUG_DIR)libnodes_tex.a
COMLIB += $(OCGDIR)/blender/nodes/$(DEBUG_DIR)libnodes.a
COMLIB += $(OCGDIR)/blender/imbuf/$(DEBUG_DIR)libimbuf.a
COMLIB += $(OCGDIR)/blender/blenlib/$(DEBUG_DIR)libblenlib.a
COMLIB += $(NAN_IKSOLVER)/lib/libiksolver.a
COMLIB += $(NAN_SUPERLU)/lib/$(DEBUG_DIR)libsuperlu.a	
COMLIB += $(OCGDIR)/blender/avi/$(DEBUG_DIR)libavi.a
COMLIB += $(NAN_JPEG)/lib/libjpeg.a
COMLIB += $(OCGDIR)/blender/gpu/$(DEBUG_DIR)libgpu.a
COMLIB += $(NAN_GLEW)/lib/libglew.a

ifneq ($(NAN_NO_KETSJI),true)
    COMLIB += $(OCGDIR)/gameengine/bloutines/$(DEBUG_DIR)libbloutines.a
    COMLIB += $(OCGDIR)/gameengine/blconverter/$(DEBUG_DIR)libblconverter.a
    COMLIB += $(OCGDIR)/gameengine/blphys/common/$(DEBUG_DIR)libcommon.a
    COMLIB += $(OCGDIR)/gameengine/ketsji/$(DEBUG_DIR)libketsji.a
    COMLIB += $(OCGDIR)/gameengine/blconverter/$(DEBUG_DIR)libblconverter.a
    COMLIB += $(OCGDIR)/gameengine/blconverter/$(DEBUG_DIR)libblconverter.a
    COMLIB += $(NAN_SOLID)/lib/libsolid.a
    COMLIB += $(NAN_SOLID)/lib/libsolid_broad.a 
    COMLIB += $(NAN_SOLID)/lib/libsolid_complex.a
    COMLIB += $(NAN_SOLID)/lib/libsolid_convex.a
    COMLIB += $(OCGDIR)/gameengine/blphys/sumo/$(DEBUG_DIR)libsumo.a
    COMLIB += $(OCGDIR)/gameengine/blphys/fuzzics/$(DEBUG_DIR)libfuzzics.a
    COMLIB += $(NAN_QHULL)/lib/libqhull.a
    COMLIB += $(OCGDIR)/gameengine/blphys/dummy/$(DEBUG_DIR)libdummy.a
    COMLIB += $(OCGDIR)/gameengine/blphys/common/$(DEBUG_DIR)libcommon.a
#    COMLIB += $(OCGDIR)/gameengine/blphys/sumo/$(DEBUG_DIR)libsumo.a
    COMLIB += $(OCGDIR)/gameengine/blphys/dummy/$(DEBUG_DIR)libdummy.a
    COMLIB += $(OCGDIR)/gameengine/ketsji/$(DEBUG_DIR)libketsji.a
    COMLIB += $(OCGDIR)/gameengine/blphys/common/$(DEBUG_DIR)libcommon.a
#    COMLIB += $(OCGDIR)/gameengine/blphys/blode/$(DEBUG_DIR)libblode.a
#    COMLIB += $(OCGDIR)/gameengine/blphys/sumo/$(DEBUG_DIR)libsumo.a
    COMLIB += $(OCGDIR)/gameengine/blphys/dummy/$(DEBUG_DIR)libdummy.a
    COMLIB += $(OCGDIR)/gameengine/blphys/blbullet/$(DEBUG_DIR)libblbullet.a
    COMLIB += $(OCGDIR)/gameengine/blphys/common/$(DEBUG_DIR)libcommon.a
#    COMLIB += $(OCGDIR)/gameengine/blphys/sumo/$(DEBUG_DIR)libsumo.a
    COMLIB += $(OCGDIR)/gameengine/blphys/dummy/$(DEBUG_DIR)libdummy.a
    COMLIB += $(OCGDIR)/gameengine/ketsji/$(DEBUG_DIR)libketsji.a
    COMLIB += $(OCGDIR)/gameengine/logic/$(DEBUG_DIR)liblogic.a
    COMLIB += $(OCGDIR)/gameengine/logic/Joystick/$(DEBUG_DIR)libJoystick.a
    COMLIB += $(OCGDIR)/gameengine/rasterizer/$(DEBUG_DIR)librasterizer.a
    COMLIB += $(OCGDIR)/gameengine/OpenGLrasterizer/$(DEBUG_DIR)libOpenGLrasterizer.a
    COMLIB += $(OCGDIR)/gameengine/expression/$(DEBUG_DIR)libexpression.a
    COMLIB += $(OCGDIR)/gameengine/scenegraph/$(DEBUG_DIR)libscenegraph.a
    COMLIB += $(OCGDIR)/gameengine/videotex/$(DEBUG_DIR)libvideotex.a
#    COMLIB += $(OCGDIR)/sumo/$(DEBUG_DIR)libfuzzics.a
#    COMLIB += $(OCGDIR)/sumo/$(DEBUG_DIR)libsolid.a
    COMLIB += $(NAN_MOTO)/lib/libmoto.a
    COMLIB += $(NAN_SND_LIBS)
    COMLIB += $(OCGDIR)/kernel/gen_system/$(DEBUG_DIR)libgen_system.a
    COMLIB += $(OCGDIR)/kernel/gen_messaging/$(DEBUG_DIR)libgen_messaging.a
    COMLIB += $(OCGDIR)/gameengine/ketsji/KXNetwork/$(DEBUG_DIR)libKXNetwork.a
    COMLIB += $(OCGDIR)/gameengine/Network/$(DEBUG_DIR)libNetwork.a
    COMLIB += $(OCGDIR)/gameengine/Network/LoopBackNetwork/$(DEBUG_DIR)libLoopBackNetwork.a
    COMLIB += $(NAN_BULLET2)/lib/libbullet2.a
endif

# Cloth requires bullet2, gameegine does not matter anymore
#COMLIB += $(NAN_BULLET2)/lib/libbullet2.a

COMLIB += $(NAN_GUARDEDALLOC)/lib/libguardedalloc.a
COMLIB += $(NAN_MEMUTIL)/lib/libmemutil.a
COMLIB += $(NAN_BMFONT)/lib/$(DEBUG_DIR)libbmfont.a
COMLIB += $(NAN_PNG)/lib/libpng.a
COMLIB += $(OCGDIR)/blender/yafray/$(DEBUG_DIR)libyafrayexport.a
COMLIB += $(OCGDIR)/blender/blenlib/$(DEBUG_DIR)libblenlib.a

ifeq ($(WITH_QUICKTIME), true)
    COMLIB += $(OCGDIR)/blender/blenderqt/$(DEBUG_DIR)libblenderqt.a
endif

ifeq ($(WITH_OPENEXR), true)
    COMLIB += $(OCGDIR)/blender/imbuf/openexr/$(DEBUG_DIR)libopenexr.a
endif

ifeq ($(WITH_OPENJPEG), true)
    COMLIB += $(OCGDIR)/extern/openjpeg/$(DEBUG_DIR)libopenjpeg.a
endif

COMLIB += $(OCGDIR)/blender/imbuf/cineon/$(DEBUG_DIR)libcineon.a

ifeq ($(WITH_DDS), true)
    COMLIB += $(OCGDIR)/blender/imbuf/dds/$(DEBUG_DIR)libdds.a
endif

ifeq ($(WITH_BINRELOC), true)
    COMLIB += $(OCGDIR)/extern/binreloc/$(DEBUG_DIR)libbinreloc.a
endif

ifeq ($(WITH_FREETYPE2), true)
    COMLIB += $(OCGDIR)/blender/ftfont/$(DEBUG_DIR)libftfont.a
    ifeq ($(OS), windows)
      ifeq ($(FREE_WINDOWS), true)
        COMLIB += $(NAN_FTGL)/lib/libftgl.a
        COMLIB += $(NAN_FREETYPE)/lib/libfreetype.a
      else
        COMLIB += $(NAN_FTGL)/lib/ftgl_static_ST.lib
        COMLIB += $(NAN_FREETYPE)/lib/freetype2ST.lib
      endif
    else
      COMLIB += $(NAN_FTGL)/lib/libftgl.a
      ifeq ($(OS), irix)
        COMLIB += $(NAN_FREETYPE)/lib/libfreetype.a
        else
            COMLIB += $(NAN_FREETYPE)/lib/libfreetype.a
      endif
    endif
endif

ifeq ($(WITH_VERSE), true)
   ifeq ($(OS), windows)
       ifeq ($(FREE_WINDOWS), true)
           COMLIB += $(NAN_VERSE)/lib/libverse.a
       else
           COMLIB += $(NAN_VERSE)/lib/verse.lib
       endif
   else
       COMLIB += $(NAN_VERSE)/lib/libverse.a
   endif
endif

ifeq ($(OS), irix)
    COMLIB += $(NAN_SDL)/lib/libSDL.a
endif

ifeq ($(OS), windows)
    ifeq ($(FREE_WINDOWS), true)
        COMLIB += $(NAN_SDL)/lib/libSDL.a
        COMLIB += $(NAN_PTHREADS)/lib/libpthreadGC2.a
    else
        COMLIB += $(NAN_SDL)/lib/SDL.lib
    endif
endif

ifeq ($(WITH_OPENEXR), true)
    COMLIB += $(NAN_OPENEXR_LIBS)
endif

PULIB = $(NAN_MOTO)/lib/libmoto.a
PULIB += $(NAN_DECIMATION)/lib/libdecimation.a
PULIB += $(NAN_ELBEEM)/lib/$(DEBUG_DIR)libelbeem.a
PULIB += $(OCGDIR)/blender/readblenfile/$(DEBUG_DIR)libreadblenfile.a
PULIB += $(OCGDIR)/blender/src/$(DEBUG_DIR)libsrcpublisher.a

ifeq ($(NAN_NO_KETSJI),true)
    PULIB += $(NAN_MOTO)/lib/libmoto.a
    PULIB += $(OCGDIR)/kernel/gen_system/$(DEBUG_DIR)libgen_system.a
    PULIB += $(OCGDIR)/kernel/gen_messaging/$(DEBUG_DIR)libgen_messaging.a
    COMLIB += $(NAN_SND_LIBS)
endif

SPLIB1 = $(OCGDIR)/gameengine/GamePlayer/ghost/$(DEBUG_DIR)libghost.a
SPLIB1 += $(OCGDIR)/gameengine/GamePlayer/common/$(DEBUG_DIR)libcommon.a
SPLIB1 += $(OCGDIR)/gameengine/blconverter/$(DEBUG_DIR)libblconverter.a
SPLIB1 += $(NAN_STRING)/lib/$(DEBUG_DIR)libstring.a
SPLIB1 += $(NAN_GHOST)/lib/$(DEBUG_DIR)libghost.a

SPLIB = $(OCGDIR)/blender/makesdna/$(DEBUG_DIR)DNA.o
SPLIB += $(OCGDIR)/blender/readblenfile/$(DEBUG_DIR)libreadblenfile.a
# this is used for the plugin. It uses some things from libz.a, 
# but somehow it consistently fails to resolve these symbols... or 
# can I just not check them? nm claims they aren't...
SPLIB += $(OCGDIR)/blender/blenkernel/blenkernel_blc/$(DEBUG_DIR)libblenkernel_blc.a
SPLIB += $(OCGDIR)/blender/python/$(DEBUG_DIR)libpython.a
SPLIB += $(OCGDIR)/blender/blenlib/$(DEBUG_DIR)libblenlib.a

# These three need to be explicitly mentioned on the cl, because 
# if they are offered as a lib, they are optimized away. (nzc)
NSPLUGLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)UnixShell.o
NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)stubs.o
NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)winstubs.o
NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)Blender3DPlugin_native_implementation.o

# Here you can configure what sort of test to make for the plugin.
#    PLUGTESTLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/test/$(DEBUG_DIR)libns_api_test_stub.a
#    PLUGTESTLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/test/$(DEBUG_DIR)libns_api_test_colorcycle.a
#    PLUGTESTLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/test/$(DEBUG_DIR)libns_api_test_gears.a
PLUGTESTLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/test/$(DEBUG_DIR)libns_api_test_threaded_gears.a

# XPCOM is done only for Linux for now
ifeq ($(OS),$(findstring $(OS), "linux"))
  ifeq ($(CPU),i386)
    NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)XPH_xpcom_hooks.o
  endif
endif

PLUGAPPLIB = $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)libplugin_ketsji_hooks.a

ifeq ($(OS),$(findstring $(OS), "freebsd linux irix solaris"))
    NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)PLG_X11_windowing.o
    PLUGAPPLIB += $(OCGDIR)/gameengine/GamePlayer/common/unix/$(DEBUG_DIR)libunix.a
endif
ifeq ($(OS),$(findstring $(OS), "windows"))
    NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)PLG_MSWindows_windowing.o
    NSPLUGLIB += $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)npB3DPlg.res
    PLUGAPPLIB += $(OCGDIR)/gameengine/GamePlayer/common/windows/$(DEBUG_DIR)libwindows.a
endif

PLUGAPPLIB += $(OCGDIR)/gameengine/GamePlayer/common/$(DEBUG_DIR)libcommon.a

ifeq ($(OS),$(findstring $(OS), "linux"))
  ifeq ($(CPU),i386)
    PLUGAPPLIB_XPLINK = $(OCGDIR)/gameengine/GamePlayer/netscape/src/$(DEBUG_DIR)_Blender3DPlugin_implementation_.o 
  endif
endif

# A bit silly... but needed to resolve symbols.
PLUGREMLIB = $(NAN_STRING)/lib/$(DEBUG_DIR)libstring.a

######################## OS dependencies (alphabetic!) ################

include nan_link.mk

ifeq ($(NAN_JUST_BLENDERDYNAMIC),true)
    BINTARGETS = blenderdynamic
endif

ifeq ($(WITH_BF_DYNAMICOPENGL), true)
    BINTARGETS += blenderdynamic
endif

ifeq ($(WITH_BF_STATICOPENGL), true)
    BINTARGETS += blenderstatic
endif

ifeq ($(WITH_BF_BLENDERPLAYER), true)
    export WITH_BF_GAMEENGINE=true
    BINTARGETS += blenderplayer
endif

ifeq ($(WITH_BF_WEBPLUGIN), true)
    BINTARGETS += plugin
    ifeq ($(OS),linux)
        ifeq ($(CPU),i386)
             BINTARGETS += xplink
        endif
    endif
endif

ifeq ($(OS),solaris)
    PULIB += $(NAN_ZLIB)/lib/libz.a
    SPLIB += $(NAN_ZLIB)/lib/libz.a
endif

# OpenAL libs are already compiled as shared code!

# Some vars to keep the rest of this section mostly readable
# in an 80 char term
SOUNDSYSTEM = $(OCGDIR)/intern/SoundSystem/$(DEBUG_DIR)libSoundSystem.a
DUMMYSOUND  = $(OCGDIR)/intern/DummySoundSystem/$(DEBUG_DIR)libDummySoundSystem.a
OPENALSOUND = $(OCGDIR)/intern/OpenALSoundSystem/$(DEBUG_DIR)libOpenALSoundSystem.a
SDLSOUND    = $(OCGDIR)/intern/SDLSoundSystem/$(DEBUG_DIR)libSDLSoundSystem.a

# Some kooky logic going on here ...
ifeq ($(NAN_NO_OPENAL), true)
    NAN_SND_LIBS =  $(SOUNDSYSTEM)
    NAN_SND_LIBS += $(DUMMYSOUND)
    NAN_SND_LIBS += $(SOUNDSYSTEM)
else
  ifeq ($(OS),$(findstring $(OS), "freebsd linux windows"))
    ifeq ($(CPU),$(findstring $(CPU), "i386 powerpc x86_64 parisc64"))
        NAN_SND_LIBS =  $(SOUNDSYSTEM)
        NAN_SND_LIBS += $(DUMMYSOUND)
        NAN_SND_LIBS += $(OPENALSOUND)
        NAN_SND_LIBS += $(SDLSOUND)
        NAN_SND_LIBS += $(NAN_OPENAL)/lib/libopenal.a
        NAN_SND_LIBS += $(SOUNDSYSTEM)
    else
      ifeq ($(OS),windows)
        NAN_SND_LIBS =  $(SOUNDSYSTEM)
        NAN_SND_LIBS += $(DUMMYSOUND)
        NAN_SND_LIBS += $(OPENALSOUND)
        NAN_SND_LIBS += $(SDLSOUND)
        NAN_SND_LIBS += $(NAN_OPENAL)/lib/openal_static.lib
        NAN_SND_LIBS += $(SOUNDSYSTEM)
      else
        NAN_SND_LIBS =  $(SOUNDSYSTEM)
        NAN_SND_LIBS += $(DUMMYSOUND)
        NAN_SND_LIBS += $(SOUNDSYSTEM)
      endif
    endif
  else
    ifeq ($(OS),darwin)
      NAN_SND_LIBS =  $(SOUNDSYSTEM)
      NAN_SND_LIBS += $(DUMMYSOUND)
      NAN_SND_LIBS += $(OPENALSOUND)
      NAN_SND_LIBS += $(NAN_OPENAL)/lib/libopenal.a
      NAN_SND_LIBS += $(SOUNDSYSTEM)
    else
      ifeq ($(OS), solaris)
        NAN_SND_LIBS =  $(SOUNDSYSTEM)
        NAN_SND_LIBS += $(DUMMYSOUND)
        NAN_SND_LIBS += $(OPENALSOUND)
        NAN_SND_LIBS += $(SDLSOUND)
        NAN_SND_LIBS += $(NAN_OPENAL)/lib/libopenal.a
        NAN_SND_LIBS += $(SOUNDSYSTEM)
      else
        ifeq ($(OS), irix)
           NAN_SND_LIBS = $(SOUNDSYSTEM)
           NAN_SND_LIBS += $(DUMMYSOUND)
           NAN_SND_LIBS += $(SDLSOUND)
           NAN_SND_LIBS += $(SOUNDSYSTEM)
        else
           NAN_SND_LIBS =  $(SOUNDSYSTEM)
           NAN_SND_LIBS += $(DUMMYSOUND)
           NAN_SND_LIBS += $(SOUNDSYSTEM)
        endif
      endif
    endif
  endif
endif

ifeq ($(OS),windows)

    # Might need to change this to $(NAN_MOZILLA_LIB)/nspr4.lib
    NSPLUGLIB += $(NAN_NSPR)/lib/nspr4.lib

    BINTARGETS = blenderdynamic
    ifeq ($(FREE_WINDOWS),true)
        ifneq ($(NAN_NO_KETSJI),true)
            BINTARGETS += blenderplayer
        endif
    else
        BINTARGETS += blenderplayer
        BINTARGETS += blenderdynplayer
        BINTARGETS += plugin
    endif

    PULIB += $(OCGDIR)/blender/icons/$(DEBUG_DIR)winblender.res
    PULIB += $(NAN_ZLIB)/lib/libz.a
    SPLIB += $(OCGDIR)/blender/icons/$(DEBUG_DIR)winblender.res
    SPLIB += $(NAN_ZLIB)/lib/libz.a
endif


# prepare for NAN_BUILDINFO compile at the *sigh* link rules below

ifdef NAN_BUILDINFO
    CSRCS =
    ALLTARGETS =
    include nan_compile.mk
endif

################## target rules ########################

all debug ::
	@echo "****> Make $@ by $(ID)@$(HOST) at $(MAKE_START) on $(CONFIG_GUESS)"
ifdef NANENV
	@for n in $(NANENV); do \
	    echo "      $$n"; \
	done
endif

DIR = $(OCGDIR)
SOURCEDIR = source

include nan_subdirs.mk

################## target rules ########################

all:: link

debug debuglink::
	@$(MAKE) link DEBUG_DIR="debug/" NANENV=$(NANENV)

clean:: linkclean debuglinkclean

link: $(BINTARGETS)
	@echo "****> Build $(MAKE_START) - `date '+%H:%M:%S %d-%b-%Y'`"
ifdef NANENV
	@for n in $(NANENV); do \
	    echo "      $$n"; \
	done
endif

linkclean:
	@$(RM) -r $(DIR)/blenderstatic* \
		  $(DIR)/blenderplayer* \
		  $(DIR)/bin/*

debuglinkclean:
	@$(RM) -r $(DIR)/debug/blenderstatic* \
		  $(DIR)/debug/blenderplayer* \
		  $(DIR)/debug/bin/*

# Shortcut for Tinderbox release builds. Mortals don't use this.
release:
	@$(MAKE) -C ../release/ all || exit 1;

############### Linker rules ###############

blenderstatic: $(DIR)/$(DEBUG_DIR)bin/blenderstatic
blenderdynamic: $(DIR)/$(DEBUG_DIR)bin/blender$(EXT)
blenderplayer: $(DIR)/$(DEBUG_DIR)bin/blenderplayer$(EXT)
blenderdynplayer: $(DIR)/$(DEBUG_DIR)bin/blenderdynplayer$(EXT)

# XPCOM connector only for linux so far...
ifeq ($(OS),linux)
    xplink: $(DIR)/$(DEBUG_DIR)bin/Blender3DPlugin$(SOEXT)
endif

# Moz/NS plugin:
ifeq ($(OS),$(findstring $(OS), "freebsd linux irix solaris"))
    plugin: $(DIR)/$(DEBUG_DIR)bin/npBlender3DPlugin$(SOEXT)
    ptest: $(DIR)/$(DEBUG_DIR)bin/npTestPlugin$(SOEXT)
endif
# Windows needs a 8.3 name... Why? Dunno...
ifeq ($(OS),windows)
	ifneq ($(FREE_WINDOWS),true)
	    plugin: $(DIR)/$(DEBUG_DIR)npB3DPlg$(SOEXT)
	endif
endif

$(DIR)/$(DEBUG_DIR)bin/blenderstatic: $(OBJS) $(GRPLIB) $(COMLIB) $(PULIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"static"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o $(DIR)/$(DEBUG_DIR)bin/blenderstatic $(BUILDINFO_O) $(OBJS) $(GRPLIB) $(COMLIB) $(PULIB) $(LLIBS) $(SADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif
ifeq ($(OS), darwin)
	@$(MAKE) -C darwin/ APPLICATION=blenderstatic
endif

$(DIR)/$(DEBUG_DIR)bin/blender$(EXT): $(OBJS) $(GRPLIB) $(COMLIB) $(PULIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o $(DIR)/$(DEBUG_DIR)bin/blender$(EXT) $(BUILDINFO_O) $(OBJS) $(GRPLIB) $(COMLIB) $(PULIB) $(LLIBS) $(DADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif
ifeq ($(OS), darwin)
	@$(MAKE) -C darwin/ APPLICATION=blender
endif

$(DIR)/$(DEBUG_DIR)bin/blenderplayer$(EXT): $(OBJS) $(SPLIB1) $(COMLIB) $(SPLIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o $(DIR)/$(DEBUG_DIR)bin/blenderplayer$(EXT) $(BUILDINFO_O) $(OBJS) $(SPLIB1) $(COMLIB) $(SPLIB) $(LLIBS) $(DADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif
ifeq ($(OS), darwin)
	@$(MAKE) -C darwin/ APPLICATION=blenderplayer
endif

$(DIR)/$(DEBUG_DIR)bin/blenderdynplayer$(EXT): $(OBJS) $(COMLIB) $(SPLIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o $(DIR)/$(DEBUG_DIR)bin/blenderdynplayer$(EXT) $(BUILDINFO_O) $(OBJS) $(SPLIB1) $(COMLIB) $(SPLIB) $(LLIBS) $(DADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif
ifeq ($(OS), darwin)
	@$(MAKE) -C darwin/ APPLICATION=blenderplayer
endif

$(DIR)/$(DEBUG_DIR)bin/Blender3DPlugin$(SOEXT): $(PLUGAPPLIB_XPLINK)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(CCFLAGS) $(DYNLDFLAGS) -o $@ $(PLUGAPPLIB_XPLINK) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif

# Windows build needs a def file? Why? For exposing functions from the
# dll to the outside world. However, this is alsi done internally..
DEFFILE = ./gameengine/GamePlayer/netscape/src/npB3DPlg.def

# Windows needs a specific name format for dll.s so we give it one.
$(DIR)/$(DEBUG_DIR)npB3DPlg$(SOEXT): $(NSPLUGLIB) $(PLUGAPPLIB) $(COMLIB) $(SPLIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
#	$(CCC) $(DYNLDFLAGS) -o $@ $(NSPLUGLIB) $(PLUGAPPLIB) $(COMLIB) $(SPLIB) $(PLUGREMLIB) $(LLIBS) $(DADD) $(LOPTS) 
	$(CCC) $(DYNLDFLAGS) -o $@ $(NSPLUGLIB) $(PLUGAPPLIB) $(COMLIB) $(SPLIB) $(PLUGREMLIB) $(LLIBS) $(DADD) $(LOPTS) /def:$(DEFFILE)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif

$(DIR)/$(DEBUG_DIR)bin/npBlender3DPlugin$(SOEXT): $(NSPLUGLIB) $(PLUGAPPLIB) $(COMLIB) $(SPLIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(DYNLDFLAGS) -o $@ $(NSPLUGLIB) $(PLUGAPPLIB) $(COMLIB) $(SPLIB) $(PLUGREMLIB) $(LLIBS) $(DADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif

$(DIR)/$(DEBUG_DIR)bin/npTestPlugin$(SOEXT): $(NSPLUGLIB)
	@echo "****> Link $@"
ifdef NAN_BUILDINFO
	$(CCC) $(REL_CFLAGS) -DBUILD_DATE='"$(BUILD_DATE)"' -DBUILD_TIME='"$(BUILD_TIME)"' -DBUILD_REV='"$(BUILD_REV)"' -DBUILD_PLATFORM='"$(CONFIG_GUESS)"' -DBUILD_TYPE='"dynamic"' $(BUILDINFO_C) -c -o $(BUILDINFO_O) -DNAN_BUILDINFO
endif
	mkdir -p $(DIR)/$(DEBUG_DIR)bin
	$(CCC) $(DYNLDFLAGS) -o $@ $(NSPLUGLIB) $(PLUGTESTLIB) $(LLIBS) $(DADD) $(LOPTS)
ifdef NAN_BUILDINFO
	/bin/rm $(BUILDINFO_O)
endif

