package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;
class Mode{

    public var _index:Int;
    public var _name:String;

    public function new(index:Int){
        _index = index;
    }

    public function close(){
    }

    public function hasData(){
        return  DataLoader.getInst().getData( "mode"+_index ) != null;
    }
    public function load():Bool{
        var data:String = DataLoader.getInst().getData( "mode"+_index );
        trace(data);

        if ( data == null) return false;
        //trace(data);
        var strarr = data.split( "%");
        var screens:Array<String> = null;
        var chns:Array<String> = null;
        var rings:Array<String> = null;
        var wnds:Array<String> = null;
        for ( i in strarr){
            if( i.length > 6 && i.substr(0, 6)=="screen"){
                screens = i.split("=");
            }
            if( i.length > 3 && i.substr(0, 3)=="chn"){
                chns = i.split("=");
            }
            if( i.length > 4 && i.substr(0, 4)=="ring"){
                rings = i.split("=");
            }
            if( i.length > 3 && i.substr(0, 3)=="wnd"){
                wnds = i.split("=");
            }
        }
        if ( screens != null && screens.length> 0){
            var keepscreens = new Array<Screen>();
            //create screens if not yet created!
            for ( s in screens){
                if ( s.length > 0){
                    var elems = s.split(":");
                    if (elems[0] == "screen" && elems[2].length > 0){
                        var datas = elems[2].split(",");
                        if ( datas[0].length > 0){
                            var ip:String = datas[0];
                            var col:Int = Std.parseInt(datas[1]);
                            var row:Int = Std.parseInt(datas[2]);
                            var rets = ScreenMgr.getInst().getScreen( col, row, ip);
                            if ( rets == null){
                                rets = ScreenMgr.getInst().createSpecificScreen( col, row, ip);
#if !neko
                                rets.connect();
#end
                            }
                            keepscreens.push(rets);
                        }
                    }
                }
            }
            //kill screens if not in file
            var removeScreens = new Array<Screen>();
            for ( s in ScreenMgr.getInst()._screens){
                var found = false;
                for ( ks in keepscreens){
                    if( ks._col == s._col && ks._row == s._row && ks._ipv4 == s._ipv4){
                        found = true;
                        break;
                    }
                }
                if ( !found){
                    removeScreens.push(s);
                }
            }
            for( s in removeScreens){
                s.close();
                ScreenMgr.getInst()._screens.remove(s);
            }

        }else{
            trace("has no screen!");
            return true;
        }

        if ( chns!= null && chns.length> 0){
            var noFound = false;
            for ( c in chns){
                if ( c.length > 0){
                    var elems = c.split(":");
                    if (elems[0] == "chn" && elems[2].length > 0){
                        var datas = elems[2].split(",");
                        if ( datas[0].length > 0){
                            var ip = datas[0];
                            var inport = datas[1];
                            var w = Std.parseInt(datas[2]);
                            var h = Std.parseInt(datas[3]);
                            var ret = ChannelMgr.getInst().hasChannel(ip, inport, w, h);
                            if ( !ret){
#if neko
                                var c = ChannelMgr.getInst().createChannel();
                                c._w = 1024;
                                c._h = 768;
                                c._screen = ScreenMgr.getInst()._screens[0];
                                c._inport = "3";
#else
                                trace("error: channel not found!");
#end
                            }
                        }
                    }
                }
            }
        }else{
#if neko
                                var c = ChannelMgr.getInst().createChannel();
                                c._w = 1024;
                                c._h = 768;
                                c._screen = ScreenMgr.getInst()._screens[0];
                                c._inport = "3";
#end
        }

        if ( rings != null && rings.length> 0){
            var count:Int = 0;
            for ( r in rings){
                if ( r.length > 0){
                    var elems = r.split(":");
                    if (elems[0] == "ring" && elems[2].length > 0){
                        var nodes = elems[2].split("|");
                        var preNode:RingNode = null;
                        for ( n in nodes){
                            if ( n.length > 0){
                                var datas = n.split(",");
                                var precol = datas[0];
                                var prerow = datas[1];
                                var nextcol = datas[2];
                                var nextrow = datas[3];
                                var col = Std.parseInt(datas[4]);
                                var row = Std.parseInt(datas[5]);
                                var rn = RingMgr.getInst().getRingNode(col, row);
                                if (rn == null){
                                    trace("error: RingNode not found! col:"+col+" row:"+row);
                                    return false;
                                }
                                if (precol != "null"){
                                    var pre = RingMgr.getInst().getRingNode(Std.parseInt(precol), Std.parseInt(prerow));
                                    rn._pre[count] = pre;
                                }
                                if ( nextcol != "null"){
                                    var next = RingMgr.getInst().getRingNode(Std.parseInt(nextcol),Std.parseInt(nextrow));
                                    rn._next[count] = next;
                                }
                            }
                        }
                    }
                    ++count;
                }
            }
        }

        if ( wnds != null && wnds.length> 0){
            for ( w in wnds){
                if ( w.length > 0){
                    var elems = w.split(":");
                    if ( elems[0] == "wnd" && elems[2].length > 0){
                        var datas = elems[2].split(",");
                        var x = Std.parseFloat(datas[0]);
                        var y = Std.parseFloat(datas[1]);
                        var w = Std.parseFloat(datas[2]);
                        var h = Std.parseFloat(datas[3]);
                        var ax = datas[4];
                        var ay = datas[5];
                        var aw = datas[6];
                        var ah = datas[7];
                        var layer = datas[8];
                        var cip = datas[9];
                        var cinport = datas[10];
                        var cw = datas[11];
                        var ch = datas[12];
                        var ringindex = datas[13];
                        var win = WndMgr.getInst().createWnd();

                        var channel = ChannelMgr.getInst().getChannel( cip, cinport, Std.parseInt(cw), Std.parseInt(ch) );
                        var ring:Ring = null;
                        if ( ringindex != "null"){
                            ring = RingMgr.getInst()._rings[ Std.parseInt(ringindex)];
                        }

                        win._layer = Std.parseInt(layer);

                        win._virtualAreaX = Std.parseFloat(ax);
                        win._virtualAreaY = Std.parseFloat(ay);
                        win._virtualAreaW = Std.parseFloat(aw);
                        win._virtualAreaH = Std.parseFloat(ah);

                        win.open( x, y, w, h, channel, ring);
                    }
                }
            }
        }
        return true;
    }

    public function save(){
        var sb = new StringBuf();
        var count:Int = 0;
        var cm = ChannelMgr.getInst().getChannelsWithOutRingPort();
        sb.add( "mode:"+_index+"%");
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
            sb.add( i._ipv4);
            sb.add(",");
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
                    if (  n._screen != null) {
                        if (n._pre[r._nodeIndex] == null){
                            sb.add( "null");
                            sb.add( ",");
                            sb.add( "null");
                        }
                        else {
                            sb.add( n._pre[r._nodeIndex]._col);
                            sb.add( ",");
                            sb.add( n._pre[r._nodeIndex]._row);
                        }
                        sb.add(",");
                        if (n._next[r._nodeIndex] == null){
                            sb.add( "null");
                            sb.add( ",");
                            sb.add( "null");
                        }
                        else {
                            sb.add( n._next[r._nodeIndex]._col);
                            sb.add( ",");
                            sb.add( n._next[r._nodeIndex]._row);
                        }
                        sb.add(",");
                        sb.add(n._col);
                        sb.add(",");
                        sb.add(n._row);
                        sb.add("|");
                    }
                    n = n._next[r._nodeIndex];
                    if ( n == i ){ break; }
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
            sb.add(",");
            sb.add(i._layer);
            sb.add(",");
            sb.add(i._channel._screen._ipv4);
            sb.add(",");
            sb.add(i._channel._inport);
            sb.add(",");
            sb.add(i._channel._w);
            sb.add(",");
            sb.add(i._channel._h);
            sb.add(",");
            if ( i._ring == null){
                sb.add("null");
            }
            else{ 
                sb.add(i._ring._nodeIndex);
            }
            sb.add("=");
        }
        sb.add("%");
        var data =  sb.toString();
        DataLoader.getInst().saveData( "mode"+_index, data);
    }
}
