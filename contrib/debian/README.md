
Debian
====================
This directory contains files used to package softcoind/softcoin-qt
for Debian-based Linux systems. If you compile softcoind/softcoin-qt yourself, there are some useful files here.

## softcoin: URI support ##


softcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install softcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your softcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/softcoin128.png` to `/usr/share/pixmaps`

softcoin-qt.protocol (KDE)

