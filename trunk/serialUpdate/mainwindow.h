#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <asio.hpp>

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


       // void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);

		QString path_;
		//char buf_[1024];

		asio::serial_port *sp_;
		asio::io_service ios_;
		asio::streambuf buf_;
		void handleRead(asio::error_code ec, std::size_t bytes_transferred);
		void handleWritePing(asio::error_code ec, std::size_t bytes_transferred);
		virtual void	timerEvent ( QTimerEvent * event )override;
		void switchCmd( size_t cmd, const std::string &data, size_t len, size_t pos);
};

#endif // MAINWINDOW_H
