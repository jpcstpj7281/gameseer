package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.CommDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;

import haxe.io.Eof;
import haxe.io.Bytes;
#if neko
import neko.FileSystem;
import neko.io.File;
import neko.io.FileInput;
#else
import cpp.FileSystem;
import cpp.io.File;
import cpp.io.FileInput;
#end
class QboxUpdateDlg extends CommDialog{
    var _qbox:Qbox;

    var _update:EmbedTextField;
    var _less:Sprite;
    var _more:Sprite;
    var _switch:EmbedTextField;
    var _currSwitch:Int;
    var _isUpdating:Bool;
    var _currInput:FileInput;

    static var POSX:Int = 300;
    static var WIDTH:Int = 300;
    public static var DIR:String="assets";

    var _dirs:Array<String>;
    public function new ( dm:ListDialogMgr, q:Qbox, dirs:Array<String>){
        super(dm);
        _qbox = q;
        addChild(createElement());
        _dirs = dirs;
        _currSwitch = 0;
    }

    function onUpdateBtnMouseClick(evt:MouseEvent){
        if ( _isUpdating) return;
        var fname = DIR+"/"+_dirs[_currSwitch];
        _currInput = File.read(fname, true );

        _qbox.clearData();
        _qbox.startListening( 2, cbUpdateFinished, 15);
        _qbox.setMsg( 1, 15);
        _qbox.addKeyVal("name", Bytes.ofString("test.txt"));
        _qbox.addKeyVal("eof", Bytes.ofString("0"));
        _qbox.addKeyVal("start", Bytes.ofString("0"));
        try{
            var bs:Bytes =Bytes.alloc( 500);
            var len = _currInput.readBytes( bs, 0, 500);
            _qbox.addKeyVal("binary", bs);
            _qbox.addKeyVal("end", Bytes.ofString(""+len));
            _qbox.sendData();
        }catch( ex:Eof){}
        _currInput.close();
        //var fileContent = neko.io.File.getContent(fname);
        //neko.Lib.println("file content:\n" + fileContent);
    }

    function cbUpdateFinished(args:Dynamic){
        trace(args);

    }

    function onLessMouseClick(evt:MouseEvent){
        --_currSwitch;
        if ( _currSwitch <0 ) _currSwitch = _dirs.length-1;
        _switch.text = _dirs[_currSwitch];
    }
    function onMoreMouseClick(evt:MouseEvent){
        ++_currSwitch;
        if ( _currSwitch >= _dirs.length ) _currSwitch = 0;
        _switch.text = _dirs[_currSwitch];
    }

    var _g:Sprite;
    var _v:EmbedTextField;
    override function show(){
        if ( _g != null) {
            if ( _v!= null){ _g.removeChild(_v); }
            if ( _update!= null){ _g.removeChild(_update); }
            if ( _less!= null){ _g.removeChild(_less); }
            if ( _more!= null){ _g.removeChild(_more); }
            if ( _switch!= null){ _g.removeChild(_switch); }

            _v= new EmbedTextField();
            _v.selectable = false;
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = nme.Lib.current.stage.stageWidth /3;
            _v.height= 20;
            _g.addChild( _v);

#if !neko
            _v.text = "Qbox: " + _qbox._ipv4;
#else
            _v.text = "Qbox: " + _qbox._ipv4;
#end

            _switch= new EmbedTextField();
            _switch.text= _dirs[_currSwitch];
            _switch.selectable = false;
            _switch.scaleX = 3;
            _switch.scaleY = 3;
            _switch.width = nme.Lib.current.stage.stageWidth /3;
            _switch.height= 20;
            _switch.x = POSX +50 ;
            _g.addChild( _switch);

            _g.height = nme.Lib.current.stage.stageHeight/15;

            _less = new Sprite();
            _less.graphics.beginFill(0x888888);
            _less.graphics.moveTo( POSX -10, 10 );
            _less.graphics.lineTo( POSX -25, 25 );
            _less.graphics.lineTo( POSX -10, 40);
            _less.graphics.lineTo( POSX -10, 10);
            _less.graphics.endFill();
            _less.addEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);
            _g.addChild(_less);

            _more= new Sprite();
            _more.graphics.beginFill(0x888888);
            _more.graphics.moveTo( POSX+WIDTH +10, 10 );
            _more.graphics.lineTo( POSX+WIDTH +25, 25 );
            _more.graphics.lineTo( POSX+WIDTH +10, 40);
            _more.graphics.lineTo( POSX+WIDTH +10, 10);
            _more.graphics.endFill();
            _more.addEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick);
            _g.addChild(_more);

            _update= new EmbedTextField();
            _update.setBorder(true);
            _update.selectable = false;
            _update.text = "update";
            _update.scaleX = 3;
            _update.scaleY = 3;
            _update.width = 40;
            _update.height= 16;
            _update.x = 690;
            _update.addEventListener( MouseEvent.CLICK, onUpdateBtnMouseClick);
            _g.addChild(_update);
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null ) {
            _g.removeChild(_v);
            _g.removeChild(_update);
            _g.removeChild(_less);
            _g.removeChild(_more);
            _g.removeChild(_switch);
            _v = null;
            _update =null;
            _less = null;
            _more= null;
            _switch= null;
        }
        return super.hide();
    }
    public function createElement():Sprite{
        _g = new Sprite();
        _g.height = nme.Lib.current.stage.stageHeight/15;
        return _g;
    }
}
