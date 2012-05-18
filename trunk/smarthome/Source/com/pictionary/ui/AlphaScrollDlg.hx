package com.pictionary.ui;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.display.DisplayObject;

import haxe.Timer;
import com.pictionary.ui.DrawingDlgMgr;
import base.ui.FixedDlg;
import base.ui.CommDialogMgr;
class AlphaScrollDlg extends FixedDlg{
    static var _scrollLength:Int  = 300;
    static var _scrollLPos:Int  = 85;
    var _note:Sprite;
    var _bm:Bitmap;
    public function new ( dm:CommDialogMgr ){
        _note = new Sprite();
        var bmd = DataLoader.getInst().bms_.get("line");
        _bm = new Bitmap( bmd);
        _bm.alpha = 0.5;
        _note.addChild(_bm);
        _note.graphics.lineStyle( 5, 0x555555, 1);
        var lx = bmd.width/2;
        var ly = bmd.height/2;
        _note.graphics.moveTo( lx, ly);
        _note.graphics.lineTo( lx, ly+_scrollLength);

        _note.x= nme.Lib.current.stage.stageWidth - bmd.width;
        _note.y=  85;
        super(dm, _note);
    }

    //public override function onMouseClick( ):Void{
    //if ( _mgr.isAnimating() ) return;
    //if ( Std.is( _mgr, DrawingDlgMgr)){
    //}
    //}

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
        if (_bm.hitTestPoint( _downx, _downy) == false ){
            _bm.y = _downy - _scrollLPos - _bm.height/2;
            cast ( _mgr, DrawingDlgMgr)._alpha= ((_scrollLength - _bm.y) /_scrollLength);
        }
        _old = _bm.y ;
        //trace("down");
    }
    public function onMouseMove(evt:MouseEvent ):Void{
        if ( _isDown){
            _bm.y = evt.stageY - _downy +_old;
            if ( _bm.y< 0 ){
                _bm.y= 0;
                _isDown = false;
            }else if ( _bm.y > _scrollLength) {
                _bm.y= _scrollLength;
                _isDown = false;
            }
            cast ( _mgr, DrawingDlgMgr)._alpha= ((_scrollLength - _bm.y) /_scrollLength);
        }
        //trace("move");
    }
    public function onMouseUp(evt:MouseEvent ):Void{
        _isDown = false;
        //trace("up");
    }
}
