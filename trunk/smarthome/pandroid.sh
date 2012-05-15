#! /bin/bash
haxelib run nme test pictionary.nmml android -DhaxeJSON
cp ./Extension/project/layout ./Export/android/bin/res/ -r
