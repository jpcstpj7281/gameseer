package com.pictionary.ui;

import com.blueseer.cmd.Command;
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
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;

class DrawingDlg extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;

    public var _id:Int;

    var _drawingDialogMgr:DrawingDlgMgr;
    public function new ( cmdDlgMgr:ListDialogMgr, name:String, id:Int ){
        _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
        _drawingDialogMgr._returnCallback = showParent;
        var s:Sprite = cmdDlgMgr.createElement( name, id);
        var dd:DialogData = cmdDlgMgr.createListDialogData( s, name+id );
        super( dd);
        dialogManager = cmdDlgMgr;
        //trace(cmdDlgMgr);
        cmdDlgMgr.addDialog(this );
        _id = id;

        this.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        this.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        this.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);

    }

    public override function onMouseClick( evt:MouseEvent):Void{
        var dm:CommDialogMgr = cast( dialogManager);
        if ( dm.isAnimating() == false){
            _drawingDialogMgr.showListDialog();
            hideParent();
        }
    }
    public function onMouseDown(evt:MouseEvent){ 
        _downx = evt.stageX;
        _downy = evt.stageY;
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
            onMouseClick(evt);
        }
        else{
            _downx = 10000;
            _downy = 10000;
            //trace("move up");
        }
    }

}

