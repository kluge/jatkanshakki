#include <QtTest/QtTest>

class TestTest : public QObject
{
  Q_OBJECT
private slots:
  void test();
};

void TestTest::test()
{
  QVERIFY(1 == 1);
}

QTEST_MAIN(TestTest)
#include "main.moc"
