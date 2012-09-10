#if sys
package base.network;

import sys.net.Socket;
import sys.net.Host;
import haxe.io.BytesBuffer;
import haxe.io.Bytes;
import base.network.NetworkMgr;


class ClientConn{
    public var _socket:BaseSocket;

    var _head:Bytes;
    var _reserved:Bytes;
    var _ctl:Bytes;
    var _msg:Bytes;

    var _length:Bytes;
    var _data:Bytes;

    inline static var FlashPolicyRsp:Bytes = Bytes.ofString("<?xml version=\"1.0\"?><!DOCTYPE cross-domain-policy SYSTEM \"http://www.adobe.com/xml/dtds/cross-domain-policy.dtd\"><cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"8000\"/></cross-domain-policy>" + String.fromCharCode(0));//套接字策略文件  

    inline static var PolicyReq:Bytes = Bytes.ofString("<policy-file-request/>"+String.fromCharCode( 0) );

    public function new( s:BaseSocket){
        _socket = s;
        //最小可以分辨毫秒
        _socket.setTimeout(0.001);

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

        _data= Bytes.ofString("");
    }

    inline public function addHeaders( buf:BytesBuffer){
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

    inline public function clearData( ):Bool{
        _data = Bytes.ofString("");
        return true;
    }

    inline public function read( ):Bytes{
        var b:Bytes= _socket.readBytes();
        if ( b.compare(PolicyReq) == 0 ){
            trace("responsed flash policy file");
            _socket.writeBytes(FlashPolicyRsp );
            b = null;
        }
        return b;
    }

    inline public function write( data:Bytes):Void{
#if flash
        _socket.writeBytes( data, 0, data.length );
        _socket.flush();
#elseif sys
        _socket.writeBytes( data);
#else
        _socket.write( data.toString() );
#end
    }

    inline public function sendDataMap( datas:Hash<Bytes> ):Void{
        var bf= new BytesBuffer();
        addHeaders(bf);
        NetworkMgr.mapToBinary( bf, datas);
        var b = bf.getBytes();
        calFinalLength(b);
        write( b);
    }

    inline public function isConected():Bool{
        return true;
    }

    inline public function close():Void{
        _socket.close();
    }


    //public function listenForData():Bytes{
    //var data:Bytes = read();
    //if ( data != null && data.length > 0){
    //trace("*Server reading Data");
    //var datas:Hash<Bytes> = NetworkMgr.parseData( data);
    //trace("*Server end reading Data");
    //if (datas == null ){
    //trace("uncomprehancable data: "+ data.toHex() );
    //}
    //return datas;
    //}
    //return null;
    //}
}
#end
