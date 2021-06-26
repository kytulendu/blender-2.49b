#
# $Id: .obj.Makefile 12931 2007-12-17 18:20:48Z theeth $
#

SDIR = $(HOME)/develop/source/blender/src

all debug clean:
	@echo "****> Object Makefile, chdir to $(SDIR) ..."
	@$(MAKE) -C $(SDIR) $@ || exit 1;
