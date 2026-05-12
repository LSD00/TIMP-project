#include <QtTest/QtTest>
#include "../src/calc.h"

class TestCalc : public QObject {
    Q_OBJECT

private slots:
    void testEdgeCases_data();
    void testEdgeCases();
    void testDivisionByZeroProtection();
};

void TestCalc::testEdgeCases_data() {
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("c");
    
    QTest::newRow("all_ones") << 1 << 1 << 1;
    QTest::newRow("zeros") << 0 << 0 << 0;
    QTest::newRow("negative") << -5 << 10 << -3;
}

void TestCalc::testEdgeCases() {
    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, c);

    auto results = MainCalcSafe(a, b, c);
    
    // Проверка, что вектор резервируется корректно
    QCOMPARE(results.size(), 41); // от -10 до 10 с шагом 0.5

    for (const auto& res : results) {
        if (res.x < 0) {
            // Для x < 0 проверка корректности
            if (std::abs(res.x * res.x - 1) > 1e-9) {
                QCOMPARE(res.y, a / (res.x * res.x - 1));
            } else {
                QCOMPARE(res.y, 0.0);
            }
        } else if (res.x > 0 && res.x < 1) {
            QCOMPARE(res.y, (1.0 / res.x) + b);
        } else if (res.x > 1) {
            QCOMPARE(res.y, (c * res.x) / (res.x * res.x + 1));
        }
    }
}

void TestCalc::testDivisionByZeroProtection() {
    // В точке x = -1.0 знаменатель (x*x - 1) равен 0. 
    // Наша функция должна защищать от этого.
    auto results = MainCalcSafe(10, 5, 2);
    
    bool foundMinusOne = false;
    for (const auto& res : results) {
        if (qFuzzyCompare(res.x, -1.0)) {
            QCOMPARE(res.y, 0.0); // По логике calc.cpp возвращается 0.0
            foundMinusOne = true;
        }
    }
    QVERIFY(foundMinusOne);
}

QTEST_MAIN(TestCalc)
#include "test_calc.moc"
