package com.pictionary.ui;

import haxe.io.Bytes;
import com.blueseer.ui.UIMgr;
import base.network.SMConnection;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

import base.network.ClientConn;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.ListDialog;

class HostDialog extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    var _drawingDialogMgr:DrawingDlgMgr;
    public function new ( cmdDlgMgr:ListDialogMgr ){
        _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
        _drawingDialogMgr._returnCallback = showParent;

        var str:String = "主机";
        var id:Int = 0;
        var s:Sprite = cmdDlgMgr.createElement( str, id);
        var dd:DialogData = cmdDlgMgr.createListDialogData( s, str+id );
        super( dd);
        dialogManager = cmdDlgMgr;
        cmdDlgMgr.addDialog(this );
        this.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        this.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        this.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);

    }

    public override function clear():Void{
        super.clear();
        if ( _drawingDialogMgr!= null) _drawingDialogMgr.clear();
        _drawingDialogMgr=null;
        NetworkMgr.getInst().removeServerHandler( serverHandler);
    }

    public function resetDlgs(){
        _drawingDialogMgr.clear();
        _drawingDialogMgr = new DrawingDlgMgr(nme.Lib.current);
        _drawingDialogMgr._returnCallback = showParent;
        NetworkMgr.getInst().addServerHandler( serverHandler);
    }

    public function cbDispatch( datas:Array<Bytes>):Void{ NetworkMgr.getInst().noreplyBroadcast( datas); }

    public override function onMouseClick( evt:MouseEvent):Void{
        var dm:CommDialogMgr = cast( dialogManager);
        if ( dm.isAnimating() == false){
            resetDlgs();
            super.onMouseClick(evt);
            NetworkMgr.getInst().runAsServer();
            NetworkMgr.getInst().addServerHandler( serverHandler);
            _drawingDialogMgr._dispatchCallback = cbDispatch;
            _drawingDialogMgr.showListDialog();
            hideParent();
        }
    }


    public function serverHandler( datas:Array<Bytes>, conn:ClientConn):Bool{
        _drawingDialogMgr.draw(datas);
        return true;
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

