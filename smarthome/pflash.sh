#! /bin/bash
#cp indextest.html ./Export/flash/bin/
haxelib run nme build pictionary.nmml flash
cp ./Export/flash/bin/*.swf ./
#flashdb11 http://www.astrol.com/smarthome/Export/flash/bin/SmartHome.swf
