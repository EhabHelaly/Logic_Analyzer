#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomPlot.h"
#include "serial.h"
#include <windows.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logs={
        ui->log_1,
        ui->log_2,
        ui->log_3,
        ui->log_4,
        ui->log_5,
        ui->log_6,
        ui->log_7,
        ui->log_8
    };
    decode_pops={
        ui->pop_decode_1,
        ui->pop_decode_2,
        ui->pop_decode_3,
        ui->pop_decode_4,
        ui->pop_decode_5,
        ui->pop_decode_6,
        ui->pop_decode_7,
        ui->pop_decode_8
    };
    clk_pops={
        ui->pop_clk_1,
        ui->pop_clk_2,
        ui->pop_clk_3,
        ui->pop_clk_4,
        ui->pop_clk_5,
        ui->pop_clk_6,
        ui->pop_clk_7,
        ui->pop_clk_8
    };

    plotInit();
    loadSettings();

    auto serial_timer = new QTimer(parent);
    serial_timer->setInterval(1000);
    connect(serial_timer, &QTimer::timeout, [this]{this->checkHardware();});
    serial_timer->start();

    /* Program main loop */
    plotting_timer = new QTimer(parent);
    plotting_timer->setInterval(30);
    connect(plotting_timer, &QTimer::timeout, [this]{this->plotRun();});
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::getBaudrate()
{
    /* max_sample_rate = 2 * uart_sample_rate = 2 * ( baud_rate / 10 ) */
    /* baud_rate = max_frequency * 5 */
    return max_sampling_rate[ ui->pop_clkFreq->currentIndex() ] * 5;
}
double MainWindow::getSamplingTime()
{
    /* sampling_rate = max_sampling_rate * sampling_rate_factor */
    /* sampling_rate_factor = 1000 / sampling_rate  <in milli seconds> */
    return 1000.0 / ( max_sampling_rate[ ui->pop_clkFreq->currentIndex() ] * sampling_rate_factor[mode] );
}

void MainWindow::plotInit()
{
    const QBrush brushes[]={
        QBrush(QColor(  0, 255,  30)),    /* green */
        QBrush(QColor(  0, 255, 100)),    /* bluish green */
        QBrush(QColor(  0, 255, 255)),    /* cyan */
        QBrush(QColor( 25,  80, 255)),    /* blue */
        QBrush(QColor(255,   0, 255)),    /* violet */
        QBrush(QColor(255,  30, 100)),    /* purple */
        QBrush(QColor(255, 150,  30)),    /* orange */
        QBrush(QColor(255, 255,   0)),    /* yellow */
    };

    /* Enable OpenGL graphics hardware acceleration */
    ui->plot->setOpenGl(true);

    /* create graphs  */
    for(int g=0; g<LA_MAX_CHANNELS; g++)
    {
        ui->plot->addGraph();
        ui->plot->graph(g)->setPen(QPen(brushes[g],2));
        ui->plot->graph(g)->setAdaptiveSampling(true);
    }

    // --------------------------------------------------------
    ui->plot->setBackground(QBrush(color_plot[theme_settings]));

    ui->plot->setInteraction(QCP::iRangeZoom);
    ui->plot->setInteraction(QCP::iRangeDrag);
    ui->plot->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->plot->axisRect()->setRangeZoom(Qt::Horizontal);



    ui->plot->xAxis->setNumberPrecision(-3);
    ui->plot->xAxis->setBasePen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setSubTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setTickLabelColor(color_plot[1-theme_settings]);
    ui->plot->xAxis->grid()->setSubGridVisible(true);
    ui->plot->xAxis->grid()->setPen(QPen(color_grid[theme_settings], 0, Qt::SolidLine));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(color_subGrid[theme_settings], 0, Qt::DotLine));
    ui->plot->xAxis->setLabel("T (msec)");
    ui->plot->xAxis->setLabelColor(color_plot[1-theme_settings]);
    ui->plot->xAxis->setRange(0, LA_MAX_WINDOW);

    ui->plot->yAxis->setBasePen(QPen(color_plot[1-theme_settings]));
    ui->plot->yAxis->setTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->yAxis->setSubTickPen(Qt::NoPen);
    ui->plot->yAxis->setTickLabelColor(color_plot[theme_settings]);
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->grid()->setPen(QPen(color_grid[theme_settings], 0, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(color_subGrid[theme_settings], 0, Qt::DotLine));
    ui->plot->yAxis->setRange(0, LA_MAX_CHANNELS);

    ui->plot->replot();
}
void MainWindow::plotRun()
{
    double t_last = (ui->plot->graph(0)->data()->size())? ((ui->plot->graph(0)->data()->end()-1)->key) : 0;
    double dt     = getSamplingTime();
    int size = 0;

    if (serialReceive(buffer+buffer_offset, size))
    {
        switch(mode)
        {
        case LA_MODE_DIGITAL:
        {
            for (int i=0; i<size; i++)
            {
                plotNewByte( buffer[i] , t_last, dt, i);
            }
            break;
        }
        case LA_MODE_DIGITAL_X2:
        {
            for (int i=0; i<size; i++)
            {
                plotNewByte( buffer[i]>>4   , t_last, dt, i*2);      /* high nibble */
                plotNewByte( buffer[i]&0x0F , t_last, dt, i*2+1);    /* low  nibble */
            }
            size<<=1;    /* real data size = size * 2 */
            break;
        }
        case LA_MODE_ANALOG:
        {
            uint16_t adc_raw_value=0;   /* stores Received 10 bit resolution ADC value */
            double adc_disp_value=0;   /* stores Displayed 10 bit resolution ADC value */
            if (buffer_offset==1)
            {
                size++;
            }
            for (int i=0; i<size-1; i+=2)
            {
                adc_raw_value = 0x3FF & *( (uint16_t*)(buffer+i) ); /* Get 16 bit value (low and high bytes of ADC)(Little Endian) */
                adc_disp_value = adc_scale/1023*adc_raw_value;
                signals_a[0].data->add(QCPGraphData( t_last + (i/2+1)*dt , adc_disp_value ));
                plotAnalog(adc_disp_value, t_last, dt, i/2);
            }

            buffer_offset = size&1;  /* buffer offset = 0 when size is even , = 1 when size is odd */
            if(size&1) /* size is an odd number */
            {
                buffer[0]=buffer[size-1];   /* move the last un processed byte to begining of buffer */
            }
            size>>=1;    /* real data size = size / 2 */
            /* stretsh plot to end of current time */
            (signals_a[0].binary.data->end()-1)->key = t_last + dt*size;

            break;
        }
        case LA_MODE_ANALOG_X2:
        {
            double adc_disp_value=0;   /* stores Displayed 8 bit resolution ADC value */
            for (int i=0; i<size; i++)
            {
                adc_disp_value = adc_scale/255*buffer[i];
                signals_a[0].data->add(QCPGraphData( t_last + (i+1)*dt , adc_disp_value ));
                plotAnalog(adc_disp_value, t_last, dt, i);
            }
            /* stretsh plot to end of current time */
            (signals_a[0].binary.data->end()-1)->key = t_last + dt*size;
            break;
        }
        }

        /* stretsh all plots to end of current time */
        for(int b=0;b<signals_d.size(); b++)
        {
            (ui->plot->graph(b)->data()->end()-1)->key = t_last + dt*size;
        }
    }


    if (t_last>LA_MAX_WINDOW)
    {
        ui->plot->xAxis->setRange(t_last-LA_MAX_WINDOW, t_last);
    }
    ui->plot->replot();

    /* stop capturing after recahing time limit */
    if (t_last>=ui->spin_msec->value())
    {
        on_pushB_capture_pressed();
    }
}
void MainWindow::plotAnalog(double adc_disp_value, double t_last, double dt, uint32_t i)
{
    /* Digital signal using schmitt trigger */
    if (signals_a[0].binary.data->size() == 0)  /* first sample ? */
    {
        double value = (adc_disp_value> (adc_scale*ui->spin_schmittHigh->value()) )? adc_high:adc_low ;
        {
            signals_a[0].binary.data->add(QCPGraphData(  0, value ));
            signals_a[0].binary.data->add(QCPGraphData( dt, value ));
        }

    }
    else    /* following samples */
    {
        double value = (signals_a[0].binary.data->end()-1)->value ;
        if( (IS_SIGNAL_HIGH(value) && (adc_disp_value< (adc_scale * ui->spin_schmittLow->value()) ) ) ||
            (IS_SIGNAL_LOW(value) && (adc_disp_value> (adc_scale * ui->spin_schmittHigh->value()) ) ) )
        {
            /* reverse last edge value */
            value = IS_SIGNAL_HIGH(value)? adc_low : adc_high;
            /* change last edge time */
            (signals_a[0].binary.data->end()-1)->key = t_last + (i*dt);
            /* add 2 points with same time and value */
            signals_a[0].binary.data->add(QCPGraphData( t_last + (i+1)*dt , value ));
            signals_a[0].binary.data->add(QCPGraphData( t_last + (i+1)*dt , value ));
        }

    }
}
void MainWindow::plotNewByte(uint8_t byte, double t_last, double dt, uint32_t i)
{
    if (ui->plot->graph(0)->data()->isEmpty()) /* first byte of data? */
    {
        for(int b=0;b<signals_d.size(); b++)
        {
            /* b0 (high) = 1.0 , b0 (low) = 0.5 */
            /* b1 (high) = 2.0 , b1 (low) = 1.5 */
            /* ........... and so on .......... */
            double value = ( byte&(1<<b) )? b+1: b+0.5;
            ui->plot->graph(b)->data()->add(QCPGraphData(  0 , value ));
            ui->plot->graph(b)->data()->add(QCPGraphData( dt , value ));
        }
        byte_old=byte;
    }
    else
    {
        unsigned char new_edge=byte_old^byte;
        if (new_edge)
        {
            for(int b=0;b<signals_d.size(); b++)
            {
               if (new_edge& (1<<b)) /* bit changed ? */
               {
                   /* reverse last edge value */
                   double value = (ui->plot->graph(b)->data()->end()-1)->value;
                   value = (value==b+0.5)? value+0.5 : value-0.5;
                   /* change last edge time */
                   (ui->plot->graph(b)->data()->end()-1)->key = t_last + (i*dt);
                   /* add 2 points with same time and value */
                   ui->plot->graph(b)->data()->add(QCPGraphData( t_last + (i+1)*dt , value ));
                   ui->plot->graph(b)->data()->add(QCPGraphData( t_last + (i+1)*dt , value ));
                   byte_old=byte;
               }
            }
        }
    }
}

void MainWindow::analyzeDigitalSignal(uint8_t signal_index, double tStart, double tEnd)
{
    signals_d[signal_index].analyze(tStart,tEnd);
    switch(decode_pops[signal_index]->currentIndex())
    {
    case LA_DECODE_I2C:
    {
        int clk_index = clk_pops[signal_index]->currentIndex();
        signals_d[signal_index].clk = clk_index==0? signals_d[0].data : signals_d[clk_index-1].data;
        signals_d[signal_index].decodeI2C(tStart,tEnd);
        break;
    }
    case LA_DECODE_SPI:
    {
        int clk_index = clk_pops[signal_index]->currentIndex();
        signals_d[signal_index].clk = clk_index==0? signals_d[0].data : signals_d[clk_index-1].data;
        signals_d[signal_index].decodeSPI(tStart,tEnd);
        break;
    }
    case LA_DECODE_NEC:
    {
        signals_d[signal_index].decodeNEC(tStart,tEnd);
        break;
    }
    }
    showDigitalSignalInfo(signal_index);
    showDecodedSignalInfo(signal_index);
}

void MainWindow::showAnalogSignalInfo(uint8_t signal_index)
{
    logs[signal_index]->clear();
    logs[signal_index]->append(QString("Amplitude (Min)\t: %1 v").arg(signals_a[signal_index].amp_min.value) );
    logs[signal_index]->append(QString("Amplitude (Max)\t: %1 v").arg(signals_a[signal_index].amp_max.value) );
    logs[signal_index]->append(QString("Amplitude (Avg)\t: %1 v").arg(signals_a[signal_index].offset) );
    logs[signal_index]->append(QString("Delta Amp (Max): %1 v/ms").arg(signals_a[signal_index].delta_max.value) );
    logs[signal_index]->append("=== Schmitt Trigger Signal ===");
    logs[signal_index]->append(QString("Frequency (Max): %1 Hz").arg(signals_a[signal_index].binary.freq_max));
    logs[signal_index]->append(QString("Frequency (Min) : %1 Hz").arg(signals_a[signal_index].binary.freq_min));
    logs[signal_index]->append(QString("Frequency (Avg): %1 Hz").arg(signals_a[signal_index].binary.freq_avg));
    logs[signal_index]->append(QString("Waves\t: %1").arg(signals_a[signal_index].binary.waves));
    logs[signal_index]->append(QString("Duty Cycle\t: %1 %").arg(signals_a[signal_index].binary.duty_cycle));
    logs[signal_index]->append(QString("Time (Start)\t: %1 ms").arg(signals_a[signal_index].binary.time_start));
    logs[signal_index]->append(QString("Time (End)\t: %1 ms").arg(signals_a[signal_index].binary.time_end));
    logs[signal_index]->append(QString("Time (High)\t: %1 ms").arg(signals_a[signal_index].binary.time_high));
    logs[signal_index]->append(QString("Time (Low)\t: %1 ms").arg(signals_a[signal_index].binary.time_low));
    logs[signal_index]->append(QString("Pulse Width (Max): %1 ms").arg(signals_a[signal_index].binary.time_max));
    logs[signal_index]->append(QString("Pulse Width (Min) : %1 ms").arg(signals_a[signal_index].binary.time_min));
}
void MainWindow::showDigitalSignalInfo(uint8_t signal_index)
{
    logs[signal_index]->clear();
    logs[signal_index]->append(QString("Frequency (Max): %1 Hz").arg(signals_d[signal_index].freq_max));
    logs[signal_index]->append(QString("Frequency (Min) : %1 Hz").arg(signals_d[signal_index].freq_min));
    logs[signal_index]->append(QString("Frequency (Avg): %1 Hz").arg(signals_d[signal_index].freq_avg));
    logs[signal_index]->append(QString("Waves\t: %1").arg(signals_d[signal_index].waves));
    logs[signal_index]->append(QString("Duty Cycle\t: %1 %").arg(signals_d[signal_index].duty_cycle));
    logs[signal_index]->append(QString("Time (Start)\t: %1 ms").arg(signals_d[signal_index].time_start));
    logs[signal_index]->append(QString("Time (End)\t: %1 ms").arg(signals_d[signal_index].time_end));
    logs[signal_index]->append(QString("Time (High)\t: %1 ms").arg(signals_d[signal_index].time_high));
    logs[signal_index]->append(QString("Time (Low)\t: %1 ms").arg(signals_d[signal_index].time_low));
    logs[signal_index]->append(QString("Pulse Width (Max): %1 ms").arg(signals_d[signal_index].time_max));
    logs[signal_index]->append(QString("Pulse Width (Min) : %1 ms").arg(signals_d[signal_index].time_min));
}
void MainWindow::showDecodedSignalInfo(uint8_t signal_index)
{
    logs[signal_index]->append("=======");
    switch(decode_pops[signal_index]->currentIndex())
    {
    case LA_DECODE_I2C:
    {
        uint32_t frame_index=0;
        logs[signal_index]->append(QString("No: Time , Address (R/W) (A/N) "));
        logs[signal_index]->append(QString("\tNo: data"));
        logs[signal_index]->append("=======");
        for(QVector<I2cFrame>::iterator frame=signals_d[signal_index].i2cMessages.begin(); frame<signals_d[signal_index].i2cMessages.end(); frame++)
        {
            logs[signal_index]->append(QString("%1: %2 ms , 0x%3 (%4) (%5)")
                                       .arg(++frame_index)
                                       .arg(frame->time)
                                       .arg( QString("%1").arg( frame->address.data>>1    , 2, 16 , QChar('0') ).toUpper() )
                                       .arg(frame->address.data&0x1? "R":"W")
                                       .arg(frame->address.ack? "A":"N")
                                        );
            for(uint32_t index=0;index<frame->dataBytes.size();index++)
            {
                logs[signal_index]->append(QString("\t%1: 0x%2 (%3)")
                                           .arg( index+1 )
                                           .arg( QString("%1").arg( frame->dataBytes[index].data , 2, 16 , QChar('0') ).toUpper() )
                                           .arg(frame->dataBytes[index].ack? "A":"N")
                                           );

            }
        }
        break;
    }
    case LA_DECODE_SPI:
    {
        uint32_t frame_index=0;
        logs[signal_index]->append(QString("No: Time , Data"));
        logs[signal_index]->append("=======");
        for(QVector<SpiFrame>::iterator frame=signals_d[signal_index].spiMessages.begin(); frame<signals_d[signal_index].spiMessages.end(); frame++)
        {
            logs[signal_index]->append(QString("%1: %2 ms ,\t 0x%3")
                                       .arg(++frame_index)
                                       .arg(frame->time)
                                       .arg( QString("%1").arg( frame->data    , 2, 16 , QChar('0') ).toUpper() )
                                        );
        }
        break;
    }
    case LA_DECODE_NEC:
    {
        uint32_t frame_index=0;
        logs[signal_index]->append(QString("No: Time (Address, Data, Repeats)"));
        logs[signal_index]->append("=======");
        for(QVector<NecFrame>::iterator frame=signals_d[signal_index].necMessages.begin(); frame<signals_d[signal_index].necMessages.end(); frame++)
        {
            logs[signal_index]->append(QString("%1: %2 ms \t ( 0x%3 , 0x%4 , %5 )")
                                       .arg(++frame_index)
                                       .arg(frame->time)
                                       .arg( QString("%1").arg( frame->address , 4, 16 , QChar('0') ).toUpper() )
                                       .arg( QString("%1").arg( frame->data    , 2, 16 , QChar('0') ).toUpper() )
                                       .arg(frame->repeat)
                                        );
        }
        break;
    }
    }
}
void MainWindow::showPulseInfo(double x, double y)
{
    int b=y;
    if (b>=signals_d.size())
    {
        b=signals_d.size()-1;
    }
    else if(b<0)
    {
        b=0;
    }

    const QCPGraphData* found = signals_d[b].data->findBegin(x);
    if (found != (signals_d[b].data->end()-1) && (found)->key<=x ) /* found time stamp */
    {
        double pulseWidth = (found+1)->key - (found)->key;
        ui->tabWidget_2->setCurrentIndex(0);
        ui->log->append("=======");
        ui->log->append(QString("Time\t: %1 ms"        ).arg( x              ));
        ui->log->append(QString("Pulse Start\t: %1 ms" ).arg( (found)->key   ));
        ui->log->append(QString("Pulse End\t: %1 ms"   ).arg( (found+1)->key ));
        ui->log->append(QString("Pulse Width\t: %1 ms" ).arg( pulseWidth     ));
    }
}
void MainWindow::showAmplitudeInfo(double x)
{
    const QCPGraphData* found = signals_a[0].data->findBegin(x);
    if (found != (signals_a[0].data->end()-1) && (found)->key<=x ) /* found time stamp */
    {
        ui->tabWidget_2->setCurrentIndex(0);
        ui->log->append("=======");
        ui->log->append(QString("Time\t: %1 ms"     ).arg( x                ));
        ui->log->append(QString("Time Pre\t: %1 ms" ).arg( (found)->key     ));
        ui->log->append(QString("Time Post\t: %1 ms").arg( (found+1)->key   ));
        ui->log->append(QString("Amp Pre\t: %1 v"   ).arg( (found)->value   ));
        ui->log->append(QString("Amp Post\t: %1 v"  ).arg( (found+1)->value ));
        found = signals_a[0].binary.data->findBegin(x);
        if (found != (signals_a[0].binary.data->end()-1) && (found)->key<=x ) /* found time stamp */
        {
            double pulseWidth = (found+1)->key - (found)->key;
            ui->log->append(QString("Pulse Start\t: %1 ms" ).arg( (found)->key   ));
            ui->log->append(QString("Pulse End\t: %1 ms"   ).arg( (found+1)->key ));
            ui->log->append(QString("Pulse Width\t: %1 ms" ).arg( pulseWidth     ));
        }
    }
}
void MainWindow::loadSettings()
{
    QSettings settings("Ehab", "LogicAnalyzer");

    /* check if settings exists */
    if (settings.value(ui->spin_port->objectName()+"/value").toInt()!=0)
    {
        ui->pop_clkFreq->setCurrentIndex(settings.value(ui->pop_clkFreq->objectName()+"/currentIndex").toInt());
        ui->pop_mode->setCurrentIndex(settings.value(ui->pop_mode->objectName()+"/currentIndex").toInt());

        ui->spin_msec->setValue(settings.value(ui->spin_msec->objectName()+"/value").toInt());
        ui->spin_port->setValue(settings.value(ui->spin_port->objectName()+"/value").toInt());
        ui->spin_vref->setValue(settings.value(ui->spin_vref->objectName()+"/value").toDouble());
        ui->spin_schmittLow->setValue(settings.value(ui->spin_schmittLow->objectName()+"/value").toDouble());
        ui->spin_schmittHigh->setValue(settings.value(ui->spin_schmittHigh->objectName()+"/value").toDouble());

        ui->checkB_pullup->setChecked(settings.value(ui->checkB_pullup->objectName()+"/isChecked").toBool());
        ui->checkB_adc->setChecked(settings.value(ui->checkB_adc->objectName()+"/isChecked").toBool());
        ui->checkB_schmitt->setChecked(settings.value(ui->checkB_schmitt->objectName()+"/isChecked").toBool());
        ui->checkB_bg->setChecked(settings.value(ui->checkB_bg->objectName()+"/isChecked").toBool());
    }
}
void MainWindow::saveSettings()
{
    QSettings settings("Ehab", "LogicAnalyzer");

    settings.setValue(ui->pop_mode->objectName()+"/currentIndex", ui->pop_mode->currentIndex());
    settings.setValue(ui->pop_clkFreq->objectName()+"/currentIndex", ui->pop_clkFreq->currentIndex());

    settings.setValue(ui->spin_msec->objectName()+"/value", ui->spin_msec->value());
    settings.setValue(ui->spin_port->objectName()+"/value", ui->spin_port->value());
    settings.setValue(ui->spin_vref->objectName()+"/value", ui->spin_vref->value());
    settings.setValue(ui->spin_schmittLow->objectName()+"/value", ui->spin_schmittLow->value());
    settings.setValue(ui->spin_schmittHigh->objectName()+"/value", ui->spin_schmittHigh->value());

    settings.setValue(ui->checkB_pullup->objectName()+"/isChecked", ui->checkB_pullup->isChecked());
    settings.setValue(ui->checkB_adc->objectName()+"/isChecked", ui->checkB_adc->isChecked());
    settings.setValue(ui->checkB_schmitt->objectName()+"/isChecked", ui->checkB_schmitt->isChecked());
    settings.setValue(ui->checkB_bg->objectName()+"/isChecked", ui->checkB_bg->isChecked());
}

void MainWindow::on_plot_mousePress(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton )
    {
        double x = ui->plot->xAxis->pixelToCoord(event->pos().x()); /* get X coordinates from graph */
        double y = ui->plot->yAxis->pixelToCoord(event->pos().y()); /* get Y coordinates from graph */
        bool ctrl_is_down = GetKeyState(VK_CONTROL)&0x8000;         /* check if CTRL keyboard key is down */
        bool alt_is_down  = GetKeyState(VK_MENU)   &0x8000;         /* check if ALT keyboard key is down */
        if (ctrl_is_down && !alt_is_down)
        {
            ui->lineE_tstart->setText(QString::number(x,'f',3));          /* Set Start time for signal analysis */
        }
        else if (alt_is_down && !ctrl_is_down)
        {
            ui->lineE_tend->setText(QString::number(x,'f',3));            /* Set End time for signal analysis */
        }
        else
        {
            if ( (mode == LA_MODE_ANALOG) || (mode == LA_MODE_ANALOG_X2) )
            {
                if(signals_a.size()) { showAmplitudeInfo(x); }
            }
            else
            {
                if(signals_d.size()) { showPulseInfo(x,y); }
            }
        }
    }
}
void MainWindow::checkHardware()
{
    if ( (!serialIsOpened()) && ui->pushB_capture->isEnabled() )
    {
        serialClose();
        ui->pushB_connect->setText("Connect");
        ui->pushB_capture->setEnabled(false);
        ui->tabWidget_2->setCurrentIndex(0);    /* make Log tab the shown tab in tabWidget */
        ui->log->append("<span style='color: red'>Device is unexpectedly disconnected</span>");
        if(plotting_timer->isActive())  /* stream is active? */
        {
            on_pushB_capture_pressed(); /* stop streaming */
        }
    }
}
void MainWindow::on_pushB_connect_pressed()
{
    if (serialIsOpened())
    {
        serialClose();
        ui->pushB_connect->setText("Connect");
        ui->pushB_capture->setEnabled(false);
        ui->log->append("<span style='color: green'>Device is disconnected Successfully</span>");
    }
    else
    {
        int portNumber=ui->spin_port->value();
        if (serialOpen(portNumber, getBaudrate()))
        {
            int size=0;
            uint8_t temp_buffer[1000];

            serialSend(LA_CMD_OFF);         /* stop data transmition if on */
            Sleep(1);                       /* Delay for 1 msec */
            serialClear();                  /* flush serial buffers */

            serialSend(LA_CMD_SYNC_CHECK);  /* test serial commumication */
            Sleep(1);                       /* Delay for 1 msec */

             /* serial test succeeded */
            if( serialReceive(temp_buffer,size) && size==1 && temp_buffer[0]==LA_CMD_SYNC_CHECK )
            {
                ui->pushB_connect->setText("Disconnect");
                ui->pushB_capture->setEnabled(true);
                ui->log->append("<span style='color: green'>Device is connected Successfully</span>");
            }
            else    /* no response received or invalid response received */
            {
                serialClose();
                ui->tabWidget_2->setCurrentIndex(0);
                ui->log->append("<span style='color: red'>Device is not responding, check hardware connections and Clock Frequency settings</span>");
            }
        }
        else
        {
            ui->tabWidget_2->setCurrentIndex(0);
            ui->log->append("<span style='color: red'>Unable to find Device, check hardware and COM port settings</span>");
        }
    }
}
void MainWindow::on_pushB_capture_pressed()
{
    if (plotting_timer->isActive())
    {
        plotting_timer->stop();
        serialSend(LA_CMD_OFF);

        ui->pushB_capture->setText("Start Capture");
        delete buffer;
        if ( (mode == LA_MODE_ANALOG) || (mode == LA_MODE_ANALOG_X2) )
        {
            for(int s=0; s<signals_a.size(); s++)
            {
                signals_a[s].analyze( signals_a[s].data->begin()->key, (signals_a[s].data->end()-1)->key);
                showAnalogSignalInfo(s);
            }
        }
        else /* Digital */
        {
            for(int s=0; s<signals_d.size(); s++)
            {
                analyzeDigitalSignal(s, signals_d[s].data->begin()->key, (signals_d[s].data->end()-1)->key);
            }
        }

        ui->pushB_connect->setEnabled(true);
        ui->pushB_analyze->setEnabled(true);
        ui->tabWidget_2->setTabEnabled(1,true);
    }
    else
    {
        const uint8_t commands[4]={
            LA_CMD_DIGITAL,     /*  8 pin digital,    150K sample rate at F_CPU 12M , Serial baud rate 1.5M */
            LA_CMD_DIGITAL_X2,  /*  4 pin digital,    300K sample rate at F_CPU 12M , Serial baud rate 1.5M */
            LA_CMD_ANALOG,      /* 10 bit resolution,  75K sample rate at F_CPU 12M , Serial baud rate 1.5M */
            LA_CMD_ANALOG_X2,   /*  8 bit resolution, 150K sample rate at F_CPU 12M , Serial baud rate 1.5M */
        };

        saveSettings();
        ui->pushB_connect->setEnabled(false);
        ui->pushB_analyze->setEnabled(false);
        uint8_t tab_index = ui->tabWidget_2->currentIndex();    /* store current tab index */
        ui->tabWidget_2->setTabEnabled(1,false);                /* disable settings tab, changes current tab if tab is disabled */
        ui->tabWidget_2->setCurrentIndex(tab_index);            /* restore current tab index */
        ui->pushB_capture->setText("Stop Capture");
        ui->plot->xAxis->setRange(0, LA_MAX_WINDOW);
        mode = ui->pop_mode->currentIndex();

        /* Adjust ADC referance in case of Analog mode */
        adc_scale = (!ui->checkB_adc->isChecked())? ui->spin_vref->value() :
                                                    (mode==LA_MODE_ANALOG)? 1023.0 :
                                                                             255.0 ;

        serialClear();      /* flush the receiving buffer */
        buffer_offset=0;    /* clear offset */
        buffer=new uint8_t[LA_MAX_SERIAL_DATA];

        /* clear data of previous signals */
        for (uint8_t i=0; i<LA_MAX_CHANNELS; ++i)
        {
            ui->plot->graph(i)->data()->clear();
            logs[i]->clear();
        }

        switch (mode)
        {
            case LA_MODE_DIGITAL:
            case LA_MODE_DIGITAL_X2:
            {
                /* resize signal vectors */
                uint8_t num_channels = mode==LA_MODE_DIGITAL? LA_MAX_CHANNELS : LA_MAX_CHANNELS/2;
                signals_d.resize(num_channels);
                signals_a.clear();
                /* Digital Signal */
                for (uint8_t i=0; i<signals_d.size(); ++i)
                {
                    signals_d[i].data = ui->plot->graph(i)->data();
                    signals_d[i].edgeTime = getSamplingTime();
                }
                /* hide y-axis data labels by setting its color same as background */
                ui->plot->yAxis->setTickLabelColor(color_plot[theme_settings]);
                /* Adjust Y axis to suit current mode */
                ui->plot->yAxis->setRange(0, LA_MAX_CHANNELS);
                break;
            }
            case LA_MODE_ANALOG:
            case LA_MODE_ANALOG_X2:
            default:
            {
                /* resize signal vectors */
                signals_a.resize(1);
                signals_d.clear();
                /* Analog Signal */
                signals_a[0].data = ui->plot->graph(LA_GRAPH_ANALOG_SIGNAL)->data();
                signals_a[0].edgeTime = getSamplingTime();
                /* Digital Representation of Analog Signal using Schmitt Trigger */
                signals_a[0].binary.data = ui->plot->graph(LA_GRAPH_ANALOG_SCHMITT)->data();
                signals_a[0].binary.edgeTime = getSamplingTime();
                /* Schmitt Trigger comparator Low */
                ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTLOW)->addData(0                       ,adc_scale*ui->spin_schmittLow->value());
                ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTLOW)->addData(ui->spin_msec->maximum(),adc_scale*ui->spin_schmittLow->value());
                /* Schmitt Trigger comparator High */
                ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTHIGH)->addData(0                       ,adc_scale*ui->spin_schmittHigh->value());
                ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTHIGH)->addData(ui->spin_msec->maximum(),adc_scale*ui->spin_schmittHigh->value());
                /* show y-axis data labels by setting its color to white */
                ui->plot->yAxis->setTickLabelColor(color_plot[1-theme_settings]);
                /* Adjust Y axis to suit current mode */
                ui->plot->yAxis->setRange(0, adc_scale>255.0? 1200.0 : adc_scale==255.0? 290.0 : 8.0); /* max data + 17% */
                /* Adjust ADC logic high and low */
                adc_high = adc_scale>255.0? 1200.0 : adc_scale==255.0? 290.0 : 8.0 ;
                adc_low  = adc_scale>255.0? 1100.5 : adc_scale==255.0? 270.5 : 7.5 ;
                break;
            }
        }

        /* adjust pullup */
        serialSend( ui->checkB_pullup->isChecked()? LA_CMD_PULLUP_OFF : LA_CMD_PULLUP_ON );

        /* Start Stream */
        serialSend( commands[mode] );
        plotting_timer->start();
    }
}
void MainWindow::on_pushB_analyze_pressed()
{
    double tStart  = ui->lineE_tstart->text().toDouble();
    double tEnd    = ui->lineE_tend->text().toDouble();
    int    channel = ui->pop_ch->currentIndex();

    if ( (mode == LA_MODE_ANALOG) || (mode == LA_MODE_ANALOG_X2) )
    {
        if ( (channel==8) || (channel == 0) ) /* all channels or  */
        {
            signals_a[0].binary.data->clear();
            for (int64_t i=0; i<signals_a[0].data->size(); i++)
            {
                plotAnalog(signals_a[0].data->at(i)->value, 0, signals_a[0].edgeTime, i);
            }
            /* stretsh plot to end of current time */
            (signals_a[0].binary.data->end()-1)->key = (signals_a[0].data->end()-1)->key;
            /* replot */
            ui->plot->replot();
            /* Start analyzing Analog Signal */
            signals_a[0].analyze(tStart,tEnd);
            showAnalogSignalInfo(0);
        }

    }
    else    /* Digital */
    {
        if (channel==8) /* all channels */
        {
            for(int s=0; s<signals_d.size();s++)
            {
                analyzeDigitalSignal(s,tStart,tEnd);
            }
        }
        else if (channel<signals_d.size())
        {
            analyzeDigitalSignal(channel,tStart,tEnd);
        }
    }
}
void MainWindow::on_pop_clkFreq_currentIndexChanged(int index)
{
    if(serialIsOpened())
    {
        on_pushB_connect_pressed(); /* close connection */
    }

    /* update frequencies of each mode */
    double max_freq = max_sampling_rate[index]/1000;
    ui->pop_mode->setItemText(LA_MODE_DIGITAL,
                              QString("Digital (%1k Sample Rate, 8 channels)")
                              .arg(max_freq*sampling_rate_factor[LA_MODE_DIGITAL]));
    ui->pop_mode->setItemText(LA_MODE_DIGITAL_X2,
                              QString("Digital (%1k Sample Rate, 4 channels)")
                              .arg(max_freq*sampling_rate_factor[LA_MODE_DIGITAL_X2]));
    ui->pop_mode->setItemText(LA_MODE_ANALOG,
                              QString("Analog  (%1k Sample Rate, 10 bit resolution)")
                              .arg(max_freq*sampling_rate_factor[LA_MODE_ANALOG]));
    ui->pop_mode->setItemText(LA_MODE_ANALOG_X2,
                              QString("Analog  (%1k Sample Rate, 8 bit resolution)")
                              .arg(max_freq*sampling_rate_factor[LA_MODE_ANALOG_X2]));

}
void MainWindow::on_checkB_adc_stateChanged(int state)
{
    ui->spin_vref->setDisabled(state);
}
void MainWindow::on_checkB_schmitt_stateChanged(int state)
{
    ui->spin_schmittLow->setEnabled(state);
    ui->spin_schmittHigh->setEnabled(state);
    if ( (mode == LA_MODE_ANALOG) || (mode == LA_MODE_ANALOG_X2) )
    {
        ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTLOW)->data()->clear();
        ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTHIGH)->data()->clear();
        if (state)
        {
            /* Schmitt Trigger comparator Low */
            ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTLOW)->addData(0                       ,adc_scale*ui->spin_schmittLow->value());
            ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTLOW)->addData(ui->spin_msec->maximum(),adc_scale*ui->spin_schmittLow->value());
            /* Schmitt Trigger comparator High */
            ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTHIGH)->addData(0                       ,adc_scale*ui->spin_schmittHigh->value());
            ui->plot->graph(LA_GRAPH_ANALOG_SCHMITTHIGH)->addData(ui->spin_msec->maximum(),adc_scale*ui->spin_schmittHigh->value());
            ui->plot->replot();
        }
        ui->plot->replot();
    }
}
void MainWindow::on_spin_schmittLow_valueChanged(double value)
{
    ui->spin_schmittHigh->setMinimum(value);
    on_checkB_schmitt_stateChanged(1);
}
void MainWindow::on_spin_schmittHigh_valueChanged(double value)
{
    ui->spin_schmittLow->setMaximum(value);
    on_checkB_schmitt_stateChanged(1);
}


void MainWindow::on_checkB_bg_stateChanged(int state)
{
    theme_settings = state? 1:0;
    QPalette pal = palette();
    //pal.setColor(QPalette::Base , bg_text[theme_settings]);
    pal.setColor(QPalette::Window, color_window[theme_settings]);
    this->setPalette(pal);


    ui->plot->setBackground(QBrush(color_plot[theme_settings]));

    ui->plot->xAxis->setBasePen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setSubTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->xAxis->setTickLabelColor(color_plot[1-theme_settings]);
    ui->plot->xAxis->setLabelColor(color_plot[1-theme_settings]);
    ui->plot->xAxis->grid()->setPen(QPen(color_grid[theme_settings], 0, Qt::SolidLine));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(color_subGrid[theme_settings], 0, Qt::DotLine));

    ui->plot->yAxis->setBasePen(QPen(color_plot[1-theme_settings]));
    ui->plot->yAxis->setTickPen(QPen(color_plot[1-theme_settings]));
    ui->plot->yAxis->setSubTickPen(QPen((color_plot[1-theme_settings])));
    if( (mode == LA_MODE_ANALOG) || (mode == LA_MODE_ANALOG_X2) )
    {
        ui->plot->yAxis->setTickLabelColor(color_plot[1-theme_settings]); /* show label */
    }
    else
    {
        ui->plot->yAxis->setTickLabelColor(color_plot[theme_settings]);   /* hide label */
    }
    ui->plot->yAxis->grid()->setPen(QPen(color_grid[theme_settings], 0, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(color_subGrid[theme_settings], 0, Qt::DotLine));

    ui->plot->replot();
}
