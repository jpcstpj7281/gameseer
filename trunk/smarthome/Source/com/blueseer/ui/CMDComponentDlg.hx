package com.blueseer.ui;

import base.ui.CommDialog;
import base.ui.ComponentDlg;
import base.ui.ComponentDlgMgr;
import com.blueseer.cmd.Command;
import com.blueseer.cmd.CommandMgr;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.eclecticdesignstudio.motion.actuators.GenericActuator;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

class CMDComponentDlg extends ComponentDlg{

    public function new ( cmdDlgMgr:ComponentDlgMgr, name:String, id:Int ){
        super( cmdDlgMgr, name, id);
    }

    override function onMouseClick( ):Void{
        var cmd:Command = CommandMgr.getInst().getCmd(_id);
        if ( cmd != null){
            cmd.fire();
        }
        else trace("unable to get coresponsed command: " + _id);
    }

}

