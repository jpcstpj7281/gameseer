package com.blueseer.ui;

import base.ui.Native;
import com.blueseer.ui.UIMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.ui.EmbedTextField;
//import nme.display.Bitmap;
//import nme.display.BitmapData;
//import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;

class NativeInputCmdDialog extends CommDialog{
    var _usrInput:EmbedTextField ;
    var _pswInput:EmbedTextField ;
    var _hint:EmbedTextField ;
    var _OK:EmbedTextField ;
    var _Cancel:EmbedTextField ;
    var _pswShow:EmbedTextField ;

    public function new ( mgr:ListDialogMgr ){
        var str:String = "中文输入";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);
    }

    override function onMouseClick(){
        //trace("NativeInputListDialog1");
        if ( cast(_mgr,ListDialogMgr).isAnimating()) return;
        //trace("NativeInputListDialog2");
        Native.nativeInput();
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, onLoop);
        //trace("NativeInputListDialog4");
    }
    public function onLoop(evt:Event){
        var res:String = Native.inputData();
        //trace("NativeInputListDialog5");
        if ( res != null ){
            //trace("NativeInputListDialog6");
            trace(res );
            //var bmd:BitmapData = Native.getBitmap();
            //trace(bmd);
            //var bm = DataLoader.getInst().getBitmapData( res);
            // 
            //var _bms = new Sprite();
            //var bm:Bitmap = new Bitmap( bmd);
            //_bms.addChild( bm);
            //_bms.x = nme.Lib.current.stage.stageWidth - 100;
            //_bms.y= nme.Lib.current.stage.stageHeight - 100;
            //nme.Lib.current.addChild(_bms);

        }
    }
}

