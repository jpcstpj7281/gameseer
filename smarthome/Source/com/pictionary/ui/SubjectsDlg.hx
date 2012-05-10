package com.pictionary.ui;


import base.ui.ListDialog;
import base.ui.CommDialogMgr;
import base.ui.CommDialog;

class SubjectsDlg extends ListDialog{
    public function new ( dm:CommDialogMgr){
        super( dm);
        //var str:String = "我画你猜";
        var str:String = "draw subjects";
        _uniqueId = str+0;
        var _content = dm.createElement( str, 0);
        addChild( _content);
    }

    override function onMouseClick(){
        if( _listDialogMgr._movableInstances.length == 0){
            createDlgs();
        }
        super.onMouseClick();
    }

    public function createDlgs():Void{
        //var cd = new DrawingDlg(_listDialogMgr, "心情涂鸦", 0);
        //cd = new DrawingDlg(_listDialogMgr, "自描自在", 0);
        //cd = new DrawingDlg(_listDialogMgr, "特发奇想", 0);
        //cd = new DrawingDlg(_listDialogMgr, "网络迷局", 0);
        //cd = new DrawingDlg(_listDialogMgr, "无拘无束", 0);
        var cd = new DrawingDlg(_listDialogMgr, "draw with feeling", 0);
        cd = new DrawingDlg(_listDialogMgr, "draw my location", 0);
        cd = new DrawingDlg(_listDialogMgr, "wild mind", 0);
        cd = new DrawingDlg(_listDialogMgr, "network riddle", 0);
        cd = new DrawingDlg(_listDialogMgr, "free draw", 0);
    }
}
