#include "ConfigMgr.h"
#include <qdebug.h>


ConfigMgr* ConfigMgr::inst = 0;
ConfigMgr *ConfigMgr::instance(){
	if ( inst) return inst;
	return inst = new ConfigMgr();
}

void ConfigMgr::makeDefault(){

	QFile file( "ac1608.xml" );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	delete doc_;
	QDomDocument &doc = *(doc_ = new QDomDocument() );

	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction( "xml", "version = \'1.0\'" );
	doc.appendChild( instruction );

	QDomElement root = doc.createElement( XML_ROOT );
	doc.appendChild( root );
	QDomElement addresses = doc.createElement( XML_ADDRESSES );
	root.appendChild( addresses );

	QDomElement address = doc.createElement( XML_ADDRESS );
	addresses.appendChild( address );
	address.setAttribute( "location", "home");
	address.setAttribute( "ip", "192.168.1.100");

	QDomElement devices = doc.createElement( XML_DEVICES );
	root.appendChild( devices );
	QDomElement device = doc.createElement( XML_DEVICE );
	devices.appendChild( device );
	device.setAttribute( "title", "password");
	device.setAttribute( "ip", "192.168.1.100");

	
	QDomElement settings = doc.createElement( XML_SETTINGS );
	root.appendChild(settings);

	QDomElement setting = doc.createElement( XML_SETTING );
	settings.appendChild(setting);
	setting.setAttribute( "componentType", "slider");
	setting.setAttribute( "min", "-100");
	setting.setAttribute( "max", "24");
	setting.setAttribute( "default", "0");

	setting = doc.createElement( XML_SETTING );
	settings.appendChild(setting);
	setting.setAttribute( "componentType", "progressBar");
	setting.setAttribute( "min", "-100");
	setting.setAttribute( "max", "20");
	setting.setAttribute( "default", "0");

	QTextStream out( &file );
	doc.save( out, 4 );

	file.close();
}

ConfigMgr::ConfigMgr():isOidEditable_(false)
{
	doc_  = new QDomDocument();
	QFile file( "ac1608.xml" );

	if ( !file.open( QIODevice::ReadOnly  ) || !doc_->setContent( &file) )
	{
		file.close();
		makeDefault();
		return ;
	}
	file.close();

	loadDefaultConfig();
}

void ConfigMgr::loadDefaultConfig(){
	defaultDoc_  = new QDomDocument();
	QFile file( "default.xml" );
	QDomDocument &doc(*defaultDoc_);

	if ( !file.open( QIODevice::ReadOnly  ) || !doc_->setContent( &file) )
	{
		defaultDoc_ = doc_;
		file.close();
		return ;
	}
	file.close();

	QDomElement root = doc.documentElement();
	if ( root.nodeName()!= XML_ROOT){
		defaultDoc_ = doc_;
		return;
	}
}

ConfigMgr::~ConfigMgr()
{	

	saveAll();
	if ( defaultDoc_ != doc_ ) {
		delete defaultDoc_;
		defaultDoc_ = 0;
	}

	delete doc_;
	doc_ = 0;
}

void ConfigMgr::saveAll(){
	QFile file1( "ac1608.xml" );
	if ( !file1.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	QTextStream out( &file1 );
	doc_->save( out, 4 );
}

QDomElement ConfigMgr::getAddressElem(){
	QDomElement root = doc_->documentElement();
	if ( root.nodeName()!= XML_ROOT){
		return QDomElement();
	}

	QDomElement addresses = root.firstChildElement();
	if ( addresses.nodeName() != XML_ADDRESSES ){
		return QDomElement();
	}

	return addresses;
}

QString getOidFromDoc( const QString &id, QDomDocument * doc){
	if ( !doc && id.isEmpty() ) return "";
	QDomElement root = doc->documentElement();

	QDomNodeList items = root.elementsByTagName("component");
	QString oid;
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("id") == id ){
			oid = elem.attribute("oid");
			//elem.attribute( "max");
			//elem.attribute( "min");
			//elem.attribute( "default");
			//elem.attribute( "floatNum");
			break;
		}

	}
	return oid;
}

QString ConfigMgr::getOid( const QString &id){
	return getOidFromDoc(id, doc_);
}

QString ConfigMgr::getDefaultOid( const QString &id){
	return getOidFromDoc(id, defaultDoc_);
}
QString ConfigMgr::getSetting( const QString &type, int & max, int & min, int & defaultVal){
	if ( !doc_ && type.isEmpty() ) return false;
	QDomElement root = doc_->documentElement();

	QDomNodeList items = root.elementsByTagName("setting");
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		//QDomNode n1 = node.attributes().item(1);
		QDomElement elem = node.toElement();
		if ( type == elem.attribute("componentType")){
			max = elem.attribute("max").toInt();
			min = elem.attribute("min").toInt();
			defaultVal = elem.attribute("default").toInt();
			return true;
		}

	}
	return false;
}

bool ConfigMgr::getValue( const QString &id, QString &val){
	if ( !doc_ && id.isEmpty() ) return false;
	QDomElement root = doc_->documentElement();

	QDomNodeList items = root.elementsByTagName("value");
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomNode n1 = node.attributes().item(1);
		if ( "id" == n1.nodeName()&& id == n1.nodeValue() ){
			val = node.attributes().item(0).nodeValue();
			return true;
		}

	}
	return false;
}

bool ConfigMgr::getProperty( const QString &id, QString &oid){
	if ( !doc_ && id.isEmpty() ) return false;
	QDomElement root = doc_->documentElement();

	QDomNodeList items = root.elementsByTagName("component");
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomNode n1 = node.attributes().item(1);
		if ( "id" == n1.nodeName()&& id == n1.nodeValue() ){
			oid = node.attributes().item(0).nodeValue();
			//max = node.attributes().item(1).nodeValue().toFloat();
			//min = node.attributes().item(2).nodeValue().toFloat();
			//defaultVal = node.attributes().item(3).nodeValue().toFloat();
			//floatNum = node.attributes().item(4).nodeValue().toInt();
			return true;
		}

	}
	return false;
}
void ConfigMgr::setProperty( const QString &id, const QString &oid){
	if ( !doc_ && id.isEmpty() ) return ;
	QDomElement root = doc_->documentElement();
	QDomNodeList items = root.elementsByTagName("component");
	bool found = false;
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("id") == id ){
			elem.setAttribute("id", id);
			elem.setAttribute("oid", oid);
			//elem.setAttribute( "max", max);
			//elem.setAttribute( "min", min);
			//elem.setAttribute( "default", defaultVal);
			//elem.setAttribute( "floatNum", floatNum);
			found = true;
			break;
		}
	}
	if ( found == false){
		QDomNodeList items = root.elementsByTagName("components");
		QDomNode node = items.at(0);
		QDomElement elem = doc_->createElement( "component");
		elem.setAttribute ("id", id);
		elem.setAttribute("oid", oid);
		//elem.setAttribute( "max", max);
		//elem.setAttribute( "min", min);
		//elem.setAttribute( "default", defaultVal);
		//elem.setAttribute( "floatNum", floatNum);
		node.insertAfter( elem, QDomElement());
	}
}

void ConfigMgr::setOid( const QString &id, const QString &oid){
	if ( !doc_ && id.isEmpty() ) return ;
	QDomElement root = doc_->documentElement();
	QDomNodeList items = root.elementsByTagName("component");
	bool found = false;
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("id") == id ){
			elem.setAttribute("id", id);
			elem.setAttribute("oid", oid);
			//elem.setAttribute( "max", 0);
			//elem.setAttribute( "min", 0);
			//elem.setAttribute( "default", 0);
			//elem.setAttribute( "floatNum", 0);
			found = true;
			break;
		}
	}
	if ( found == false){
		QDomNodeList items = root.elementsByTagName("components");
		QDomNode node = items.at(0);
		QDomElement elem = doc_->createElement( "component");
		elem.setAttribute ("id", id);
		elem.setAttribute( "oid", oid);
		//elem.setAttribute( "max", 0);
		//elem.setAttribute( "min", 0);
		//elem.setAttribute( "default", 0);
		//elem.setAttribute( "floatNum", 0);
		node.insertAfter( elem, QDomElement());
	}
}

void ConfigMgr::setIP( const QString &ip, const QString &loc){
	QDomElement root = doc_->documentElement();
	QDomNodeList items = root.elementsByTagName("address");
	bool found = false;
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("ip") == ip ){
			elem.setAttribute ("location", loc);
			found = true;
			break;
		}
	}
	if ( found == false){
		QDomNodeList items = root.elementsByTagName("addresses");
		QDomNode node = items.at(0);
		QDomElement elm = doc_->createElement( "address");
		elm.setAttribute ("ip", ip);
		elm.setAttribute ("location", loc);
		node.insertAfter( elm, QDomElement());
	}
}
void ConfigMgr::removeIP( const QString &ip){
	QDomElement root = doc_->documentElement();
	QDomNodeList addressRoot = root.elementsByTagName("addresses");
	QDomNode addressRootNode = addressRoot.at(0);
	QDomNodeList items = root.elementsByTagName("address");
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("ip") == ip ){
			addressRootNode.removeChild(node);
			break;
		}
	}
}