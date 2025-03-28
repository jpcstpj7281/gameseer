package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;
class Mode{

    public var _index:Int;
    public var _name:String;

    public var _cbDone:Void->Void;
    public var _currLoadWnds:Array<Wnd>;
    public var _currLoadScreens:Array<Screen>;
    public var _isLoading:Bool;

    var screens:Array<String> ;
    var chns:Array<String> ;
    var rings:Array<String> ;
    var wnds:Array<String> ;
    public function new(index:Int){
        _index = index;
        screens = null;
        chns = null;
        rings = null;
        wnds = null;
        _isLoading = false;
    }

    public function hasData(){
        return  DataLoader.getInst().getData( "mode"+_index ) != null;
    }

    public function cbLoad():Void{
        _currLoadWnds = new Array<Wnd>();
        _currLoadScreens = new Array<Screen>();
        var data:String = DataLoader.getInst().getData( "mode"+_index );
        trace(data);

        if ( data != null) {
            //trace(data);
            var strarr = data.split( "%");
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
                            var rets = ScreenMgr.getInst().getScreen( col, row);
                            if ( rets == null){
                                rets = ScreenMgr.getInst().createSpecificScreen( col, row, ip);

                                _currLoadScreens.push(rets);
                                //#if !neko
                                //rets.connect();
                                //rets.connectedInit(onLoadingScreens);
                                //#end
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
                    if( ks._col == s._col && ks._row == s._row ){
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
        }
        onLoadingScreens();
    }

    public function load( cbDone:Void->Void ):Bool{
        if ( _isLoading ) {trace("mode possessd!"); return false;}
        _isLoading = true;
        _cbDone = cbDone;

        if ( WndMgr.getInst()._wnds.length > 0){
            WndMgr.getInst().closeAll( cbLoad);
        }else{
            cbLoad();
        }
        return true;
    }

    public function onAfterLoadScreens():Void{

        if ( chns!= null && chns.length> 0){
            var noFound = false;
            for ( c in chns){
                if ( c.length > 0){
                    var elems = c.split(":");
                    if (elems[0] == "chn" && elems[2].length > 0){
                        var datas = elems[2].split(",");
                        if ( datas[0].length > 0){
                            var ip = datas[0];
                            var col = Std.parseInt(datas[1]);
                            var row = Std.parseInt(datas[2]);
                            var inport = datas[3];
                            var w = Std.parseInt(datas[4]);
                            var h = Std.parseInt(datas[5]);
                            var ret = ChannelMgr.getInst().hasChannel(ip, inport, w, h, col, row);
                            if ( !ret){
                                var c = ChannelMgr.getInst().createChannel();
                                c._w = w;
                                c._h = h;
                                c._screen = ScreenMgr.getInst().getScreen(col, row);
                                c._inport = inport;
                            }
                        }
                    }
                }
            }
        }else{
#if neko
            if ( ChannelMgr.getInst()._channels.length == 0){
                trace("create neko virtual channel");
                var c = ChannelMgr.getInst().createChannel();
                c._w = 1024;
                c._h = 768;
                c._screen = ScreenMgr.getInst()._screens[0];
                c._inport = "3";
            }
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
                        var isHead = true;
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
                                }
                                if ( isHead) {
                                    //the first node have to be head!
                                    RingMgr.getInst()._rings[count].newHead(rn);
                                    isHead = false;
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
                        var col = Std.parseInt(datas[10]);
                        var row = Std.parseInt(datas[11]);
                        var cinport = datas[12];
                        var cw = datas[13];
                        var ch = datas[14];
                        var ringindex = datas[15];
                        var chn = ChannelMgr.getInst().getChannel( cip, cinport, Std.parseInt(cw), Std.parseInt(ch), col, row );
                        if (chn != null){
                            var l= Std.parseInt(layer);
                            WndMgr.getInst().setIfBiggerLayer(l);
                            var win = WndMgr.getInst().createWnd(l);
                            win._channel = chn;
                            var ring:Ring = null;
                            if ( ringindex != "null"){
                                win._ring = RingMgr.getInst()._rings[ Std.parseInt(ringindex)];
                            }
                            win._virtualAreaX = Std.parseFloat(ax);
                            win._virtualAreaY = Std.parseFloat(ay);
                            win._virtualAreaW = Std.parseFloat(aw);
                            win._virtualAreaH = Std.parseFloat(ah);
                            win._virtualX = x;
                            win._virtualY = y;
                            win._virtualWidth = w;
                            win._virtualHeight = h;

                            _currLoadWnds.push( win);
                        }else{
                            trace("a window without correspond channel!");
                        }
                    }
                }
            }
        }
        if (_currLoadWnds.length > 0){
            onLoadingWnds(true);
        }else{
            var tmp = _cbDone;
            _cbDone = null;
            tmp();
            _isLoading = false;
        }
    }

    public function onLoadingScreens():Void{
        var screen:Screen= null;
        if (_currLoadScreens!= null && _currLoadScreens.length > 0){
            screen= _currLoadScreens[0];
            _currLoadScreens.remove(screen);
        }

        if ( screen ==  null){
            onAfterLoadScreens();
            trace("load screens done");
            return;
        }

        trace("loading screen..."+ _currLoadScreens.length);
#if !neko
        screen.connect();
        if (screen.isConected()){
            screen.connectedInit(onLoadingScreens);
        }else{
            trace("screen: "+screen._ipv4+" connect failed!");
        }
#else
        onLoadingScreens();
#end
    }

    public function onLoadingWnds(args):Void{

        var wnd:Wnd = null;
        if (_currLoadWnds != null && _currLoadWnds.length > 0){
            wnd = _currLoadWnds[0];
            _currLoadWnds.remove(wnd);
        }
        if ( wnd ==  null){
            var tmp = _cbDone;
            _cbDone = null;
            tmp();
            _isLoading = false;
            trace("load windows done");
            return;
        }

        trace("loading window..."+ _currLoadWnds.length);
        wnd.resurrectWnd(onLoadingWnds);
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
            sb.add ( i._screen._col);
            sb.add( ',');
            sb.add ( i._screen._row);
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
                        //pre position
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
                        //next position
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
                        //my position
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
            sb.add(i._channel._screen._col);
            sb.add(",");
            sb.add(i._channel._screen._row);
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
