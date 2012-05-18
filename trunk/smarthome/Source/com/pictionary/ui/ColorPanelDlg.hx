package com.pictionary.ui;

import haxe.Int32;
import nme.geom.Rectangle;
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

    var _tmp:Sprite;
    var _noteColorLevel:Sprite;
    var _bmColorLevel:Bitmap;
    var _bmdColorLevel:BitmapData;
    var _rect:Rectangle;
     
    static var _colorLevelOffset:Int= 10;
    static var _colorLevelWidth:Int= 30;

    var _note:Sprite;

    var _x:Float;
    var _y:Float;
    public function new ( dm:CommDialogMgr ){
        _note = new Sprite();
        _bmd = DataLoader.getInst().bms_.get("color");
        _bm = new Bitmap( _bmd);
        _note.addChild(_bm);

        //var pos= cast ( (nme.Lib.current.stage.stageWidth - (_bmd.width + _colorLevelOffset + _colorLevelWidth))/2);
        //_x = cast (pos, Float);
        _x = 121;
        _y = 150;
        _note.x= _x;
        _note.y= _y;
        _tmp= new Sprite();
        _rect = new Rectangle( 0, 0, _colorLevelWidth, _bmd.height);
        _bmdColorLevel= new BitmapData( cast _rect.width, cast _rect.height);
        //var color:BitmapInt32 = #if neko {rgb:cast(dm, DrawingDlgMgr)._color, a:0xFF} #else cast(dm,DrawingDlgMgr)._color #end ;
        //_bmdColorLevel.fillRect( _rect, color);
        fillColorLevel( cast(dm,DrawingDlgMgr)._color );
        //var _bmColorLevel = new Bitmap( _bmdColorLevel);
        super(dm, _note);
    }

    public function fillColorLevel( incolor:Int):Void{
        var num = 10;
        var scaleheight = _rect.height/num;
        var mask:Int32 = Int32.ofInt(0xFF);
        //_rect.height = _bmd.height/scale;
        var color:Int32 = Int32.ofInt(incolor);
        var c1:Int32 = Int32.div( Int32.shr( color , 16) , Int32.ofInt(num ));
        var c2:Int32 = Int32.div( Int32.and( Int32.shr( color , 8), mask) , Int32.ofInt(num));
        var c3:Int32 = Int32.div( Int32.and( color, mask) , Int32.ofInt(num) );

        var t1:Int32 = Int32.div( Int32.sub( Int32.ofInt(0xFF) ,Int32.shr( color , 16)) , Int32.ofInt(num ));
        var t2:Int32 = Int32.div( Int32.sub( Int32.ofInt(0xff) , Int32.and( Int32.shr( color , 8), mask) ) , Int32.ofInt(num));
        var t3:Int32 = Int32.div( Int32.sub( Int32.ofInt(0xff), Int32.and( color, mask)) , Int32.ofInt(num) );

        for ( i in 0...num){
            var n:Int32 = Int32.ofInt(num -i );
            var color2:Int32 = Int32.or( Int32.or( Int32.shl( Int32.mul(t1, n) , 16) ,  Int32.shl( Int32.mul(t2, n),  8) ) ,  Int32.mul(t3, n) );
            //trace( StringTools.hex( incolor + Int32.toInt(color2)) );
            _tmp.graphics.beginFill( incolor + Int32.toInt(color2));
            _tmp.graphics.drawRect( 0, cast scaleheight * i/2 , cast _rect.width, cast scaleheight/2+1 );
            _tmp.graphics.endFill();
            _bmdColorLevel.draw( _tmp);
        }
        for ( i in 0...num){
            var n:Int32 = Int32.ofInt(i);
            var color1:Int32 = Int32.or( Int32.or( Int32.shl( Int32.mul(c1, n) , 16) ,  Int32.shl( Int32.mul(c2, n),  8) ) ,  Int32.mul(c3, n) );
            //trace( color1);
            //trace( StringTools.hex( incolor - Int32.toInt(color1)) );
            _tmp.graphics.beginFill( incolor - Int32.toInt(color1));
            _tmp.graphics.drawRect( 0, cast (scaleheight*num/2 + scaleheight * i /2), cast _rect.width, cast scaleheight/2+1 );
            _tmp.graphics.endFill();
            //var thiscolor:BitmapInt32 = #if neko {rgb:color, a:0xFF} #else color #end ;
            _bmdColorLevel.draw( _tmp);
        }

        if ( _noteColorLevel == null ){
            _noteColorLevel = new Sprite();
            _noteColorLevel.x = _bmd.width+_colorLevelOffset;
            _noteColorLevel.y = 0;
            _note.addChild(_noteColorLevel);
        }else{
            _noteColorLevel.removeChild(_bmColorLevel);
        }

        _bmColorLevel = new Bitmap( _bmdColorLevel);
        _noteColorLevel.addChild(_bmColorLevel);
    }

    public override function hide(){
        _isDown = false;
        return super.hide();
    }
    var _isDown:Bool;
    var _downx:Float;
    var _downy:Float;
    var _old:Float;

    inline public function getColor( x:Int, y:Int):Int{
        var color:Int;
        if ( x > 0&& y > 0 && x <= _bmd.width && y < _bmd.height ){
            color= _bmd.getPixel( x, y);
            fillColorLevel( color );
        }else{
            x = x - _colorLevelOffset - _bmd.width;
            //trace( x);
            //trace( y);
            if ( x > 0&& y > 0 && x <= _rect.width && y < _bmd.height ){
                color= _bmdColorLevel.getPixel( x, y);
            }else{
                color = -1;
            }
        }
        return color;
    }
    public function onMouseDown(evt:MouseEvent ):Void{
        _isDown = true;
        _downx = evt.stageX;
        _downy = evt.stageY;

        var x = _downx - _x;
        var y = _downy - _y;

        var color:Int = getColor( cast (x, Int), cast (y, Int) );
        if ( color == -1 ) return;

        //trace(color);
        cast ( _mgr, DrawingDlgMgr)._color= color;
        //_bmdColorLevel.fillRect( _rect, #if neko {rgb:color, a:0} #else color #end);
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
