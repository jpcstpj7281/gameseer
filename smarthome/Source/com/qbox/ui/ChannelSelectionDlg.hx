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
            _isSelected = true;
            ChannelMgr.getInst()._currSelected = _channel;
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
                    ChannelMgr.getInst()._currSelected = null;
                    unselected();
                    //trace("unselected");
                }
            }else{
                if ( QboxMgr.getInst()._qboxes.length == 0) {
                    trace("there is no qbox!");
                    return;
                }
                if (ChannelMgr.getInst()._channels.length >8 ) return;

                for ( q in  QboxMgr.getInst()._qboxes){
                    for ( k in q._inputs.keys() ){
                        if ( q._inputs.get(k) != "default"){
                            var c = ChannelMgr.getInst().createChannel();
                            c.addNode( q, k );
                            cast(_mgr, MainStage).addChannelSelect();
                            _channel = c;
                            alpha = 1;
                            //trace(k);
                            //trace(q._inputs.get(k));
                            break;
                        }
                    }
                }
                //var q = QboxMgr.getInst()._qboxes[0];
                //c._nodes.push( q._ipv4 +":"+q._inputs.iterator().next());
                //for ( i in q._inputs){
                //c.addNode( q, q._inputs.keys().next());
                //}
            }
        }
    }
}
