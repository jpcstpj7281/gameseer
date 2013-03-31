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

class OsdInit extends OsdCommDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
#if neko
        TXT= "Initialize";
#else
        TXT= "初始化";
#end
    }

    public override function onMouseClick( ):Void{
        trace("test");
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x57); 
            bs.addByte( 0x41); 
            bs.addByte( 0x28); 
            bs.addByte( 0x8c); 
            bs.addByte( 0x03);
            bs.addByte( 0x9b);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x56);
            bs.addByte( 0xd5);
            bs.addByte( 0x29);
            bs.addByte( 0x02);
            bs.addByte( 0x01);
            bs.addByte( 0x93);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x56); 
            bs.addByte( 0x7d); 
            bs.addByte( 0x29); 
            bs.addByte( 0x30); 
            bs.addByte( 0x03); 
            bs.addByte( 0x3f);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc);
    }
    function cbFunc(args, s){
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x01); 
            bs.addByte( 0x00); 
            bs.addByte( 0x15); 
            bs.addByte( 0x87); 
            bs.addByte( 0x61); 
            bs.addByte( 0x1d); 
            bs.addByte( 0x09);
            bs.addByte( 0xe5);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x01);
            bs.addByte( 0x00);
            bs.addByte( 0x12);
            bs.addByte( 0x40);
            bs.addByte( 0x61);
            bs.addByte( 0xbd);
            bs.addByte( 0x03);
            bs.addByte( 0x99);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x01); 
            bs.addByte( 0x00); 
            bs.addByte( 0x18); 
            bs.addByte( 0x51); 
            bs.addByte( 0x61); 
            bs.addByte( 0x26); 
            bs.addByte( 0x09); 
            bs.addByte( 0x55);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc2);
    }
    function cbFunc2(args, s){
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x02); 
            bs.addByte( 0x00); 
            bs.addByte( 0x12); 
            bs.addByte( 0x1c); 
            bs.addByte( 0x02); 
            bs.addByte( 0x1c); 
            bs.addByte( 0x00);
            bs.addByte( 0x5e);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x02);
            bs.addByte( 0x00);
            bs.addByte( 0x12);
            bs.addByte( 0xc0);
            bs.addByte( 0x03);
            bs.addByte( 0x8e);
            bs.addByte( 0x00);
            bs.addByte( 0x35);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x02); 
            bs.addByte( 0x00); 
            bs.addByte( 0x12); 
            bs.addByte( 0x1c); 
            bs.addByte( 0x02); 
            bs.addByte( 0x30); 
            bs.addByte( 0x00); 
            bs.addByte( 0x5c);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc3);
    }
    function cbFunc3(args, s){
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x17); 
            bs.addByte( 0x00); 
            bs.addByte( 0x06); 
            bs.addByte( 0x1b); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00);
            bs.addByte( 0x00);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x17);
            bs.addByte( 0x00);
            bs.addByte( 0x0d);
            bs.addByte( 0x07);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x17); 
            bs.addByte( 0x00); 
            bs.addByte( 0x0a); 
            bs.addByte( 0x8d); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc4);
    }
    function cbFunc4(args, s){
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x17); 
            bs.addByte( 0x01); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x08); 
            bs.addByte( 0x20); 
            bs.addByte( 0x00);
            bs.addByte( 0x00);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x17);
            bs.addByte( 0x01);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x0c);
            bs.addByte( 0x1e);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x17); 
            bs.addByte( 0x01); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x0a); 
            bs.addByte( 0x39); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc5);
    }
    function cbFunc5(args, s){
        var bs:BytesBuffer  = new BytesBuffer();
        if ( _screen._ipv4 =="192.168.67.104"){
            bs.addByte( 0x17); 
            bs.addByte( 0x02); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x0c);
            bs.addByte( 0x7b);
        }
        if ( _screen._ipv4 =="192.168.67.101"){
            bs.addByte( 0x17);
            bs.addByte( 0x02);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x00);
            bs.addByte( 0x09);
            bs.addByte( 0x7d);
        }
        if ( _screen._ipv4 =="192.168.67.102"){
            bs.addByte( 0x17); 
            bs.addByte( 0x02); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x00); 
            bs.addByte( 0x08); 
            bs.addByte( 0x65);
        }
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bs.getBytes(), cbFunc6);
    }
    function cbFunc6(args, s){
        var bf:BytesBuffer  = new BytesBuffer();
        bf.addByte(0x27 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x1 );
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bf.getBytes(), cbFunc7);
    }
    function cbFunc7(args, ss){
        var bf  = new BytesBuffer();
        bf.addByte(0x87 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x1 );
        _screen.setOsdCB( Std.string(0x5e), Std.string(8), bf.getBytes(), cbFunc8);
    }
    function cbFunc8(args, ss){
    }
}
