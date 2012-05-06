


package com.blueseer.ui;

import com.blueseer.cmd.Command;
import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;
import com.eclecticdesignstudio.motion.actuators.GenericActuator;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;

class SimpleCmdDialog extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _isDown:Bool;
    public var _id:Int;

    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        var str:String = name;
        _id = id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);

        _isDown =false;
    }

    public override function showParent():Void{
        var dm:ListDialogMgr= cast (_mgr);
        dm.showListDialog();
    }
    public override function hideParent():Void{
        var dm:ListDialogMgr = cast (_mgr);
        dm.hideListDialog();
    }
    override function show():IGenericActuator {
        //trace("showing");
        return super.show();
    }

    override function onMouseClick( ):Void{
        var cmd:Command = CommandMgr.getInst().getCmd(_id);
        if ( cmd != null){
            cmd.fire();
        }
        else trace("unable to get coresponsed command: " + _id);
    }
}

