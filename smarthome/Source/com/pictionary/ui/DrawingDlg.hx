package com.pictionary.ui;

import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;

class DrawingDlg extends CommDialog{

    var _drawingDialogMgr:DrawingDlgMgr;
    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
        _drawingDialogMgr._returnCallback = showParent;
        _uniqueId = name + id;
        var s= mgr.createElement( name, id);
        super( mgr);
        addChild(s);
    }

    override function onMouseClick( ):Void{
        var dm:CommDialogMgr = _mgr;
        if ( dm.isAnimating() == false){
            _drawingDialogMgr.showListDialog();
            hideParent();
        }
    }

}

