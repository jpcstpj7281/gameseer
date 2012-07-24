package com.qbox.ui;

import com.qbox.logic.Channel;
import com.qbox.logic.QboxMgr;

import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.ListDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;

class EditChannelDlg extends ListDialog{

    var _editBtn:EmbedTextField;
    var _channel:Channel;

    public function new ( cmdDlgMgr:ListDialogMgr, c:Channel ){
        var s:Sprite = createElement( );
        super(  cmdDlgMgr );
        addChild(s);
        _channel = c;
        createDlgs();
    }

    public override function clear():Void{
        if ( _listDialogMgr != null) _listDialogMgr.clear();
        _listDialogMgr =null;
    }

    public function resetDlgs(){
        _listDialogMgr.clear();
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = showParent;
        createDlgs();
    }

    public override function onMouseClick( ):Void{
        var dm:CommDialogMgr = cast( _mgr);
        if ( dm.isAnimating() == false){
            resetDlgs();
            super.onMouseClick();
        }
    }

    public function createDlgs(){
        _channel.addNode( QboxMgr.getInst()._qboxes[0], "in0");
            trace("test");
        for ( i in _channel._nodes){
            trace("test");
        }
    }


    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        _editBtn= new EmbedTextField();
        _editBtn.selectable = false;
        _editBtn.text = "Edit";
        _editBtn.scaleX = 3;
        _editBtn.scaleY = 3;
        _editBtn.width = 20;
        _editBtn.height= 18;
        _editBtn.setBorder(true);
        _editBtn.x = nme.Lib.current.stage.stageWidth - 80;

        s.addChild( _editBtn);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }

}

