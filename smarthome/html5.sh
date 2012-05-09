#! /bin/bash
haxelib run nme build maintest.nmml html5
cp -r Export/html5/bin/*.* .
