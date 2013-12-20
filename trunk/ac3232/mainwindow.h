#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class InputGainCtrlWnd;
class ChangePasswordWnd;
class CopyParamWnd;
class DevicesWnd;
class GateNOMWnd;
class HighPassWnd;
class Level8CHWnd;
class MatrixMixerWnd;
class MetersWnd;

class PEQWnd;
class PresetWnd;

class HomePage;
class NOMWnd;
class CobraNetWnd;
class SnmpNetWnd;


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

		
    public:

		enum Mode{
			ControlMode,
			EditMode,
		};

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

		void setMode( Mode mode){
			_mode = mode;
		}
		Mode getMode(){
			return _mode ;
		}

		
    private slots:
        void on_actionCopyParam_clicked(QAction*);
		void on_actionEdit_clicked(QAction*);

    private:

		QTabWidget* tab_;
		Mode _mode;

        Ui::MainWindow *ui;

		std::vector< QWidget*> modules_;

		void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);


};

#endif // MAINWINDOW_H
