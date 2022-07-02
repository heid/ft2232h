#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ft2232h.h"
#include <QThread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onBytesReceived(int bytesCount);

private slots:
    void onClick();
    void timeOut();

private:
    Ui::Widget *ui;
    FT2232H *ft;
    QThread *ftThread;
    QTimer *m_tmrReadingSpeed;
    int m_bytesReceived;
};

#endif // WIDGET_H
