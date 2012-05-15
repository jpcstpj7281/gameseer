
package base.social;

import base.social.SinaWeibo;

/**
 * ...
 * @author Wills
 */

class SocialMgr
{

    public  var _socials:Hash<Dynamic>;
    static var inst:SocialMgr;
    public var _loginCount:Int;

    //invoke must at the begining of your app
    inline public static function getInst():SocialMgr{
        if ( inst == null) {
            inst = new SocialMgr();
        }
        return inst;
    }

    public function new() {
        _loginCount = 0;
        _socials = new Hash<Dynamic>();
        var sina = new SinaWeibo("4121333920", "0512e457b9a5f71fc0fb22a865dd7640");
        _socials.set( Type.getClassName( SinaWeibo), sina);
        if ( sina.isBound() ){
            sina.login( false, null);
        }
#if flash
        else{
            var pin:String = getPin();
            if (pin != null && pin.length > 0 ){
                sina._sig.add( onLogin);
                sina.login( false, pin );
                ++ _loginCount;
            }
        }
#end

    }

    public function isInitialized():Bool{
        return _loginCount == 0;
    }


    public function bindSina(){
        var sina= _socials.get( Type.getClassName(base.social.SinaWeibo));
        sina._sig.add( onLogin);
        sina.login( false, getPin() );
        ++ _loginCount;
    }

    public function onLogin( msg:String, args:Array<Dynamic>, obj:Dynamic){
        if( msg == "LoginSucceed"){
            trace("weibo login succeed! "+ Type.getClassName( Type.getClass(obj) ) );
        }else if (msg == "LoginFailed" ){
            trace("weibo login failed! "+ Type.getClassName( Type.getClass(obj) ) );
        }else if (msg == "LoginRequirePin" ){
            trace("weibo login require pin! "+ Type.getClassName( Type.getClass(obj) ) );
        }

        -- _loginCount;
        var sina:SinaWeibo = _socials.get( Type.getClassName(Type.getClass(obj)));
        sina._sig.remove( onLogin);
    }

    inline public function getPin():String{
        var pin:String=null;
#if flash
        pin= flash.Lib.current.root.loaderInfo.parameters.pin;
#end
        return pin;
    }

    inline public function isRefresh():Bool{
        var refresh:Bool = false;
#if flash
        var refreshstr= flash.Lib.current.root.loaderInfo.parameters.refresh;
        if ( refreshstr != null ) refresh = true;
#end
        return refresh;
    }


}
