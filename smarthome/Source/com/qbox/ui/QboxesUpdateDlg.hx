package com.qbox.ui;

import com.qbox.logic.ScreenMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.CommDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;

#if neko
import neko.FileSystem;
#else
import cpp.FileSystem;
#end

class QboxesUpdateDlg extends ListDialog{
    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild(createElement());
    }

    var _g:Sprite;
    var _v:EmbedTextField;
    override function show(){
        if ( _g != null) {
            if ( _v!= null){ _g.removeChild(_v); }

            _v= new EmbedTextField();
            _v.selectable = false;
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = nme.Lib.current.stage.stageWidth /3;
            _v.height= 16;
            _g.addChild( _v);

#if !neko
            _v.text = "Qbox系统: " ;
#else
            _v.text = "Qbox System Version: " ;
#end
            _g.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null ) {
            _g.removeChild(_v);
            _v = null;
            //_listDialogMgr.removeAllMovables();
        }
        return super.hide();
    }
    public function createElement():Sprite{
        _g = new Sprite();
        _g.height = nme.Lib.current.stage.stageHeight/15;
        return _g;
    }
    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            var dirs = new Array<String>();
            if(FileSystem.exists(QboxUpdateDlg.DIR)){
                var arr = FileSystem.readDirectory(QboxUpdateDlg.DIR);
                for( i in arr){
                    if ( !FileSystem.isDirectory( QboxUpdateDlg.DIR+"/"+i) ){
                        dirs.push(i);
                    }
                }
            }

            for ( q in ScreenMgr.getInst()._qboxes ){
                new QboxUpdateDlg(_listDialogMgr, q, dirs);
            }

        }
        super.onMouseClick();
    }
}
