#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

echo "-> local-release xyo"

cmdX(){
	if ! "$@" ; then
		echo "Error: local-release"
		exit 1
	fi
}

export XYO_PATH_RELEASE=release

cmdX /bin/sh ./port/build.ubuntu.sh make
cmdX /bin/sh ./port/build.ubuntu.sh install
cmdX /bin/sh ./port/build.ubuntu.sh install-release
cmdX ./build/xyo.cc xyo --archive-release-sha512 --version-file=source/xyo.version.ini
