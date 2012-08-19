package com.qbox.ui;

import com.qbox.logic.QboxMgr;
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
        if ( QboxMgr.getInst()._qboxes.length == 0) {
            trace("there is no qbox!");
            return;
        }
        if (ChannelMgr.getInst()._channels.length >8 ) return;
        var c = ChannelMgr.getInst().createChannel();
        var q = QboxMgr.getInst()._qboxes[0];
        c._nodes.push( q._ipv4 +":"+q._inputs.iterator().next());
        var qd = new ChannelDlg(_listDialogMgr, c);
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( QboxMgr.getInst()._qboxes.length == 0) {
            trace("there is no qbox!");
            return;
        }
        var selected:ChannelDlg = null;
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in ChannelMgr.getInst()._channels){
                if ( ChannelMgr.getInst()._currSelected == c){
                    selected = new ChannelDlg(_listDialogMgr, c);
                }
                else {
                    new ChannelDlg(_listDialogMgr, c);
                }
            }
        }
        super.onMouseClick();

        if ( selected != null){
            //trace("onMouseClick");
            selected.onEditBtnMouseClick(null);
        }
    }
}
