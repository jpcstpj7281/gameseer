package base.state;

import base.data.DataLoader;

class LoadDataState extends State{


    public function new( ){
        super("LoadDataState");
    }

    override function fromState(s:State):Void{
        DataLoader.getInst().loadAssets(null);
    }


    override function run():Bool{
        return !(DataLoader.getInst().loadcouter_ == DataLoader.getInst().totalItem_);
    }

    override function toState(s:State):Void{
    }
    
}
