package com.pictionary.ui;


import base.ui.ListDialog;
import base.ui.CommDialogMgr;
import base.ui.CommDialog;

class SubjectsDlg extends ListDialog{
    public function new ( dm:CommDialogMgr){
        super( dm);
        var str:String = "我画你猜";
        _uniqueId = str+0;
        var _content = dm.createElement( str, 0);
        addChild( _content);
        createDlgs();
    }

    public function createDlgs():Void{
        var cd = new DrawingDlg(_listDialogMgr, "心情涂鸦", 0);
        cd = new DrawingDlg(_listDialogMgr, "自描自在", 0);
        cd = new DrawingDlg(_listDialogMgr, "特发奇想", 0);
        cd = new DrawingDlg(_listDialogMgr, "网络迷局", 0);
        cd = new DrawingDlg(_listDialogMgr, "无拘无束", 0);
    }
}
