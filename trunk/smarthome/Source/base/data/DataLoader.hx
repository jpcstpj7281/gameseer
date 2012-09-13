package base.data;
import base.conf.Config;
import nme.Assets;
import nme.display.Bitmap;
import nme.display.BitmapData;
import nme.display.Loader;
import nme.display.Sprite;
import nme.events.Event;
import nme.geom.Matrix;
import nme.geom.Point;
import nme.geom.Rectangle;
import nme.net.SharedObject;
import nme.net.URLLoader;
import nme.net.URLRequest;
import nme.text.Font;
import nme.text.TextField;
import nme.Lib;
import nme.text.TextFormat;

//import ui.CommBtn;
import haxe.Timer;



/**
 * ...
 * @author Wills
 */

class DataLoader
{
    public var loadcouter_:Int;
    public var totalItem_:Int;
    private var loaders_:Hash<Loader>;
    private var urlLoaders_:Hash<URLLoader>;

    public var bms_:Hash<BitmapData>;
    public var lvls_:Hash<String>;
    public static  var inst:DataLoader;


    public var font_:Font;
    public var textFormat_:TextFormat;


    //invoke must at the begining of your app
    inline public static function getInst():DataLoader{
        if ( inst == null) {
            inst = new DataLoader();
        }
        return inst;
    }

    public function new() 
    {
        //super();
        //Lib.current.addChild( this);		
        bms_ = new Hash<BitmapData>();
        lvls_ = new Hash<String>();
        loadcouter_ = 0;
    }

    public function loadAssets( evt:Event ):Void {
        totalItem_ = Config.conf_.node.config.nodes.item.length;
        if ( loadcouter_ == totalItem_ ) return;

#if ( flash)
        loaders_ = new Hash<Loader>();
        urlLoaders_ = new Hash<URLLoader>();

        for ( item in Config.conf_.node.config.nodes.item) {
            //trace("test1");
            if ( item.node.type.innerData == "level") {
                var loader:URLLoader = new URLLoader();
                urlLoaders_.set(  item.node.name.innerData, loader);

                var url:String = Config.host + Config.basePath + "/" + item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData;
                trace(url);
                var req:URLRequest = new URLRequest(url);
                loader.addEventListener( Event.COMPLETE, loadComplete);
                loader.load(req);
                //trace("loading data: " + item.node.type.innerData);

            }
            else if ( item.node.type.innerData == "font") {
                loadComplete(null);
            }
            else {

                var loader:Loader = new Loader();
                loaders_.set(item.node.type.innerData, loader);

                var url:String = Config.host + Config.basePath + "/" + item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData;

                trace(url);
                var req:URLRequest = new URLRequest(url);
                loader.contentLoaderInfo.addEventListener( Event.COMPLETE, loadComplete);
                loader.load(req);

                //trace("loading data: " + item.node.type.innerData);
            }

        }
#else
        for ( item in Config.conf_.node.config.nodes.item) {
            trace("loading assets: " + item.node.type.innerData);
            if ( item.node.type.innerData == "level") {
                var str:String = Assets.getText( "assets/" + item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData);
                if ( str != null){
                    lvls_.set(item.node.name.innerData, str  );
                    loadComplete(null);
                }else {
                    Config.inst.error_.text = "no assets!";
                }
            } else if ( item.node.type.innerData == "font") {
                font_ = Assets.getFont( "assets/" + item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData);
                if ( font_ != null) {
                    textFormat_ = new TextFormat( font_.fontName, 12, 0x80FF80);
                    textFormat_.align = nme.text.TextFormatAlign.CENTER;
                    textFormat_.font = font_.fontName;
                    //trace("load font: "+ font_.fontName);
                    loadComplete(null);
                }else {
                    Config.inst.error_.text = "no font!";
                    trace(Config.inst.error_.text );
                }
            } else{
                //trace( item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData);
                var bmd:BitmapData = Assets.getBitmapData( "assets/" + item.node.loc.innerData + "/" + item.node.name.innerData +  item.node.extension.innerData);
                if ( bmd != null){
                    bms_.set(item.node.type.innerData, bmd );
                    loadComplete(null);
                }else {
                    Config.inst.error_.text = "no assets!";
                }
            }
        }
#end
        //trace(Config.conf_.node.config.nodes[0]);
    }

    public function getBitmapData( urlStr:String){
        var bmd:BitmapData = Assets.getBitmapData( urlStr);
        if ( bmd != null){
            //bms_.set(item.node.type.innerData, bmd );
            //loadComplete(null);
            trace("load bitmap data: "+ urlStr);
        }else {
            //Config.inst.error_.text = "no assets!";
            trace("unable to load bitmap data: "+ urlStr);
        }
        return bmd;
    }

    // load img file callback, invoke every time loaded a img file, and recusive if there are more to be load
    private function loadComplete(  evt:Event): Void{
        ++loadcouter_;

        if ( loadcouter_ == totalItem_) {
            trace(loadcouter_ + " item loaded!" );

#if ( flash||js )
            var keys:Iterator<String> = loaders_.keys();
            for ( k in keys ) {
                bms_.set( k , cast( loaders_.get( k).content, Bitmap).bitmapData );
            }
            loaders_ = null;

            keys = urlLoaders_.keys();
            for ( k in keys ) {
                lvls_.set( k , urlLoaders_.get( k).data );
            }
            urlLoaders_ = null;
#end


        }
    }

    public function getData( key:String):Dynamic{
        var so:SharedObject = SharedObject.getLocal( Config.appName );
        //trace(Config.appName);
        var data= Reflect.field( so.data, key);
        //trace("getData: " + data);
        return data;
    }

    public function getSharedObj( ):SharedObject{
        return SharedObject.getLocal( Config.appName );
    }

    public function getSaveData( ):Dynamic{
        var so:SharedObject = SharedObject.getLocal( Config.appName );
        return so.data;
    }

    public function saveDynamicData( key:String, val:Dynamic):Void{
        var so:SharedObject = SharedObject.getLocal( Config.appName );
        Reflect.setField( so.data, key, val);
        trace("saveData key: " + key +" val: "+ val);
        so.flush();
    }
    public function saveData( key:String, val:String):Void{
        var so:SharedObject = SharedObject.getLocal( Config.appName );
        Reflect.setField( so.data, key, val);
        trace("saveData key: " + key +" val: "+ val);
        so.flush();
    }

}
