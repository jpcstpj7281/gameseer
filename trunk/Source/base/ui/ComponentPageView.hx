package base.ui;


import base.data.DataLoader;

import nme.display.Bitmap;
import nme.display.Sprite;

class ComponentPageView extends Sprite{

    var _curDot:Sprite;
    var _cur:Int;

    var _allDots:Array<Sprite>;

    public function new (){
        super();

        _allDots = new Array<Sprite>();

        _cur = 0;
        _curDot = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("bluedot"));
        _curDot.addChild( bm);

        var orangedot:Sprite;
        for( i in 0...5){
            bm= new Bitmap( DataLoader.getInst().bms_.get("orangedot"));
            orangedot= new Sprite();
            _allDots.push( orangedot);
            orangedot.addChild(bm);
            orangedot.x = nme.Lib.current.stage.stageWidth - 300 + 20 * i;
            orangedot.y= nme.Lib.current.stage.stageHeight - 100;
            addChild(orangedot);
        }
        //orangedot.addChild( bm);
        //orangedot.x = nme.Lib.current.stage.stageWidth - 240;
        //orangedot.y= nme.Lib.current.stage.stageHeight - 100;

        addChild(_curDot);

        _curDot.x = _allDots[_cur].x;
        _curDot.y = _allDots[_cur].y;
    }

    public function hasNextPage():Bool{ 
        if ( _cur >= 4){
            return false;
        }
        return true; 
    }
    public function hasPrePage():Bool{ 
        if ( _cur <= 0){
            return false;
        }
        return true; 
    }
    public function nextPage():Bool{ 
        if ( hasNextPage() ){
            _curDot.x = _allDots[++_cur].x;
            return true;
        }
        return false; 
    }
    public function prePage():Bool{ 
        if ( hasPrePage()){
            _curDot.x = _allDots[--_cur].x;
            return true;
        }
        return false; 
    }
    public function toPage( num:Int):Bool{
        if ( num <0 || num >=5){
            return false;
        }
        _cur = num;
        _curDot.x = _allDots[--_cur].x;
        return true;
    }
    public function currPage( ):Int{ return _cur; }

}
