dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This dwm version has a few patches applied to it:

* [tab+pertag](http://dwm.suckless.org/patches/tab)
* [statuscolors](http://dwm.suckless.org/patches/statuscolors)
* [xft](http://dwm.suckless.org/patches/xft)

The patch files are here only for reference, I patched dwm.c manually after the first patch.

I also put in a boolean in config.h for choosing whether the client title is displayed in the status bar. The included status bar script is based on [w0ng's](https://github.com/w0ng/bin/blob/master/dwm-statusbar) and relies on a [custom font](https://github.com/epedroni/dvicons).
