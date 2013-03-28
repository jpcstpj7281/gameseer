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
    var _whiteGain:Int;
    var _whiteSat:Int;
    var _whiteHue:Int;
        
    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        _screen = s;
        new HSGRedGain(_listDialogMgr, s);
        new HSGRedSaturation(_listDialogMgr, s);
        new HSGRedHue(_listDialogMgr, s);
        new HSGGreenGain(_listDialogMgr, s);
        new HSGGreenSaturation(_listDialogMgr, s);
        new HSGGreenHue(_listDialogMgr, s);
#if neko
        TXT="HSG Setting";
#else
        TXT="HSG设置";
#end
    }

    function dispatch(){
        var bs:BytesBuffer  = new BytesBuffer();
        bs.addByte(_redGain>>8);
        bs.addByte(_redGain);
        bs.addByte(_redSat>>8);
        bs.addByte(_redSat);
        bs.addByte(_redHue>>8);
        bs.addByte(_redHue);
        _screen.setOsd( Std.string(0x13), Std.string(42), bs.getBytes(), cbFunc);
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
    public function setWhiteGain( value:Int){ _whiteGain=value; dispatch();}
    public function setWhiteSat( value:Int){ _whiteSat=value; dispatch();}
    public function setWhiteHue( value:Int){ _whiteHue=value; dispatch();}

}
