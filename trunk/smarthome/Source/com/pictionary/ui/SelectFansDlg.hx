package com.pictionary.ui;

import com.blueseer.cmd.Command;
import com.blueseer.cmd.CommandMgr;

import com.eclecticdesignstudio.motion.actuators.GenericActuator;
import com.eclecticdesignstudio.motion.Actuate;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import base.ui.EmbedTextField;
import nme.text.TextFormat;
import nme.events.Event;
import nme.geom.Point;

class SelectFansDlg extends CommDialog{

    var _id:String;
    var _name:String;
    var _show:Sprite;
    public function new ( mgr:ListDialogMgr, id:String, name:String = ""){
        _id = id;
        _name = name;
        _show = getElement( name, id);
        super( mgr);
        addChild(_show);
        nme.Lib.current.stage.addEventListener( Event.ENTER_FRAME , onEnterFrame);
    }


    function onEnterFrame( evt:Event):Void{
        if ( _name.length >0 ) return;
        var interval = nme.Lib.current.stage.stageHeight/10;
        for ( i in 0...10){
            if ( hitTestPoint( 1, 1+interval*i )){
                _name = "loading...";
                removeChild( _show);
                _show = getElement( _name, _id);
                addChild(_show);
                var sina:base.social.SinaWeibo = base.social.SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
                sina._sig.add( onData);
                sina.loadUserInfo(_id);
                nme.Lib.current.stage.removeEventListener( Event.ENTER_FRAME , onEnterFrame);
                break;
            }
        }
    }

    function onData( msg:String, args:Array<Dynamic>, obj:Dynamic):Void{
        if ( msg == "OnData"){
            var rsp = args[0];
            trace("test");
            var json = hxjson2.JSON.decode( rsp);
            trace("test");
            if ( json.id == _id ){
                _name = json.screen_name;
                removeChild( _show);
                _show = getElement( _name, _id);
                addChild(_show);
            trace("test");
                var sina:base.social.SinaWeibo = cast obj;
                sina._sig.remove( onData);
                sina.setFanScreenName( _id, _name);
            trace("test");
            }
        }
    }

    override function show(){
        var sina:base.social.SinaWeibo = base.social.SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
        var a:Float = 0;
        if( sina.hasMsgTo( _name) ){
            a = 0.5;
        }else{
            a = 1;
        }
        return Actuate.tween (this, _fadeInTime, { alpha: a} ).autoVisible(true);
    }

    override function onMouseClick():Void{
        var sina:base.social.SinaWeibo = base.social.SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
        var a:Float = 0;
        if( sina.hasMsgTo( _name)  == false){
            a = 0.5;
            sina.addMsgTo( _name);
        }else{
            a = 1;
            sina.removeMsgTo( _name);
        }
        Actuate.apply (this, { alpha: a} ).autoVisible(true);
    }

    static public function getElement( name:String, id:String):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 200;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 200/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        var txtFormat:TextFormat = new TextFormat();
        txtFormat.align = flash.text.TextFormatAlign.CENTER;
        txt.setTextFormat(txtFormat);
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = id;
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.width = 200;
        txt1.setBorder(true);
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var s:Sprite = new Sprite();
        s.addChild( txt1);
        s.addChild( txt);
        s.height = nme.Lib.current.stage.stageHeight/10;
        return s;
    }
}

