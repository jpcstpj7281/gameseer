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

class QboxInputsDlg extends CommDialog{
    var _qbox:Qbox;

    public function new ( dm:ListDialogMgr, q:Qbox){
        super(dm);
        _qbox = q;
        addChild(createElement());
    }

    var _g:Sprite;
    var _v:EmbedTextField;
    override function show(){
        if ( _g != null) {
            if ( _v!= null){ _g.removeChild(_v); }

            _v= new EmbedTextField();
            _v.selectable = false;
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = nme.Lib.current.stage.stageWidth /3;
            _v.height= 20;
            _g.addChild( _v);

            var str:String = "";
            if ( Lambda.count( _qbox._inputs) == 0){
                str = null;
            }else{
                for ( i in _qbox._inputs.keys()){
                    str += "   ";
                    str += i;
                }
            }
#if !neko
            _v.text = "输入信号: " + str;
#else
            _v.text = "Input Source: " + str;
#end
            _g.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null ) {
            _g.removeChild(_v);
            _v = null;
        }
        return super.hide();
    }
    public function createElement():Sprite{
        _g = new Sprite();
        _g.height = nme.Lib.current.stage.stageHeight/15;
        return _g;
    }
}
