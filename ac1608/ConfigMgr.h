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

	QDomDocument *doc_;
	QDomDocument *defaultDoc_;
	QFile *_file;

	
	bool isOidEditable_;
	void loadDefaultConfig();


public :

	inline bool isOidEditable(){ return isOidEditable_;}

	inline void setOidEditable( bool flag){	 isOidEditable_ = flag;	}

	void setOid( QString &id, QString &oid);
	QString getOid( QString &id);
	QString getDefaultOid( QString &id);

	~ConfigMgr();

	static ConfigMgr *instance();

	inline QDomDocument* getDoc(){ return doc_;}

	QDomElement getAddressElem();

	void makeDefault();
};
#endif // CONFIGMGR_H