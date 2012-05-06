#! /bin/bash
cp indextest.html ./Export/flash/bin/
haxelib run nme build maintest.nmml flash
cp ./Export/flash/bin/TestMain.swf ./
#flashdb11 http://www.astrol.com/smarthome/Export/flash/bin/SmartHome.swf
