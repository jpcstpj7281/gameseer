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
    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
        _drawingDialogMgr._returnCallback = showParent;
        _uniqueId = name + id;
        var s:Sprite = mgr.createElement( name, id);
        super( mgr);
        addChild(s);
        _id = id;
    }

    override function onMouseClick( ):Void{
        var dm:CommDialogMgr = _mgr;
        if ( dm.isAnimating() == false){
            _drawingDialogMgr.showListDialog();
            hideParent();
        }
    }

}

