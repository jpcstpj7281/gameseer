#! /bin/bash
cp ./Extension/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme build pictionary.nmml windows 
haxelib run nme run pictionary.nmml windows 
