#! /bin/bash
cp ./Extension/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme build pictionary.nmml windows -debug
haxelib run nme run pictionary.nmml windows -debug
