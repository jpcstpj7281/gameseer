#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include <QDomDocument>
#include <QFile>
#include <QTextStream>


#define XML_ROOT "root"
#define XML_ADDRESSES "addresses"
#define XML_ADDRESS "address"
#define XML_DEVICES "devices"
#define XML_DEVICE	"device"

class ConfigMgr{


	static ConfigMgr* inst;
	ConfigMgr();
	

	QDomDocument *_doc;
	QFile *_file;

	
public :

	~ConfigMgr();

	static ConfigMgr *instance();

	inline QDomDocument* getDoc(){ return _doc;}

	QDomElement getAddressElem();

	void makeDefault();
};
#endif // CONFIGMGR_H