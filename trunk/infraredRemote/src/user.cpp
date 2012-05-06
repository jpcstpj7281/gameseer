/*
 * user.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include "user.h"
#include "protocol.h"
#include "map"
#include "vector"
#include "fstream"
#include "string.h"
using namespace std;
struct User::Impl{
    typedef map<string, string> SSMap;

    SSMap     _usrs;
    SSMap     _confs;
    SSMap   _datas;
    const static int MAX_DEV = 32;
    string   _devices[MAX_DEV];
    const static int MAX_CMD = 1024;
    string   _cmds[MAX_CMD];

    Impl(){
        loadPersistency( _datas, "test.data");
    }

    void onUserReg(MsgInfo *msg,uint32_t connID){
        cout<<"onUserReg"<<" connID="<<connID <<endl;
        MsgInfo rsp;
        rsp.msgType = PUserRegRsp::uri;
        string usr = msg->info["user"];
        if ( _usrs.find(usr) == _usrs.end()){
            _usrs[usr] = msg->info["psw"] ;
            rsp.info["_result"] = "true";
            cout<<"user="<<msg->info["user"] <<" psw="<<msg->info["psw"] <<" reg succeed"<<endl;
        }
        else
        {
            cout<<"user="<<msg->info["user"] <<" psw="<<msg->info["psw"] <<" reg failed"<<endl;
            rsp.info["_result"] = "false";
        }
        response( connID, &rsp);
    }

    void onUserLogin(MsgInfo *msg,uint32_t connID)
    {
        cout<<"onUserLogin"<<" connID="<<connID <<endl;

        MsgInfo rsp;
        rsp.msgType = PUserLoginRsp::uri;

        string usr = msg->info["user"];
        SSMap::iterator found = _usrs.find(usr);
        if ( found != _usrs.end() && msg->info["psw"] == found->second )
        {
            rsp.info["_result"] = "true";
            cout<<"user="<<msg->info["user"] <<" psw="<<msg->info["psw"] <<" login succeed"<<endl;
        }
        else
        {
            rsp.info["_result"] = "false";
            cout<<"user="<<msg->info["user"] <<" psw="<<msg->info["psw"] <<" login failed"<<endl;
        }
        response(connID,&rsp);
    }

    void onUserPing(MsgInfo *msg,uint32_t connID)
    {
        cout<<"onUserPing"<<" connID="<<connID <<endl;
        MsgInfo rsp;
        if ( msg->info["ping"] == "test"){
            cout<<"got ping data: "<< msg->info["ping"]<<endl;
        }
        rsp.msgType = PUserPingRsp::uri;
        rsp.info["ping"] = "hello";
        response(connID,&rsp);
    }
    void onUserSave(MsgInfo *msg,uint32_t connID)
    {
        cout<<"onUserSave"<<" connID="<<connID <<endl;
        MsgInfo rsp;
        SSMap::iterator it(msg->info.begin()), end(msg->info.end());
        for( ;it!=end;++it){
            _datas[it->first] = it->second;
            cout<<"saved data: "<<it->first<<"-->"<<it->second<<endl;
        }
        rsp.msgType = PUserSaveRsp::uri;
        rsp.info["_result"] = "true";
        response(connID,&rsp);
    }
    void onUserLoad(MsgInfo *msg,uint32_t connID)
    {
        cout<<"onUserLoad"<<" connID="<<connID <<endl;
        MsgInfo rsp;
        SSMap::iterator it(msg->info.begin()), end(msg->info.end());
        for( ;it!=end;++it){
            string & str =  _datas[it->first];
            rsp.info[it->first] = str;
            cout<<"loaded data: "<<it->first<<"-->"<<str<<endl;
        }
        rsp.msgType = PUserLoadRsp::uri;
        rsp.info["_result"] = "true";
        response(connID,&rsp);
    }
    void onUserOP(MsgInfo *msg,uint32_t connID)
    {
        cout<<"onUserOP"<<" connID="<<connID <<endl;
        MsgInfo rsp;

        string &op = msg->info["__OP__"];
        cout<<"OP:  "<<op<<endl;
        if ( op == "add_device"){ addDevice( *msg, rsp); flushPersistency( _datas, string("test.data")); }
        else if ( op == "load_device"){ loadDevice( *msg, rsp); }
        else if ( op == "load_all_devices"){ loadAllDevice( *msg, rsp); }
        else if ( op == "remove_device"){ removeDevice( *msg, rsp); }
        else if ( op == "add_cmd"){ addCMD( *msg, rsp); flushPersistency( _datas, string("test.data")); }
        else if ( op == "load_all_cmds"){ loadAllCMDs( *msg, rsp); }
        else if ( op == "load_cmd"){ loadCMD( *msg, rsp); }
        else if ( op == "modify_cmd_type"){ modifyCMDType( *msg, rsp); flushPersistency( _datas, string("test.data") ); }
        else if ( op == "remove_cmd"){ removeCMD( *msg, rsp); }
        else if ( op == "fire_cmd"){ fireCMD( *msg, rsp); }

        rsp.msgType = PUserOPRsp::uri;
        response(connID,&rsp);
    }


    private:

    void loadPersistency( SSMap & map, const string & fileName ){
        ifstream in(fileName.c_str(), ios::binary);
        if ( in.is_open() == false) return;
        int sz;
        in.read( (char*)&sz, sizeof(int));
        cout<<"load map size: "<< sz<<endl;
        int klen,vlen;
        char key[256];
        char val[256];
        char tmp[256];
        for ( int i = 0; i < sz; ++i){
            memset( key, 0, 256);
            memset( val, 0, 256);
            in.read( (char*)&klen, sizeof(int));
            in.read( key, klen);
            in.read( (char*)&vlen, sizeof(int));
            in.read( val, vlen);
            map[key].assign( val, val + vlen);
            cout<<"load  key: "<< key<< " val: "<< val<< " int: "<<*(int*)val<<" vlen: "<<vlen<<endl;
            memset( tmp, 0, 256);
            strcpy( tmp, key);
            static const char * d = "_DEVICE_ID";
            static const char * c = "_CMD_ID";
            //cout<<"show: "<<tmp<<endl;
            if ( strlen(key) > strlen(d) && strncmp( d, tmp, strlen(d) ) == 0){//initialize deivces array
                int id = 0;
                memcpy( (char*) &id, val, vlen);
                //cout<<"load device: key: "<< key<< " val: "<< id<< " vlen: "<<vlen<<endl;
                _devices[id-1] = &key[strlen(d)]; 
                //cout<<"load device id: "<<val[0]-1<< key<<endl;
            }
            else if ( strlen(key) > strlen(c) && strncmp(c, tmp, strlen(c)) == 0){ //initialize cmds array
                int id = 0;
                memcpy( (char*) &id, val, vlen);
                //cout<<"load cmd: key: "<< key<< " val: "<< id<< " vlen: "<<vlen<<endl;
                _cmds[ id-1 ] = &key[strlen(c)]; 
                //cout<<"load cmd id: "<<val[0]-1<< key<<endl;
            }
        }
    }
    void flushPersistency( const SSMap & map, const string & fileName ){
        ofstream out(fileName.c_str(), ios::binary);
        int sz = map.size();
        out.write( (char*)&sz, sizeof(sz));
        cout<<"saved map size: "<< sz<<endl;
        SSMap::const_iterator it(map.begin()), end( map.end());
        int len;
        for ( ; it != end; ++it){
            len = it->first.size();
            out.write( (char*)&len, sizeof(int));
            out.write( (char*)it->first.c_str(), len);
            len = it->second.size();
            const char* str = it->second.c_str();
            out.write( (char*)&len, sizeof(int));
            out.write( str, len);
            cout<<"saved map: key: "<< it->first<< " val: "<<it->second <<" int: "<<*(int*)str<<" len: "<<len<<endl;

        }
        out<<endl;
        out.flush();
        out.close();
        cout<< "_datas saved! "<<endl;
    }

    void loadAllCMDs( MsgInfo& msg, MsgInfo& rsp){
        for ( int i = 0; i < MAX_CMD; ++i){
            if (_cmds[i].empty() ==false ){
                string &cmd = _cmds[i];
                string cmdkey = "_CMD_ID" + cmd;
                string cmdtype = "_CMD_TYPE" + cmd;
                rsp.info[ cmdkey ] = _datas[cmdkey];
                rsp.info[ cmdtype] = _datas[cmdtype];

                //string &id = _datas[cmdkey];
                //string &type = _datas[cmdtype];
                //int *iid = (int*)id.c_str();
                //int *itype = (int*)type.c_str();
                //cout<<"load all cmd: "<<cmdkey<< ": "<<*iid<<" "<<cmdtype<<": "<<*itype<<endl;
            }
        }
        rsp.info["_result"] = "true";
    }

    void modifyCMDType( MsgInfo& msg, MsgInfo& rsp){
        string &cmd= msg.info["_CMD_ID"];
        int id = cmd[0];
        id += cmd[1]<<8;
        id += cmd[2]<<16;
        id += cmd[3]<<24;
        cout<<"got cmd id: "<<id ;
        string &t = msg.info["_CMD_TYPE"];
        int type = t[0];
        type += t[1]<<8;
        type += t[2]<<16;
        type += t[3]<<24;
        cout<<" type: "<<type<<endl;

        string cmdtype= "_CMD_TYPE" + _cmds[id-1];
        SSMap::iterator found = _datas.find( cmdtype);
        if ( found == _datas.end() ){
            rsp.info["_result"] = "Command type: "+cmdtype+" not exist!";
        }
        else{
            found->second.assign( (char*)&type, sizeof(type) );
            rsp.info["_result"] = "true";
        } 
    }
    void addCMD( MsgInfo& msg, MsgInfo& rsp){
        if ( checkName( msg.info["CMD"], rsp) == false){ return ; }
        string &cmd= msg.info["CMD"];
        string cmdkey= "_CMD_ID" + cmd;
        string cmdtype= "_CMD_TYPE" +cmd;
        SSMap::iterator found = _datas.find( cmdkey);
        if ( found != _datas.end() ){
            rsp.info["_result"] = "Command alread existed!";
        }
        else{
            for ( int i = 0; i < MAX_CMD; ++i){
                if (_cmds[i].empty() ){
                    _cmds[i] = cmd;
                    string & ck = _datas[cmdkey];
                    //ck = (char)(i+1);
                    int pos = i+1;
                    ck.assign( (char*)&pos, sizeof(int));
                    cout<< "add cmd: "<<cmd<< " id: "<<i+1<<endl;
                    rsp.info[cmdkey] = ck;
                    string & ct = _datas[cmdtype] ;
                    int type = 0;
                    ct.assign( (char*)&type, sizeof(int));
                    rsp.info[cmdtype] = ct;
                    rsp.info["_result"] = "true";
                    break;
                }
                else{
                    cout<< "already existed cmd: "<<_cmds[i]<< " id: "<<i+1<<endl;
                }
            }
        }
    }

    void fireCMD( MsgInfo& msg, MsgInfo& rsp){

        //string &cmd= msg.info["_CMD_ID"];
        //string cmdkey= "_CMD_ID" + cmd;
        rsp.info["_result"] = "true";
    }

    void removeCMD( MsgInfo& msg, MsgInfo& rsp){
        string &cmd= msg.info["CMD"];
        string cmdkey= "_CMD_ID" + cmd;
        SSMap::iterator found = _datas.find( cmdkey);
        if ( found != _datas.end() ){
            _cmds[ found->second[0] -1 ] = "";
            _datas.erase( found);

            string cmdtype= "_CMD_TYPE" + cmd;
            found = _datas.find( cmdtype);
            if ( found != _datas.end() ){
                _datas.erase( found);
                rsp.info["_result"] = "true";
            }
            else{
                rsp.info["_result"] = "Command device type not exist!";
            }
        }
        else{
            rsp.info["_result"] = "Command id not exist!";
        }

    }

    void loadCMD( MsgInfo& msg, MsgInfo& rsp){
        string &dev = msg.info["CMD"];
        string deviceKey = "_CMD_ID" + dev;
        SSMap::iterator found = _datas.find( deviceKey);
        if ( found != _datas.end() ){
            rsp.info["id"] = found->second;
            rsp.info["_result"] = "true";
        }
        else{
            rsp.info["_result"] = "Device not exist!";
        }
    }


    void loadAllDevice( MsgInfo& msg, MsgInfo& rsp){
        //printf("msgtype: %d\n", msg.msgType>>16);
        for ( int i = 0; i < MAX_DEV; ++i){
            if (_devices[i].empty() ==false ){
                string &dev = _devices[i];
                string deviceKey = "_DEVICE_ID" + dev;
                rsp.info[_devices[i] ] = _datas[deviceKey];
                //cout<<"devcie val datas len: "<< _datas[deviceKey].size()<<endl;
                //cout<<"devcie val rsp len: "<< rsp.info[_devices[i]].size()<<endl;
            }
        }
        rsp.info["_result"] = "true";
    }

    void removeDevice( MsgInfo& msg, MsgInfo& rsp){
        string &dev = msg.info["DEVICE"];
        string deviceKey = "_DEVICE_ID" + dev;
        SSMap::iterator found = _datas.find( deviceKey);
        if ( found != _datas.end() ){
            _devices[ found->second[0] -1 ] = "";
            _datas.erase( found);
            rsp.info["_result"] = "true";
        }
        else{
            rsp.info["_result"] = "Device not exist!";
        }
    }

    void loadDevice( MsgInfo& msg, MsgInfo& rsp){
        string &dev = msg.info["DEVICE"];
        string deviceKey = "_DEVICE_ID" + dev;
        SSMap::iterator found = _datas.find( deviceKey);
        if ( found != _datas.end() ){
            rsp.info["id"] = found->second;
            rsp.info["_result"] = "true";
        }
        else{
            rsp.info["_result"] = "Device not exist!";
        }
    }

    void addDevice( MsgInfo& msg, MsgInfo& rsp){
        if ( checkName( msg.info["DEVICE"], rsp) == false){ return ; }
        string &dev = msg.info["DEVICE"];
        string deviceKey = "_DEVICE_ID" + dev;
        SSMap::iterator found = _datas.find( deviceKey);
        if ( found != _datas.end() ){
            rsp.info["_result"] = "Device alread existed!";
        }
        else{
            for ( int i = 0; i < MAX_DEV; ++i){
                if (_devices[i].empty() ){
                    _devices[i] = dev;
                    int pos = i+1;
                    _datas[deviceKey].assign( (char*)&pos, sizeof(int))  ;
                    cout<< "add device: "<<dev<<endl;
                    string & id = rsp.info[deviceKey] ;
                    id.assign( (char*)&pos, sizeof(int));
                    rsp.info["_result"] = "true";
                    break;
                }
            }
        }
    }

    bool checkName( string & name, MsgInfo& rsp){
        if ( name.empty()){
            rsp.info["_result"] = "Unexpected empty name!";
            return false;
        }else if( name[0] == '_'){
            rsp.info["_result"] = "Unexpected name: "+name+", name cannot leading by \'_\'";
            return false;
        }else if( name == "_result"){
            rsp.info["_result"] = "Illegal name: " +name;
        }
        return true;
    }
};

User::User():_impl(new Impl) { }

User::~User() { delete _impl; }


uint32_t User::onMsgReq(MsgInfo *msg,uint32_t connID)
{
    //printf("dispatching msg... PUserOPReq: %d, msgType:%d\n", PUserOPReq::uri, msg->msgType);
    switch(msg->msgType)
    {
        case PUserLoginReq::uri: _impl->onUserLogin(msg,connID); break;
        case PUserPingReq::uri: _impl->onUserPing(msg,connID); break;
        case PUserRegReq::uri: _impl->onUserReg(msg,connID); break;
        case PUserSaveReq::uri: _impl->onUserSave(msg,connID); break;
        case PUserLoadReq::uri: _impl->onUserLoad(msg,connID); break;
        case PUserOPReq::uri: _impl->onUserOP(msg,connID); break;
    }

    return 0;
}





