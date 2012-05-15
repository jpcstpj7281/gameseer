package base.social;


import base.data.DataLoader;

import base.conf.Config;
import base.common.Tools;

import haxe.io.Bytes;
import haxe.io.BytesBuffer;

import haxe.Http;
import nme.display.Sprite;
import hxs.Signal3;

import nme.net.SharedObject;
import nme.utils.ByteArray;

/**
 * ...
 * @author Wills
 */




enum AuthType{
    XAUTH;
    OAUTH;
}

class SocialWorld
{

    dynamic var API_BASE_URL:String ;
    dynamic var PROLICY_FILE_URL:String ;

    dynamic var OAUTH_ACCESS_TOKEN_REQUEST_URL:String;
    dynamic var OAUTH_REQUEST_TOKEN_REQUEST_URL:String ;
    dynamic var OAUTH_AUTHORIZE_REQUEST_URL:String;


    dynamic var PUBLIC_TIMELINE_REQUEST_URL:String;
    dynamic var FRIENDS_TIMELINE_REQUEST_URL:String;
    dynamic var USER_TIMELINE_REQUEST_URL:String;
    dynamic var MENTIONS_REQUEST_URL:String;
    dynamic var COMMENTS_TIMELINE_REQUEST_URL:String;
    dynamic var COMMENTS_BY_ME_REQUEST_URL:String ;
    dynamic var COMMENTS_TO_ME_REQUEST_URL:String ;
    dynamic var COMMENTS_REQUEST_URL:String;
    dynamic var STATUS_COUNTS_REQUEST_URL:String ;
    dynamic var REPOST_TIMELINE_URL:String ;
    dynamic var REPOST_BY_ME_URL:String ;		
    dynamic var STATUS_UNREAD_REQUEST_URL:String ;
    dynamic var RESET_STATUS_COUNT_REQUEST_URL:String ;
    ///emotions表情接口

    dynamic var SHOW_STATUS_REQUEST_URL:String ;
    //页面跳转接口
    dynamic var UPDATE_STATUS_REQUEST_URL:String;
    dynamic var UPDATE_STATUS_WITH_IMAGE_REQUEST_URL:String;
    dynamic var DELETE_STATUS_REQUEST_URL:String;
    dynamic var REPOST_STATUS_REQUEST_URL:String;
    dynamic var COMMENT_STATUS_REQUEST_URL:String;
    dynamic var DELETE_COMMENT_REQUEST_URL:String ;
    dynamic var DELETE_COMMENT_BATCH_URL:String ;
    dynamic var REPLY_STATUS_REQUEST_URL:String ;	

    dynamic var LOAD_USER_INFO_REQUEST_URL:String;
    dynamic var LOAD_FRIENDS_INFO_REQUEST_URL:String;
    dynamic var LOAD_FOLLOWERS_INFO_REQUEST_URL:String ;
    dynamic var LOAD_HOT_USERS_URL:String ;
    dynamic var UPDATE_FRIENDS_REMARK_URL:String ;
    dynamic var RETURN_SUGGESTIONS:String;

    dynamic var LOAD_DIRECT_MESSAGES_RECEIVED_REQUEST_URL:String;
    dynamic var LOAD_DIRECT_MESSAGES_SENT_REQUEST_URL:String;
    dynamic var SEND_DIRECT_MESSAGE_REQUEST_URL:String;
    dynamic var DELETE_DIRECT_MESSAGE_REQUEST_URL:String;		

    dynamic var FOLLOW_REQUEST_URL:String;
    dynamic var CANCEL_FOLLOWING_REQUEST_URL:String;
    dynamic var CHECK_IS_FOLLOWING_REQUEST_URL:String;
    dynamic var CHECK_IS_Friendship_Exists_URL:String;

    dynamic var LOAD_FRIENDS_ID_LIST_REQUEST_URL_V2:String;
    dynamic var LOAD_FRIENDS_ID_LIST_REQUEST_URL:String;
    dynamic var LOAD_FOLLOWERS_ID_LIST_REQUEST_URL:String;
    dynamic var LOAD_FOLLOWERS_ID_LIST_REQUEST_URL_VIP:String; 

    dynamic var VERIFY_CREDENTIALS_REQUEST_URL:String;
    dynamic var GET_RATE_LIMIT_STATUS_REQUEST_URL:String;
    dynamic var LOGOUT_REQUEST_URL:String;
    dynamic var UPDATE_PROFILE_IMAGE_REQUEST_URL:String;
    dynamic var UPDATE_PROFILE_REQUEST_URL:String ;
    //account/register 注册新浪微博帐号 
    //Account/activate 二次注册微博的接口 

    dynamic var LOAD_FAVORITE_LIST_REQUEST_URL:String;
    dynamic var ADD_TO_FAVORITES_REQUEST_URL:String;
    dynamic var REMOVE_FROM_FAVORITES_REQUEST_URL:String;

    dynamic var ENABLE_NOTIFICATION_REQUEST_URL:String;

    dynamic var LOAD_PROVINCE_CITY_ID_LIST:String;


    public inline static var CONTENT_MULTIPART_FORMDATA:String="multipart/form-data; boundary=";
    public inline static var CONTENT_DISPOSITION_BASIC:String="Content-Disposition: form-data; name=\"$name\"";
    public inline static var CONTENT_TYPE_IMG:String = "Content-Type: image/"; 
    public inline static var CONTENT_TYPE_JPEG:String = "Content-Type: image/pjpeg"; 

    public var _sig:Signal3< String, Array<Dynamic>, Dynamic> ;

    var	_xauthUser:String;
    var	_xauthPass:String;

    var _consumerKey:String;
    var _consumerSecret:String;
    public var _accessTokenKey:String;
    public var	_accessTokenSecret:String;
    var	_anywhereToken:String;
    var	_pin:String;

    var _callbackUrl:String;
    var _cburlappend:String;

    public var _userId:String;

    var _bilateral:Array<String>;


    //var	_source:String;//same as ping?
    //var	_verifyer:String;
    //var	isTrustDomain_:Bool;
    //var	useProxy_:Bool;
    //var	debugMode_:Bool;

    public function new(appKey:String, appSecret:String) 
    {
        _consumerKey = appKey;
        _consumerSecret = appSecret;
        _accessTokenKey ="";
        _accessTokenSecret ="";
        _pin = "";
        _xauthUser = "";
        _xauthPass = "";
        //_source = "";
        //_verifyer = "";
        //通过此值获取用户当前状态，使用proxy接口时需要带上此值

        _anywhereToken = "";
        //isTrustDomain_ = false;
        //useProxy_ = false;
        //debugMode_ = false;

        _sig = new Signal3();
    }

    dynamic function openBrowser( url){

        /* //this will open new windows of browser.
           if ( flash.external.ExternalInterface.available ){
           try {
           flash.external.ExternalInterface.call("window.open", url,"newwindow","height=420,width=500,top=0,left=0,toolbar=no,menubar=no,scrollbars=no, resizable=no,location=no, status=no, z-look=yes, alwaysRaised=yes");
           }catch ( msg:String) {
           var f = untyped __global__["flash.net.navigateToURL"];
           f(new flash.net.URLRequest(url), "_blank");
           trace( msg);
           }
           }else {
         */
#if flash
        var f = untyped __global__["flash.net.navigateToURL"];
        f(new flash.net.URLRequest(url), "_blank");
        //trace( "flash.external.ExternalInterface.available: " + flash.external.ExternalInterface.available);
        //}
#elseif android
        //base.ui.Native.openBrowser(url);
        base.ui.Native.openBrowser(url);
#elseif cpp
        base.ui.Native.openBrowser(url);
#end
    }

    //dynamic function cbAccessTocken( args:Dynamic):Bool {
    //_pin = args[0];
    //trace( _pin);
    //var httpLoader:Http = signRequest( OAUTH_ACCESS_TOKEN_REQUEST_URL, null);
    //httpLoader.onData = cbAccessToken;
    //httpLoader.onError = function (e) {trace(e);}
    //httpLoader.onStatus = function (e) {trace(e);}
    //httpLoader.request(true);
    //
    //return false;
    //}

    //public function loginByXauth( userName:String, password:String):Void{
    //_xauthUser = _xauthPass = "";
    //if (userName != null && password != null) {
    ////如果传了用户名密码使用XAuth!
    //_xauthUser = userName;
    //_xauthPass = password;
    //
    //var httpLoader:Http = signRequest( OAUTH_ACCESS_TOKEN_REQUEST_URL, null);
    //httpLoader.onData = cbAccessToken;
    //httpLoader.onError = function (e) {trace(e);}
    //httpLoader.onStatus = function (e) {trace(e);}
    //httpLoader.request(true);
    //}
    //}



    dynamic function makeOAuthParams():Hash<String>{
        var oauthParams:Hash<String> = new Hash<String>();

        oauthParams.set("oauth_consumer_key", _consumerKey);
        oauthParams.set("source", _consumerKey);

        if ( _accessTokenKey != null && _accessTokenKey.length > 0)	{
            oauthParams.set ("oauth_token", _accessTokenKey);
        }

        if ( _pin != null &&  _pin.length > 0) {
            oauthParams.set("oauth_verifier", _pin);
        }else{
            oauthParams.set("oauth_callback", _callbackUrl + _cburlappend );
        }

        oauthParams.set("oauth_signature_method", "HMAC-SHA1");
        var timestr:String = Std.string( Date.now().getTime() ).substr( 0, 10) ;
        timestr = StringTools.replace( timestr, ".", "0");
        //var timestr = "1335265830";
        //trace("timestr: "+ timestr);
        oauthParams.set("oauth_timestamp",  timestr);
        var unistr = Tools.uniqueStr();
        //var unistr = "17511276417629568517511276417629";
        //trace("unistr: "+ unistr);
        oauthParams.set("oauth_nonce", unistr);
        oauthParams.set("oauth_version", "1.0");

        return oauthParams;
    }

    dynamic function makeSignableParamStr(params:Hash<String>):String
    {
        var retParams:Array<String>=[];

        //var keys:Iterator<String> = params.keys();
        //while ( keys.hasNext()) {
        //var key:String = keys.next();
        for( key in params.keys() ){
            if (key != "oauth_signature")
            {
                var param:String = params.get(key);
                if ( param != null) {
                    //retParams.push(key + "=" + urlEncodeSpecial(param));
                    retParams.push(key + "=" + urlEncodeSpecial(param));
                    //retParams.push(key + "=" + StringTools.urlEncode(param));
                    //trace( "key: "+key+" val: "+ param);
                    //trace( "len: "+retParams[retParams.length -1].length);
                }
            }
        }
        retParams.sort(Tools.sortString); //after i tested, it seems have to be sort, if u want a right response
        var str:String =  retParams.join("&");

        //trace(str.substr(0, 100) );
        //trace(str.substr(100, 100) );
        //trace(str.substr(200, 100) );
        //trace(str.substr(300, str.length - 300) );
        return str;
    }


    private function signRequest(url:String, requestParams:Hash<String> = null, isPost:Bool = true ):Http {			

        var http:Http = new Http(url);
        var params = makeParamsData( url, requestParams, isPost);
        for( key in params.keys() ) {
            http.setParameter( key, params.get(key));
        }
        return http;
    }

    public function makeParamsData( url:String, requestParams:Hash<String> = null, isPost:Bool = true ):Hash<String>{
        var params:Hash<String> = makeOAuthParams();
        if ( requestParams != null){
            for( key in requestParams.keys() ) {
                params.set( key,  requestParams.get( key));
            }
        }
        var paramsStr:String = makeSignableParamStr(params);
        //trace("parstr len: "+paramsStr.length+" parstr: "+paramsStr);
        var msgStr:String = "";
        if ( isPost) {
            msgStr+="POST&";
        }else {
            msgStr+="GET&";
        }

        msgStr += urlEncodeUtf8String(url);
        msgStr += "&";
        //msgStr += StringTools.urlEncode(paramsStr);
        msgStr += urlEncodeSpecial(paramsStr);
        var secrectStr:String = _consumerSecret + "&";

        if (_accessTokenSecret.length > 0 && _accessTokenKey.length > 0){
            secrectStr += _accessTokenSecret;
        }

        //trace("msg len: "+msgStr.length+" msg: "+msgStr);
        var sig:String = Tools.base64_HMAC_SHA1(secrectStr, msgStr);		
        // The matchers are specified in OAuth only.		
        params.set("oauth_signature", sig);
        return params;
    }

    public function update(content:String):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "status", StringTools.urlEncode( Bytes.ofString(content).toString() ) );
        var req:Http = signRequest( UPDATE_STATUS_REQUEST_URL, params);
        req.onData = function(d) { trace(d); }
        req.onError = function (e) {trace(e);}
        req.onStatus = function (e) {trace(e);}
        req.request( true);
    }

    public function onData(d):Void {	
        if ( d.substr(0, 1) == "{"){
            var json = hxjson2.JSON.decode( cast(d, String));
            _sig.dispatch( "OnDataAsJson", [json] , this);
        }
        else _sig.dispatch( "OnData", [d] , this);
        //trace("test");
    }
    public function onError(e):Void {	
        trace(e);
    }
    public function onStatus(s):Void {	
        trace(s);
    }

    public function loadFollowersV1( id:String = null):Void {
        if ( id == null ){
            if ( _userId != null){
                id = _userId;
            }
            else{
                trace("cannot deal with null id!");
            }
        }

        var params:Hash<String> = new Hash<String>();
        params.set("count", "5000");
        var url = StringTools.replace(LOAD_FOLLOWERS_ID_LIST_REQUEST_URL, "$id", id);
        var req:Http = signRequest( url , null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadFriendsV1( id:String = null):Void {
        if ( id == null ){
            if ( _userId != null){
                id = _userId;
            }
            else{
                trace("cannot deal with null id!");
            }
        }

        var params:Hash<String> = new Hash<String>();
        params.set("count", "5000");
        var url = StringTools.replace(LOAD_FRIENDS_ID_LIST_REQUEST_URL, "$id", id);
        var req:Http = signRequest( url , null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }  

    //public function loadFriendsV2( id:String = null):Void {
    //if ( id == null ){
    //if ( _userId != null){
    //id = _userId;
    //}
    //else{
    //trace("cannot deal with null id!");
    //}
    //}
    //
    ////var url = StringTools.replace(LOAD_FRIENDS_ID_LIST_REQUEST_URL_V2, "$id", id);
    //
    //var params:Hash<String> = new Hash<String>();
    //params.set("uid", id);
    //var req:Http = signRequest( LOAD_FRIENDS_ID_LIST_REQUEST_URL_V2, params, false);
    //req.onData = onData;
    //req.onError = onError;
    //req.onStatus = onStatus;
    //req.request( false);
    //}  

    public function loadPublicTimeLine():Void {	
        var req:Http = signRequest( PUBLIC_TIMELINE_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadFriendsTimeline():Void {	
        var req:Http = signRequest( FRIENDS_TIMELINE_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }


    public function loadUserTimeline():Void {	
        var req:Http = signRequest( USER_TIMELINE_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadMentions():Void {	
        var req:Http = signRequest( MENTIONS_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadCommentsTimeline():Void {	
        var req:Http = signRequest( COMMENTS_TIMELINE_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadMyComments():Void {	
        var req:Http = signRequest( COMMENTS_BY_ME_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadCommentsToMe():Void {	
        var req:Http = signRequest( COMMENTS_TO_ME_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }	

    //arg id: 指定要获取的评论列表所属的微博消息ID
    public function loadCommentList( id:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "id", id);
        var req:Http = signRequest( COMMENTS_REQUEST_URL, params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    //arg ids: 要获取评论数和转发数的微博消息ID列表，用逗号隔开
    public function loadStatusCounts( ids:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "ids", ids);
        var req:Http = signRequest( STATUS_COUNTS_REQUEST_URL, params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }	

    //arg id: 要获取转发微博列表的原创微博ID。
    public function repostTimeline( id:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "id", id);
        var req:Http = signRequest( REPOST_TIMELINE_URL, params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    //arg id: 要获取转发微博列表的用户ID。
    public function repostByMe( id:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "id", id);
        var req:Http = signRequest( REPOST_BY_ME_URL, params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function loadStatusUnread( ):Void {	
        var req:Http = signRequest( STATUS_UNREAD_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    //arg type: 需要清零的计数类别，值为下列四个之一：1. 评论数，2. @me数，3. 私信数，4. 关注数
    public function resetCount( type:Int ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "type", Std.string(type));
        var req:Http = signRequest( RESET_STATUS_COUNT_REQUEST_URL, params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    //arg id: 要获取的微博消息ID，该参数为REST风格的参数
    public function loadStatusInfo( id:String ):Void {	
        var req:Http = signRequest( StringTools.replace(SHOW_STATUS_REQUEST_URL, "$id", id) , null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }


    public function loadUserInfo( id:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "user_id", id );
        //var req:Http = signRequest( StringTools.replace(LOAD_USER_INFO_REQUEST_URL, "$id", id) , null, false);
        var req:Http = signRequest( LOAD_USER_INFO_REQUEST_URL , params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }


    public function isFriendshipExists( a_user_id:String , b_user_id:String ):Void {	
        var params:Hash<String> = new Hash<String>();
        params.set( "user_a", a_user_id );
        params.set( "user_b", b_user_id );
        var req:Http = signRequest( CHECK_IS_Friendship_Exists_URL , params, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    public function follow( id:String  ):Void {	
        //trace("follow: "+ id);
        var params:Hash<String> = new Hash<String>();
        //params.set( "user_id", id );
        var req:Http;
        params.set( "user_id", id );
        req= signRequest( StringTools.replace(FOLLOW_REQUEST_URL, "$id", id) , params, true);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( true);
    }

    // not used bug keep it
    /*
       function makeMultiPostData( boundary:String, imgFieldName:String, filename:String, imgData:Bytes, params:Hash<String>, imgType:String):Bytes{

       var postData=new BytesBuffer();
       for (name in params.keys()) {
       boundaryPostData( postData, boundary);
       addLineBreak(postData);
       postData.add( Bytes.ofString ( StringTools.replace( CONTENT_DISPOSITION_BASIC, "$name", name)));
       addLineBreak(postData);
       addLineBreak(postData);
       postData.add( Bytes.ofString( params.get(name)));
       addLineBreak(postData);
       }

       boundaryPostData( postData, boundary);
       addLineBreak(postData);
       postData.add( Bytes.ofString( StringTools.replace( CONTENT_DISPOSITION_BASIC, "$name", imgFieldName) + "; filename=\"" + filename + "\""));
       addLineBreak(postData);
       postData.add( Bytes.ofString(CONTENT_TYPE_IMG + imgType));
       addLineBreak(postData);
       addLineBreak(postData);
       postData.add(imgData);
       addLineBreak(postData);

       boundaryPostData( postData, boundary);
       addDoubleDash(postData);

       var b = postData.getBytes();
       return b;
       }
     */

#if flash
    function makeMultiPostData( boundary:String, imgFieldName:String, filename:String, imgData:ByteArray, params:Hash<String>, imgType:String):ByteArray{
        var postData:ByteArray=new ByteArray();
        postData.endian=nme.utils.Endian.BIG_ENDIAN;
        for (name in params.keys()) {
            boundaryPostData(postData, boundary);
            addLineBreak(postData);
            postData.writeUTFBytes( StringTools.replace( CONTENT_DISPOSITION_BASIC, "$name", name));
            addLineBreak(postData);
            addLineBreak(postData);
            postData.writeUTFBytes(params.get(name));
            //trace("after writeUTFBytes: "+ name + " "+ params.get(name) );
            addLineBreak(postData);
        }

        //trace("in makeMultiPostData");
        boundaryPostData(postData, boundary);
        addLineBreak(postData);
        postData.writeUTFBytes( StringTools.replace( CONTENT_DISPOSITION_BASIC, "$name", imgFieldName) + "; filename=\"" + filename + "\"");
        addLineBreak(postData);
        postData.writeUTFBytes(CONTENT_TYPE_IMG + imgType);
        addLineBreak(postData);
        addLineBreak(postData);
        postData.writeBytes(imgData, 0, imgData.length);
        addLineBreak(postData);

        boundaryPostData(postData, boundary);
        addDoubleDash(postData);

        //var b:Bytes= Bytes.ofData( postData);
        //trace(b.readString(0 , b.length ) );

        postData.position=0;
        return postData;
    }
#end


    public function loadVerifyCredentials( ):Void {	
        var req:Http = signRequest( VERIFY_CREDENTIALS_REQUEST_URL, null, false);
        req.onData = onData;
        req.onError = onError;
        req.onStatus = onStatus;
        req.request( false);
    }

    private function encodeMsg(content:String):String {
        var source:String = content;
        var pattern1:EReg = new EReg("^[ ]+|[ ]+$", "g");
        source = pattern1.replace(source, "");
        var pattern2:EReg = new EReg("[ \n\t\r]", "g");
        source = pattern2.replace(source, " ");
        var pattern3:EReg = ~/( )+/g;
        source = pattern3.replace(source, " ");
        return urlEncodeSpecial(source);
        //return source;
    }

    public static function urlEncodeSpecial(srcStr:String):String {
        if (srcStr == null )
        {
            return "";
        }
        var chr:Int = 0;
        var utfStr:String='';
        //When encode the string using utf8. The encoder should encode the original string one byte by one byte.
#if flash
        for (i in 0...srcStr.length)
        {
            chr=srcStr.charCodeAt(i);
#else
        for (i in 0...haxe.Utf8.length(srcStr))
        {
            chr=haxe.Utf8.charCodeAt(srcStr,i);
#end
            if (chr < 128)
            {
                utfStr+=String.fromCharCode(chr);
            }
            else if ((chr > 127) && (chr < 2048))
            {
                utfStr+=String.fromCharCode((chr >> 6) | 192);
                utfStr+=String.fromCharCode((chr & 63) | 128);
            }
            else
            {
                utfStr+=String.fromCharCode((chr >> 12) | 224);
                utfStr+=String.fromCharCode(((chr >> 6) & 63) | 128);
                utfStr+=String.fromCharCode((chr & 63) | 128);
            }
        }
        return urlEncode(utfStr);
        //return utfStr;
    }
    public static function urlEncode(srcStr:String):String {
        if (  srcStr == null )
        {
            return "";
        }
        var urlStr:String='';
        var chr:Int=0;

        for (index in 0...srcStr.length)
        {
            //chr=utfStr.charCodeAt(index);
            chr = srcStr.charCodeAt(index);
            if ((chr >= 48 && chr <= 57) || // 09
                    (chr >= 65 && chr <= 90) || // AZ
                    (chr >= 97 && chr <= 122) || // az
                    chr == 45 || // -
                    chr == 95 || // _
                    chr == 46 || // .
                    chr == 126) // ~
            {
                urlStr+=String.fromCharCode(chr);
            }
            else
            {
                urlStr+='%' + StringTools.hex(chr ).toUpperCase();
            }
        }

        return urlStr;
    }
    public static function urlEncodeUtf8String(srcStr:String):String {
        if ( srcStr == null)
        {
            return "";
        }
#if js
        return urlEncode( srcStr);
#else
        var ba:ByteArray = new ByteArray();
        var chr:Int= 0;
        ba.writeUTFBytes(srcStr);
        ba.position = 0;
        //trace(ba.toString());
        var utfStr:String="";
        //When encode the string using utf8. The encoder should encode the original string one byte by one byte.
        for (i in 0...ba.length)
        {
            chr=ba[i];
            if (chr < 128)
            {
                utfStr+=String.fromCharCode(chr);
            }
            else if ((chr > 127) && (chr < 2048))
            {
                utfStr+=String.fromCharCode((chr >> 6) | 192);
                utfStr+=String.fromCharCode((chr & 63) | 128);
            }
            else
            {
                utfStr+=String.fromCharCode((chr >> 12) | 224);
                utfStr+=String.fromCharCode(((chr >> 6) & 63) | 128);
                utfStr+=String.fromCharCode((chr & 63) | 128);
            }
        }
        return urlEncode(utfStr);
#end
    }
    /**
     * base OAUTH中需要使用utf8编码
     * @param	string
     * @return
     */
    public static function utf8Encode(string:String):String {
        var e1:EReg = ~/\r\n/g;
        var e2:EReg = ~/\r/g;
        string = e1.replace(string,'\n');
        string = e2.replace(string,'\n');

        var utfString:String = '';

        for (i in 0...string.length)
        {
            var chr:Int = string.charCodeAt(i);
            if (chr < 128)
            {
                utfString += String.fromCharCode(chr);
            }
            else if ((chr > 127) && (chr < 2048))
            {
                utfString += String.fromCharCode((chr >> 6) | 192);
                utfString += String.fromCharCode((chr & 63) | 128);
            }
            else
            {
                utfString += String.fromCharCode((chr >> 12) | 224);
                utfString += String.fromCharCode(((chr >> 6) & 63) | 128);
                utfString += String.fromCharCode((chr & 63) | 128);
            }
        }

        return utfString;
    }


    private function makeBoundary():String {
        var boundary:String="";
        for (i in 0...13)
        {
            boundary+=String.fromCharCode( 97 + Std.int(  Math.random() * 25 ));
        }
        boundary="---------------------------" + boundary;
        return boundary;
    }


#if flash
    private function addLineBreak(data:ByteArray):Void { data.writeShort(0x0d0a); }
    private function addDoubleDash(data:ByteArray):Void { data.writeShort(0x2d2d); }
    private function boundaryPostData(data:ByteArray, boundary:String):Void {
        var len:Int=boundary.length;
        addDoubleDash(data);
        for (i in 0...len) {
            data.writeByte(boundary.charCodeAt(i));
        }
    }
#elseif cpp
    private function addLineBreak(data:BytesBuffer):Void {data.addByte(0x0d);data.addByte( 0x0a);}
    private function addDoubleDash(data:BytesBuffer):Void {data.addByte(0x2d); data.addByte( 0x2d);}
    private function boundaryPostData(data:BytesBuffer, boundary:String):Void {
        var len:Int=boundary.length;
        addDoubleDash(data);
        data.add( Bytes.ofString(boundary));
    }
#end
    }
