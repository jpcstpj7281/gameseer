#! /bin/bash
cp index.html ./Export/flash/bin/
haxelib run nme build project.nmml html5
#haxelib run nme build maintest.nmml flash
#flashdb11 http://www.astrol.com/smarthome/Export/flash/bin/SmartHome.swf
