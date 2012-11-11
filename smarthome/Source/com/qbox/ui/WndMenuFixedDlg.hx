package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Qbox;
import com.qbox.logic.Wnd;

class WndMenuFixedDlg extends CommDialog{

    var _x:EmbedTextField;
    var _y:EmbedTextField;
    var _w:EmbedTextField;
    var _h:EmbedTextField;

    var _ax:EmbedTextField;
    var _ay:EmbedTextField;
    var _aw:EmbedTextField;
    var _ah:EmbedTextField;

    var _s:Sprite;

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());
    }

    override function show(){
        if ( _s != null) {
            if (_x!= null)_s.removeChild(_x);
            if (_y!= null)_s.removeChild(_y);
            if (_w!= null)_s.removeChild(_w);
            if (_h!= null)_s.removeChild(_h);
            if (_ax!= null)_s.removeChild(_ax);
            if (_ay!= null)_s.removeChild(_ay);
            if (_aw!= null)_s.removeChild(_aw);
            if (_ah!= null)_s.removeChild(_ah);

            _x= new EmbedTextField();
            _x.scaleX = 3;
            _x.scaleY = 3;
            _x.width = 24;
            _x.height= 16;
            _x.x = 110;
            _x.text = "x";

            _y= new EmbedTextField();
            _y.scaleX = 3;
            _y.scaleY = 3;
            _y.width = 24;
            _y.height= 16;
            _y.x = 190;
            _y.text = "y";

            _w= new EmbedTextField();
            _w.scaleX = 3;
            _w.scaleY = 3;
            _w.width = 24;
            _w.height= 16;
            _w.x = 270;
            _w.text = "w";

            _h= new EmbedTextField();
            _h.scaleX = 3;
            _h.scaleY = 3;
            _h.width = 24;
            _h.height= 16;
            _h.x = 350;
            _h.text = "h";

            _ax= new EmbedTextField();
            _ax.scaleX = 3;
            _ax.scaleY = 3;
            _ax.width = 24;
            _ax.height= 16;
            _ax.x = 430;
            _ax.text = "ax";

            _ay= new EmbedTextField();
            _ay.scaleX = 3;
            _ay.scaleY = 3;
            _ay.width = 24;
            _ay.height= 16;
            _ay.x = 510;
            _ay.text = "ay";

            _aw= new EmbedTextField();
            _aw.scaleX = 3;
            _aw.scaleY = 3;
            _aw.width = 24;
            _aw.height= 16;
            _aw.x = 590;
            _aw.text = "aw";

            _ah= new EmbedTextField();
            _ah.scaleX = 3;
            _ah.scaleY = 3;
            _ah.width = 24;
            _ah.height= 16;
            _ah.x = 670;
            _ah.text = "ah";

            _s.addChild( _x);
            _s.addChild( _ax);
            _s.addChild( _y);
            _s.addChild( _w);
            _s.addChild( _h);
            _s.addChild( _ay);
            _s.addChild( _aw);
            _s.addChild( _ah);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }

        return super.show();
    }

    override function hide(){
        if ( _s != null ) {
            if ( _x!= null){ _s.removeChild(_x);_x= null;}
            if ( _y!= null){ _s.removeChild(_y);_y= null;}
            if ( _w!= null){ _s.removeChild(_w);_w= null;}
            if ( _h!= null){ _s.removeChild(_h);_h= null;}

            if ( _ax!= null){ _s.removeChild(_ax);_ax= null;}
            if ( _ay!= null){ _s.removeChild(_ay);_ay= null;}
            if ( _aw!= null){ _s.removeChild(_aw);_aw= null;}
            if ( _ah!= null){ _s.removeChild(_ah);_ah= null;}
        }
        return super.hide();
    }
    public function createElement():Sprite{

        _s= new Sprite();
        return _s;
    }
}
