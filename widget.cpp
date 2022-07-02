#include "widget.h"
#include "ui_widget.h"

#include "ftd2xx.h"
#include <QDebug>
#include <QThread>

FT_HANDLE ftHandle;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {

    ui->setupUi(this);

    connect(ui->btnOpen, &QPushButton::clicked, this, &Widget::onClick);

    char *BufPtrs[4];                                               // pointer to array of 4 pointers
    char Buffer1[64];                                               // buffer for description of first device
    char Buffer2[64];                                               // buffer for description of second device
    char Buffer3[64];                                               // buffer for description of second device

    // initialize the array of pointers
    BufPtrs[0] = Buffer1;
    BufPtrs[1] = Buffer2;
    BufPtrs[2] = Buffer3;
    BufPtrs[3] = NULL;                                              // last entry should be NULL

    int numDevs = FT2232H::getDevices(BufPtrs);
    if (numDevs > 0) {
        for (int i = 0; i < numDevs; i++) {
            ui->cbDevices->addItem(BufPtrs[i]);
        }
    } else {
        qDebug() << "FTDI devices not found!";
        close();
    }

    ftThread = new QThread(this);

    ft = new FT2232H();
    ft->moveToThread(ftThread);
    connect(ftThread, &QThread::started, ft, &FT2232H::startReading);
    connect(ft, &FT2232H::onBytesReceived, this, &Widget::onBytesReceived);

    m_tmrReadingSpeed = new QTimer();
    connect(m_tmrReadingSpeed, &QTimer::timeout, this, &Widget::timeOut);
}

Widget::~Widget() {

    delete ui;
}

void Widget::onBytesReceived(int bytesCount) {

    if (!m_tmrReadingSpeed->isActive()) {
        m_tmrReadingSpeed->start(1000);
    }

    m_bytesReceived += bytesCount;
}

void Widget::onClick() {

    int devNum = ui->cbDevices->currentIndex();
    if (ft->open(devNum) != FT_OK)
    {
        qDebug() << "Open failed!";
        close();
    }

    if (ft->set245FIFO() != FT_OK) {
        qDebug() << "Set 245 FIFO mode failed!";
        close();
    }

    ftThread->start();
}

void Widget::timeOut() {

    ui->lblReadingSpeed->setText(QString("%1 МБайт/c").arg(QString::number(m_bytesReceived/1024.0/1024.0, 'f', 1)));
    m_bytesReceived = 0;
}

