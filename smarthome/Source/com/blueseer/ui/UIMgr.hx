package com.blueseer.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import com.blueseer.cmd.CommandMgr;
import com.blueseer.device.Device;
import com.blueseer.device.DeviceMgr;
import com.blueseer.cmd.Command;
import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;

import haxe.Timer;

class UIMgr extends ListDialogMgr {


    var _exit:Sprite;
    var _mic:Sprite;

#if sys
    public function initExit():Void{
        _exit = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("exit"));
        _exit.addChild( bm);
        _exit.x = 50;
        _exit.y= nme.Lib.current.stage.stageHeight - 100;
        _exit.addEventListener( MouseEvent.CLICK, onExit);
    }

    public function onExit( evt:MouseEvent):Void{
        nme.system.System.exit();
    }
#end

#if android
    var _speechCmdsMgr:SubListDialogMgr;
    function new(){
        super(nme.Lib.current);
        _mic = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("mic"));
        _mic.addChild( bm);
        _mic.x = nme.Lib.current.stage.stageWidth - 100;
        _mic.y= nme.Lib.current.stage.stageHeight - 100;
        _mic.addEventListener( MouseEvent.CLICK, onMic);

        new CenterCtrlDialog(this);
        initExit();
    }

    public function getFuzzyMatchCmd( cmdName:String):Array<Command>{
        var arr:Array<Command> = new Array<Command>();
        trace("cmd len: "+cmdName.length);
        for ( c in CommandMgr.getInst()._commands ){
            var clen:Int = c._commandName.length;
            var fuzzyStrLen:Int = cmdName.length;
            trace("try match: "+c._commandName+ " len: "+clen);

            if ( fuzzyStrLen>clen){
                var endpos:Int = fuzzyStrLen - clen;
                var pos:Int = 0;

                while ( pos < endpos ){
                    if ( cmdName.substr( pos, clen ) == c._commandName){
                        trace("found match: " +c._commandName);
                        arr.push(c);
                        break;
                    }
                    ++pos;
                }
            }
        }
        return arr;
    }
    public function onLoop(evt:Event){
        var res:String = base.ui.Native.inputData();
        if ( res != null ){
            if ( res == "__failed__"){
                nme.Lib.current.removeEventListener( Event.ENTER_FRAME, onLoop);
                return;
            }
            trace(res );
            nme.Lib.current.removeEventListener( Event.ENTER_FRAME, onLoop);

            var cmds = getFuzzyMatchCmd( res);

            if(cmds.length > 0){
                showSpeechCmds(cmds);
            }
        }
    }
    public function onMic( evt:MouseEvent){
        if (isAnimating()) return;
        base.ui.Native.speechInput();
        //Native.openBrowser( "http://qq.com");
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, onLoop);
    }
    public function showSpeechCmds( cmds:Array<Command> ):Void{
        if( _speechCmdsMgr != null ){
            _speechCmdsMgr.clear();
            _speechCmdsMgr = null;
        }
        _speechCmdsMgr = new SubListDialogMgr(nme.Lib.current);
        _speechCmdsMgr._returnCallback= showListDialog;

        for( cmd in cmds){
            new SimpleCmdDialog( _speechCmdsMgr, cmd._commandName, cmd._commandID);
        }
        _speechCmdsMgr.showListDialog();
        hideListDialog();
    }
#elseif sys
    function new(){ 
        super(nme.Lib.current);
        new CenterCtrlDialog(this);
        initExit();
    }
#elseif flash
    function new(){ 
        super(nme.Lib.current);
        new CenterCtrlDialog(this);
    }
#end


    public function createDeviceDlgs(){
        for( dev in DeviceMgr.getInst()._devices){
            new DeviceDialog( this, dev._deviceName, dev._deviceID);
        }
    }


    public override function showListDialog( ):Void{
        if (_mic != null &&  _mic.parent == null  ) { nme.Lib.current.addChild(_mic); }
        if (_exit!= null &&  _exit.parent == null  ) { nme.Lib.current.addChild(_exit); }
        super.showListDialog();
    }

    public override function hideListDialog( ):Void{
        if (_mic!= null &&  _mic.parent != null  ) { nme.Lib.current.removeChild(_mic); }
        if (_exit!= null &&  _exit.parent != null  ) { nme.Lib.current.removeChild(_exit); }
        super.hideListDialog();
    }

    public override function clear(){
        hideListDialog();
        super.clear();
    }

    public function resetDlgs(){
        for ( d in _movableInstances){
            if( Std.is( d , CenterCtrlDialog) == false ){
                d.clear();
                _movableInstances.remove(d);
            }else{
                var c:CenterCtrlDialog = cast d;
                c.resetDlgs();
            }
        }
        for( dev in DeviceMgr.getInst()._devices){
            //trace("resetDlgs");
            new DeviceDialog( this, dev._deviceName, dev._deviceID);
            //trace("resetDlgs");
        }
    }

    //public function onEnterFrame(evt:Event){ 
    //if ( _stagewidth != nme.Lib.current.stage.stageWidth){
    //_stagewidth = nme.Lib.current.stage.stageWidth;
    //}
    //}

    public override function createElement(name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 220;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 220/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = Std.string(id);
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.setBorder(true);
        txt1.width = 100;
        txt1.x = 120;
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("trunk") );
        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt1);
        s.addChild( txt);
        s.height = nme.Lib.current.stage.stageHeight/10;
        return s;
    }

    static var inst:UIMgr;
    inline public static function getInst():UIMgr{
        if ( inst == null) {
            inst = new UIMgr();
        }
        return inst;
    }


}

