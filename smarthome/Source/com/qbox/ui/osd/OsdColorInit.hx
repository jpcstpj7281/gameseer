package com.qbox.ui.osd;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialogMgr;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class OsdColorInit extends OsdCommDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
#if neko
        TXT= "Color Initialize";
#else
        TXT= "颜色初始化";
#end
    }

    public override function onMouseClick( ):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x50); 
            bs.addByte( 0x80); 
            bs.addByte( 0x65); 
            bs.addByte( 0x7f); 
            bs.addByte( 0x0a); 
            bs.addByte( 0x8a); 

            bs.addByte( 0x36);
            bs.addByte( 0x80);
            bs.addByte( 0x38); 
            bs.addByte( 0x98); 
            bs.addByte( 0xd6); 
            bs.addByte( 0x11); 

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x3d);
            bs.addByte( 0x19);
            bs.addByte( 0xef); 
            bs.addByte( 0xa0); 

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x0f); 
            bs.addByte( 0xc0); 
            bs.addByte( 0xd9);
            bs.addByte( 0x11);

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x2d); 
            bs.addByte( 0x5a); 
            bs.addByte( 0xf2); 
            bs.addByte( 0xec); 

            bs.addByte( 0x40);
            bs.addByte( 0x00);
            bs.addByte( 0x37); 
            bs.addByte( 0xb9); 
            bs.addByte( 0xe5); 
            bs.addByte( 0xd0); 

            bs.addByte( 0x7f); 
            bs.addByte( 0xff); 
            bs.addByte( 0x3e);
            bs.addByte( 0x4a);
            bs.addByte( 0x43); 
            bs.addByte( 0x69); 
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x50); 
            bs.addByte( 0x80); 
            bs.addByte( 0x65); 
            bs.addByte( 0x7f); 
            bs.addByte( 0x0a); 
            bs.addByte( 0x8a); 

            bs.addByte( 0x36);
            bs.addByte( 0x80);
            bs.addByte( 0x38); 
            bs.addByte( 0x98); 
            bs.addByte( 0xd6); 
            bs.addByte( 0x11); 

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x3d);
            bs.addByte( 0x19);
            bs.addByte( 0xef); 
            bs.addByte( 0xa0); 

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x0f); 
            bs.addByte( 0xc0); 
            bs.addByte( 0xd9);
            bs.addByte( 0x11);

            bs.addByte( 0x40); 
            bs.addByte( 0x00); 
            bs.addByte( 0x2d); 
            bs.addByte( 0x5a); 
            bs.addByte( 0xf2); 
            bs.addByte( 0xec); 

            bs.addByte( 0x40);
            bs.addByte( 0x00);
            bs.addByte( 0x37); 
            bs.addByte( 0xb9); 
            bs.addByte( 0xe5); 
            bs.addByte( 0xd0); 

            bs.addByte( 0x7f); 
            bs.addByte( 0xff); 
            bs.addByte( 0x3e);
            bs.addByte( 0x4a);
            bs.addByte( 0x43); 
            bs.addByte( 0x69); 
        }
        _screen.setOsd( Std.string(0x13), Std.string(42), bs.getBytes(), cbFunc);
    }

    function cbFunc(args, ss){
    }
}
