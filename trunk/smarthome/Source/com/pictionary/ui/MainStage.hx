package com.pictionary.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.InputDialog;
import com.pictionary.ui.ConnDrawingDlg;
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
        var name:String = DataLoader.getInst().getData("usrname");
        if (name == null) {
            name = "玩家";
        }
        new base.ui.SocialBinderDlg(this);
        //new UserNameInputDlg( this, name, 0, "输入名称:");
        //new ConnDrawingDlg( this);
#if !flash
        //new HostDialog( this  );
#end
        //new DrawingDlg( this, "SNS猜猜",0 );
        var d = new DrawingDlg( this, "SNS drawing",0 );
        new SubjectsDlg( this);
    }


    public override function showListDialog( ):Void{
        super.showListDialog();
    }

    public override function hideListDialog( ):Void{
        super.hideListDialog();
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
        var txtFormat:TextFormat = new TextFormat();
        txtFormat.align = flash.text.TextFormatAlign.CENTER;
        //txtFormat.font = "DroidSansFallback";
        txt.setTextFormat(txtFormat);

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


}

