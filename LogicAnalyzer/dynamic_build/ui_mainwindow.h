/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *plot;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QComboBox *pop_ch;
    QLabel *label_5;
    QLineEdit *lineE_tstart;
    QLabel *label_4;
    QLineEdit *lineE_tend;
    QPushButton *pushB_analyze;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextBrowser *log_1;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QComboBox *pop_decode_1;
    QLabel *label_12;
    QComboBox *pop_clk_1;
    QWidget *tab_2;
    QTextBrowser *log_2;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QComboBox *pop_decode_2;
    QLabel *label_13;
    QComboBox *pop_clk_2;
    QWidget *tab_3;
    QTextBrowser *log_3;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_20;
    QComboBox *pop_decode_3;
    QLabel *label_15;
    QComboBox *pop_clk_3;
    QWidget *tab_4;
    QTextBrowser *log_4;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_21;
    QComboBox *pop_decode_4;
    QLabel *label_16;
    QComboBox *pop_clk_4;
    QWidget *tab_5;
    QTextBrowser *log_5;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_23;
    QComboBox *pop_decode_5;
    QLabel *label_22;
    QComboBox *pop_clk_5;
    QWidget *tab_6;
    QTextBrowser *log_6;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_24;
    QComboBox *pop_decode_6;
    QLabel *label_17;
    QComboBox *pop_clk_6;
    QWidget *tab_7;
    QTextBrowser *log_7;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_25;
    QComboBox *pop_decode_7;
    QLabel *label_18;
    QComboBox *pop_clk_7;
    QWidget *tab_8;
    QTextBrowser *log_8;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_26;
    QComboBox *pop_decode_8;
    QLabel *label_19;
    QComboBox *pop_clk_8;
    QTabWidget *tabWidget_2;
    QWidget *tab_11;
    QTextBrowser *log;
    QWidget *tab_12;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget0;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkB_adc;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QDoubleSpinBox *spin_vref;
    QCheckBox *checkB_schmitt;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_28;
    QDoubleSpinBox *spin_schmittLow;
    QDoubleSpinBox *spin_schmittHigh;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label;
    QSpinBox *spin_port;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_27;
    QComboBox *pop_clkFreq;
    QCheckBox *checkB_pullup;
    QGroupBox *groupBox;
    QCheckBox *checkB_bg;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushB_connect;
    QComboBox *pop_mode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spin_msec;
    QPushButton *pushB_capture;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1362, 741);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(256, 38, 1101, 691));
        plot->setAutoFillBackground(false);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(583, 2, 441, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        pop_ch = new QComboBox(layoutWidget2);
        pop_ch->setObjectName(QStringLiteral("pop_ch"));

        horizontalLayout_3->addWidget(pop_ch);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineE_tstart = new QLineEdit(layoutWidget2);
        lineE_tstart->setObjectName(QStringLiteral("lineE_tstart"));

        horizontalLayout_3->addWidget(lineE_tstart);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lineE_tend = new QLineEdit(layoutWidget2);
        lineE_tend->setObjectName(QStringLiteral("lineE_tend"));

        horizontalLayout_3->addWidget(lineE_tend);

        pushB_analyze = new QPushButton(layoutWidget2);
        pushB_analyze->setObjectName(QStringLiteral("pushB_analyze"));

        horizontalLayout_3->addWidget(pushB_analyze);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(9, 40, 251, 691));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 9, 0);
        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        tabWidget = new QTabWidget(layoutWidget3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setSizeIncrement(QSize(0, 0));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::ElideRight);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        log_1 = new QTextBrowser(tab);
        log_1->setObjectName(QStringLiteral("log_1"));
        log_1->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_2 = new QWidget(tab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_8->addWidget(label_11);

        pop_decode_1 = new QComboBox(layoutWidget_2);
        pop_decode_1->setObjectName(QStringLiteral("pop_decode_1"));

        horizontalLayout_8->addWidget(pop_decode_1);

        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_8->addWidget(label_12);

        pop_clk_1 = new QComboBox(layoutWidget_2);
        pop_clk_1->setObjectName(QStringLiteral("pop_clk_1"));
        pop_clk_1->setAutoFillBackground(false);

        horizontalLayout_8->addWidget(pop_clk_1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        log_2 = new QTextBrowser(tab_2);
        log_2->setObjectName(QStringLiteral("log_2"));
        log_2->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_3 = new QWidget(tab_2);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_11->addWidget(label_14);

        pop_decode_2 = new QComboBox(layoutWidget_3);
        pop_decode_2->setObjectName(QStringLiteral("pop_decode_2"));

        horizontalLayout_11->addWidget(pop_decode_2);

        label_13 = new QLabel(layoutWidget_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_11->addWidget(label_13);

        pop_clk_2 = new QComboBox(layoutWidget_3);
        pop_clk_2->setObjectName(QStringLiteral("pop_clk_2"));

        horizontalLayout_11->addWidget(pop_clk_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        log_3 = new QTextBrowser(tab_3);
        log_3->setObjectName(QStringLiteral("log_3"));
        log_3->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_4 = new QWidget(tab_3);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget_4);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_12->addWidget(label_20);

        pop_decode_3 = new QComboBox(layoutWidget_4);
        pop_decode_3->setObjectName(QStringLiteral("pop_decode_3"));

        horizontalLayout_12->addWidget(pop_decode_3);

        label_15 = new QLabel(layoutWidget_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_12->addWidget(label_15);

        pop_clk_3 = new QComboBox(layoutWidget_4);
        pop_clk_3->setObjectName(QStringLiteral("pop_clk_3"));

        horizontalLayout_12->addWidget(pop_clk_3);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        log_4 = new QTextBrowser(tab_4);
        log_4->setObjectName(QStringLiteral("log_4"));
        log_4->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_5 = new QWidget(tab_4);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_13 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget_5);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_13->addWidget(label_21);

        pop_decode_4 = new QComboBox(layoutWidget_5);
        pop_decode_4->setObjectName(QStringLiteral("pop_decode_4"));

        horizontalLayout_13->addWidget(pop_decode_4);

        label_16 = new QLabel(layoutWidget_5);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_13->addWidget(label_16);

        pop_clk_4 = new QComboBox(layoutWidget_5);
        pop_clk_4->setObjectName(QStringLiteral("pop_clk_4"));

        horizontalLayout_13->addWidget(pop_clk_4);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        log_5 = new QTextBrowser(tab_5);
        log_5->setObjectName(QStringLiteral("log_5"));
        log_5->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget4 = new QWidget(tab_5);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(layoutWidget4);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_5->addWidget(label_23);

        pop_decode_5 = new QComboBox(layoutWidget4);
        pop_decode_5->setObjectName(QStringLiteral("pop_decode_5"));

        horizontalLayout_5->addWidget(pop_decode_5);

        label_22 = new QLabel(layoutWidget4);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_5->addWidget(label_22);

        pop_clk_5 = new QComboBox(layoutWidget4);
        pop_clk_5->setObjectName(QStringLiteral("pop_clk_5"));

        horizontalLayout_5->addWidget(pop_clk_5);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        log_6 = new QTextBrowser(tab_6);
        log_6->setObjectName(QStringLiteral("log_6"));
        log_6->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_6 = new QWidget(tab_6);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(layoutWidget_6);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_14->addWidget(label_24);

        pop_decode_6 = new QComboBox(layoutWidget_6);
        pop_decode_6->setObjectName(QStringLiteral("pop_decode_6"));

        horizontalLayout_14->addWidget(pop_decode_6);

        label_17 = new QLabel(layoutWidget_6);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_14->addWidget(label_17);

        pop_clk_6 = new QComboBox(layoutWidget_6);
        pop_clk_6->setObjectName(QStringLiteral("pop_clk_6"));

        horizontalLayout_14->addWidget(pop_clk_6);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        log_7 = new QTextBrowser(tab_7);
        log_7->setObjectName(QStringLiteral("log_7"));
        log_7->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_7 = new QWidget(tab_7);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(layoutWidget_7);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_15->addWidget(label_25);

        pop_decode_7 = new QComboBox(layoutWidget_7);
        pop_decode_7->setObjectName(QStringLiteral("pop_decode_7"));

        horizontalLayout_15->addWidget(pop_decode_7);

        label_18 = new QLabel(layoutWidget_7);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_15->addWidget(label_18);

        pop_clk_7 = new QComboBox(layoutWidget_7);
        pop_clk_7->setObjectName(QStringLiteral("pop_clk_7"));

        horizontalLayout_15->addWidget(pop_clk_7);

        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        log_8 = new QTextBrowser(tab_8);
        log_8->setObjectName(QStringLiteral("log_8"));
        log_8->setGeometry(QRect(5, 40, 226, 261));
        layoutWidget_8 = new QWidget(tab_8);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(10, 10, 221, 22));
        horizontalLayout_16 = new QHBoxLayout(layoutWidget_8);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_26 = new QLabel(layoutWidget_8);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_16->addWidget(label_26);

        pop_decode_8 = new QComboBox(layoutWidget_8);
        pop_decode_8->setObjectName(QStringLiteral("pop_decode_8"));

        horizontalLayout_16->addWidget(pop_decode_8);

        label_19 = new QLabel(layoutWidget_8);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_16->addWidget(label_19);

        pop_clk_8 = new QComboBox(layoutWidget_8);
        pop_clk_8->setObjectName(QStringLiteral("pop_clk_8"));

        horizontalLayout_16->addWidget(pop_clk_8);

        tabWidget->addTab(tab_8, QString());

        verticalLayout->addWidget(tabWidget);

        tabWidget_2 = new QTabWidget(layoutWidget3);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setEnabled(true);
        tabWidget_2->setTabShape(QTabWidget::Triangular);
        tab_11 = new QWidget();
        tab_11->setObjectName(QStringLiteral("tab_11"));
        log = new QTextBrowser(tab_11);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(5, 10, 226, 291));
        tabWidget_2->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        groupBox_2 = new QGroupBox(tab_12);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(11, 100, 219, 121));
        layoutWidget0 = new QWidget(groupBox_2);
        layoutWidget0->setObjectName(QStringLiteral("layoutWidget0"));
        layoutWidget0->setGeometry(QRect(10, 15, 182, 98));
        verticalLayout_4 = new QVBoxLayout(layoutWidget0);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        checkB_adc = new QCheckBox(layoutWidget0);
        checkB_adc->setObjectName(QStringLiteral("checkB_adc"));

        verticalLayout_4->addWidget(checkB_adc);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget0);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        spin_vref = new QDoubleSpinBox(layoutWidget0);
        spin_vref->setObjectName(QStringLiteral("spin_vref"));
        spin_vref->setMinimum(2.7);
        spin_vref->setMaximum(5.5);
        spin_vref->setSingleStep(0.01);
        spin_vref->setValue(5);

        horizontalLayout_10->addWidget(spin_vref);


        verticalLayout_4->addLayout(horizontalLayout_10);

        checkB_schmitt = new QCheckBox(layoutWidget0);
        checkB_schmitt->setObjectName(QStringLiteral("checkB_schmitt"));

        verticalLayout_4->addWidget(checkB_schmitt);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_28 = new QLabel(layoutWidget0);
        label_28->setObjectName(QStringLiteral("label_28"));

        horizontalLayout_9->addWidget(label_28);

        spin_schmittLow = new QDoubleSpinBox(layoutWidget0);
        spin_schmittLow->setObjectName(QStringLiteral("spin_schmittLow"));
        spin_schmittLow->setEnabled(false);
        spin_schmittLow->setMinimum(0);
        spin_schmittLow->setMaximum(1);
        spin_schmittLow->setSingleStep(0.01);
        spin_schmittLow->setValue(0.2);

        horizontalLayout_9->addWidget(spin_schmittLow);

        spin_schmittHigh = new QDoubleSpinBox(layoutWidget0);
        spin_schmittHigh->setObjectName(QStringLiteral("spin_schmittHigh"));
        spin_schmittHigh->setEnabled(false);
        spin_schmittHigh->setMinimum(0);
        spin_schmittHigh->setMaximum(1);
        spin_schmittHigh->setSingleStep(0.01);
        spin_schmittHigh->setValue(0.8);

        horizontalLayout_9->addWidget(spin_schmittHigh);


        verticalLayout_4->addLayout(horizontalLayout_9);

        groupBox_3 = new QGroupBox(tab_12);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(11, 0, 219, 91));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 15, 154, 75));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_17->addWidget(label);

        spin_port = new QSpinBox(layoutWidget);
        spin_port->setObjectName(QStringLiteral("spin_port"));
        spin_port->setMinimum(1);
        spin_port->setValue(9);

        horizontalLayout_17->addWidget(spin_port);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_27 = new QLabel(layoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_18->addWidget(label_27);

        pop_clkFreq = new QComboBox(layoutWidget);
        pop_clkFreq->setObjectName(QStringLiteral("pop_clkFreq"));

        horizontalLayout_18->addWidget(pop_clkFreq);


        verticalLayout_3->addLayout(horizontalLayout_18);

        checkB_pullup = new QCheckBox(layoutWidget);
        checkB_pullup->setObjectName(QStringLiteral("checkB_pullup"));

        verticalLayout_3->addWidget(checkB_pullup);

        groupBox = new QGroupBox(tab_12);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(11, 230, 219, 41));
        checkB_bg = new QCheckBox(groupBox);
        checkB_bg->setObjectName(QStringLiteral("checkB_bg"));
        checkB_bg->setGeometry(QRect(10, 20, 151, 17));
        tabWidget_2->addTab(tab_12, QString());

        verticalLayout->addWidget(tabWidget_2);

        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(5, 2, 552, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushB_connect = new QPushButton(layoutWidget5);
        pushB_connect->setObjectName(QStringLiteral("pushB_connect"));

        horizontalLayout_4->addWidget(pushB_connect);

        pop_mode = new QComboBox(layoutWidget5);
        pop_mode->setObjectName(QStringLiteral("pop_mode"));

        horizontalLayout_4->addWidget(pop_mode);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget5);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spin_msec = new QSpinBox(layoutWidget5);
        spin_msec->setObjectName(QStringLiteral("spin_msec"));
        spin_msec->setMinimum(1);
        spin_msec->setMaximum(30000);
        spin_msec->setValue(15000);

        horizontalLayout_2->addWidget(spin_msec);

        pushB_capture = new QPushButton(layoutWidget5);
        pushB_capture->setObjectName(QStringLiteral("pushB_capture"));
        pushB_capture->setEnabled(false);

        horizontalLayout_2->addWidget(pushB_capture);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pop_ch->setCurrentIndex(8);
        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);
        pop_clkFreq->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Logic Analyzer", 0));
        label_6->setText(QApplication::translate("MainWindow", "Channel", 0));
        pop_ch->clear();
        pop_ch->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "All", 0)
        );
        label_5->setText(QApplication::translate("MainWindow", "Start (msec)", 0));
        lineE_tstart->setText(QApplication::translate("MainWindow", "0", 0));
        label_4->setText(QApplication::translate("MainWindow", "End (msec)", 0));
        lineE_tend->setText(QApplication::translate("MainWindow", "0", 0));
        pushB_analyze->setText(QApplication::translate("MainWindow", "Analyze", 0));
        label_7->setText(QApplication::translate("MainWindow", "Channels", 0));
        label_11->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_1->clear();
        pop_decode_1->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_12->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_1->clear();
        pop_clk_1->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
#ifndef QT_NO_WHATSTHIS
        pop_clk_1->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "1", 0));
        label_14->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_2->clear();
        pop_decode_2->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_13->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_2->clear();
        pop_clk_2->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "2", 0));
        label_20->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_3->clear();
        pop_decode_3->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_15->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_3->clear();
        pop_clk_3->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "3", 0));
        label_21->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_4->clear();
        pop_decode_4->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_16->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_4->clear();
        pop_clk_4->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "4", 0));
        label_23->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_5->clear();
        pop_decode_5->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_22->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_5->clear();
        pop_clk_5->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "5", 0));
        label_24->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_6->clear();
        pop_decode_6->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_17->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_6->clear();
        pop_clk_6->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "6", 0));
        label_25->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_7->clear();
        pop_decode_7->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_18->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_7->clear();
        pop_clk_7->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainWindow", "7", 0));
        label_26->setText(QApplication::translate("MainWindow", "Protocol", 0));
        pop_decode_8->clear();
        pop_decode_8->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "I2C", 0)
         << QApplication::translate("MainWindow", "SPI", 0)
         << QApplication::translate("MainWindow", "NEC", 0)
        );
        label_19->setText(QApplication::translate("MainWindow", "Clock", 0));
        pop_clk_8->clear();
        pop_clk_8->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("MainWindow", "8", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_11), QApplication::translate("MainWindow", "Log", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Analog", 0));
        checkB_adc->setText(QApplication::translate("MainWindow", "Display Raw ADC Output", 0));
        label_10->setText(QApplication::translate("MainWindow", "Voltage Ref", 0));
        checkB_schmitt->setText(QApplication::translate("MainWindow", "Display Schmitt Levels", 0));
        label_28->setText(QApplication::translate("MainWindow", "Schmitt Levels", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Hardware", 0));
        label->setText(QApplication::translate("MainWindow", "Com Port", 0));
        label_27->setText(QApplication::translate("MainWindow", "CLK Frequency", 0));
        pop_clkFreq->clear();
        pop_clkFreq->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8M", 0)
         << QApplication::translate("MainWindow", "10M", 0)
         << QApplication::translate("MainWindow", "12M", 0)
         << QApplication::translate("MainWindow", "14M", 0)
         << QApplication::translate("MainWindow", "16M", 0)
        );
        checkB_pullup->setText(QApplication::translate("MainWindow", "Disable Pull-up Resistances", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Graph", 0));
        checkB_bg->setText(QApplication::translate("MainWindow", "use Highlighted Theme", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_12), QApplication::translate("MainWindow", "Settings", 0));
        pushB_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        pop_mode->clear();
        pop_mode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Digital (200 Sample Rate, 8 channels)", 0)
         << QApplication::translate("MainWindow", "Digital (400k Sample Rate, 4 channels)", 0)
         << QApplication::translate("MainWindow", "Analog  (100k Sample Rate, 10 bit resolution)", 0)
         << QApplication::translate("MainWindow", "Analog  (200k Sample Rate, 8 bit resolution)", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "Duration (msec)", 0));
        pushB_capture->setText(QApplication::translate("MainWindow", "Start Capture", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
