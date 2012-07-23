/****************************************************************************
 **
 ** Copyright (C) 2012 Digia Plc
 ** All rights reserved.
 ** For any questions to Digia, please use contact form at http://qt.digia.com
 **
 ** This file is part of the Qt Commercial Charts Add-on.
 **
 ** $QT_BEGIN_LICENSE$
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.digia.com
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "../qabstractaxis/tst_qabstractaxis.h"
#include <qdatetimeaxis.h>
#include <qlineseries.h>

class tst_QDateTimeAxis : public QObject//: public tst_QAbstractAxis
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qdatetimeaxis_data();
    void qdatetimeaxis();

    void max_raw_data();
    void max_raw();
    void max_data();
    void max();
    //    void max_animation_data();
    //    void max_animation();
    void min_raw_data();
    void min_raw();
    void min_data();
    void min();
    //    void min_animation_data();
    //    void min_animation();
    //    void range_raw_data();
    //    void range_raw();
    //    void range_data();
    //    void range();
    //    void range_animation_data();
    //    void range_animation();

private:
    QDateTimeAxis *m_dateTimeAxisX;
    QDateTimeAxis *m_dateTimeAxisY;
    QLineSeries* m_series;
    QChartView* m_view;
    QChart* m_chart;
};

void tst_QDateTimeAxis::initTestCase()
{
}

void tst_QDateTimeAxis::cleanupTestCase()
{
}

void tst_QDateTimeAxis::init()
{
    m_dateTimeAxisX = new QDateTimeAxis();
    m_dateTimeAxisY = new QDateTimeAxis();
    m_series = new QLineSeries();
    *m_series << QPointF(-100, -100) << QPointF(0, 0) << QPointF(100, 100);
//    tst_QAbstractAxis::init(m_datetimeaxis, m_series);

    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
    m_chart->addSeries(m_series);
    m_chart->setAxisY(m_dateTimeAxisY, m_series);
    m_chart->setAxisX(m_dateTimeAxisX, m_series);
}

void tst_QDateTimeAxis::cleanup()
{
    delete m_series;
    delete m_dateTimeAxisX;
    delete m_dateTimeAxisY;
    m_series = 0;
    m_dateTimeAxisX = 0;
    m_dateTimeAxisY = 0;
    delete m_view;
    m_view = 0;
    m_chart = 0;
//    tst_QAbstractAxis::cleanup();
}

void tst_QDateTimeAxis::qdatetimeaxis_data()
{
}

void tst_QDateTimeAxis::qdatetimeaxis()
{
//    qabstractaxis();

//    QVERIFY(m_datetimeaxis->max().toMSecsSinceEpoch() == 0);
//    QVERIFY(m_datetimeaxis->min().toMSecsSinceEpoch() == 0);
    QCOMPARE(m_dateTimeAxisX->type(), QAbstractAxis::AxisTypeDateTime);

    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(m_dateTimeAxisX->max().toMSecsSinceEpoch() != 0);
    QVERIFY(m_dateTimeAxisX->min().toMSecsSinceEpoch() != 0);
}

void tst_QDateTimeAxis::max_raw_data()
{
    QTest::addColumn<QDateTime>("max");
    QTest::addColumn<bool>("valid");
    QDateTime dateTime;
    dateTime.setDate(QDate(2012, 7, 19));
    QTest::newRow("19.7.2012 - Valid") << dateTime << true;
    dateTime.setDate(QDate(2012, 17, 32));
    QTest::newRow("32.17.2012 - Invalid") << dateTime << false;
}

void tst_QDateTimeAxis::max_raw()
{
    QFETCH(QDateTime, max);
    QFETCH(bool, valid);

    QSignalSpy spy0(m_dateTimeAxisX, SIGNAL(maxChanged(QDateTime)));
    QSignalSpy spy1(m_dateTimeAxisX, SIGNAL(minChanged(QDateTime)));
    QSignalSpy spy2(m_dateTimeAxisX, SIGNAL(rangeChanged(QDateTime, QDateTime)));

    m_dateTimeAxisX->setMax(max);


    if (valid) {
        QVERIFY2(m_dateTimeAxisX->max() == max, "Not equal");
        QCOMPARE(spy0.count(), 1);
        QCOMPARE(spy1.count(), 0);
        QCOMPARE(spy2.count(), 1);
    } else {
        QVERIFY2(m_dateTimeAxisX->max() != max, "Date is invalid");
        QCOMPARE(spy0.count(), 0);
        QCOMPARE(spy1.count(), 0);
        QCOMPARE(spy2.count(), 0);
    }
}

void tst_QDateTimeAxis::max_data()
{
    max_raw_data();
}

void tst_QDateTimeAxis::max()
{
    m_chart->setAxisX(m_dateTimeAxisX, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    max_raw();
}

//void tst_QDateTimeAxis::max_animation_data()
//{
//    max_data();
//}

//void tst_QDateTimeAxis::max_animation()
//{
//    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
//    max();
//}

void tst_QDateTimeAxis::min_raw_data()
{
    QTest::addColumn<QDateTime>("min");
    QTest::addColumn<bool>("valid");
    QDateTime dateTime;
    dateTime.setDate(QDate(1908, 1, 11));
    QTest::newRow("11.1.1908 - Valid") << dateTime << true; // negative MSecs from Epoch
    dateTime.setDate(QDate(2012, 17, 32));
    QTest::newRow("32.17.2012 - Invalid") << dateTime << false;
}

void tst_QDateTimeAxis::min_raw()
{
    QFETCH(QDateTime, min);
    QFETCH(bool, valid);

    QSignalSpy spy0(m_dateTimeAxisX, SIGNAL(maxChanged(QDateTime)));
    QSignalSpy spy1(m_dateTimeAxisX, SIGNAL(minChanged(QDateTime)));
    QSignalSpy spy2(m_dateTimeAxisX, SIGNAL(rangeChanged(QDateTime, QDateTime)));

    m_dateTimeAxisX->setMin(min);

    if (valid) {
        QVERIFY2(m_dateTimeAxisX->min() == min, "Not equal");
        QCOMPARE(spy0.count(), 0);
        QCOMPARE(spy1.count(), 1);
        QCOMPARE(spy2.count(), 1);
    } else {
        QVERIFY2(m_dateTimeAxisX->min() != min, "Date is invalid");
        QCOMPARE(spy0.count(), 0);
        QCOMPARE(spy1.count(), 0);
        QCOMPARE(spy2.count(), 0);
    }
}

void tst_QDateTimeAxis::min_data()
{
    min_raw_data();
}

void tst_QDateTimeAxis::min()
{
    m_chart->setAxisX(m_dateTimeAxisX, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    min_raw();
}

//void tst_QDateTimeAxis::min_animation_data()
//{
//    min_data();
//}

//void tst_QDateTimeAxis::min_animation()
//{
//    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
//    min();
//}

//void tst_QDateTimeAxis::range_raw_data()
//{
//    QTest::addColumn<qreal>("min");
//    QTest::addColumn<qreal>("max");
//    QTest::newRow("1.0 - 101.0") << -1.0 << 101.0;
//    QTest::newRow("25.0 - 75.0") << 25.0 << 75.0;
//    QTest::newRow("101.0") << 40.0 << 60.0;
//}

//void tst_QDateTimeAxis::range_raw()
//{
//    QFETCH(qreal, min);
//    QFETCH(qreal, max);

//    QSignalSpy spy0(m_intervalsaxis, SIGNAL(maxChanged(qreal)));
//    QSignalSpy spy1(m_intervalsaxis, SIGNAL(minChanged(qreal)));
//    QSignalSpy spy2(m_intervalsaxis, SIGNAL(rangeChanged(qreal, qreal)));

//    m_intervalsaxis->setRange(min, max);
//    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->min() - min), "Min not equal");
//    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->max() - max), "Max not equal");

//    QCOMPARE(spy0.count(), 1);
//    QCOMPARE(spy1.count(), 1);
//    QCOMPARE(spy2.count(), 1);
//}

//void tst_QDateTimeAxis::range_data()
//{
//    range_raw_data();
//}

//void tst_QDateTimeAxis::range()
//{
//    m_chart->setAxisX(m_intervalsaxis, m_series);
//    m_view->show();
//    QTest::qWaitForWindowShown(m_view);
//    range_raw();
//}

//void tst_QDateTimeAxis::range_animation_data()
//{
//    range_data();
//}

//void tst_QDateTimeAxis::range_animation()
//{
//    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
//    range();
//}

QTEST_MAIN(tst_QDateTimeAxis)
#include "tst_qdatetimeaxis.moc"
