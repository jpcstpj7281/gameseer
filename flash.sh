#! /bin/bash
haxelib run nme build project.nmml flash
cp Export/flash/bin/SmartHome.swf .
#haxelib run nme build maintest.nmml flash
#flashdb11 http://www.astrol.com/smarthome/Export/flash/bin/SmartHome.swf
