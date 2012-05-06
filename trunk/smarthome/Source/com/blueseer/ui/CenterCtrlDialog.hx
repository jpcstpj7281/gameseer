package com.blueseer.ui;

import nme.display.Sprite;

import base.ui.ListDialog;
import base.ui.ListDialogMgr;
import base.ui.ConnDialog;
import base.ui.CommDialog;

class CenterCtrlDialog extends ListDialog{

    public function new( dm:ListDialogMgr ){
        //trace("CenterCtrlDialog");
        var str = "中控";
        var id = 0;
        _uniqueId =  str + id;
        var s:Sprite = dm.createElement( str, id );
        super(  dm );
        addChild(s);

    }

    public function resetDlgs():Void{
        _listDialogMgr.removeAll();

        new ConnDialog( _listDialogMgr);
#if sys
        new DeviceSimulatorDialog(_listDialogMgr); 
#end
        if ( base.network.NetworkMgr.getInst().getConn().isConected() ){
            new LoginCmdDialog(_listDialogMgr);
            new DeviceCreatorDialog( _listDialogMgr);
            new CommandCreatorDialog( _listDialogMgr);
            //new NativeInputCmdDialog(_listDialogMgr);
            new TypedCmdDialog(_listDialogMgr);
            new UntypedCmdDialog(_listDialogMgr);
        }
    }
}
