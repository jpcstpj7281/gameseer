package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;
import base.network.ClientConn;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialog;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;

import haxe.io.Bytes;

class SimulatedDeviceDlg extends CommDialog{

    public var _cmdid:Int;
    public function new ( mgr:ListDialogMgr, cmdName:String, cmdid:Int ){

        var str:String = cmdName;
        _cmdid = cmdid;
        _uniqueId = str+_cmdid;
        var s:Sprite = createElement( str, cmdid);
        super(  mgr);
        addChild( s);
    }


    public function createElement(name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 220;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 220/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = Std.string(id);
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.setBorder(true);
        txt1.width = 100;
        txt1.x = 120;
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("trunk") );
        //bm.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;

        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt1);
        s.addChild( txt);
        //var w:Float = nme.Lib.current.stage.stageWidth / txt.width;
        //s.width=  nme.Lib.current.stage.stageWidth;
        s.height = nme.Lib.current.stage.stageHeight/10;
        //txt.scaleY = 2;
        return s;
    }

    public function onLoop(evt:Event):Void{
        if( DeviceSimulatorDialog._stats[_cmdid] == false){
            alpha = 1;
        }
        else alpha = 0.3;
    }

    public override function show(){
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, onLoop);
        return super.show();
    }
    public override function hide(){
        nme.Lib.current.removeEventListener( Event.ENTER_FRAME, onLoop);
        return super.hide();
    }
}


class DeviceSimulatorDialog extends ListDialog{

    static public var _stats:Array<Bool>;
    static public var _devices:Array<String>;
    static public var _datas:Hash<String>;
    static public var _cmds:Array<String>;

    public function new ( mgr:ListDialogMgr ){


        var str:String = "模拟服务器";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super(  mgr);
        addChild(s);

        if( _devices == null ){
            trace("initializing simulator data!");
            _devices = new Array<String>();
            _cmds= new Array<String>();
            _stats= new Array<Bool>();
            _datas = new Hash<String>();
            _devices.push( "电视");
            _devices.push( "电灯");
            _devices.push( "空调");
            _devices.push( "窗帘");
            _cmds.push("开电视");
            _cmds.push("关电视");
            _cmds.push("开灯");
            _cmds.push("关灯");
            _datas.set("_DEVICE_ID电视", NetworkMgr.int2Str(1));
            _datas.set("_DEVICE_ID电灯", NetworkMgr.int2Str(2));
            _datas.set("_DEVICE_ID空调", NetworkMgr.int2Str(3));
            _datas.set("_DEVICE_ID窗帘", NetworkMgr.int2Str(4));

            _datas.set("_CMD_ID开电视", NetworkMgr.int2Str(1));
            _datas.set("_CMD_ID关电视", NetworkMgr.int2Str(2));
            _datas.set("_CMD_ID开灯", NetworkMgr.int2Str(3));
            _datas.set("_CMD_ID关灯", NetworkMgr.int2Str(4));

            _datas.set("_CMD_TYPE开电视", NetworkMgr.int2Str(1));
            _datas.set("_CMD_TYPE关电视", NetworkMgr.int2Str(1));
            _datas.set("_CMD_TYPE开灯", NetworkMgr.int2Str(2));
            _datas.set("_CMD_TYPE关灯", NetworkMgr.int2Str(2));

            _cmds.push("开窗帘");
            _cmds.push("关窗帘");
            _cmds.push("开空调");
            _cmds.push("关空调");
            _datas.set("_CMD_ID开窗帘", NetworkMgr.int2Str(5));
            _datas.set("_CMD_ID关窗帘", NetworkMgr.int2Str(6));
            _datas.set("_CMD_ID开空调", NetworkMgr.int2Str(7));
            _datas.set("_CMD_ID关空调", NetworkMgr.int2Str(8));
            _datas.set("_CMD_TYPE开窗帘", NetworkMgr.int2Str(4));
            _datas.set("_CMD_TYPE关窗帘", NetworkMgr.int2Str(4));
            _datas.set("_CMD_TYPE开空调", NetworkMgr.int2Str(8));
            _datas.set("_CMD_TYPE关空调", NetworkMgr.int2Str(8));
        }

        //var str:String = NetworkMgr.int2Str(1);
        //if ( str.charCodeAt(0) == 1){
        //trace("right");
        //}
        createDlgs();
    }

    public override function clear():Void{
        if ( _listDialogMgr != null) _listDialogMgr.clear();
        _listDialogMgr =null;
        //NetworkMgr.getInst().removeServerHandler( serverHandler);
    }

    public function resetDlgs(){
        _listDialogMgr.clear();
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = showParent;
        createDlgs();
    }

    public override function onMouseClick( ):Void{
        var dm:CommDialogMgr = cast( _mgr);
        if ( dm.isAnimating() == false){
            resetDlgs();
            super.onMouseClick();
            NetworkMgr.getInst().runAsServer();
            NetworkMgr.getInst().addServerHandler( serverHandler);
        }
    }

    public function createDlgs(){
        for( i in 0..._devices.length){
             new SimulatedDeviceDlg( _listDialogMgr, _devices[i], i+1);
        }
    }

    static public function serverHandler( datas:Hash<Bytes>, conn:ClientConn):Bool{
        if ( _devices == null)return false;
        //trace("Simulated server got incoming msg!");

        var b:Bytes= datas.get("__OP__");
        var op:String = null;
        if (b != null){
            op= b.toString();
        }

        var res:Hash<Bytes> = new Hash<Bytes>();
        if (op != null &&  op == "load_all_devices"){ 
            for (i in 0..._devices.length){
                if( _devices[i] != null && _devices[i].length > 0){
                    var dkey:String = "_DEVICE_ID"+_devices[i];
                    res.set( _devices[i], Bytes.ofString(_datas.get(dkey) ));
                }
            }
        }
        else if ( op != null && op == "load_all_cmds"){ 
            //trace("loading cmds: " + _cmds.length);
            for( i in 0..._cmds.length){
                if( _cmds[i] != null && _cmds[i].length >0){
                    var ckey:String = "_CMD_ID"+_cmds[i];
                    var ctype:String = "_CMD_TYPE"+_cmds[i];
                    res.set( ckey, Bytes.ofString(_datas.get(ckey)));
                    res.set( ctype, Bytes.ofString(_datas.get(ctype)));
                }
            }
            res.set("_result", Bytes.ofString("true"));
        }
        else if ( op != null && op == "add_device"){ 
            var dev:String = datas.get("DEVICE").toString();
            var devkey:String = "_DEVICE_ID"+dev;
            var devid:String = _datas.get(devkey);
            if ( devid != null && devid.length > 0){
                for ( i in 0..._devices.length){
                    if ( _devices[i].length == 0 ){
                        _devices[i] = dev;
                        _datas.set( devkey, NetworkMgr.int2Str( i+1) );
                        res.set( devkey, NetworkMgr.int2Bytes(i+1));
                        break;
                    }
                }
            }
            if ( Lambda.count( res) == 0){
                _devices.push( dev);
                _datas.set( devkey, NetworkMgr.int2Str( _devices.length) );
                res.set( devkey, NetworkMgr.int2Bytes(_devices.length));
            }
        }
        else if ( op != null && op == "add_cmd"){ 
            var cmd:String = datas.get( "CMD").toString();
            var ckey:String = "_CMD_ID"+cmd;
            var ctype:String = "_CMD_TYPE"+cmd;
            var cid:String = _datas.get(ckey);
            if ( cid != null && cid.length > 0){
                for ( i in 0..._cmds.length){
                    if( _cmds[i].length == 0){
                        _cmds[i] = cmd;
                        _datas.set( ckey, NetworkMgr.int2Str( i+1));
                        res.set(ckey, NetworkMgr.int2Bytes( i+1));
                        _datas.set( ctype, NetworkMgr.int2Str( 0));
                        res.set(ctype, NetworkMgr.int2Bytes( 0));
                        break;
                    }
                }
            }
            if( Lambda.count( res) == 0){
                _cmds.push( cmd);
                _datas.set( ckey, NetworkMgr.int2Str( _cmds.length));
                res.set(ckey, NetworkMgr.int2Bytes( _cmds.length));
                _datas.set( ctype, NetworkMgr.int2Str( 0));
                res.set(ctype, NetworkMgr.int2Bytes( 0));
            }

        }
        else if (op != null &&  op == "modify_cmd_type"){ 
            var cid:Int = NetworkMgr.bytes2Int( datas.get("_CMD_ID"));
            var ctype:Int = NetworkMgr.bytes2Int( datas.get("_CMD_TYPE")) ;
            var cmdtype:String = "_CMD_TYPE"+_cmds[cid-1];
            //trace( "ctype: " + ctype );
            _datas.set( cmdtype, NetworkMgr.int2Str( ctype ) );
            res.set( "_result", Bytes.ofString("true"));
        }
        else if ( op != null && op == "fire_cmd"){ 
            var cid:Int = NetworkMgr.bytes2Int( datas.get("_CMD_ID"));
            var cmdtype:String = "_CMD_TYPE"+_cmds[cid-1];
            var cmdt:String = _datas.get( cmdtype );
            var ct:Int = NetworkMgr.str2Int( cmdt);
            var flag:Int = 1;
            for ( i in 0...32){
                if ( ( ct & (flag << i) ) != 0  ){
                    _stats[i+1] = !_stats[i+1];
                }
            }

            res.set( "_result", Bytes.ofString("true"));
        }
        var ping:Bytes = datas.get("ping");
        if ( ping != null && ping.toString() == "test"){
            conn.setMsg( 4);
            res.set("ping", Bytes.ofString("hello"));
            trace("ping pong!");
            conn.sendDataMap( res );
            return true;
        }

        if ( Lambda.count(res) > 0 ){
            conn.setMsg( 12);
            res.set("__OP__", Bytes.ofString(op));
            res.set("_result", Bytes.ofString("true"));
            //for (k in res.keys() ){ trace( "send out map data: "+ k + ": " + res.get(k) ); }
            conn.sendDataMap( res);
            return true;
        }else{
            conn.setMsg( 12);
            res.set("__OP__", Bytes.ofString(op));
            res.set("_result", Bytes.ofString("false"));
            //for (k in res.keys() ){ trace( "send out map data: "+ k + ": " + res.get(k) ); }
            trace("failed to resolve, OP: " + op );
            conn.sendDataMap( res);
            return true;
        }

        trace("***cannot resolve datas!");
        return false;
    }
}

