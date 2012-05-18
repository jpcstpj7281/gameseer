
package com.blueseer.ui;

import com.blueseer.cmd.Command;
import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
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

class TypedCmdDialog extends ListDialog{

    public function new ( cmdDlgMgr:ListDialogMgr ){
        var str:String = "分类";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = cmdDlgMgr.createElement( str, id);
        super(  cmdDlgMgr );
        addChild(s);
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
        var arr:Array<Command> = CommandMgr.getInst().getTyped();
        for( i in arr){
            new SelCmdDlg( _listDialogMgr, i._commandName, i._commandID);
        }
    }



}

