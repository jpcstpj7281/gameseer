#ifndef PRESETWND_H
#define PRESETWND_H

#include <QWidget>
#include <map>
namespace Ui {
class PresetWnd;
}

class QPushButton;
class QRadioButton;

class Preset : public QObject{
	Q_OBJECT

public:
	QPushButton * open_;
	QPushButton * save_;
	QPushButton * upload_;
	QPushButton * download_;
	QRadioButton* select_;
	private slots:
	void save();
	void open();
	void upload();
	void download();
	void select();
};

class PresetWnd : public QWidget
{
    Q_OBJECT
    private slots:
	void saveAs();
	void openFrom();
public:
    explicit PresetWnd(QWidget *parent = 0);
    ~PresetWnd();
    
private:
	Preset* usePreset(const QString & id);
    Ui::PresetWnd *ui;
	QList<QPushButton *> qpbtnl_;
	QList<QRadioButton *> qrbtnl_;
	std::map<QString, Preset*> presets_;
	QString currPresetId_;
};

#endif // PRESETWND_H
