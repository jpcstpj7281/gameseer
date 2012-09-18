package base.ui;


import nme.Assets;
import nme.text.TextField;
import base.data.DataLoader;


class EmbedTextField extends TextField {
    public function new (){

        super();
#if (android||neko)
        //if( Sys.systemName() == "Linux" ){
            if ( DataLoader.inst.textFormat_ != null){
                defaultTextFormat = DataLoader.inst.textFormat_;
                embedFonts = true;
            }
            //}
            //}
#end
    }

    public function setBorder( flag:Bool):Void{

#if neko border = flag; #end
#if android
        border = flag;
#elseif cpp
        if( Sys.systemName() != "Linux" ){
            border = flag;
        }
#end
    }

}
