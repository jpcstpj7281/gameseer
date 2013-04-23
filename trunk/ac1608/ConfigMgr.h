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

	void setIP( const QString &ip, const QString &loc);
	void removeIP( const QString &ip);
	void setOid( const QString &id, const QString &oid);
	QString getOid( const QString &id);
	QString getDefaultOid( const QString &id);

	QString getSetting( const QString &type, int & max, int & min, int & defaultVal);

	bool getProperty( const QString &id, QString &oid);
	void setProperty( const QString &id, const QString &oid);

	bool getValue( const QString &id, QString &val);
	void saveAll();

	~ConfigMgr();

	static ConfigMgr *instance();

	inline QDomDocument* getDoc(){ return doc_;}

	QDomElement getAddressElem();

	void makeDefault();
};
#endif // CONFIGMGR_H