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

import com.qbox.logic.Mode;

class ModeDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _saveBtn:EmbedTextField;
    var _s:Sprite;

    var _mode:Mode;

    public function new ( dm:ListDialogMgr, m:Mode){
        _mode = m;
        super(dm);
        addChild( createElement());

    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        trace("delete");
    }

    public override function onMouseClick():Void{ }

    function onSaveBtnMouseClick( evt:MouseEvent ):Void{
        _mode.save();
    }

    override function show(){
        if ( _s != null) {
            if ( _qboxip != null){
                _s.removeChild(_qboxip);
                //_s.removeChild(_output);
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                _s.removeChild(_saveBtn);
            }


            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "mode:" ;
            _pos.scaleX = 3;
            _pos.scaleY = 3;
            _pos.width = 50;
            _pos.height= 16;

            _deleteBtn= new EmbedTextField();
            _deleteBtn.selectable = false;
            _deleteBtn.text = "Delete";
            _deleteBtn.scaleX = 3;
            _deleteBtn.scaleY = 3;
            _deleteBtn.width = 30;
            _deleteBtn.height= 16;
            _deleteBtn.setBorder(true);
            _deleteBtn.x = nme.Lib.current.stage.stageWidth - 80;
            _deleteBtn.addEventListener( MouseEvent.CLICK, onDeleteBtnMouseClick);

            _saveBtn= new EmbedTextField();
            _saveBtn.setBorder(true);
            _saveBtn.selectable = false;
            _saveBtn.scaleX = 3;
            _saveBtn.scaleY = 3;
            _saveBtn.width = 30;
            _saveBtn.height= 16;
            _saveBtn.x = nme.Lib.current.stage.stageWidth - 180;
            _saveBtn.text = "Save";
            _saveBtn.addEventListener( MouseEvent.CLICK, onSaveBtnMouseClick);

            _s.addChild( _pos);
            //_s.addChild( _output);
            _s.addChild( _deleteBtn);
            _s.addChild( _saveBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _qboxip != null) {
            //_qboxip.removeEventListener(  MouseEvent.CLICK, onQboxMouseClick); 
            //_output.removeEventListener(  MouseEvent.CLICK, onOutputMouseClick); 
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _saveBtn.removeEventListener(  MouseEvent.CLICK, onSaveBtnMouseClick); 
            _s.removeChild(_qboxip);
            _s.removeChild(_pos);
            //_s.removeChild(_output);
            _s.removeChild(_deleteBtn);
            _s.removeChild(_saveBtn);
            _qboxip = null;
            _pos= null;
            _deleteBtn= null;
            _saveBtn= null;
            //_output= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
