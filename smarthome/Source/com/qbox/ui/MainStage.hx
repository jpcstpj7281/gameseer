package com.qbox.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import com.qbox.logic.ChannelMgr;
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

        new QboxesDlg(this);
        new ChannelsDlg(this);
        new WndsDlg(this);
        new ScreensDlg(this);
        new ScreenPlate(this);

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


    public override function showListDialog( ):Void{
        var cm = ChannelMgr.getInst()._channels;
        for ( i in 0...cm.length){
            //trace("add ChannelSelectionDlg");
            var c = new ChannelSelectionDlg( this, cm[i], i);
            if ( ChannelMgr.getInst()._currSelected ==cm[i]){
                c.selected();
            }
        }
        super.showListDialog();
    }

    public override function hideListDialog( ):Void{
        super.hideListDialog();
        var arr:Array<ChannelSelectionDlg> = new Array<ChannelSelectionDlg>();
        for ( i in _instancesByDisplayOrder){
            if ( Std.is( i , ChannelSelectionDlg) ){
                arr.push(cast i);
            }
        }

        for ( i in arr){
            remove(i);
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
        //trace("clear1");
        super.clear();
        //trace("clear2");
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
        //var txtFormat:TextFormat = new TextFormat();
        //txtFormat.align = flash.text.TextFormatAlign.CENTER;
        //txt.setTextFormat(txtFormat);

        //var txt1:EmbedTextField = new EmbedTextField();
        //txt1.text = Std.string(id);
        //txt1.scaleX = 1;
        //txt1.scaleY = 3;
        //txt1.setBorder(true);
        //txt1.width = 100;
        //txt1.x = 120;
        //txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        //txt1.selectable = false;

        //var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("trunk") );
        var s:Sprite = new Sprite();
        //s.addChild( bm);
        //s.addChild( txt1);
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

    /*
    public override function showListDialog():Void{
        if ( _isListening == false  ){
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            setAnimationNum( _movableInstances.length);
            _isDown = false;
            _isListening = true;
            //trace("super show: "+ _instancesByDisplayOrder.length);
            for ( i in 0..._movableInstances.length){//must use int! for i number
                var d = _movableInstances[i];
                d.show().delay(0.05 * i).onComplete(decreaseAnimationNum, []);
            }
            for ( i in _instancesByDisplayOrder){ i.show(); }
        }
    }
    */


}

