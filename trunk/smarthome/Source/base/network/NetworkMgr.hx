package base.network;

import base.network.Connection;
import nme.events.Event;
import haxe.io.BytesBuffer;
import haxe.io.Bytes;
#if sys
import sys.net.Socket;
import base.network.ClientConn;
#end

class NetworkMgr{

    var _conn(getConn, setConn):Connection;

    function new(){
    }

    inline public function setConn( conn:Connection):Connection{
        _conn = conn;
        return _conn;
    }

    inline public function getConn( ):Connection{
        return _conn ;
    }

    public static var inst:NetworkMgr;
    inline public static function getInst():NetworkMgr{
        if ( inst == null) {
            inst = new NetworkMgr();
        }
        return inst;
    }

    inline public static function bytes2Short( str:Bytes, pos:Int = 0):Int{
        var res:Int = str.get(pos++);
        res += str.get(pos)<<8;
        return res;
    }
    inline public static function str2Short( str:String, pos:Int = 0):Int{
        var res:Int = str.charCodeAt(pos++);
        res += str.charCodeAt(pos)<<8;
        return res;
    }
    inline public static function bytes2Int( str:Bytes, pos:Int = 0):Int{
        var res:Int = str.get(pos++);
        res += str.get(pos++)<<8;
        res += str.get(pos++)<<16;
        res += str.get(pos)<<28;
        return res;
    }
    inline public static function str2Int( str:String, pos:Int = 0):Int{
        var res:Int = str.charCodeAt(pos++);
        res += str.charCodeAt(pos++)<<8;
        res += str.charCodeAt(pos++)<<16;
        res += str.charCodeAt(pos)<<28;
        return res;
    }

    inline public static function short2Bytes( i:Int):Bytes{
        var bb = Bytes.alloc(2);
        bb.set(0, i);
        bb.set(1, i>>8);
        return bb;
    }
    inline public static function int2Bytes( i:Int):Bytes{
        var bb = Bytes.alloc(4);
        bb.set(0, i);
        bb.set(1, i>>8);
        bb.set(2, i>>16);
        bb.set(3, i>>24);
        return bb;
    }
    inline public static function int2Str( i:Int):String{
        return int2Bytes(i).toString();
    }

#if sys
    var _acc:Acceptor ;
    var _handlers:Array< Dynamic->ClientConn->Bool >;
    var _clients:Array<ClientConn>;
    var _selects:Array<Socket> ;
    var _pre:Float;
    var _now:Float;

    public function runAsServer():Void{
        if ( _acc != null ) return;
        trace("simulated server start up!");
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, onListening);
        _acc= new Acceptor( 8000);
        _clients = new Array<ClientConn>();
        _handlers = new Array<Hash<Bytes>->ClientConn->Bool>();
        _selects = new Array<Socket>();
        _selects.push(_acc._socket);
        _pre = _now = haxe.Timer.stamp();
    }

    public function noreplyBroadcast( ba:Array<Bytes> , exceptThis:ClientConn = null ):Void{
        if ( _clients.length > 0){
            if ( _clients.length == 1 && _clients[0] == exceptThis) return;//如果广播的对象只是消息的源客户端则不广播
            var buf = new BytesBuffer();
            _clients[0].setMsg( 0, 2);
            _clients[0].addHeaders( buf);
            buf.add( NetworkMgr.short2Bytes( ba.length) );
            for ( b in ba){
                buf.add( NetworkMgr.short2Bytes( b.length) );
                buf.add( b );
            }
            var b = buf.getBytes();
            _clients[0].calFinalLength(b);

            for ( c in _clients ){
                if ( c != exceptThis) c.write( b);
            }
        }
    }


    public function onListening( evt:nme.events.Event ):Void{
        var arr = Socket.select( _selects, [], [], 0.0000001 );
        if ( arr.read.length  > 0 ){
            //trace("there are incoming data wait for read!");
            for( s in arr.read){
                if ( s == _acc._socket ){
                    var s:Socket = _acc._socket.accept();
                    var bs:BaseSocket = new BaseSocket(s);
                    if (s != null ) {
                        var c = new ClientConn(bs);
                        _clients.push(c);
                        _selects.push(bs);
                        trace("someone connected");
                    }
                    continue;
                }
                var isThis:ClientConn = null;
                for( i in _clients){
                    if ( s == i._socket ){
                        isThis = i;
                    }
                }
                if ( isThis == null)break;
                //var data = isThis.listenForData();
                var data:Bytes = null;
                try{
                    data = isThis.read();
                }catch( e:String ){
                    trace(e);
                    _clients.remove( isThis);
                    _selects.remove( isThis._socket);
                    trace("client connection error!");
                }
                if ( data == null ) return;
                if (  data.length < 20 ) {
                    if( data.length == 0){
                        _clients.remove( isThis);
                        _selects.remove( isThis._socket);
                        trace("client disconnected!");
                    }else trace("unavailable data: " + data.toString() );
                    return ; 
                }
                var msgType:Int = NetworkMgr.bytes2Short( data, 16 );

                if (msgType == 1 ){
                    var datas:Hash<Bytes> = parseData( data);
                    if ( datas != null){
                        for( handler in _handlers){
                            trace("dispathing a hash bytes handler");
                            handler( datas, isThis);
                        }
                    }
                }else if ( msgType == 2 ){
                    var datas:Array<Bytes> = parseBytesArray( data);
                    if ( datas != null){
                        for( handler in _handlers){
                            trace("dispathing a array bytes handler");
                            handler( datas, isThis);
                        }
                    }
                    noreplyBroadcast(datas, isThis);
                }

            }
        }
    }

    public function addServerHandler( func:Dynamic->ClientConn->Bool ):Void{
        if ( _handlers != null) {
            for (i in _handlers){ if ( i == func ) {trace("func allready existed!");return;}}
            _handlers.push( func);
        }
    }
    inline public function removeServerHandler( func:Dynamic):Void{
        if ( _handlers != null) {
            //for ( h in _handlers){
            //if (h == func) _handlers.remove( h);
                //}
            _handlers.remove( func);
        }
    }
#end

    static public function parseBytesArray( str:Bytes):Array<Bytes>{
        if ( str != null &&  str.length >0 && str.get( 0 ) == 0xef && str.get( 1 ) == 0xdf && str.get( 2 ) == 0x67 && str.get( 3 ) == 0x67 ){
            var len:Int = bytes2Int( str, 4);

            var datalen:Int = len - 12;//reduce base msg bytes num
            var dataPos:Int = 20;
            if ( len != (str.length - 8) ){
                trace("***illegal response data, raw len: "+str.length +" data len: "+datalen + " total len: "+len +8);
                trace( str.toHex() );
                return null;
            }else{
                trace("got qualified response raw len: "+str.length +" data len: "+datalen + "total len: "+len );
            }

            if ( datalen > 0 ){
                var num:Int = bytes2Short( str, dataPos );
                dataPos += 2;
                if ( num <= 0 ) return null;

                var res:Array<Bytes> = new Array<Bytes>();
                while ( num > 0 ){
                    var len:Int = bytes2Short( str, dataPos );
                    dataPos += 2;
                    res.push( str.sub( dataPos, len ) );
                    dataPos += len;
                    --num;
                }
                return res;
            }
        }

        return null;
    }

    static public function parseData( str:Bytes):Hash<Bytes>{
        if ( str != null &&  str.length >0 && str.get( 0 ) == 0xef && str.get( 1 ) == 0xdf && str.get( 2 ) == 0x67 && str.get( 3 ) == 0x67 ){
            var len:Int = bytes2Int( str, 4);

            var datalen:Int = len - 12;//reduce base msg bytes num
            var dataPos:Int = 20;
            if ( len != (str.length - 8) ){
                trace("***illegal response data, raw len: "+str.length +" data len: "+datalen + " total len: "+len +8);
                trace( str.toHex() );
                return null;
            }else{
                trace("got qualified response raw len: "+str.length +" data len: "+datalen + "total len: "+len );
            }

            if ( datalen > 0 ){
                //var data:Bytes= str.sub( dataPos, datalen ) ;
                var datas:Hash<Bytes> = parseDataMap(str, dataPos);
                datas.set( "__MSGTYPE__", str.sub( 16, 4));
                return datas;
            }
        }
        else{
            trace("***illegal header!");
        }
        return null;
    }

    static public function parseDataMap( data:Bytes, pos:Int = 0):Hash<Bytes>{
        var num:Int =  data.get( pos++); num +=  data.get(pos++) << 8;

        if ( num == 0 ) return null;
        var rspsMap:Hash<Bytes> = new Hash<Bytes>();
        //trace( "num: "+num);
        while ( num > 0){
            var keylen:Int = data.get(pos++); keylen += data.get(pos++)<<8;

            var key:String = data.readString( pos, keylen);
            pos+=keylen;

            var vallen:Int = data.get(pos++); vallen += data.get(pos++)<<8;

            var val:Bytes = data.sub( pos, vallen);
            pos+=vallen;

            if ( vallen ==4 ) trace( "key: "+key+ " len: "+keylen + " intval: " + bytes2Int(val)+" len: " +vallen)  ;
            else  trace( "key: "+key+ " len: "+keylen + " strval: "+val.readString(0, val.length)+ " len: " +vallen ) ;

            rspsMap.set( key, val);
            --num;
        }
        //trace( "final pos: "+pos);
        return rspsMap;
    }

    static public function mapToBinary( data:BytesBuffer , datas:Hash<Bytes> ):Bool{
        var count:Int = Lambda.count(datas);
        //trace("count: "+ count);
        if ( count > 0){
            data.add( short2Bytes(count) );
            var it = datas.keys();
            do{
                var key:String = it.next();
                var val:Bytes = datas.get(key);

                var bb:Bytes = Bytes.ofString(key);
                data.addByte( bb.length );
                data.addByte( bb.length >> 8 );
                data.addBytes( bb, 0, bb.length);
                data.addByte( val.length );
                data.addByte( val.length >> 8 );
                //trace( key+ " val: "+ val + " b.length: "+b.length+"compress to "+ b.toHex() );
                data.addBytes( val, 0, val.length);

            }while( it.hasNext() );
            return true;
        }
        return false;
    }

    static public function responseTrue( datas:Hash<Bytes> ):Bool{
        var result:Bytes = datas.get("_result");
        if (result ==null) return false;
        var res:String = result.readString( 0, result.length);
        if( res == "true"){return true;}else return false;
    }

}
