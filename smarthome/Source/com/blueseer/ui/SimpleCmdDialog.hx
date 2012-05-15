package com.blueseer.ui;

import com.blueseer.cmd.Command;
import com.blueseer.cmd.CommandMgr;

import base.ui.CommDialog;
import base.ui.ListDialogMgr;
import nme.display.Sprite;

class SimpleCmdDialog extends CommDialog{

    public var _id:Int;
    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        var str:String = name;
        _id = id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);

    }

    override function onMouseClick( ):Void{
        var cmd:Command = CommandMgr.getInst().getCmd(_id);
        if ( cmd != null){
            cmd.fire();
        }
        else trace("unable to get coresponsed command: " + _id);
    }
}

