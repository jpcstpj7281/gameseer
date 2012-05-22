package base.social;
import nme.net.SharedObject;
import base.common.Tools;

import nme.utils.ByteArray;
import haxe.io.Bytes;
#if flash
import flash.system.Security;

#end

import base.data.DataLoader;
import nme.net.URLLoader;
import nme.net.URLRequest;

import nme.events.Event;
import nme.events.IOErrorEvent;
import nme.events.SecurityErrorEvent;
import haxe.Http;

/**
 * ...
 * @author Wills
 */

class SinaWeibo extends SocialWorld{



    //inline private static var OAUTH_REQUEST_TOKEN_REQUEST_URL:String =   "https://open.t.qq.com/cgi-bin/request_token";



    var urlLoader:URLLoader ;
    var _brief:String;
    var _msgAto:Array<String>;


    public function new( appKey:String, appSecret:String) {
        super( appKey, appSecret);

        _brief = "";
        _msgAto = new Array<String>();

        API_BASE_URL = "http://api.t.sina.com.cn";
        PROLICY_FILE_URL =  API_BASE_URL + "/flash/crossdomain.xml";
        //var policyfile:String = "http://astrol.vicp.net:8080/trunksm/crossdomain.xml"; 
        //_callbackUrl = "http://astrol.vicp.net:8080/trunksm/indextest.html"; 
        //#if flash
        _cburlappend= ""; 
        //#elseif cpp

#if flash
        //_callbackUrl = "http://gameseer.sinaapp.com/trunksm/hpictionary.html"; 
        _callbackUrl = "http://gameseer.sinaapp.com:8080/smarthome/hpictionary.html"; 
#else
        _callbackUrl = "oob"; 
#end
        //#end
        //var policyfile:String = "http://gameseer.sinaapp.com/crossdomain.xml"; 
        //_callbackUrl = "http://gameseer.sinaapp.com/indextest.html"; 
#if flash
        trace(PROLICY_FILE_URL);
        Security.loadPolicyFile(PROLICY_FILE_URL);
#end


        OAUTH_ACCESS_TOKEN_REQUEST_URL = API_BASE_URL + "/oauth/access_token";
        OAUTH_REQUEST_TOKEN_REQUEST_URL = API_BASE_URL + "/oauth/request_token";
        OAUTH_AUTHORIZE_REQUEST_URL = API_BASE_URL + "/oauth/authorize";


        PUBLIC_TIMELINE_REQUEST_URL = API_BASE_URL + "/statuses/public_timeline.json";
        FRIENDS_TIMELINE_REQUEST_URL = API_BASE_URL +  "/statuses/friends_timeline.json";
        USER_TIMELINE_REQUEST_URL= API_BASE_URL + "/statuses/user_timeline.json";
        MENTIONS_REQUEST_URL= API_BASE_URL + "/statuses/mentions.json";
        COMMENTS_TIMELINE_REQUEST_URL= API_BASE_URL + "/statuses/comments_timeline.json";
        COMMENTS_BY_ME_REQUEST_URL = API_BASE_URL +  "/statuses/comments_by_me.json";
        COMMENTS_TO_ME_REQUEST_URL = API_BASE_URL +  "/statuses/comments_to_me.json";
        COMMENTS_REQUEST_URL= API_BASE_URL + "/statuses/comments.json";
        STATUS_COUNTS_REQUEST_URL = API_BASE_URL +  "/statuses/counts.json";
        REPOST_TIMELINE_URL = API_BASE_URL +  "/statuses/repost_timeline.json";
        REPOST_BY_ME_URL = API_BASE_URL +  "/statuses/repost_by_me.json";		
        STATUS_UNREAD_REQUEST_URL = API_BASE_URL +  "/statuses/unread.json";
        RESET_STATUS_COUNT_REQUEST_URL = API_BASE_URL +  "/statuses/reset_count.json";
        SHOW_STATUS_REQUEST_URL = API_BASE_URL +  "/statuses/show/$id.json";


        UPDATE_STATUS_REQUEST_URL= API_BASE_URL + "/statuses/update.json";
        UPDATE_STATUS_WITH_IMAGE_REQUEST_URL= API_BASE_URL + "/statuses/upload.json";
        DELETE_STATUS_REQUEST_URL= API_BASE_URL + "/statuses/destroy/_S_id.json";
        REPOST_STATUS_REQUEST_URL= API_BASE_URL + "/statuses/repost.json";
        COMMENT_STATUS_REQUEST_URL= API_BASE_URL + "/statuses/comment.json";
        DELETE_COMMENT_REQUEST_URL = API_BASE_URL +  "/statuses/comment_destroy/_S_id.json";
        DELETE_COMMENT_BATCH_URL = API_BASE_URL +  "/statuses/comment/destroy_batch.json";
        REPLY_STATUS_REQUEST_URL = API_BASE_URL +  "/statuses/reply.json";	

        LOAD_USER_INFO_REQUEST_URL= API_BASE_URL + "/users/show.json";
        LOAD_FRIENDS_INFO_REQUEST_URL= API_BASE_URL + "/statuses/friends/$id.json";
        LOAD_FOLLOWERS_INFO_REQUEST_URL = API_BASE_URL +  "/statuses/followers_S_user.json";
        LOAD_HOT_USERS_URL = API_BASE_URL +  "/users/hot.json";
        UPDATE_FRIENDS_REMARK_URL = API_BASE_URL +  "/user/friends/update_remark.json";
        RETURN_SUGGESTIONS = API_BASE_URL + "/users/suggestions";

        LOAD_DIRECT_MESSAGES_RECEIVED_REQUEST_URL= API_BASE_URL + "/direct_messages.json";
        LOAD_DIRECT_MESSAGES_SENT_REQUEST_URL= API_BASE_URL + "/direct_messages/sent.json";
        SEND_DIRECT_MESSAGE_REQUEST_URL= API_BASE_URL + "/direct_messages/new.json";
        DELETE_DIRECT_MESSAGE_REQUEST_URL= API_BASE_URL + "/direct_messages/destroy/_S_id.json";		

        FOLLOW_REQUEST_URL= API_BASE_URL + "/friendships/create/$id.json";
        CANCEL_FOLLOWING_REQUEST_URL= API_BASE_URL + "/friendships/destroy_S_user.json";
        CHECK_IS_FOLLOWING_REQUEST_URL = API_BASE_URL + "/friendships/show.json";
        CHECK_IS_Friendship_Exists_URL= API_BASE_URL + "/friendships/exists.json";

        LOAD_FRIENDS_ID_LIST_REQUEST_URL= API_BASE_URL + "/friends/ids/$id.json";
        LOAD_FOLLOWERS_ID_LIST_REQUEST_URL= API_BASE_URL + "/followers/ids/$id.json";

        LOAD_FOLLOWERS_ID_LIST_REQUEST_URL_VIP = API_BASE_URL +"/1/friendships/followers/all/ids.json";

        LOAD_FRIENDS_ID_LIST_REQUEST_URL_V2 = API_BASE_URL +"/1/friendships/friends/ids.json"; 

        VERIFY_CREDENTIALS_REQUEST_URL = API_BASE_URL + "/account/verify_credentials.json";

        GET_RATE_LIMIT_STATUS_REQUEST_URL= API_BASE_URL + "/account/rate_limit_status.json";
        LOGOUT_REQUEST_URL= API_BASE_URL + "/account/end_session.json";
        UPDATE_PROFILE_IMAGE_REQUEST_URL= API_BASE_URL + "/account/update_profile_image.json";
        UPDATE_PROFILE_REQUEST_URL = API_BASE_URL +  "/account/update_profile.json";
        //account/register 注册新浪微博帐号 
        //Account/activate 二次注册微博的接口 

        LOAD_FAVORITE_LIST_REQUEST_URL= API_BASE_URL + "/favorites.json";
        ADD_TO_FAVORITES_REQUEST_URL= API_BASE_URL + "/favorites/create.json";
        REMOVE_FROM_FAVORITES_REQUEST_URL= API_BASE_URL + "/favorites/destroy/_S_id.json";

        ENABLE_NOTIFICATION_REQUEST_URL= API_BASE_URL + "/notifications/_S_enabled_S_user.json";

        LOAD_PROVINCE_CITY_ID_LIST = API_BASE_URL +  API_BASE_URL + "provinces.json";
    }

    // 添加到社交网络授权后的返回地址,用于把授权的PIN权保存到对应的帐号用,添加的就是对应数据库的用户帐号信息
    // 注意,以URL的参数形式添加
    public function setCallbackAppendent( append:String){
        _cburlappend = append;
    }

    public function loginByOauth( oauthToken:String){ _anywhereToken = oauthToken; }

    /*  will dispatch a "LoginSucceed" in _sig signal dispatcher after logined
        will dispatch a "Required_Pin" in _sig signal dispatcher after got a req_token to authorize, 
        and open a browser with authorization url for usr, requir to login again with pin
     */
    public function login(   refresh:Bool = false, pin:String =  null):Bool{ 
        if( refresh == false  && pin == null ){//没有从外部存入PIN，查看SO中有没有相关PIN和ACC_TOKEN
            if ( _accessTokenKey == null || _accessTokenKey.length == 0 ){
                _accessTokenKey= DataLoader.getInst().getData( "acc_token");
                _accessTokenSecret= DataLoader.getInst().getData( "acc_secret");
                _userId = DataLoader.getInst().getData( "user_id");
            }
            trace( "reachieve acc_token: "+_accessTokenKey);
            trace( "reachieve acc_secret: "+_accessTokenSecret);
            trace( "reachieve user_id: "+_userId);
            if ( _accessTokenKey != null && _accessTokenKey.length > 0 
                    && _accessTokenSecret != null && _accessTokenSecret.length > 0  
                    && _userId != null && _userId.length > 0) 
            {
                _sig.dispatch("LoginSucceed", [], this);
                return true;
            }
        }else if( pin != null &&  pin.length > 0){
            //cbOauthToken 拿到request token and secret, 保存在SharedObject中，现在从中取出申请access token and secret
            _pin = pin; 
            _accessTokenKey= DataLoader.getInst().getData( "req_token");
            _accessTokenSecret= DataLoader.getInst().getData( "req_secret");
            trace( "reachieve req_token: "+_accessTokenKey);
            trace( "reachieve req_secret: "+_accessTokenSecret);
            if ( _accessTokenKey != null && _accessTokenKey.length > 0 && _accessTokenSecret != null && _accessTokenSecret.length > 0) {
                getAccessTokenByPin();
                return true;
            }
        }
        if( (_accessTokenKey == null || 
                    _accessTokenKey.length == 0|| 
                    _accessTokenSecret == null || 
                    _accessTokenSecret.length == 0|| 
                    _pin == null || 
                    _pin.length == 0) ){ 
            openBrowserToGetPin(); 
            //openBrowser( _callbackUrl);
        }else{
            _sig.dispatch("LoginFailed", [], this);
        }

        return false;
    }

    public function unBound():Void{
        //trace( "acckey: " + _accessTokenKey);
        //trace( "accSecret: " + _accessTokenSecret);
        _accessTokenKey= "";
        DataLoader.getInst().saveData( "acc_token", null);
        _accessTokenSecret="";
        DataLoader.getInst().saveData( "acc_secret", null);
        _userId="";
        DataLoader.getInst().saveData( "user_id", null);
        //trace( "acckey: " + _accessTokenKey);
        //trace( "accSecret: " + _accessTokenSecret);
    }

    //check whether there is access token, and achieve it.
    public function isBound():Bool{
        _accessTokenKey= DataLoader.getInst().getData( "acc_token");
        _accessTokenSecret= DataLoader.getInst().getData( "acc_secret");
        _userId= DataLoader.getInst().getData( "user_id");
        if (_accessTokenKey == null || _accessTokenKey.length == 0|| 
                _accessTokenSecret == null || _accessTokenSecret.length == 0 ||
                _userId == null || _userId.length == 0 ) 
        {
            return false;
        }else{
            return true;
        }
    }


    public function brief( content:String):Bool{
        if ( isOutRange( content) ){ return false;}
        _brief = content;
        return true;
    }

    public function addMsgTo( name:String):Bool{
        for ( i in _msgAto){
            if ( name == i) return false;
        }
        if ( isOutRange( name) ){ return false;}
        _msgAto.push(name);
        return true;
    }

    public function removeMsgTo( name:String):Void{
        for ( i in _msgAto){
            if ( name == i) {
                _msgAto.remove(i);
                return;
            }
        }
    }
    public function hasMsgTo( name:String):Bool{
        for ( i in _msgAto){
            if ( name == i) {
                return true;
            }
        }
        return false;
    }

    public function isOutRange( name:String):Bool{
        var len:Int = haxe.Utf8.length( name);
        for ( i in _msgAto){
            len += haxe.Utf8.length(i)+1;
        }
        len+= haxe.Utf8.length(_brief);
        if ( len > 140 ) return true;
        else return false;
    }

    public function clearMsgTo():Void{
        _msgAto = [];
    }
    public function getMsg():String{
        var res = _brief + getAtoString();
        //_brief = "";
        //_msgAto = [];
        return res;
    }

    public function getAtoString( ):String{
        var ns = "";
        for ( i in _msgAto){
            ns += "@"+i;
        }
        return ns;
    }

    public function setFanScreenName( id:String, name:String):Void{
        DataLoader.getInst().saveData( "sina_id_"+id, name);
    }
    public function getScreenName( id:String):String{
        return DataLoader.getInst().getData("sina_id_"+id);
    }
    //inline public function getSaveObj():SharedObject{
    //return DataLoader.getInst().getSharedObj();
    //}

    public function loadBilateralInfoAfterId(id:String, num:Int =10 ){
        var bs = getBilateral();
        for ( i in 0...bs.length){
            if ( bs[i] == id){
                var len = bs.length  - i;
                if ( len > 10 ) len  =10;
                for ( l in 0...len){
                    if ( getScreenName( bs[i+l] ) == "loading..."){ continue; }
                    setFanScreenName( bs[i+l], "loading...");
                    loadUserInfo(bs[i+l]);
                }
                return;
            }
        }
    }

    public function getBilateral():Array<String>{
        if ( _bilateral == null ) {
            _bilateral = DataLoader.getInst().getData("sina_bilateral_" + _userId);
        }
        return _bilateral;
    }

    public function refreshBilateral( fans:Array<String>):Void{
        _bilateral = fans;
        DataLoader.getInst().saveDynamicData( "sina_bilateral_" + _userId, fans);
    }

    dynamic function cbAccessToken( data:String):Void {
        var segs:Array<String> = data.split( "&");
        for ( i in 0...segs.length) {
            var seg:Array<String> = segs[i].split("=");
            if ( seg[0] == "oauth_token") {
                _accessTokenKey = seg[1];
            }else if (seg[0] == "oauth_token_secret" ) {
                _accessTokenSecret = seg[1];
            }if ( seg[0]=="user_id"){
                _userId = seg[1];
            }
        }
        DataLoader.getInst().saveData( "acc_token", _accessTokenKey);
        DataLoader.getInst().saveData( "acc_secret", _accessTokenSecret);
        DataLoader.getInst().saveData( "user_id", _userId);
        DataLoader.getInst().saveData( "req_token", null);
        DataLoader.getInst().saveData( "req_secret", null);
        DataLoader.getInst().saveData( "pin", _pin);

        _sig.dispatch( "LoginSucceed", [ _accessTokenKey, _accessTokenSecret, _userId], this);

    }
    dynamic function getAccessTokenByPin() {
        //用PIN获取access token and secret，并会保存在SharedObject中
        var httpLoader:Http = signRequest( OAUTH_ACCESS_TOKEN_REQUEST_URL, null);
        httpLoader.onData = cbAccessToken;
        httpLoader.onError = function (e) {trace(e);}
        httpLoader.onStatus = function (e) {trace(e);}
        httpLoader.request(true);
        return ;
    }

    //got the request token first, and than open brower to authorize in the callback handler.
    public function openBrowserToGetPin( ):Void{
        _accessTokenKey = "";
        _accessTokenSecret = "";
        if (_consumerKey.length > 0 && _consumerSecret.length > 0){
            var httpLoader:Http = signRequest( OAUTH_REQUEST_TOKEN_REQUEST_URL, null);
            httpLoader.onData = cbOauthToken;
            httpLoader.onError = function (e) {trace(e);}
            httpLoader.onStatus = function (e) {trace(e);}
            httpLoader.request(true);
        }
    }

    dynamic function cbOauthToken( data:String):Void {
        var segs:Array<String> = data.split( "&");
        for ( i in 0...segs.length) {
            var seg:Array<String> = segs[i].split("=");
            if ( seg[0] == "oauth_token") {
                _accessTokenKey = seg[1];
            }else if (seg[0] == "oauth_token_secret" ) {
                _accessTokenSecret = seg[1];
            }
        }
        //just a request token 
        //trace(data);
        //trace( "cb from openBrowserToGetPin reqkey: " + _accessTokenKey); 
        //trace( "cb from openBrowserToGetPin reqSecret: " + _accessTokenSecret);

        DataLoader.getInst().saveData("req_token", _accessTokenKey);
        DataLoader.getInst().saveData("req_secret", _accessTokenSecret);
        //trace( "cbOauthToken req_token: "+_accessTokenKey);
        //trace( "cbOauthToken req_secret: "+_accessTokenSecret);

        authorizeRequestToken();
    }

    public function authorizeRequestToken( ){
        //Ask user authorize and get the pin key, after done will return to the callback url which defined previous.
        var url:String = OAUTH_AUTHORIZE_REQUEST_URL + "?oauth_token=" + _accessTokenKey;
#if android
        nme.Lib.current.addEventListener( nme.events.Event.ENTER_FRAME, onLoop);
        base.ui.Native.openEmbedBrowser(url);
#else
        openBrowser( url);
        _sig.dispatch( "LoginRequirePin", [], this);
#end
    }

#if android
    //打开内嵌浏览器进行授权,监听用户授权完成后的结果
    public function onLoop(evt:nme.events.Event){
        var res:String = base.ui.Native.inputData();
        if ( res != null ){
            if ( res != "__failed__"){
                login( false, res);
            }else{
                _sig.dispatch( "LoginFailed", [], this);
            }
            nme.Lib.current.removeEventListener( nme.events.Event.ENTER_FRAME, onLoop);
        }
    }
#end

    public function updateNewStatus( content:String  ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set("status", content);
        //trace(  encodeMsg(content));
        //params.set("annotations", "test");
        //params.set("_url", UPDATE_STATUS_REQUEST_URL);
        var req:Http = signRequest( UPDATE_STATUS_REQUEST_URL , params, true);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( true);
    }

    public function updateNewStatusWithImg( content:String, img:Bytes = null, imgType:String= "png", fileName:String = "unknow.png"  ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set("status", content);
        //trace(  encodeMsg(content));
        //params.set("annotations", "test");
#if sys
        if( img == null){ img = testimg(); }
        trace("img len: "+ img.length);

        var bi = new haxe.io.BytesInput( img, 0, img.length);

        var req:Http = signRequest( UPDATE_STATUS_WITH_IMAGE_REQUEST_URL, params, true);
        req.fileTransfert( "pic", fileName, bi, img.length);

        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( true);

        //var req = new Http( UPDATE_STATUS_WITH_IMAGE_REQUEST_URL);
        //var boundary:String = makeBoundary();
        //req.setHeader("Content-Type", SocialWorld.CONTENT_MULTIPART_FORMDATA + boundary );
        //params = makeParamsData( UPDATE_STATUS_WITH_IMAGE_REQUEST_URL, params);
        //var str = makeMultiPostData(boundary, "pic", fileName, img, params, imgType);
        //req.setPostData( str);
#elseif flash

        if( img == null){ img = testimg(); }
        var img:ByteArray = img.getData();
        var req = new nme.net.URLRequest(UPDATE_STATUS_WITH_IMAGE_REQUEST_URL);
        var boundary:String = makeBoundary();
        var header:flash.net.URLRequestHeader = new flash.net.URLRequestHeader ("Content-Type", SocialWorld.CONTENT_MULTIPART_FORMDATA + boundary); 
        req.requestHeaders.push(header); 
        req.url = UPDATE_STATUS_WITH_IMAGE_REQUEST_URL;
        req.method = nme.net.URLRequestMethod.POST;

        //params.set("source", _consumerKey);
        params = makeParamsData( UPDATE_STATUS_WITH_IMAGE_REQUEST_URL, params);

        req.data = makeMultiPostData(boundary, "pic", fileName, img, params, imgType);

        urlLoader= new URLLoader( );
        urlLoader.addEventListener(Event.COMPLETE, loader_onComplete);
        urlLoader.addEventListener(IOErrorEvent.IO_ERROR, loader_onError);
        urlLoader.addEventListener(SecurityErrorEvent.SECURITY_ERROR, loader_onSecurityError);
        //trace( "before urlLoader");
        trace( req.data.length);
        urlLoader.load(req);
        //trace( "after urlLoader");
#end
    }

    public function testimg():Bytes{
        var s= new flash.display.Sprite();
        s.graphics.clear();
        s.graphics.beginFill(0xf75544, .5);
        s.graphics.moveTo(50, 0);
        s.graphics.lineTo(100, 50);
        s.graphics.lineTo(50, 100);
        s.graphics.lineTo(0, 50);
        s.graphics.lineTo(50, 0);
        s.graphics.endFill();
#if neko
        var color:nme.display.BitmapInt32 =  {rgb:0, a:1};
#else
        var color:nme.display.BitmapInt32 = 0;
#end
        var b= new nme.display.BitmapData(100, 100, true,color);
        b.draw(s);

        var strimg = Tools.converToPNGBytes( b);
        //var strimg = Tools.converToJPEGBytes( b);
        return strimg;
    }

    function loader_onComplete( evt:Event):Void{ trace("loader_onComplete"); trace( urlLoader.data); }
    function loader_onError( evt:IOErrorEvent):Void{ trace("loader_onError" + evt.toString()); }
    function loader_onSecurityError( evt:SecurityErrorEvent):Void{ trace("loader_onSecurityError"); }

}
