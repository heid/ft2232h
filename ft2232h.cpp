#include "ft2232h.h"
#include <QDebug>

FT2232H::FT2232H(QObject *parent) : QObject(parent) {

    m_first = true;
}

int FT2232H::getDevices(char *devices[]) {
    FT_STATUS ftStatus;
    int numDevs;

    ftStatus = FT_ListDevices(devices, &numDevs, FT_LIST_ALL|FT_OPEN_BY_DESCRIPTION);
    if (ftStatus == FT_OK) {

        return numDevs;
    }

    return 0;
}

FT_STATUS FT2232H::open(int devIndex) {
    FT_STATUS ftStatus;

    ftStatus = FT_Open(devIndex, &m_ftHandle);

    return ftStatus;
}

FT_STATUS FT2232H::set245FIFO() {
    FT_STATUS ftStatus;

    UCHAR Mask = 0xff;
    UCHAR Mode = 0;                                                 // reset mode
    UCHAR LatencyTimer = 2;                                        // 2-255 ms

    ftStatus = FT_SetBitMode(m_ftHandle, Mask, Mode);
    QThread::msleep(10);

    Mode = 0x40;                                                    // Sync FIFO mode
    ftStatus = FT_SetBitMode(m_ftHandle, Mask, Mode);
    if (ftStatus == FT_OK) {
        ftStatus = FT_SetLatencyTimer(m_ftHandle, LatencyTimer);
        ftStatus = FT_SetUSBParameters(m_ftHandle, 0x10000, 0x10000);
        ftStatus = FT_SetFlowControl(m_ftHandle, FT_FLOW_RTS_CTS, 0, 0);
//        ftStatus = FT_Purge(m_ftHandle, FT_PURGE_RX);
    }

    return ftStatus;
}

void FT2232H::startReading() {
    uchar RxBuffer[BUF_SIZE];
    FT_STATUS ftStatus;
    DWORD RxBytes = 0;
    DWORD TxBytes;
    DWORD EventDWord;
    DWORD BytesReceived;

    ftStatus = FT_Purge(m_ftHandle, FT_PURGE_RX);

    while (1) {
        /*while (RxBytes != BUF_SIZE) {
            ftStatus = FT_GetStatus(m_ftHandle, &RxBytes, &TxBytes, &EventDWord);
        }*/

        ftStatus = FT_GetStatus(m_ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if (RxBytes > 0) {
            ftStatus = FT_Read(m_ftHandle, RxBuffer, RxBytes, &BytesReceived);
            emit onBytesReceived(BytesReceived);

            if (m_first) {
                m_first = false;

                m_etalonData = RxBuffer[0];
            }

            for (int i = 0; i < BytesReceived; i++, m_etalonData++) {
                if (RxBuffer[i] != m_etalonData) {
                    qDebug() << "Data doesn't match! Receive = " << RxBuffer[i] << "Expected = " << m_etalonData << "i = " << i;
                    m_etalonData++;
                }
            }
        }
    }
}

void FT2232H::stopReading() {

    FT_Close(m_ftHandle);
}
