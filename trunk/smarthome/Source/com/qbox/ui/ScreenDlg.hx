package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;
import base.ui.ListDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;
import com.qbox.logic.ScreenMgr;

import com.qbox.ui.osd.OsdFitnessDlg;
import com.qbox.ui.osd.OsdGroupDlg;
import com.qbox.ui.osd.OsdImgDlg;
import com.qbox.ui.osd.OsdOptionDlg;
import com.qbox.ui.osd.OsdSourceDlg;
import com.qbox.ui.osd.OsdSpecialDlg;
import com.qbox.ui.osd.OsdSysDlg;
import com.qbox.ui.osd.OsdProjModeDlg;
import haxe.io.BytesBuffer;

class ScreenDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;
    var _screen:Screen;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _osdBtn:EmbedTextField;
    var _connBtn:EmbedTextField;
    var _s:Sprite;

    public function new ( dm:ListDialogMgr, c:Screen){
        super(dm);
        _screen = c;
        addChild( createElement());
    }

    public function onOsdBtnMouseClick( evt:MouseEvent ):Void{
        super.onMouseClick();
    }

    public override function onMouseClick():Void{ }

    function cbConnectInit():Void{}
    function cbFunc1(args, ss){}
    function cbFunc(args, ss){
        var bf  = new BytesBuffer();
        bf.addByte(0x87 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x0 );
        bf.addByte(0x1 );
        _screen.setOsd( Std.string(0x5e), Std.string(8), bf.getBytes(), cbFunc1);
    }

    function onConnBtnMouseClick( evt:MouseEvent ):Void{
#if neko
        if ( _connBtn.text == "disc"){
#else
            if ( _connBtn.text == "断开"){
#end
                _screen.close();
#if neko
                _connBtn.text = "conn";
#else
                _connBtn.text = "连接";
#end
                trace("disconnect");
            }else{
                _screen._ipv4 = _qboxip.text;
                _screen.connect();
                if (_screen._isFailed == false && _screen.isConected() ){
                    trace("connected");
                    _screen.connectedInit(cbConnectInit);
                    var bf:BytesBuffer  = new BytesBuffer();
                    bf.addByte(0x27 );
                    bf.addByte(0x0 );
                    bf.addByte(0x0 );
                    bf.addByte(0x0 );
                    bf.addByte(0x0 );
                    bf.addByte(0x0 );
                    bf.addByte(0x0 );
                    bf.addByte(0x1 );
                    _screen.setOsd( Std.string(0x5e), Std.string(8), bf.getBytes(), cbFunc);
#if neko
                    _connBtn.text = "disc";
#else
                    _connBtn.text = "断开";
#end
                }else{
                    trace("connect failed");
                }
            }
        }

        override function show(){
            if ( _s != null) {
                if ( _qboxip != null){
                    _s.removeChild(_qboxip);
                    //_s.removeChild(_output);
                    _s.removeChild(_pos);
                    _s.removeChild(_osdBtn);
                    _s.removeChild(_connBtn);
                }

                /*
                   _output= new EmbedTextField();
                   _output.selectable = false;
                   _output.text = _screen._output;
                   _output.scaleX = 3;
                   _output.scaleY = 3;
                   _output.width = 50;
                   _output.height= 20;
                   _output.x = 300;
                   _output.addEventListener( MouseEvent.CLICK, onOutputMouseClick);
                 */


                _pos= new EmbedTextField();
                _pos.selectable = false;
                _pos.text = "screen:" + _screen._col+"|"+_screen._row;
                _pos.scaleX = 3;
                _pos.scaleY = 3;
                _pos.width = 50;
                _pos.height= 16;

                _osdBtn= new EmbedTextField();
                _osdBtn.selectable = false;
                _osdBtn.text = "OSD";
                _osdBtn.scaleX = 3;
                _osdBtn.scaleY = 3;
                _osdBtn.width = 30;
                _osdBtn.height= 16;
                _osdBtn.setBorder(true);
                _osdBtn.x = nme.Lib.current.stage.stageWidth - 80;
                _osdBtn.addEventListener( MouseEvent.CLICK, onOsdBtnMouseClick);

                _connBtn= new EmbedTextField();
                _connBtn.setBorder(true);
                _connBtn.selectable = false;
                if ( _screen._isFailed || !_screen.isConected() ){
#if neko
                    _connBtn.text = "conn";
#else
                    _connBtn.text = "连接";
#end
                }else{
#if neko
                    _connBtn.text = "disc";
#else
                    _connBtn.text = "断开";
#end
                }
                _connBtn.scaleX = 3;
                _connBtn.scaleY = 3;
                _connBtn.width = 30;
                _connBtn.height= 16;
                _connBtn.x = 420;
                _connBtn.addEventListener( MouseEvent.CLICK, onConnBtnMouseClick);

                _qboxip= new EmbedTextField();
                _qboxip.selectable = false;
                if ( _screen._ipv4 == "") {
                    _qboxip.text = "192.168.67.101";
                }else{
                    _qboxip.text = _screen._ipv4;
                }
                _qboxip.type = INPUT;
                _qboxip.scaleX = 3;
                _qboxip.scaleY = 3;
                _qboxip.width = 74;
                _qboxip.height= 16;
                _qboxip.setBorder(true);
                _qboxip.x = 150;
                //_qboxip.addEventListener( MouseEvent.CLICK, onQboxMouseClick);

                _s.addChild( _pos);
                _s.addChild( _qboxip);
                //_s.addChild( _output);
                _s.addChild( _osdBtn);
                _s.addChild( _connBtn);
                _s.height = nme.Lib.current.stage.stageHeight/15;
            }
            return super.show();
        }
        override function hide(){
            if ( _s != null && _qboxip != null) {
                //_qboxip.removeEventListener(  MouseEvent.CLICK, onQboxMouseClick); 
                //_output.removeEventListener(  MouseEvent.CLICK, onOutputMouseClick); 
                _osdBtn.removeEventListener(  MouseEvent.CLICK, onOsdBtnMouseClick); 
                _connBtn.removeEventListener(  MouseEvent.CLICK, onConnBtnMouseClick); 
                _s.removeChild(_qboxip);
                _s.removeChild(_pos);
                //_s.removeChild(_output);
                _s.removeChild(_osdBtn);
                _s.removeChild(_connBtn);
                _qboxip = null;
                _pos= null;
                _osdBtn= null;
                _connBtn= null;
                //_output= null;
            }
            return super.hide();
        }

        public function createElement():Sprite{
            _s= new Sprite();

            new OsdImgDlg(_listDialogMgr, _screen);
            new OsdFitnessDlg( _listDialogMgr, _screen);
            //new OsdSourceDlg(_listDialogMgr, _screen);
            //new OsdOptionDlg(_listDialogMgr, _screen);
            //new OsdGroupDlg(_listDialogMgr, _screen);
            new OsdSpecialDlg(_listDialogMgr, _screen);
            //new OsdSysDlg(_listDialogMgr, _screen);

            return _s;
        }
    }
