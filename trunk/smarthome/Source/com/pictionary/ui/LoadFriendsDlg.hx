package com.pictionary.ui;


import base.ui.CommDialog;
import base.ui.ListDialog;
import base.ui.ListDialogMgr;
import nme.display.Sprite;

import base.social.SinaWeibo;
import base.social.SocialMgr;
class LoadFriendsDlg extends ListDialog{

    var _friends:Hash<String>;
    var _followers:Hash<String>;
    var _bilateral:Array<String>;
    public function new ( mgr:ListDialogMgr, name:String, id:Int ){
        var str:String = name;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);
    }


    override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return ;

        _listDialogMgr.removeAllMovables();

        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        _bilateral = sina.getBilateral();
        if (_bilateral == null ){
            sina._sig.add( onLoadedFriends);
            sina.loadFriendsV1();
        }

        //trace( _bilateral);
        createBilateralDlg( _bilateral);

        _listDialogMgr.showListDialog();
        _mgr.hideListDialog();
    }

    function createBilateralDlg( bilateral:Array<String> ):Void{
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        for ( f in bilateral){
            var sn = sina.getScreenName(f);
            new SelectFansDlg( _listDialogMgr, f, sn);
        }
    }

    public function onLoadedFriends( msg:String, args:Array<Dynamic>, obj:Dynamic){
        if( msg == "OnDataAsJson"){
            var sina:SinaWeibo = cast obj;
            sina._sig.remove(onLoadedFriends);
            //trace( args[0] );
            _friends = hashString(args[0]);
            //trace("friends: " + Lambda.count(_friends));
            sina._sig.add( onLoadedFollowers);
            sina.loadFollowersV1();
        }
    }

    public function onLoadedFollowers( msg:String, args:Array<Dynamic>, obj:Dynamic){
        if( msg == "OnDataAsJson"){
            var sina:SinaWeibo = cast obj;
            sina._sig.remove(onLoadedFollowers);
            _followers = hashString(args[0]);
            var b = getBilateral();
            sina.refreshBilateral( b);
            _bilateral = b;
            //trace("Biteral: " + Lambda.count(res));
        }
    }

    public function getBilateral():Array<String>{
        var res = new Array<String>();

        var key = _friends.keys();
        while( key.hasNext() ){
            var k = key.next();
            var r = _followers.get( k );
            if ( r != null ){
                res.push(k);
            }
        }
        _followers = null;
        _friends = null;
        return res;
    }

    public function hashString( data:Dynamic):Hash<String>{
        //trace( data);
        //var json = hxjson2.JSON.decode( data);
        var ids:Array<String>=  data.ids;
        var d = new Hash<String>();
        for ( i in ids ){
            d.set( i, "");
        }
        return d;
    }
}

