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


class ChannelSelectionDlg extends ListFixedDlg{

    var _channel:Channel;
    var _clicked:Sprite;
    var _isSelected:Bool;
    var _cb:Channel->Void;
    public function new ( dm:CommDialogMgr, channel:Channel, index:Int, cb:Channel->Void ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("erase")));

        x = 100 * index;
        y= nme.Lib.current.stage.stageHeight - 160;

        _channel = channel;
        _isSelected = false;
        _cb = cb;
    }

    override function show(){
        var s = super.show();
        if (_channel == null){ alpha = 0.5; }
        else { alpha = 1; }
        return s;
    }
    public function unselected():Void{
        if (_isSelected ){
            _isSelected=false;
            if ( _clicked.parent != null ){
                removeChild(_clicked);
            }
            _cb( null);
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
            _cb( _channel);
            addChild(_clicked);
            _isSelected = true;
        }
    }

    public override function onMouseClick( ):Void{
        //if ( QboxMgr.getInst()._qboxes.length == 0) return;
        if ( _mgr.isAnimating() == false){

            if (_channel != null){
                if ( !_isSelected ){
                    selected();
                    //trace("selected");
                }else{
                    unselected();
                    //trace("unselected");
                }
            }else{
            }
        }
    }
}
