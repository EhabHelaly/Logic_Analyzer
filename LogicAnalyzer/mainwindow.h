#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include "analogsignal.h"
#include "digitalsignal.h"
#include "logic_analyzer.h"

#define LA_MAX_SERIAL_DATA  1000000
#define LA_MAX_CHANNELS     8
#define LA_MAX_WINDOW       5000

/* Menu Options */
enum{
    LA_MODE_DIGITAL,
    LA_MODE_DIGITAL_X2,
    LA_MODE_ANALOG,
    LA_MODE_ANALOG_X2,
};

/* Protocols Decoding Options */
enum{
    LA_DECODE_OFF,
    LA_DECODE_I2C,
    LA_DECODE_SPI,
    LA_DECODE_NEC,
};

/* Analog signal graphs order (must not exceed or be equal to LA_MAX_CHANNELS )*/
enum{
    LA_GRAPH_ANALOG_SIGNAL,
    LA_GRAPH_ANALOG_SCHMITTLOW,
    LA_GRAPH_ANALOG_SCHMITTHIGH,
    LA_GRAPH_ANALOG_SCHMITT,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_plot_mousePress(QMouseEvent *event);

    void on_pushB_connect_pressed();
    void on_pushB_capture_pressed();
    void on_pushB_analyze_pressed();

    void on_pop_clkFreq_currentIndexChanged(int index);

    void on_checkB_bg_stateChanged(int state);
    void on_checkB_adc_stateChanged(int state);
    void on_checkB_schmitt_stateChanged(int state);

    void on_spin_schmittLow_valueChanged(double value);
    void on_spin_schmittHigh_valueChanged(double value);


private:
    Ui::MainWindow *ui;

    QVector<DigitalSignal> signals_d;
    QVector<AnalogSignal>  signals_a;

    QTimer* plotting_timer = 0;
    QTimer*   serial_timer = 0;
    uint8_t           mode = LA_MODE_DIGITAL;
    uint8_t       byte_old = 0xFF;
    uint8_t*        buffer = 0;
    uint32_t buffer_offset = 0;   /* used in analog 10 bit resolution mode to sync receiving multiple bytes of data */
    double adc_scale       = 0.0;
    double adc_high        = 0.0;
    double adc_low         = 0.0;

    const double sampling_rate_factor[4]= {
        1/2.0,  /*  8 pin digital,    200K sample rate at F_CPU 16M , Serial baud rate 2M */
        1/1.0,  /*  4 pin digital,    400K sample rate at F_CPU 16M , Serial baud rate 2M */
        1/4.0,  /* 10 bit resolution, 100K sample rate at F_CPU 16M , Serial baud rate 2M */
        1/2.0   /*  8 bit resolution, 200K sample rate at F_CPU 16M , Serial baud rate 2M */
    };
    const int max_sampling_rate[5]= {
        200000, /* F_CPU  8M , Serial baud rate 1.00 M */
        250000, /* F_CPU 10M , Serial baud rate 1.25 M */
        300000, /* F_CPU 12M , Serial baud rate 1.50 M */
        350000, /* F_CPU 14M , Serial baud rate 1.75 M */
        400000, /* F_CPU 16M , Serial baud rate 2.00 M */
    };
    const QColor color_window[2]={
        QColor(240,240,240),
        QColor(180,182,184),
    };
    const QColor color_plot[2]={
        QColor( 50, 50, 50),
        QColor(255,255,255),
    };
    const QColor color_grid[2]={
        QColor(130,130,130),
        QColor(200,200,200),
    };
    const QColor color_subGrid[2]={
        QColor(100,100,100),
        QColor(230,230,230),
    };
    uint8_t theme_settings = 0;

    QVector<QTextBrowser*> logs;
    QVector<QComboBox*> decode_pops;
    QVector<QComboBox*> clk_pops;

    int getBaudrate();
    double getSamplingTime();
    void checkHardware();

    void saveSettings();
    void loadSettings();

    void plotInit();
    void plotRun();
    void plotNewByte(uint8_t byte, double t_last, double dt, uint32_t i);
    void plotAnalog(double adc_disp_value, double t_last, double dt, uint32_t i);

    void analyzeDigitalSignal(uint8_t signal_index, double tStart, double tEnd);
    void showAnalogSignalInfo(uint8_t signal_index);
    void showDigitalSignalInfo(uint8_t signal_index);
    void showDecodedSignalInfo(uint8_t signal_index);
    void showPulseInfo(double x, double y);
    void showAmplitudeInfo(double x);

};

#endif // MAINWINDOW_H
