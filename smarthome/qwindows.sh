#! /bin/bash
haxelib run nme build qbox.nmml windows  -debug
cp ./Extension/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme run qbox.nmml windows  -debug
