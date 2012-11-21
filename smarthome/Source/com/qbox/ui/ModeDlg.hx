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

class ModeDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _saveBtn:EmbedTextField;
    var _connBtn:EmbedTextField;
    var _s:Sprite;

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());
    }

    public function onSaveBtnMouseClick( evt:MouseEvent ):Void{
        super.onMouseClick();
    }

    public override function onMouseClick():Void{ }


    function onConnBtnMouseClick( evt:MouseEvent ):Void{
    }

    override function show(){
        if ( _s != null) {
            if ( _qboxip != null){
                _s.removeChild(_qboxip);
                //_s.removeChild(_output);
                _s.removeChild(_pos);
                _s.removeChild(_saveBtn);
                _s.removeChild(_connBtn);
            }


            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "mode:" ;
            _pos.scaleX = 3;
            _pos.scaleY = 3;
            _pos.width = 50;
            _pos.height= 16;

            _saveBtn= new EmbedTextField();
            _saveBtn.selectable = false;
            _saveBtn.text = "OSD";
            _saveBtn.scaleX = 3;
            _saveBtn.scaleY = 3;
            _saveBtn.width = 30;
            _saveBtn.height= 16;
            _saveBtn.setBorder(true);
            _saveBtn.x = nme.Lib.current.stage.stageWidth - 80;
            _saveBtn.addEventListener( MouseEvent.CLICK, onSaveBtnMouseClick);

            _connBtn= new EmbedTextField();
            _connBtn.setBorder(true);
            _connBtn.selectable = false;
            _connBtn.scaleX = 3;
            _connBtn.scaleY = 3;
            _connBtn.width = 30;
            _connBtn.height= 16;
            _connBtn.x = 420;
            _connBtn.text = "test";
            _connBtn.addEventListener( MouseEvent.CLICK, onConnBtnMouseClick);

            _s.addChild( _pos);
            //_s.addChild( _output);
            _s.addChild( _saveBtn);
            _s.addChild( _connBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _qboxip != null) {
            //_qboxip.removeEventListener(  MouseEvent.CLICK, onQboxMouseClick); 
            //_output.removeEventListener(  MouseEvent.CLICK, onOutputMouseClick); 
            _saveBtn.removeEventListener(  MouseEvent.CLICK, onSaveBtnMouseClick); 
            _connBtn.removeEventListener(  MouseEvent.CLICK, onConnBtnMouseClick); 
            _s.removeChild(_qboxip);
            _s.removeChild(_pos);
            //_s.removeChild(_output);
            _s.removeChild(_saveBtn);
            _s.removeChild(_connBtn);
            _qboxip = null;
            _pos= null;
            _saveBtn= null;
            _connBtn= null;
            //_output= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();

        new OsdImgDlg(_listDialogMgr);
        //new OsdFitnessDlg( _listDialogMgr);
        //new OsdSourceDlg(_listDialogMgr);
        //new OsdOptionDlg(_listDialogMgr);
        //new OsdGroupDlg(_listDialogMgr);
        //new OsdSpecialDlg(_listDialogMgr);
        //new OsdSysDlg(_listDialogMgr);

        return _s;
    }
}
