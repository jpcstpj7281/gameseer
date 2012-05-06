package com.pictionary.ui;

import base.ui.ConnDialog;
import haxe.io.Bytes;
import com.blueseer.ui.UIMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.network.SMConnection;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.ListDialog;

class ConnDrawingDlg extends ConnDialog{

    var _drawingDialogMgr:DrawingDlgMgr;
    public function new ( mgr:ListDialogMgr ){
        super( mgr );
    }

    public override function clear():Void{
        if ( _drawingDialogMgr!= null) _drawingDialogMgr.clear();
        _drawingDialogMgr=null;
    }

    public function resetDlgs(){
        clear();
        if ( NetworkMgr.getInst().getConn() != null && NetworkMgr.getInst().getConn().isConected() ){
            _drawingDialogMgr= new DrawingDlgMgr(nme.Lib.current);
            _drawingDialogMgr._returnCallback = showParent;
            _drawingDialogMgr._dispatchCallback = cbDispatch;

            var conn:SMConnection = cast NetworkMgr.getInst().getConn();
            conn.startListening( 0, connHandler, 2);
        }else{
        }
    }

    public function cbDispatch( datas:Array<Bytes>):Void{
            trace("sent data1");
        if ( NetworkMgr.getInst().getConn() != null && NetworkMgr.getInst().getConn().isConected() ){
            var conn:SMConnection = cast NetworkMgr.getInst().getConn();
            conn.clearData();
            conn.setMsg( 0, 2);
            conn.addBytesArray( datas);
            conn.sendData();
            trace("sent data2");
        }
    }

    override function onMouseClick( ):Void{
        var dm:CommDialogMgr = _mgr;
        if ( dm.isAnimating() == false){
            if ( NetworkMgr.getInst().getConn() != null && NetworkMgr.getInst().getConn().isConected() ){
                if ( _drawingDialogMgr== null ){
                    resetDlgs();
                }
                _drawingDialogMgr.showListDialog();
            }else{
                resetDlgs();
                super.onMouseClick();
            }
        }
    }

    public function connHandler( datas:Array<Bytes>):Bool{
        _drawingDialogMgr.draw(datas);
        return true;
    }
}

