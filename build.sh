#!/bin/sh

BUILDDIR=$(pwd)/build
LIST2BAR=$(pwd)/build/list2bar
BIN2S=$(pwd)/build/bin2s

case $1 in
	pkgtools)
		gcc pkgtools/list2bar.c -o build/list2bar
		gcc pkgtools/bin2s.c -o build/bin2s
	;;
	ffmpeg)
		cd $BUILDDIR
		wget https://github.com/m4gh3/ffmpeg_linux_builder/releases/download/release.2022.12.17/ffmpeg_libs.tar.bz2
		tar xjf ffmpeg_libs.tar.bz2
	;;
	FastVideoDSEncoder)
		cd FastVideoDSEncoder
		dotnet publish -p:PublishSingleFile=true -r linux-x64 -c Release -p:PublishTrimmed=true
		cd bin/Release/net6.0/linux-x64/
		rm publish/FastVideoDSEncoder.pdb publish/Gericom.FastVideoDS.pdb
		cp $BUILDDIR/lib/*.so.* publish/x64/
		rm publish/x64/*.so.*.*
		find publish | $LIST2BAR publish.bar
		rm publish.bar.gz
		gzip publish.bar
		$BIN2S publish.bar.gz | as -o $BUILDDIR/publish.o
		cd $BUILDDIR
		g++ -static $BUILDDIR/publish.o ../pkgtools/packed_exec.cpp -l:libz.a -o FastVideoDSEncoder
	;;
esac
