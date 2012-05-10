package base.ui;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import nme.display.Sprite;

import com.eclecticdesignstudio.dialog.DialogManager;
import base.social.SocialMgr;
import nme.events.MouseEvent;

import base.social.SinaWeibo;
class SinaBinderDlg extends InputDialog{

    var _content:Sprite;
    public function new ( dm:ListDialogMgr):Void{
        _uniqueId = Type.getClassName( SinaBinderDlg);
        super(dm);
        resetDlgs();
    }

    public function resetDlgs():Void{
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        //trace(  Type.getClassName(base.social.SinaWeibo));
        var str= null;
        var dm:ListDialogMgr= cast _mgr;
        if ( sina != null && sina.isBound() ) {
            //str= "解除绑定新浪微博";
            str= "unbind sina weibo";
        }
        else{
            str= "bind sina weibo";
            //str= "绑定新浪微博";
        }
        if ( _content!= null && _content.parent != null ){
            _content.parent.removeChild(_content);
        }
        _content = CommDialogMgr.getElement( str, 0);
        addChild( _content);
    }

    override function onMouseClick():Void{
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        if ( sina != null && sina.isBound() ) {
            sina.unBound();
        }else{
            //SocialMgr.getInst().bindSina();
            sina._sig.add( onLogin);
            sina.login( false, null );
            //trace("bindSina");
        }
        resetDlgs();
    }
    public function onLogin( msg:String, args:Array<Dynamic>, obj:Dynamic){
        if( msg == "LoginSucceed"){
            resetDlgs();
        }else if( msg == "LoginFailed"){
        }else if( msg == "LoginRequirePin"){
            flashInput();
            cast(_mgr,ListDialogMgr).hideListDialog();
        }
        var sina:SinaWeibo = cast obj;
        sina._sig.remove(onLogin);
        trace(msg);
    }
    override function fireInput( data:String):Void{ 
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        sina._sig.add( onLogin);
        sina.login( false, data);
        swichBackToCMDView();
    }
}

class SocialBinderDlg extends ListDialog {

    var _binder:SinaBinderDlg;

    public function new ( mgr:ListDialogMgr){
        var str:String = "bind SNS";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super(  mgr);
        addChild(s);
        _binder = new SinaBinderDlg(  _listDialogMgr);
    }

    public function createDlgs():Void{
        //var sina= SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
        //var str:String = null;
        //if ( sina.isBound() == false ){
        //str= "绑定新浪微博";
        //}else{
        //str= "解除绑定新浪微博";
        //}
        //var id:Int = 0;
        //var s:Sprite = _listDialogMgr.createElement( str, id);
    }

    override function onMouseClick():Void{
        _binder.resetDlgs();
        super.onMouseClick();
    }
    //public function resetDlgs():Void{
    //createDlgs();
    //}

}
