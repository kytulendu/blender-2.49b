#
# $Id: .obj.Makefile 2 2002-10-12 11:37:38Z hans $
#

SDIR = $(HOME)/develop/source

all debug link debuglink clean linkclean debuglinkclean:
	@echo "****> Object Makefile, chdir to $(SDIR) ..."
	@$(MAKE) -C $(SDIR) $@ || exit 1;
