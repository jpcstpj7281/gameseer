package com.qbox.ui;

import base.ui.FixedDlg;
import nme.events.MouseEvent;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.logic.ChannelMgr;
import com.qbox.logic.WndMgr;
import com.qbox.logic.RingMgr;
import com.qbox.logic.Ring;
import com.qbox.logic.Screen;



class ScreenFlag{
    public var isSelected:Bool;
    public var screen:Screen;
    public var inputCount:Int;
    static public var InportNum = 6;
    public function new ( s:Screen){ screen = s;isSelected= false;inputCount = 0;}
}

class RingsPlate extends CommDialog{

    var _screens:Sprite;
    var _wnds:Sprite;
    var _isDown:Bool;
    var _downx:Int;
    var _downy:Int;
    var _movex:Int;
    var _movey:Int;

    var _RingWidth:Float;
    var _RingHeight:Float;

    var _currRing:Ring;
    var _screenFlags:Array<ScreenFlag>;
    var _preFlag:ScreenFlag;

    var _rs:Array<RingSelectDlg>;

    public function new ( dm:CommDialogMgr ){
        super(dm);

        _screens = new Sprite();
        _wnds = new Sprite();
        addChild(_screens);
        addChild(_wnds);
        _isDown = false;
        //_isClose= false;
        _downx = 0;
        _downy = 0;
        _rs = new Array<RingSelectDlg>();
        _rs.push(new RingSelectDlg( dm, RingMgr.getInst()._rings[0], 0, cbChangedCurrRing));
        _rs.push( new RingSelectDlg( dm, RingMgr.getInst()._rings[1], 1, cbChangedCurrRing));
    }

    function cbChangedCurrRing(r:Ring){
        for ( i in _rs){
            i.unselected();
        }
        _currRing = r;
        if ( _preFlag != null) _preFlag.isSelected = false;
        _preFlag = null;

        createRing(r);
    }

    function createRing( ring:Ring){
        var col = ScreenMgr.getInst()._col;
        var row = ScreenMgr.getInst()._row;
        if ( col == 0 && row == 0 ) {
            return;
        }
        var sw = ScreenMgr.getInst()._virtualWidth/col;
        var sh = ScreenMgr.getInst()._virtualHeight/row;

        _RingWidth = sw;
        _RingHeight= sh;

        if (_screens.parent != null) removeChild(_screens);
        _screens = new Sprite();
        addChildAt( _screens, 0);
        for ( flag in _screenFlags){
            var i = flag.screen;
            var s = new Sprite();
            //i._virtualHeight = cast _RingHeight;
            //i._virtualWidth = cast _RingWidth;

            if ( ring != null){
                var node = RingMgr.getInst().getRingNode( i._col, i._row);
                if ( node != null){
                    var next = node._next[ring._nodeIndex];
                    var pre = node._pre[ring._nodeIndex];
                    if (next !=null){
                        if ( next._col > node._col && next._row == node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.75) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth-10, (i._row+0.5) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col+1) * _RingWidth-10, (i._row+0.5) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+0.5) * _RingHeight );

                        }else if ( next._col == node._col && next._row > node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.75) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row+1) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth+10, (i._row+1) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth-10, (i._row+1) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row+1) * _RingHeight );
                            //s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row+1+0.25) * _RingHeight );
                        }else if ( next._col < node._col && next._row == node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.25) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth+10, (i._row+0.5) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col) * _RingWidth+10, (i._row+0.5) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row+0.5) * _RingHeight );
                        }else if ( next._col == node._col && next._row < node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.25) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth-10, (i._row) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth+10, (i._row) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row) * _RingHeight );
                        }else if ( next._col > node._col && next._row > node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+1) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+1) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col+1) * _RingWidth-10, (i._row+1) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+1) * _RingHeight );
                        }else if ( next._col < node._col && next._row < node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col) * _RingWidth+10, (i._row) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row) * _RingHeight );
                        }else if ( next._col > node._col && next._row < node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row) * _RingHeight+10 );
                            s.graphics.lineTo( (i._col+1) * _RingWidth-10, (i._row) * _RingHeight );
                            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row) * _RingHeight );
                        }else if ( next._col < node._col && next._row > node._row){ 
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row+1) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row+1) * _RingHeight-10 );
                            s.graphics.lineTo( (i._col) * _RingWidth+10, (i._row+1) * _RingHeight );
                            s.graphics.lineTo( (i._col) * _RingWidth, (i._row+1) * _RingHeight );
                        }
                    }
                    if (pre!=null){
                        if ( pre._col < node._col && pre._row == node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.25) * _RingWidth, (i._row+0.5) * _RingHeight );
                        }
                        if ( pre._col > node._col && pre._row == node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+1) * _RingWidth, (i._row+0.5) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.75) * _RingWidth, (i._row+0.5) * _RingHeight );
                        }
                        if ( pre._col == node._col && pre._row < node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.25) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row) * _RingHeight );
                        }
                        if ( pre._col == node._col && pre._row > node._row){
                            s.graphics.lineStyle( 2, 0x00FF00, 1 );
                            s.graphics.moveTo( (i._col+0.5) * _RingWidth, (i._row+0.75) * _RingHeight );
                            s.graphics.lineTo( (i._col+0.5) * _RingWidth, (i._row+1) * _RingHeight );
                        }
                    }
                }
            }

            s.graphics.lineStyle( 1, 0x000000, 1);
            s.graphics.moveTo( i._col * _RingWidth, i._row * _RingHeight );
            s.graphics.lineTo( (i._col+1) * _RingWidth, i._row * _RingHeight );
            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+1) * _RingHeight );
            s.graphics.lineTo( i._col * _RingWidth, (i._row+1) * _RingHeight );
            s.graphics.beginFill(0x888888);
            //s.graphics.drawRect( (i._col+0.5) * _RingWidth, i._row * _RingHeight, _RingWidth*0.5, _RingHeight);
            s.graphics.drawRect( (i._col+0.25) * _RingWidth, (i._row+0.25) * _RingHeight, _RingWidth*0.5, _RingHeight*0.5);
            
            if ( ring != null){
                for ( it in 0...6){
                    var portstring = "" + (it +1);
                    if ( portstring == flag.screen._ringNode._inport[ring._nodeIndex] ){
                        s.graphics.beginFill(0x00FF00);
                        s.graphics.drawRect( (i._col+0.25) * _RingWidth, (i._row+0.25) * _RingHeight + _RingHeight /12 * it , _RingHeight /16, _RingHeight /16);
                    }else{
                        s.graphics.beginFill(0x0000FF);
                        s.graphics.drawRect( (i._col+0.25) * _RingWidth, (i._row+0.25) * _RingHeight + _RingHeight /12 * it , _RingHeight /16, _RingHeight /16);
                    }
                }
                for ( it in 0...2){
                    var portstring = "" + (it +3);
                    if ( portstring == flag.screen._ringNode._outport[ring._nodeIndex] ){
                        s.graphics.beginFill(0x00FF00);
                        s.graphics.drawRect( (i._col+0.75) * _RingWidth, (i._row+0.25) * _RingHeight + _RingHeight /12 * it , _RingHeight /16, _RingHeight /16);
                    }else{
                        s.graphics.beginFill(0x0000FF);
                        s.graphics.drawRect( (i._col+0.75) * _RingWidth, (i._row+0.25) * _RingHeight + _RingHeight /12 * it , _RingHeight /16, _RingHeight /16);
                    }
                }
            }

            if ( flag.isSelected== true){
                s.graphics.beginFill(0x333333, 0.5);
                s.graphics.drawRect( (i._col) * _RingWidth, (i._row) * _RingHeight, _RingWidth, _RingHeight);
            }
            _screens.addChild(s);

        }

        _screens.x = Math.round( (width - _screens.width) /2);
        //_screens.x = ScreenMgr.getInst()._virtualX;
        //ScreenMgr.getInst()._virtualX= cast _screens.x;
        //ScreenMgr.getInst()._virtualY= cast _screens.y;

    }

    function createWnds(){
        var ms = cast(_mgr, ListDialogMgr)._movableInstances;
        if ( ms.length > 0 ){
            var m = ms[0];
            var p = m.parent;
            var arr = new Array<WndGraphicDlg>();
            for ( i in 0...p.numChildren){
                var w = p.getChildAt( p.numChildren - i -1 );
                if ( Std.is(w, WndGraphicDlg) ){
                    var wgd:WndGraphicDlg = cast( w, WndGraphicDlg);
                    arr.push(wgd);
                }
            }
            for ( i in arr){
                i.clear();
            }
        }
        for ( i in WndMgr.getInst()._wnds){
            trace("create wnd");
            var win = new WndGraphicDlg(_mgr);
            win.resurrectWnd(i);
            win.show();
        }
    }

    override function show(){
        //trace("Test");
        _screenFlags = new Array<ScreenFlag>();
        for ( i in ScreenMgr.getInst()._screens){
            _screenFlags.push( new ScreenFlag(i));
        }

        if (_currRing == null){
            _currRing = RingMgr.getInst()._rings[0];
        }

        if ( _rs[_currRing._nodeIndex]._isSelected){
            createRing(_currRing);
        }else{
            _rs[_currRing._nodeIndex].selected();
        }

        //createWnds();

        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onThisMouseDown);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onThisMouseMove);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onThisMouseUp);

        return super.show();
    }

    override function hide(){
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onThisMouseDown);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onThisMouseMove);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onThisMouseUp);
        if ( _screens != null && _screens.parent != null) removeChild(_screens);


        //trace("test============================================================================================");
        RingMgr.getInst().setupAllRing();
        return super.hide();
    }

    function onThisMouseDown( evt:MouseEvent ):Void{
        var ms = cast(_mgr, ListDialogMgr)._movableInstances;
        if ( ms.length > 0 ){
        }
        if ( _screens.hitTestPoint( evt.stageX, evt.stageY)){
            //screen plate has been clicked.
            _isDown = true;
            _downx = cast evt.stageX;
            _downy = cast evt.stageY;

        }
    }
    function onThisMouseMove( evt:MouseEvent ):Void{ 
        if ( _isDown){
        }
    }

    function getScreenFlag( col:Int, row:Int):ScreenFlag{
        for ( i in _screenFlags){
            if ( i.screen._col == col && i.screen._row == row){
                return i;
            }
        }
        return null;
    }
    function onThisMouseUp( evt:MouseEvent ):Void{ 
        if ( _isDown ){
            if ( _currRing != null && evt.stageX > _downx -5 && evt.stageX < _downx +5 && evt.stageY > _downy-5 && evt.stageY < _downy +5){
                var col = Std.int(_downx / _RingWidth);
                var row = Std.int(_downy / _RingHeight);
                var flag = getScreenFlag( col, row);
                if ( flag != null){
                    if (_preFlag == flag){
                        ++flag.inputCount;
                        if ( flag.inputCount >= ScreenFlag.InportNum){
                            flag.inputCount = 0;
                        }
                        flag.screen._ringNode._inport[_currRing._nodeIndex] = ""+ (flag.inputCount +1);
                        //flag.isSelected = false;
                        var tmp = _preFlag.screen._ringNode._next[ _currRing._nodeIndex];
                        if ( tmp != null && tmp._pre[_currRing._nodeIndex] != null){
                            tmp._pre[_currRing._nodeIndex] = null;
                        }
                    }else if( _preFlag == null){
                        flag.isSelected= true;
                        flag.inputCount = Std.parseInt(flag.screen._ringNode._inport[_currRing._nodeIndex]) -1;
                        _preFlag = flag;
                    }
                    else{
                        if (_preFlag.isSelected ) _preFlag.isSelected = false;
                        //_preFlag.inputCount = 0;
                        flag.isSelected = true;
                        ++flag.inputCount;
                        flag.inputCount = Std.parseInt(flag.screen._ringNode._inport[_currRing._nodeIndex]) -1;
                        //flag.screen._ringNode._inport[ _currRing._nodeIndex] = ""+(flag.inputCount+1);
                        var tmp = _preFlag.screen._ringNode._next[ _currRing._nodeIndex];
                        if ( tmp != null && tmp._pre[_currRing._nodeIndex] != null){
                            tmp._pre[_currRing._nodeIndex] = null;
                        }
                        _preFlag.screen._ringNode._next[ _currRing._nodeIndex] = flag.screen._ringNode;
                        tmp = flag.screen._ringNode._pre[_currRing._nodeIndex];
                        if( tmp != null && tmp._next[_currRing._nodeIndex] != null){
                            tmp._next[_currRing._nodeIndex] = null;
                        }
                        flag.screen._ringNode._pre[_currRing._nodeIndex] = _preFlag.screen._ringNode;
                        if( !_currRing.isInRing( _preFlag.screen)){
                            _currRing.newHead( _preFlag.screen._ringNode);
                        }

                        //trace( flag.screen._col);
                        //trace( flag.screen._row);
                        //trace( _preFlag.screen._col);
                        //trace( _preFlag.screen._row);
                        _preFlag = flag;

                    }
                    createRing( _currRing);
                }else{
                    _preFlag = flag;
                }
            }
        }
        _isDown = false;
        _downx = 0;
        _downy = 0;
        //_isClose = false;
    }
}
