
package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.logic.Channel;
import com.qbox.logic.ChannelMgr;

import com.pictionary.ui.DrawingDlgMgr;

class ChannelSelectionDlg extends ListFixedDlg{

    var _channel:Channel;
    var _clicked:Sprite;
    var _isSelected:Bool;
    public function new ( dm:CommDialogMgr, channel:Channel, index:Int ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("erase")));

        x = 100 * index;
        y= nme.Lib.current.stage.stageHeight - 160;

        _channel = channel;
        _isSelected = false;
    }

    public function unselected():Void{
        if (_isSelected ){
            _isSelected=!_isSelected;
            if ( _clicked.parent != null ){
                removeChild(_clicked);
            }
        }
    }

    public function selected():Void{
        if (_clicked == null){
            _clicked = new Sprite();
            _clicked.graphics.beginFill(0x888888);
            _clicked.graphics.drawRect(0,0,60,60);
            _clicked.alpha = 0.5;
        }
        if ( !_isSelected ){
            cast(_mgr, MainStage).clearChannelSelecting();
            addChild(_clicked);
            _isSelected = !_isSelected;
            ChannelMgr.getInst()._currSelected = _channel;
        }
    }

    public override function onMouseClick( ):Void{
        //if ( QboxMgr.getInst()._qboxes.length == 0) return;
        if ( _mgr.isAnimating() == false){

            if ( !_isSelected ){
                selected();
                //trace("selected");
            }else{
                ChannelMgr.getInst()._currSelected = null;
                unselected();
                //trace("unselected");
            }
            //_listDialogMgr.removeAllMovables();
            //for ( c in ScreenMgr.getInst()._screens){
            //new ChannelSelectionDlg(_listDialogMgr, c);
            //}
        }
        //super.onMouseClick();
    }
}
