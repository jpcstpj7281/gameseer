#! /bin/bash
haxelib run nme build project.nmml windows 
cp ./Extension/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme run project.nmml windows 
