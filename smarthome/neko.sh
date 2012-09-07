#! /bin/bash

cp ./Extension/project/ndll/Windows/native.ndll ./Export/neko/windows/bin/
haxelib run nme test project.nmml neko
