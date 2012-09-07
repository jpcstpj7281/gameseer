#! /bin/bash
haxelib run nme build project.nmml windows  -debug
cp ./Extension/project/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme run project.nmml windows  -debug
