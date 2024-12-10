// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widget.h"
// #include "xyseriesiodevice.h"

// #include <QAudioDevice>
// #include <QAudioInput>
// #include <QAudioSource>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QPoint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_chart(new QChart)
    , m_series(new QLineSeries)
{
    auto chartView = new QChartView(m_chart);
    m_chart->addSeries(m_series);
    auto axisX = new QValueAxis;
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    auto axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio level");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    m_chart->setTitle("Title");

    *m_series << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7)
            << QPointF(12, 6) << QPointF(16, 7) << QPointF(18, 5);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

    // m_audioInput = new QAudioInput(deviceInfo, this);

    // QAudioFormat formatAudio;
    // formatAudio.setSampleRate(8000);
    // formatAudio.setChannelCount(1);
    // formatAudio.setSampleFormat(QAudioFormat::UInt8);

    // m_audioSource = new QAudioSource(deviceInfo, formatAudio);
    // m_audioSource->setBufferSize(200);

    // m_device = new XYSeriesIODevice(m_series, this);
    // m_device->open(QIODevice::WriteOnly);

    // m_audioSource->start(m_device);
}

Widget::~Widget()
{
    // m_audioSource->stop();
    // m_device->close();
    // delete m_audioInput;
    // delete m_device;
}
