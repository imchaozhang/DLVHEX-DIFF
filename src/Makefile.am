#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin-diff.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexplugin_diff_la_SOURCES = diff.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_diff_la_LDFLAGS = -avoid-version -module


libdlvhexplugin-diff-static.la: $(libdlvhexplugin_diff_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_diff_la_OBJECTS)

install-static: libdlvhexplugin-diff-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-diff-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-diff-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-diff-static.la
