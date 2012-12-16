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
import com.qbox.logic.ModeMgr;

class ModeDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _loadBtn:EmbedTextField;
    var _saveBtn:EmbedTextField;
    var _s:Sprite;

    var _mode:Mode;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Mode, cbdelete:Void->Void){
        _mode = m;
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;
    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        ModeMgr.getInst().deleteMode(_mode);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }

    function onSaveBtnMouseClick( evt:MouseEvent ):Void{ _mode.save(); }
    function onLoadBtnMouseClick( evt:MouseEvent ):Void{
        _mode.load(cbDone);
    }

    function cbDone(){
        trace("finish loading mode");
    }

    override function show(){
        if ( _s != null) {
            if ( _saveBtn != null){
                //_s.removeChild(_output);
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                _s.removeChild(_saveBtn);
                _s.removeChild(_loadBtn);
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

            _loadBtn= new EmbedTextField();
            _loadBtn.setBorder(true);
            _loadBtn.selectable = false;
            _loadBtn.scaleX = 3;
            _loadBtn.scaleY = 3;
            _loadBtn.width = 30;
            _loadBtn.height= 16;
            _loadBtn.x = nme.Lib.current.stage.stageWidth - 280;
            _loadBtn.text = "Load";
            _loadBtn.addEventListener( MouseEvent.CLICK, onLoadBtnMouseClick);

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.addChild( _saveBtn);
            _s.addChild( _loadBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _saveBtn!= null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _saveBtn.removeEventListener(  MouseEvent.CLICK, onSaveBtnMouseClick); 
            _loadBtn.removeEventListener(  MouseEvent.CLICK, onLoadBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _s.removeChild(_saveBtn);
            _s.removeChild(_loadBtn);
            _pos= null;
            _deleteBtn= null;
            _loadBtn= null;
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
