#ifndef DEVICE_H
#define DEVICE_H

#include <vector>
#include <QObject>
#include <QPointF>
#include <QVector>
#include "../HIDAPI/hidapi.h"
#include "../../shared/common.h"

#define MAX_STR 65

class Device : public QObject
{
        typedef float sample_t;
        Q_OBJECT

public:
        typedef unsigned short triggerLevel_t;
    /*
        enum Channel_t {
                ADC_ch1 = 0,
                ADC_ch2 = 1,
                ADC_triggerLevel = 2
        };

        enum TriggerSource_t {
                Trigger_Ch1,
                Trigger_Ch2,
                Trigger_Free
        };

        enum ACDC_t {
                ACDC_AC = 1,
                ACDC_DC = 0
        };*/
        enum VdivValues_t {
                Vdiv_10,
                Vdiv_5,
                Vdiv_2,
                Vdiv_1,
                Vdiv_05,
                Vdiv_02,
                Vdiv_01,
                Vdiv_005,
                Vdiv_LAST = Vdiv_005
        };
        enum TdivValues_t {
                Tdiv_max, // = 0.0128
                Tdiv_003,
                Tdiv_01, Tdiv_03,
                Tdiv_1, Tdiv_3,
                Tdiv_10, Tdiv_30,
                Tdiv_100, Tdiv_300,
                Tdiv_1000, Tdiv_3000,
                Tdiv_LAST = Tdiv_3000
        };

        enum {
                RX_SIZE = 10
        };
public:
        explicit Device(QObject *parent = 0);
        ~Device();

        bool isConnected() { return device != NULL; }
        void connect();
        void disConnect();



        void setVdiv(VdivValues_t gaina, VdivValues_t gainb);
        void ping();
        void setTriggerLevel(triggerLevel_t level);
        void selectChannel(DeviceConstants::Channel_t ch);
        sample_t getADCSingle();
        QVector<QPointF> getADCBlock(int delay = 0);

        void getADCInterleaved(int delay, QVector<QPointF>& ch1, QVector<QPointF>& ch2);
        void setACDC_Ch1(DeviceConstants::ACDC_t ch1);
        void setACDC_Ch2(DeviceConstants::ACDC_t ch2);
        void selectTriggerSource(DeviceConstants::TriggerSource_t trigger_source);
        DeviceConstants::TriggerSource_t getTriggerSource() { return config.triggerChannel; }


        static QString getTdivUnit(TdivValues_t);
        static QString getTdivLabel(TdivValues_t);
        static QString getVdivLabel(VdivValues_t);
        static QString getChannelName(DeviceConstants::Channel_t);
signals:
        void connected(bool connected);
        void fatal(QString message);

public slots:
        void refresh();

private:
        hid_device* device;
        unsigned char buf[MAX_STR];

        sample_t normalizeSample(unsigned char val) {
                return 2.05 * (val - 128) / 128.0;
        }
        void comm(const unsigned char command);
        DeviceConstants::osci_config_t config;
        void transmitConfig();
};

#endif // DEVICE_H
