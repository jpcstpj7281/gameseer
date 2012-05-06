#! /bin/bash
haxelib run nme test pictionary.nmml android
cp ./Extension/project/layout ./Export/android/bin/res/ -r
