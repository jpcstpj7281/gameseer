package base.conf;
//import base.state.StateMachine;
//import base.state.LoadConfState;
import nme.text.TextField;
import haxe.Http;
import haxe.xml.Fast;
import nme.Assets;
import nme.display.Sprite;
import nme.events.Event;
import nme.Lib;

/**
 * ...
 * @author Wills
 */

class Config extends Sprite
{

    public static  var inst:Config;

#if android
    public static var confFileName:String = "conf.xml";
#else
    public static var confFileName:String = "conf_nofont.xml";
#end
    public static var appName:String = "SmartHome";

#if flash
    inline static public var host:String = "http://gameseer.sinaapp.com:8080/" ;
    inline static public var basePath:String = "smarthome/Assets/" ;
    //inline static public var host:String = "http://astrol.vicp.net:8080/" ;
    //inline static public var basePath:String = "smarthome/Assets/" ;
#end

    //public static var connIP:String = "192.168.1.129";
    public static var connIP:String = "192.168.1.131";
    //public static var connIP:String = "192.168.1.127";

    public static var conf_:Fast; //静态化才可以在CPP中提早初始化对象
    public static var xml_:Xml; //静态化才可以在CPP中提早初始化对象
    public var isLoaded_:Bool;

    inline static public var ConfigLoadedEventStr:String = "ConfigLoadedEventStr";


    public static var ScaleX:Float;
    public static var ScaleY:Float ;

    public var error_:TextField;

    function new() 
    {
        super();
        isLoaded_ = false;
        error_ = new TextField();
        addChild( error_);
        Lib.current.addChild( this);
        //Lib.current.addEventListener( "LoadConf",  loadConf);
    }

    // Will fire a "LoadConfComplete" event to Lib.current after config loaded.
    public function loadConf(evt:Event = null) {
        if ( isLoaded_ ) return;

#if (flash )
        var h:Http = new Http(host + basePath + confFileName);
        h.onData = parseData;
        h.request(false);
#else
        var str:String = Assets.getText( "assets/"+confFileName);
        if ( str != null){
            parseData(str );
        }else {
            trace("no configuration!");
            error_.text = "no configuration!";
        }
#end
    }


    public function parseData(d:String):Void { 
        conf_ = new Fast( Xml.parse(d));
        isLoaded_ = true;
        //xml_ = Xml.parse(d);
        trace("conf data loaded");
    }

    inline public static function getInst():Config {
        if ( inst == null) {
            inst = new Config();
        }
        return inst;
    }

}
