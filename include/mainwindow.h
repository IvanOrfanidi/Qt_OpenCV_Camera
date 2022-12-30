#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <include/ui_mainwindow.h>
#include <opencv2/opencv.hpp>

#include <mutex>
#include <string>

#include <QMainWindow>
#include <QTimer>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    QTimer _timer;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void startPlayVideo();
    void playVideo();
    void clearVideo();

private:
    Ui::MainWindow* _form;

    cv::VideoCapture _capture;
    cv::Size _size;
    cv::Mat _frame;
};

#endif // MAINWINDOW_H
