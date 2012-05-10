package com.pictionary.ui;

import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;

class DrawingDlg extends CommDialog{

    static var _drawingDialogMgr:DrawingDlgMgr;
    static var _currThisDlg;
    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        _uniqueId = name + id;
        var s= mgr.createElement( name, id);
        super( mgr);
        addChild(s);
    }

    override function onMouseClick( ):Void{
        var dm:CommDialogMgr = _mgr;
        if ( dm.isAnimating() == false){

            if ( _drawingDialogMgr == null ){
                _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
            }
            _drawingDialogMgr.showListDialog();
            hideParent();
            if ( _currThisDlg != this){
                _currThisDlg = this;
                _drawingDialogMgr.eraseDrawing();
                _drawingDialogMgr._returnCallback = showParent;
            }
        }
    }

}

