package base.ui;

import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;
import com.eclecticdesignstudio.dialog.events.DialogEvent;
import com.eclecticdesignstudio.motion.Actuate;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class ComponentDlgMgr extends CommDialogMgr{

    var _downy:Float;
    var _downx:Float;
    var _movey:Float;
    var _movex:Float;

    var _oldx:Float;
    var _oldy:Float;

    var _isDown:Bool;

    var _view:Sprite;
    var _returnParent:Sprite;
    public var _returnCallback:Dynamic;

    var _edit:Sprite;
    var _page:ComponentPageView;
    var _isFixed:Bool;

    var _pressTime:Float;
    var RightEdge:Float ;
    var LeftEdge:Float ;

    public function new (droppoint:Sprite ){
        _view= new Sprite();
        droppoint.addChild(_view);
        super( _view);

        RightEdge= nme.Lib.current.stage.stageWidth - 50;
        //trace("RightEdge: "+RightEdge);
        LeftEdge= 50;
        //trace("LeftEdge: "+LeftEdge);


        _oldx = _view.x;
        _oldy = _view.y;
        _isDown = false;
        _returnParent = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("btn_return"));
        _returnParent.addChild( bm);
        _returnParent.x = nme.Lib.current.stage.stageWidth - 80;
        _returnParent.y= nme.Lib.current.stage.stageHeight - 80;
        _returnParent.addEventListener( MouseEvent.CLICK, onClickReturn);

        _edit = new Sprite();
        bm= new Bitmap( DataLoader.getInst().bms_.get("btn_edit"));
        _edit.addChild( bm);
        _edit.x = nme.Lib.current.stage.stageWidth - 160;
        _edit.y= nme.Lib.current.stage.stageHeight - 80;
        _edit.addEventListener( MouseEvent.CLICK, onClickEdit);
        _isFixed = true;


        _page = new ComponentPageView();
    }

    public function showListDialog():Void{
        if ( getInstancesByDisplayOrder() != null ){
            setAnimationNum(getInstancesByDisplayOrder().length);
            var c:Int = 0;
            for ( i in getInstancesByDisplayOrder()){
                ++c;
                i.show().delay(0.05 * c).onComplete( decreaseAnimationNum, []);

                var row = (c-1) % 5;
#if flash
                i.y=  i.height*(row);
                var page:Int = Std.int( c / 5 );
                i.x=  nme.Lib.current.stage.stageWidth * page /4;
#else
                i.y=  i.height*i.scaleY *(row);
                var page:Int = Std.int( c/ 5 );
                i.x=  nme.Lib.current.stage.stageWidth * page /4;
#end
            }
        }
        _isDown = false;
        if ( _returnParent.parent == null ) {
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            nme.Lib.current.stage.addEventListener( Event.ENTER_FRAME , onEnterFrame);
            nme.Lib.current.addChild(_returnParent);
            nme.Lib.current.addChild(_edit);
            nme.Lib.current.addChild(_page);
        }
        _isFixed = true;
        //fixedDialog(_isFixed);
    }
    public function hideListDialog( ):Void{
        for ( i in getInstancesByDisplayOrder()){
            i.hide();
        }
        _isDown = false;
        if ( _returnParent.parent != null ) {
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            nme.Lib.current.stage.removeEventListener( Event.ENTER_FRAME, onEnterFrame);
            nme.Lib.current.removeChild(_returnParent);
            nme.Lib.current.removeChild(_edit);
            nme.Lib.current.removeChild(_page);
        }
    }
    public override function clear():Void{
        hideListDialog();
        super.clear();
        _returnParent = null;
        _returnCallback = null;
        _edit = null;
    }
    public function onMouseDown(evt:MouseEvent){ 
        //trace( "ComponentDlgMgr onMouseDown");
        if ( isAnimating()  ) return;
        _downx = evt.stageX;
        _downy = evt.stageY;
        _movex= 0;
        _movey= 0;
        _isDown = true;
        if ( !_isFixed  ){
            _pressTime = 0;
        }
    }
    public function onMouseMove(evt:MouseEvent){ 
        if ( _isDown){
            if ( _isFixed   ){
                if ( ( evt.stageX < 0 || evt.stageX > nme.Lib.current.stage.stageWidth || evt.stageY < 0 || evt.stageY > nme.Lib.current.stage.stageHeight ) ){
                    onMouseUp(evt); 
                }
                else{
                    _oldx = _movex;
                    _movex = evt.stageX - _downx;
                    switchListDialog( );
                }
            }
            else {
                if ( ( evt.stageX < 0 || evt.stageX > nme.Lib.current.stage.stageWidth || evt.stageY < 0 || evt.stageY > nme.Lib.current.stage.stageHeight ) ){
                    onMouseUp(evt); 
                }
                else if ( !_isFixed  && _isDown){
                    if ( evt.stageX <= LeftEdge && _pressTime ==0){
                        _pressTime = Timer.stamp();
                        _movex = nme.Lib.current.stage.stageWidth;
                        trace( "left: "+ _movex );
                    }
                    else if ( evt.stageX >= RightEdge && _pressTime == 0){
                        _pressTime = Timer.stamp();
                        _movex = -nme.Lib.current.stage.stageWidth;
                        trace( "right: "+ _movex );
                    }
                    else if ( _pressTime > 0 ){
                        if ( evt.stageX > LeftEdge && _movex > 0 ){
                            trace( "reset!" );
                            _pressTime = 0;
                        }
                        else if ( evt.stageX < RightEdge && _movex < 0 ){
                            trace( "reset!" );
                            _pressTime = 0;
                        }
                    }
                    //if( _pressTime > 0 && Timer.stamp() - _pressTime  > 3){
                    //trace( "move: "+ _movex );
                    //_oldx = 0;
                    //_pressTime = 0;
                    //switchListDialog();
                    //}
                } 
            }
        }
    }
    public function onEnterFrame(evt:Event){
        if( !_isFixed && _isDown && _pressTime > 0 && Timer.stamp() - _pressTime  > 2){
            trace( "move: "+ _movex );
            switchListDialog();
            _oldx = 0;
            _movex = 0;
            _pressTime = 0;
        }
    }
    public function onMouseUp(evt:MouseEvent){ 
        if ( _isDown){
            if( getInstancesByDisplayOrder().length > 0 && (evt.stageY - _downy) <50 && (evt.stageY - _downy ) > -50  && (evt.stageX - _downx) < 50 && (evt.stageX - _downx ) > -50 ){
                for ( i in getInstancesByDisplayOrder()){
                    if( i.hitTestPoint(_downx, _downy) ) {
                        i.onMouseClick();
                        _isDown = false;
                        return;
                    }
                }
            }else{

                var x:Float, y:Float;
                if ( evt.stageX < 0 ){ x = 0; }else x = evt.stageX;
                if ( evt.stageY < 0 ){ y = 0; }else y = evt.stageY;
                if ( evt.stageX > nme.Lib.current.stage.stageWidth ){ x = nme.Lib.current.stage.stageWidth; }else x = evt.stageX;
                if ( evt.stageY > nme.Lib.current.stage.stageHeight){ y = nme.Lib.current.stage.stageHeight; }else y = evt.stageY;

                trace( "x: "+x);
                if ( _isFixed  ){
                    if ( (x - _downx <200 && x - _downx  > 0 ) || (x- _downx > -200 && x - _downx < -0 ) ){
                        _oldx = _movex;
                        _movex = 0;
                        trace( "_movex: "+_movex);
                    }
                    else if ( x- _downx <= -200 ){
                        _oldx = _movex;
                        _movex = -nme.Lib.current.stage.stageWidth;
                        trace( "_movex: "+_movex);
                    }
                    else if ( x- _downx  >= 200  ){
                        _oldx = _movex;
                        _movex = nme.Lib.current.stage.stageWidth;
                        trace( "_movex: "+_movex);
                    }
                    switchListDialog( );
                }
                else if ( !_isFixed  ){
                }
            }
        }
        _downx = 10000;
        _downy = 10000;
        _isDown = false;
        _movex = 0;
        _oldx = 0;
    }


    public function switchListDialog():Void{
        if ( isAnimating() ){ return; }

        if ( _movex == -nme.Lib.current.stage.stageWidth || _movex == nme.Lib.current.stage.stageWidth ){
            setAnimationNum( getInstancesByDisplayOrder().length);

            if ( _movex > 0 && _page.hasPrePage() == false){
                _movex = 0;
                trace( "no pre page");
            }else if ( _movex < 0 && _page.hasNextPage() == false){
                _movex = 0;
                trace( "no next page");
            }else {
                if (_movex > 0 ) _page.prePage();
                else if (_movex < 0 ) _page.nextPage();
                trace("move page: " +_movex);
            }
            for ( i in getInstancesByDisplayOrder()){
                var c:ComponentDlg= cast(i);
                if (c._isDown == false) { 
                    Actuate.tween (i, 0.5, { x: (i.x  -_oldx + _movex) } ).onComplete( decreaseAnimationNum, []);
                }else{
                    decreaseAnimationNum();
                }
            }
        }
        else for ( i in getInstancesByDisplayOrder()){
            i.x += -_oldx +_movex;
        }
    }

    //public function fixedDialog( flag:Bool){
    //if( flag){
    //for ( i in getInstancesByDisplayOrder()){
    //i.dialogData.type = DialogType.FIXED;
    //}
    //}else{
    //for ( i in getInstancesByDisplayOrder()){
    //i.dialogData.type = DialogType.DRAGGABLE;
    //}
    //}
    //}

    public function onClickEdit( evt:MouseEvent):Void{
        _isFixed = !_isFixed;
        //fixedDialog( _isFixed);
    }

    public function createListDialogData( displayObj:Sprite, name:String): DialogData{
        var dd:DialogData = new DialogData(displayObj, name);
        var row = getInstancesByDisplayOrder().length % 5;
#if flash
        dd.alignOffsetY = displayObj.height/2 + displayObj.height*(row);
        var page:Int = Std.int(getInstancesByDisplayOrder().length / 5 );
        dd.alignOffsetX = displayObj.width /2 + nme.Lib.current.stage.stageWidth * page /4;
#else
        dd.alignOffsetY = displayObj.height* displayObj.scaleY/2 + displayObj.height*displayObj.scaleY *(row);
        var page:Int = Std.int(getInstancesByDisplayOrder().length / 5 );
        dd.alignOffsetX = displayObj.width * displayObj.scaleX /2 + nme.Lib.current.stage.stageWidth * page /4;
#end
        dd.fadeInTime = 0.5;
        dd.fadeOutTime = 0 ;
        return dd;
    }

    override function createElement(name:String, id:Int):Sprite{
        var scale:Int = 3;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("cmd") );
        bm.height = nme.Lib.current.stage.stageHeight/10;

        //s.addChild( txt1);
        //var w:Float = nme.Lib.current.stage.stageWidth / txt.width;
        //s.width=  nme.Lib.current.stage.stageWidth;
        //s.height = nme.Lib.current.stage.stageHeight/10;
        //txt.scaleY = 2;

        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = scale;
        txt.scaleY = scale;
        //txt.x = 220;
        txt.y = 80;
        txt.width = nme.Lib.current.stage.stageWidth/13;
        txt.height = nme.Lib.current.stage.stageHeight/10/scale/2;
        //txt.setBorder(true);
        txt.selectable = false;


        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt);
        return s;
    }

    public function onClickReturn( evt:MouseEvent) :Void{
        if ( _returnCallback != null ){
            _returnCallback();
        }
        hideListDialog();
    }
}
