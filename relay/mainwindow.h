#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>  
#include <QMenu>  


class DevicesWnd;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
		private slots:
			void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason);
			void actionShow();
			void actionExit();
		
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:

        Ui::MainWindow *ui;

        DevicesWnd *devicesWnd_;
		//std::vector< QWidget*> modules_;

       // void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);

		QSystemTrayIcon *trayicon;  
		QMenu *trayiconMenu;  
};

#endif // MAINWINDOW_H
