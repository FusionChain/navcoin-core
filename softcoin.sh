#!/bin/sh

if [ "$1" = "build" ]; then
    cd ~/org/software/softcoin
    export CXXFLAGS="$CXXFLAGS -fPIC"
    make clean
    ./autogen.sh
    autoupdate
    ./configure --with-gui=qt5 --enable-tests=no --enable-upnp-default --with-qrcode=yes --disable-hardening --enable-shared
    make
fi