BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_CPPFLAGS = -DMIG_VERSION=\"$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)\" \
              $(COMPAT_CPPFLAGS)
bin_PROGRAMS = migcom
migcom_SOURCES = alloc.h \
                 error.c \
                 error.h \
                 global.c \
                 global.h \
                 header.c \
                 lexxer.h \
                 lexxer.l \
                 mig.c \
                 mig_errors.h \
                 mig_machine.h \
                 parser.y \
                 routine.c \
                 routine.h \
                 server.c \
                 statement.c \
                 statement.h \
                 strdefs.h \
                 string.c \
                 type.c \
                 type.h \
                 user.c \
                 utils.c \
                 utils.h \
                 write.h

dist_bin_SCRIPTS = mig.sh
install-exec-hook:
	mv $(DESTDIR)$(bindir)/mig.sh $(DESTDIR)$(bindir)/mig

dist_man_MANS = mig.1 \
                migcom.1

EXTRA_DIST = handler.c \
             xcode/parser.h
