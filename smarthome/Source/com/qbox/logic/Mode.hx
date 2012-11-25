package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;
class Mode{

    public var _id:Int;
    public function new(id:Int){
        _id = id;
    }

    public function close(){
    }

    public function load( data:String){
        var strarr = data.split( "%");
        for ( i in strarr){
            if( i.length > 3 && i.substr(0, 3)=="chn"){
                var chns = i.split("=");
                var noFound = false;
                for ( c in chns){
                    if ( c.length > 0){
                        var elems = c.split(":");
                        if (elems[0] == "chn" && elems[2].length > 0){
                            var datas = elems[2].split(",");
                            if ( datas[0].length > 0){

                            }
                        }
                    }
                }
            }
        }
    }

    public function save(){
        var sb = new StringBuf();
        var count:Int = 0;
        var cm = ChannelMgr.getInst().getChannelsWithOutRingPort();
        sb.add( "mode:"+_id+"%");
        for ( i in cm){
            sb.add( "chn:"+ count++ +":");
            var w = Std.string(i._w);
            var h = Std.string(i._h);
            sb.add ( i._screen._ipv4);
            sb.add( ',');
            sb.add ( i._inport);
            sb.add( ',');
            sb.add( w);
            sb.add( ',');
            sb.add( h);
            sb.add("=");
        }
        sb.add("%");

        var sm = ScreenMgr.getInst()._screens;
        count = 0;
        for( i in sm){
            sb.add("screen:"+count++ +":");
            sb.add(i._col);
            sb.add(",");
            sb.add(i._row);
            sb.add("=");
        }

        sb.add("%");

        var rm = RingMgr.getInst()._rings;
        count = 0;
        for ( r in rm){
            sb.add("ring:" + count++ + ":" );
            var hm = r._heads;
            for ( i in hm){
                var n:RingNode = i;
                while (n !=null ){
                    n = n._next[r._nodeIndex];
                    if ( n == i || n == null){
                        break;
                    }
                    if (  n._screen != null) {
                        sb.add( n._screen._ipv4);
                        sb.add(",");
                        sb.add(n._inport[r._nodeIndex]);
                        sb.add(",");
                        sb.add(n._outport[r._nodeIndex]);
                        sb.add(",");
                        sb.add(n._col);
                        sb.add(",");
                        sb.add(n._row);
                        sb.add("|");
                    }
                }
            }
            sb.add("=");
        }

        sb.add("%");

        var wm = WndMgr.getInst()._wnds;
        count = 0;
        for ( i in wm){
            sb.add("wnd:" + count++ + ":" );
            sb.add(i._virtualX);
            sb.add(",");
            sb.add(i._virtualY);
            sb.add(",");
            sb.add(i._virtualWidth);
            sb.add(",");
            sb.add(i._virtualHeight);
            sb.add(",");
            sb.add(i._virtualAreaX);
            sb.add(",");
            sb.add(i._virtualAreaY);
            sb.add(",");
            sb.add(i._virtualAreaW);
            sb.add(",");
            sb.add(i._virtualAreaH);
            sb.add("=");
        }
        sb.add("%");
        var data =  sb.toString();
        DataLoader.getInst().saveData( "mode"+_id, data);
    }
}
