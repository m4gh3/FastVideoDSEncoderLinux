#!/bin/sh
gcc pkgtools/list2bar.c -o build/list2bar
gcc pkgtools/bin2s.c -o build/bin2s
BUILDDIR=$(pwd)/build
LIST2BAR=$(pwd)/build/list2bar
BIN2S=$(pwd)/build/bin2s
cd FastVideoDSEncoder
dotnet publish -p:PublishSingleFile=true -r linux-x64 -c Release -p:PublishTrimmed=true
cd bin/Release/net6.0/linux-x64/
rm publish/FastVideoDSEncoder.pdb publish/Gericom.FastVideoDS.pdb
find publish | $LIST2BAR publish.bar
gzip publish.bar
$BIN2S publish.bar.gz | as -o $BUILDDIR/publish.o
cd $BUILDDIR
g++ $BUILDDIR/publish.o ../pkgtools/packed_exec.cpp -lz -o FastVideoDSEncoder
