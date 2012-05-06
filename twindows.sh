#! /bin/bash
cp ./Extension/ndll/Windows/native.ndll ./Export/cpp/windows/bin/
haxelib run nme build maintest.nmml windows 
haxelib run nme run maintest.nmml windows 
