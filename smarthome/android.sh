#! /bin/bash
haxelib run nme test project.nmml android 
cp ./Extension/project/layout ./Export/android/bin/res/ -r
