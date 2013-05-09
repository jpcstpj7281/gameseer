#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>  
#include <QMenu>  
#include <asio.hpp>

class DevicesWnd;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
		private slots:
			void clickStart();
			void clickLoad();
		
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
		QString path_;
		//char buf_[1024];

		asio::serial_port sp_;
		asio::io_service ios_;
		asio::streambuf buf_;
		void handleRead(asio::error_code ec, std::size_t bytes_transferred);
		virtual void	timerEvent ( QTimerEvent * event )override;
};

#endif // MAINWINDOW_H
