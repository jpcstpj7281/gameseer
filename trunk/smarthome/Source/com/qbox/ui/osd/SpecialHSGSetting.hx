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
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;
import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class SpecialHSGSetting extends OsdListDlg{

    var _screen:Screen;

    var _redGain:Int;
    var _redSat:Int;
    var _redHue:Int;
    var _greenGain:Int;
    var _greenSat:Int;
    var _greenHue:Int;
    var _blueGain:Int;
    var _blueSat:Int;
    var _blueHue:Int;
    var _cyanGain:Int;
    var _cyanSat:Int;
    var _cyanHue:Int;
    var _magentaGain:Int;
    var _magentaSat:Int;
    var _magentaHue:Int;
    var _yellowGain:Int;
    var _yellowSat:Int;
    var _yellowHue:Int;
    var _whiteRed:Int;
    var _whiteGreen:Int;
    var _whiteBlue:Int;
        
    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());
        _redGain= 0x0000;
        _redSat = 0x0000;
        _redHue = 0;
        _greenGain= 0x0000;
        _greenSat = 0x0000;
        _greenHue = 0;
        _blueGain= 0x0000;
        _blueSat = 0x0000;
        _blueHue = 0;
        _cyanGain= 0x0000;
        _cyanSat = 0x0000;
        _cyanHue = 0;
        _magentaGain= 0x0000;
        _magentaSat = 0x0000;
        _magentaHue = 0;
        _yellowGain= 0x0000;
        _yellowSat = 0x0000;
        _yellowHue = 0;
        _whiteRed= 0x0000;
        _whiteGreen= 0x0000;
        _whiteBlue= 0x0000;

        _screen = s;
        new HSGRed(_listDialogMgr, s, this);
        new HSGGreen(_listDialogMgr, s, this);
        new HSGBlue(_listDialogMgr, s, this);
        new HSGCyan(_listDialogMgr, s, this);
        new HSGMagenta(_listDialogMgr, s, this);
        new HSGYellow(_listDialogMgr, s, this);
        new HSGWhite(_listDialogMgr, s, this);
#if neko
        TXT="HSG Setting";
#else
        TXT="HSG设置";
#end
    }

    function addB( bf:BytesBuffer, val:Int){
        if( val < 0){
            bf.addByte( (val >>8) | 0x80);
            bf.addByte( val );
        }else{
            bf.addByte( val >>8 );
            bf.addByte( val );
        }
    }

    function dispatch(){
        var bf:BytesBuffer  = new BytesBuffer();
        addB( bf, _redGain);
        addB( bf, _redSat);
        addB( bf, _redHue);
        addB( bf, _greenGain);
        addB( bf, _greenSat);
        addB( bf, _greenHue);
        addB( bf, _blueGain);
        addB( bf, _blueSat);
        addB( bf, _blueHue);
        addB( bf, _magentaGain);
        addB( bf, _magentaSat);
        addB( bf, _magentaHue);
        addB( bf, _cyanGain);
        addB( bf, _cyanSat);
        addB( bf, _cyanHue);
        addB( bf, _yellowGain);
        addB( bf, _yellowSat);
        addB( bf, _yellowHue);
        addB( bf, _whiteRed);
        addB( bf, _whiteGreen);
        addB( bf, _whiteBlue);
        _screen.setOsd( Std.string(0x13), Std.string(42), bf.getBytes(), cbFunc);
    }

    function cbFunc(args,ss){
    }

    public function setRedGain( value:Int){ _redGain =value; dispatch(); }
    public function setRedSat( value:Int){ _redSat=value; dispatch();}
    public function setRedHue( value:Int){ _redHue=value; dispatch();}
    public function setGreenGain( value:Int){ _greenGain=value; dispatch();}
    public function setGreenSat( value:Int){ _greenSat=value; dispatch();}
    public function setGreenHue( value:Int){ _greenHue=value; dispatch();}
    public function setBlueGain( value:Int){ _blueGain=value; dispatch();}
    public function setBlueSat( value:Int){ _blueSat=value; dispatch();}
    public function setBlueHue( value:Int){ _blueHue=value; dispatch();}
    public function setCyanGain( value:Int){ _cyanGain=value; dispatch();}
    public function setCyanSat( value:Int){ _cyanSat=value; dispatch();}
    public function setCyanHue( value:Int){ _cyanHue=value; dispatch();}
    public function setMagentaGain( value:Int){ _magentaGain=value; dispatch();}
    public function setMagentaSat( value:Int){ _magentaSat=value; dispatch();}
    public function setMagentaHue( value:Int){ _magentaHue=value; dispatch();}
    public function setYellowGain( value:Int){ _yellowGain=value; dispatch();}
    public function setYellowSat( value:Int){ _yellowSat=value; dispatch();}
    public function setYellowHue( value:Int){ _yellowHue=value; dispatch();}
    public function setWhiteRed( value:Int){ _whiteRed=value; dispatch();}
    public function setWhiteGreen( value:Int){ _whiteGreen=value; dispatch();}
    public function setWhiteBlue( value:Int){ _whiteBlue=value; dispatch();}

}
