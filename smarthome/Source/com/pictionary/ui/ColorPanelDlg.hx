package com.pictionary.ui;

import nme.display.BitmapInt32;
import nme.display.Sprite;
import nme.display.Bitmap;
import nme.display.BitmapData;
import nme.events.MouseEvent;
import base.data.DataLoader;

import nme.display.DisplayObject;

import haxe.Timer;
import com.pictionary.ui.DrawingDlgMgr;
import base.ui.FixedDlg;
import base.ui.CommDialogMgr;
class ColorPanelDlg extends FixedDlg{

    var _bm:Bitmap;
    var _bmd:BitmapData;

    var _bmdColorLevel:BitmapData;
    public function new ( dm:CommDialogMgr ){
        _bmd = DataLoader.getInst().bms_.get("color");
        _bm = new Bitmap( _bmd);
        _bm.alpha = 1;
        super(dm, _bm);
        x = 100;
        y=  85;
    }

    public override function hide(){
        _isDown = false;
        return super.hide();
    }
    var _isDown:Bool;
    var _downx:Float;
    var _downy:Float;
    var _old:Float;
    public function onMouseDown(evt:MouseEvent ):Void{
        _isDown = true;
        _downx = evt.stageX;
        _downy = evt.stageY;

        var x = _downx - 100;
        var y = _downy - 85;

        var color:Int=   _bmd.getPixel( cast x, cast y);
        cast ( _mgr, DrawingDlgMgr)._color= color;
        //if (_bm.hitTestPoint( _downx, _downy) == false ){
        //_bm.y = _downy - _scrollLPos - _bm.height/2;
        //cast ( _mgr, DrawingDlgMgr)._alpha= ((_scrollLength - _bm.y) /_scrollLength);
        //}
        //_old = _bm.y ;
        //trace("down");
    }
    public function onMouseMove(evt:MouseEvent ):Void{
        if ( _isDown){


            //_bm.y = evt.stageY - _downy +_old;
            //if ( _bm.y< 0 ){
            //_bm.y= 0;
            //_isDown = false;
            //}else if ( _bm.y > _scrollLength) {
            //_bm.y= _scrollLength;
            //_isDown = false;
            //}
            //cast ( _mgr, DrawingDlgMgr)._alpha= ((_scrollLength - _bm.y) /_scrollLength);
        }
        //trace("move");
    }
    public function onMouseUp(evt:MouseEvent ):Void{
        _isDown = false;
        //trace("up");
    }
}
