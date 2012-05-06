package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
import com.blueseer.cmd.Command;
import com.blueseer.device.Device;
import com.blueseer.device.DeviceMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import com.eclecticdesignstudio.motion.actuators.GenericActuator;
import com.eclecticdesignstudio.motion.Actuate;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;

class SelectDeviceDialog extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _deviceID:Int;
    public var _cmdid:Int;


    public function new ( mgr:ListDialogMgr, devicename:String, deviceid:Int, cmdid:Int ){
        var str:String = devicename;
        _deviceID = deviceid;
        _cmdid =  cmdid;
        _uniqueId = str+_cmdid;
        var s:Sprite = createElement( str, deviceid);
        super(  mgr);
        addChild(s);
    }

    private function createElement(name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 220;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 220/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = Std.string(id);
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.setBorder(true);
        txt1.width = 100;
        txt1.x = 120;
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("trunk") );
        //bm.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;

        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt1);
        s.addChild( txt);
        //var w:Float = nme.Lib.current.stage.stageWidth / txt.width;
        //s.width=  nme.Lib.current.stage.stageWidth;
        s.height = nme.Lib.current.stage.stageHeight/10;
        //txt.scaleY = 2;
        return s;
    }

    override function show():IGenericActuator {
        //var res = super.show();
        visible = true;
        mouseEnabled = true;
        var res;
        var cmd:Command = CommandMgr.getInst()._commands.get(_cmdid);
        var flag:Int = 1 << (_deviceID -1);
        if ( ( cmd._deviceType & flag )!= 0 ){
            res = Actuate.apply(this, { alpha: 0.5} );
        }
        else{
            res = Actuate.apply(this, { alpha: 1} );
        }
        //trace( "did: "+_deviceID + " shows " + alpha);
        return res;
    }

    override function onMouseClick( ):Void{
        var cmd:Command = CommandMgr.getInst()._commands.get(_cmdid);
        var flag:Int = 1 << (_deviceID -1);
        if ( ( cmd._deviceType & flag )!= 0 ){
            cmd._deviceType = cmd._deviceType & ~flag;
            alpha = 1;
        }
        else{
            cmd._deviceType = cmd._deviceType | flag;
            alpha = 0.5;
        }
    }

}

