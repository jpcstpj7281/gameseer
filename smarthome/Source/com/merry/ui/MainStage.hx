package com.merry.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import base.data.DataLoader;

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
import nme.media.Sound;
import nme.net.URLRequest;
import base.conf.Config;

class MainStage extends ListDialogMgr {


    //var _exit:Sprite;
    var _music:Sound;


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
        //trace("test");

        
        _music = new Sound();
        _music.load(new  URLRequest( Config.host+Config.basePath+"merry/love_paradise.mp3")) ;
        _music.play();

#if !neko
        //new base.ui.SocialBinderDlg(this);
        //new SubjectsDlg( this);
#end
        new InputDialog( this, "test", 0, "输入名称:");
        //new ConnDrawingDlg( this);
#if !flash
        //new HostDialog( this  );
#end
        //new DrawingDlg( this, "SNS猜猜",0 );
        //var d = new DrawingDlg( this, "SNS drawing",0 );



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

}

