package base.network;

import base.network.Connection;
import flash.utils.ByteArray;

import haxe.io.BytesBuffer;
import haxe.io.Bytes;

import nme.events.Event;
import haxe.Timer;
import base.network.NetworkMgr;
import base.state.StateMachine;

class SMConnection extends Connection{


    var _listeners:IntHash< Dynamic->Void >;
    public var _sendTime:Float;
    var _now:Float;
    var _map:Hash<Bytes>;
    var _bytesArr:Array<Bytes>;

    var _head:Bytes;
    var _reserved:Bytes;
    var _ctl:Bytes;
    var _msg:Bytes;

    var _length:Bytes;
    //var _data:Bytes;
    public function new( ip:String = "127.0.0.1", port:Int = 8000){
        //super( ip, 8989 );
        super( ip, port);

        _map = new Hash<Bytes>();
        _bytesArr = new Array<Bytes>();
        _listeners = new IntHash<Hash<Bytes>->Void >();
        _now = _sendTime=Timer.stamp();

        var bb:BytesBuffer = new BytesBuffer();
        //head
        bb.addByte( 0xef);
        bb.addByte( 0xdf);
        bb.addByte( 0x67);
        bb.addByte( 0x67);
        _head= bb.getBytes();

        //length
        var buf:BytesBuffer= new BytesBuffer();
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        buf.addByte( 0x0c);
        _length = buf.getBytes();

        buf= new BytesBuffer();
        //ctl.head
        buf.addByte( 0x00);
        //ctl.totalPad
        buf.addByte( 0x00);
        //ctl.numPad
        buf.addByte( 0x00);
        //ctl.deviceType
        buf.addByte( 0x00);
        _ctl= buf.getBytes();

        buf= new BytesBuffer();
        //reserved
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        _reserved = buf.getBytes();

        buf= new BytesBuffer();
        //msgType.head
        buf.addByte( 0x00);
        //msgType.msgID
        buf.addByte( 0x00);
        //msgType.msgType
        buf.addByte( 0x00);
        buf.addByte( 0x00);
        _msg = buf.getBytes();

        //_data= Bytes.ofString("");
        //refreshLength();
        
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, listenIncomingData);
    }
    
    override function sendData( ):Bool{
        //trace("test1");
        var buf:BytesBuffer = new BytesBuffer();
        addHeaders(buf);
        //trace("test1");
        if ( _bytesArr.length > 0){
            buf.add( NetworkMgr.short2Bytes( _bytesArr.length) );
            for ( b in _bytesArr){
                buf.add( NetworkMgr.short2Bytes( b.length) );
                buf.add( b );
            }
        }else if ( Lambda.count( _map) > 0){
            NetworkMgr.mapToBinary(buf, _map);
        }
        //trace("test1");
        var data = buf.getBytes();
        calFinalLength(data);
        //trace("test1");
        write( data );
        //trace("test1");
        trace("sent out data len: "+ data.length +" to "+_ipv4);
        _sendTime = Timer.stamp();
        return true;
    }

    inline function addHeaders( buf:BytesBuffer){
        buf.add(_head);
        buf.add(_length);
        buf.add(_ctl);
        buf.add(_reserved);
        buf.add(_msg);
    }
    inline public function calFinalLength( data:Bytes){
        var len:Int = data.length - 8;
        data.set( 4, len );
        data.set( 5, len >>8 );
        data.set( 6, len >>16);
        data.set( 7, len >>24);
    }

    inline public function setCtl( deviceType:Int , numPad:Int = 0, totalPad:Int = 0):Bool{
        _ctl.set(0,  0);
        _ctl.set(1,  totalPad);
        _ctl.set(2,  numPad);
        _ctl.set(3,  deviceType);
        return true;
    }

    inline public function setMsg(  msgId:Int , msgType:Int = 1 ) :Bool{
        _msg.set(0,  msgId );
        _msg.set(1,  msgId >> 8);
        _msg.set(2,  msgType );
        _msg.set(3,  msgType >> 8);
        return true;
    }

    inline public function addKeyVal( key:String, val:Bytes):Void{
        _map.set( key, val);
    }

    inline public function addBytesArray( ba:Array<Bytes>):Void{
        for ( b in ba){
            _bytesArr.push( b);
        }
    }
    inline public function addBytes( bytes:Bytes):Void{
        _bytesArr.push( bytes);
    }

    inline public function clearData( ):Bool{
        if (_bytesArr.length > 0){
            _bytesArr = new Array<Bytes>();
        }
        if( Lambda.count(_map) > 0 ){
            _map = new Hash<Bytes>();
        }
        return true;
    }

    // before send out the data, you have to set up the handler for deal with the reponses, or the data will lost
    // func:Dynamic->Void
    inline public function startListening( msgId:Int, func:Dynamic, msgType:Int = 1 ):Bool{
        var msgidtype = (msgId<< 16) + msgType;
        trace("start listen msgidtype: " + msgidtype );
        var res:Bool = true;
        if (  _listeners.get(msgidtype) != null ){
            trace("already listening");
            res = false;
        }else{
            _listeners.set(msgidtype, func);
            _sendTime = Timer.stamp();
        }
        //if( _listeners.get(msgType) != null ) return false;
        return res;
    }

    inline public function listenIncomingData( evt:Event):Void{
        //if ( _now - _sendTime < 0.1){
        //return;
        //}

        if ( Lambda.count( _listeners) == 0 ) return ;
        //for ( i in _listeners.keys() ){
        //trace("try to listen for response: " + i);
        //}

        //trace("try to listen for response: " );
        var data = read();
        //trace("try to listen for response: 1" );

        if ( data == null || data.length < 20 ){
            //_now = Timer.stamp();
            //if ( _now - _sendTime > 10){
            //for ( i in _listeners.keys() ){
            //_listeners.remove( i);
            //}
            //trace("10 sec no response!");
            //StateMachine.getInst().toState("InitBaseState");
            //}
            return;
        }
        //trace("try to listen for response: 2" );
        _sendTime = Timer.stamp();

        //trace("try to listen for response: msgidType "+ msgidType );

        var pos:Int = 0;
        trace( "data len: "+ data.length + " from " + _ipv4);
        while ( pos  < data.length ){
            var msgid:Int = NetworkMgr.bytes2Short( data, pos+16 );
            var msgType:Int= NetworkMgr.bytes2Short( data, pos+18);
            var msgidType= (msgid << 16) + msgType;

            var len:Int = NetworkMgr.bytes2Int( data, pos+ 4);
            //trace(len);
            var subdata = data.sub(pos, len+8 );
            //trace( subdata.toHex() );
            //trace( data.toHex() );

            var d:Dynamic = null;
            d= NetworkMgr.parseData(subdata);

            if ( d == null ){ 
                trace("data cannot be parse!");
                return;
            }
            //trace("diapatching msg id type: " +msgidType);
            var func = _listeners.get( msgidType);
            _listeners.remove( msgidType);
            if ( func == null){
                trace("***There is not coresponsing incoming data handler! msgType: " + msgidType);
                //return ;
            }
            else{
                func( d);
            }

            //trace(pos);
            pos = pos+len+8;
            //trace(pos);
        }

    }

    inline public function ping(func:Dynamic):Bool{
        var res:Bool = false;
        if ( startListening( 4, func)){
            clearData();
            setMsg( 3 );
            addKeyVal( "ping", Bytes.ofString("test"));
            sendData( );
            res = true;
        }
        return res;

    }

}
