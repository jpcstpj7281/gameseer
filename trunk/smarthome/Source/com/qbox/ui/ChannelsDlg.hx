package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ChannelMgr;
import com.qbox.logic.Channel;

import com.pictionary.ui.DrawingDlgMgr;
class ChannelsDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("channel")));

        x = 170;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusItemFixedDlg(_listDialogMgr, cbPlus);
    }

    public function cbPlus( ):Void{
        if (ChannelMgr.getInst()._channels.length >8 ) return;
        var qd = new ChannelDlg(_listDialogMgr, ChannelMgr.getInst().createChannel());
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in ChannelMgr.getInst()._channels){
                new ChannelDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
