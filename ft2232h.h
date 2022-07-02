#ifndef FT2232H_H
#define FT2232H_H

#include <QObject>
#include "ftd2xx.h"
#include <QThread>

enum {
    BUF_SIZE = 0x10000
};

class FT2232H : public QObject {
    Q_OBJECT

public:
    explicit FT2232H(QObject *parent = nullptr);
    static int getDevices(char *devices[]);
    FT_STATUS open(int devIndex);
    FT_STATUS set245FIFO();
    void startReading();

public slots:
    void stopReading();

signals:
    void onBytesReceived(int bytesCount);

private:
    FT_HANDLE m_ftHandle;
    bool m_first;
    uint8_t m_etalonData;
};

#endif // FT2232H_H
