#! /bin/bash
haxelib run nme test maintest.nmml android
cp ./Extension/project/layout ./Export/android/bin/res/ -r
