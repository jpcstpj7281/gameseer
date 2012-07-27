package com.qbox.ui;

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

class WndGraphicDlg extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _isDown:Bool;


    public var _wnd:Sprite;
    public function new ( mgr:CommDialogMgr ){
        super( mgr);

        _wnd = new Sprite();
        addChild(_wnd);
    }

    public function resizeWnd( w:Int, h:Int){
        //removeChild(_wnd);
        //_wnd = new Sprite();
        _wnd.graphics.clear();
        _wnd.graphics.lineStyle( 1, 0x121212, 1);
        _wnd.graphics.beginFill(0xFFFFFF, 1);
        _wnd.graphics.drawRect( 0,0, w, h);
        _wnd.graphics.beginFill(0x808080, 1);
        _wnd.graphics.drawRect( w-10,h-10, 10, 10);
        _wnd.graphics.beginFill(0x808080, 1);
        _wnd.graphics.drawRect( w-10,0, 10, 10);
        //addChild(_wnd);

    }
    public function openWnd( x:Int, y:Int, w:Int, h:Int){
        _wnd.graphics.lineStyle( 1, 0x121212, 1);
        _wnd.graphics.beginFill(0xFFFFFF, 1);
        _wnd.graphics.drawRect( 0,0, w, h);
        _wnd.graphics.beginFill(0x808080, 1);
        _wnd.graphics.drawRect( w-10,h-10, 10, 10);
        _wnd.graphics.beginFill(0x808080, 1);
        _wnd.graphics.drawRect( w-10,0, 10, 10);
        this.x = x;
        this.y = y;
    }
    public function closeWnd( ){
        _wnd.graphics.clear();
        removeChild(_wnd);
        _wnd = null;
    }

}

