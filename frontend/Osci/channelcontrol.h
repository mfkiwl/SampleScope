#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include <QCheckBox>
#include <QWidget>
#include "device.h"

namespace Ui {
class ChannelControl;
}

class ChannelControl : public QWidget
{
        Q_OBJECT

public:
        explicit ChannelControl(QWidget *parent = 0);
        ~ChannelControl();

        void setChannel(DeviceConstants::Channel_t c);
        void initialEmit();
        bool isActive();
        bool fitSin();
        void setFitData(double a0, double a1, double a2);

private slots:
        void vdivValueChanged(int gain);
        void acdcValueChanged(bool acdc);
signals:
        void vdivSelected(QString hr, Device::VdivValues_t code);
        void acdcSelected(DeviceConstants::ACDC_t acdc);
private:
        Ui::ChannelControl *ui;
        DeviceConstants::Channel_t channel;
};

#endif // CHANNELCONTROL_H
