#ifndef OIDINPUTDLG_H
#define OIDINPUTDLG_H

#include <QWidget>
#include <QDialog>



namespace Ui {
class OIDInputDlg;
}

class OIDInputDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit OIDInputDlg(QWidget *parent = 0);
    ~OIDInputDlg();

	static QString getNewOid(QString &id);
	static OIDInputDlg *instance();
private slots:    
 
	void okClick();
	void defaultClick();
	void cancelClick();

private:

	void closeEvent ( QCloseEvent * event );
	QString id_, oldOid_, defaultOid_;
	static OIDInputDlg * inst;
    Ui::OIDInputDlg *ui;
};

#endif // OIDINPUTDLG_H
