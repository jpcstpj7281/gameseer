


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

    public function new ( cmdDlgMgr:ListDialogMgr, name:String, id:Int ){
        var str:String = name;
        _id = id;
        var s:Sprite = cmdDlgMgr.createElement( str, id);
        var dd:DialogData = cmdDlgMgr.createListDialogData( s, str+id );
        super( dd);
        dialogManager = cmdDlgMgr;
        //trace(cmdDlgMgr);
        cmdDlgMgr.addDialog(this );

        this.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        this.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        this.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);

        _isDown =false;
    }

    public override function showParent():Void{
        var dm:ListDialogMgr= cast (dialogManager);
        dm.showListDialog();
    }
    public override function hideParent():Void{
        var dm:ListDialogMgr = cast (dialogManager);
        dm.hideListDialog();
    }
    override function show():IGenericActuator {
        //trace("showing");
        return super.show();
    }

    private function onMouseClicked( evt:MouseEvent):Void{
        var cmd:Command = CommandMgr.getInst().getCmd(_id);
        if ( cmd != null){
            cmd.fire();
        }
        else trace("unable to get coresponsed command: " + _id);
    }
    public function onMouseDown(evt:MouseEvent){ 
        _downx = evt.stageX;
        _downy = evt.stageY;
        _isDown = true;
        //trace("down");
    }
    public function onMouseMove(evt:MouseEvent){ 
        if( (evt.stageX- _downx) > 100 ){
            //trace("move");
            _downx = 10000;
            _downy = 10000;
        }else if ( (evt.stageY - _downy)  > 100 ){
            //trace("move");
            _downx = 10000;
            _downy = 10000;
        }
    }
    public function onMouseUp(evt:MouseEvent){ 
        if( (evt.stageX - _downx) < 10 && (evt.stageX - _downx) > -10&& (evt.stageY - _downy) <10 && (evt.stageY - _downy) >-10 ){
            onMouseClicked(evt);
        }
        else{
            _downx = 10000;
            _downy = 10000;
            //trace("move up");
        }
        _isDown = false;
    }

}

