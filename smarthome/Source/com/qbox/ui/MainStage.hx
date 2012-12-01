package com.qbox.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import base.data.DataLoader;

import com.qbox.logic.ChannelMgr;
import com.qbox.logic.RingMgr;
import com.qbox.logic.Ring;
import com.qbox.logic.Channel;
import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.InputDialog;
import base.ui.FixedDlg;
import nme.text.TextFormat;
import nme.text.TextFormatAlign;

import haxe.Timer;

class MainStage extends ListDialogMgr {


    //var _exit:Sprite;

    var _screenPlate:ScreenPlate;

#if (cpp || neko)
    public function initExit():Void{
        new base.ui.ExitDlg(this);
    }

    public function onExit( evt:MouseEvent):Void{
        nme.system.System.exit();
    }

    function new(){ 
        super(nme.Lib.current);
        initExit();
    }
#elseif flash
    function new(){ 
        super(nme.Lib.current);
    }
#end


    public function createDlgs(){
        //var name:String = DataLoader.getInst().getData("usrname");
        //if (name == null) {
        //name = "玩家";
        //}

#if !flash
        new FileManagerDlg(this);
#end
        new ModeMgrDlg(this);
        new TaskMgrDlg(this);
        //new QboxesDlg(this);
        new ChannelsDlg(this);
        new WndsDlg(this);
        new ScreensDlg(this);
        new RingsDlg(this);
        _screenPlate = new ScreenPlate(this);

        new PlusDown(this);
        new PlusRight(this);
#if !neko
        //new base.ui.SocialBinderDlg(this);
        //new SubjectsDlg( this);
#end
        //new UserNameInputDlg( this, name, 0, "输入名称:");
        //new ConnDrawingDlg( this);
#if !flash
        //new HostDialog( this  );
#end
        //new DrawingDlg( this, "SNS猜猜",0 );
        //var d = new DrawingDlg( this, "SNS drawing",0 );

    }

    public function resetScreenPlate():Void{
        if ( _screenPlate != null){
            _screenPlate.hide();
            _screenPlate.show();
        }
    }

    public function showRingDlg( ):Void{
        var cm = RingMgr.getInst()._rings;
        var index:Int = 0;
        for ( i in 0...cm.length){
            ++index;
            //trace("add ChannelSelectionDlg");
            var c = new RingSelectDlg( this, cm[i], i, cbChangedCurrRing);
            if ( RingMgr.getInst()._currSelected ==cm[i]){
                c.selected();
            }
        }
        //new ChannelSelectionDlg( this, null, index);
        //super.showListDialog();
    }

    function cbChangedCurrChannel( c:Channel){
        clearChannelSelecting();
        ChannelMgr.getInst()._currSelected = c;
        resetScreenPlate();
        if ( c != null) _screenPlate.changedCurrChannel( c );
    }

    function cbChangedCurrRing(r:Ring){
        clearRingSelecting();
        RingMgr.getInst()._currSelected = r;
        resetScreenPlate();
    }

    public function showChannelDlg( ):Void{
        //var cm = ChannelMgr.getInst()._channels;
        var cm = ChannelMgr.getInst().getChannelsWithOutRingPort();
        var index:Int = 0;
        for ( i in 0...cm.length){
            ++index;
            //trace("add ChannelSelectionDlg");
            var c = new ChannelSelectionDlg( this, cm[i], i, cbChangedCurrChannel);
            if ( ChannelMgr.getInst()._currSelected ==cm[i]){
                c.selected();
            }
        }
        //new ChannelSelectionDlg( this, null, index);
        //super.showListDialog();
    }

    public override function hideListDialog( ):Void{
        super.hideListDialog();
        var arr = new Array<Dynamic>();
        for ( i in _instancesByDisplayOrder){
            if ( Std.is( i , ChannelSelectionDlg) ){
                arr.push(i);
            }
            if ( Std.is( i , RingSelectDlg) ){
                arr.push(i);
            }
        }
        for ( i in arr){
            remove(i);
        }

        //var rarr = new Array<RingSelectDlg>();
        //for ( i in _instancesByDisplayOrder){
        //if ( Std.is( i , RingSelectDlg) ){
        //arr.push(cast i);
        //}
        //}
        //for ( i in arr){
        //remove(i);
        //}
    }

    //public function addChannelSelect(){
    //var cm = ChannelMgr.getInst()._channels;
    //var c = new ChannelSelectionDlg( this, null, cm.length);
    //c.show();
    //}

    public function clearRingSelecting(){
        for ( i in _instancesByDisplayOrder){
            if ( Std.is( i , RingSelectDlg) ){
                cast (i, RingSelectDlg).unselected();
            }
        }
    }
    public function clearChannelSelecting(){
        for ( i in _instancesByDisplayOrder){
            if ( Std.is( i , ChannelSelectionDlg) ){
                cast (i, ChannelSelectionDlg).unselected();
            }
        }
    }
    override function clear(){
        hideListDialog();
        super.clear();
    }

    public function resetDlgs(){
        getInst().removeAllMovables();
        getInst().createDlgs();
    }

    public override function createElement(name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX ;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var s:Sprite = new Sprite();
        s.addChild( txt);
        s.height = nme.Lib.current.stage.stageHeight/10;
        return s;
    }

    static var inst:MainStage;
    inline public static function getInst():MainStage{
        if ( inst == null) {
            inst = new MainStage();
        }
        return inst;
    }

    public override function showListDialog():Void{
        if ( _isListening == false  ){
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            setAnimationNum( _movableInstances.length);
            _isDown = false;
            _isListening = true;
            //trace("super show: "+ _instancesByDisplayOrder.length);
            showChannelDlg();
            showRingDlg();
            for ( i in 0..._movableInstances.length){//must use int! for i number
                var d = _movableInstances[i];
                d.show().delay(0.05 * i).onComplete(decreaseAnimationNum, []);
            }
            for ( i in _instancesByDisplayOrder){ i.show(); }
        }
    }
}

