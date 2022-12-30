#include <iostream>

#include <include/mainwindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _form(new Ui::MainWindow)
{
    _form->setupUi(this);

    // Fixed form size
    this->setFixedSize(this->width(), this->height());

    _timer.stop();

    QObject::connect(_form->playVideoButton, SIGNAL(clicked()), this, SLOT(startPlayVideo()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(playVideo()));

    _size = cv::Size(_form->label->geometry().width(), _form->label->geometry().height());
}

MainWindow::~MainWindow()
{
    _capture.release();
    delete _form;
}

void MainWindow::playVideo()
{
    std::lock_guard<std::mutex> lock(_mtx);
    if (_capture.read(_frame)) {
        cv::resize(_frame, _frame, _size, 0, 0);
        const QImage qimg(_frame.data, _frame.cols, _frame.rows, _frame.step, QImage::Format_RGB888);
        _form->label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
    }
}

void MainWindow::startPlayVideo()
{
    _timer.stop();

    _capture.open(_form->fileNameEdit->toPlainText().toStdString());
    if (!_capture.isOpened()) {
        std::cerr << "Cannot open the video camera!" << std::endl;
        clearVideo();
        return;
    }

    _timer.start(1);
}

void MainWindow::clearVideo()
{
    _frame = cv::Mat(_size, CV_8UC3, cv::Scalar(0, 0, 0));
    const QImage qimg(_frame.data, _frame.cols, _frame.rows, _frame.step, QImage::Format_RGB888);
    _form->label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
}