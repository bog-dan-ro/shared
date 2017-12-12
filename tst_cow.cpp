#include <QtTest>
#include "testcow.h"

class cow : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void test_shared();
    void test_cow();
    void cleanupTestCase();

private:
    TestCow m_tc;
    TestCowString m_tcs;
};

void cow::initTestCase()
{
    m_tcs.setValue("bla");
    QCOMPARE(m_tcs.value(), std::string("bla"));
    m_tc.setValue(10);
    QCOMPARE(m_tc.value(), 10);
    m_tc.setCowString(m_tcs);
    QCOMPARE(m_tc.cowString().value(), m_tcs.value());
    QCOMPARE(m_tc.useCount(), 1);
    QCOMPARE(m_tcs.useCount(), 2);
}

void cow::test_shared()
{
    {
        auto tccopy1 = m_tc;
        auto tccopy2 = tccopy1;
        QCOMPARE(tccopy1.value(), tccopy2.value());
        QCOMPARE(m_tc.value(), tccopy1.value());
        QCOMPARE(m_tc.value(), tccopy2.value());
        QCOMPARE(m_tc.useCount(), 3);

        auto tcscopy = m_tcs;
        QCOMPARE(tcscopy.value(), m_tcs.value());
        QCOMPARE(tcscopy.value(), m_tc.cowString().value());
        QCOMPARE(m_tcs.useCount(), 3);
    }
    QCOMPARE(m_tc.useCount(), 1);
    QCOMPARE(m_tcs.useCount(), 2);
}

void cow::test_cow()
{
    {
        auto tccopy1 = m_tc;
        auto tccopy2 = tccopy1;
        tccopy1.setValue(1);
        QCOMPARE(tccopy1.value(), 1);
        QCOMPARE(m_tc.value(), tccopy2.value());
        QCOMPARE(m_tc.useCount(), 2);
        QCOMPARE(tccopy2.useCount(), 2);
        QCOMPARE(tccopy1.useCount(), 1);

        auto tcscopy = m_tcs;
        QCOMPARE(m_tcs.useCount(), 4);
        tcscopy.setValue("something");
        QCOMPARE(tcscopy.value(), std::string("something"));
        QCOMPARE(m_tcs.value(), m_tc.cowString().value());
        QCOMPARE(tcscopy.useCount(), 1);
        QCOMPARE(m_tcs.useCount(), 3);
    }
    QCOMPARE(m_tc.useCount(), 1);
    QCOMPARE(m_tcs.useCount(), 2);
}

void cow::cleanupTestCase()
{
    QCOMPARE(m_tcs.value(), std::string("bla"));
    QCOMPARE(m_tc.value(), 10);
    QCOMPARE(m_tc.cowString().value(), m_tcs.value());
    QCOMPARE(m_tc.useCount(), 1);
    QCOMPARE(m_tcs.useCount(), 2);
}

QTEST_APPLESS_MAIN(cow)

#include "tst_cow.moc"
