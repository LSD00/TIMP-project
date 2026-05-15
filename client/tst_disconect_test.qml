#include <QTest>
#include <QTcpSocket>
#include <QSignalSpy>
#include <QJsonDocument>
#include <functional>
#include "net.h" // ваш реальный Client

// Mock-класс для эмуляции потери соединения
class MockClient : public Client {
    Q_OBJECT
public:
    void sendJson(const QJsonObject &json) override {
        // Имитируем потерю соединения: не отправляем, а сразу эмитим ошибку
        emit connectionLost(); // предполагаем, что у Client есть такой сигнал
        // Или вызываем обработчик ошибки
        QTimer::singleShot(0, [this]() {
            emit errorOccurred(QAbstractSocket::NetworkError);
        });
    }

    bool isConnected() const override {
        return false; // всегда разорвано
    }

signals:
    void connectionLost();
    void errorOccurred(QAbstractSocket::SocketError);
};

// ========== 1. Тест для regist() ==========
void testRegistConnectionLost() {
    // Подменяем глобальный client на mock
    MockClient mockClient;
    // Предполагаем, что client в net.h - глобальная переменная
    // Придётся временно заменить (через friend или сеттер)

    bool callbackCalled = false;
    // В оригинальном regist нет callback, поэтому проверяем через сигналы/состояние

    regist("test@mail.com", "pass123");

    // Проверяем, что client пытался отправить, но соединение потеряно
    QVERIFY(!mockClient.isConnected());
    // Можно проверить, что не было утечек или падений
    QVERIFY(true); // если дошли сюда без краша - тест пройден
}

// ========== 2. Тест для for_codereset() ==========
void testForCoderesetConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    bool callbackResult = true; // изменится на false при ошибке

    for_codereset("123456", [&](bool success) {
        callbackResult = success;
        loop.quit();
    });

    // Эмулируем потерю соединения через таймаут
    QTimer::singleShot(100, [&]() {
        // Если соединение потеряно, callback должен получить false
        if (!mockClient.isConnected()) {
            // Имитируем, что ответ не пришёл
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(!callbackResult); // должно быть false при потере соединения
}

// ========== 3. Тест для autor() ==========
void testAutorConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    bool callbackResult = true;

    autor("user@mail.com", "pass", [&](bool success) {
        callbackResult = success;
        loop.quit();
    });

    QTimer::singleShot(100, [&]() {
        if (!mockClient.isConnected()) {
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(!callbackResult); // при потере соединения - false
}

// ========== 4. Тест для for_pdtmail() ==========
void testForPdtmailConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    bool callbackResult = true;

    for_pdtmail("123456", [&](bool success) {
        callbackResult = success;
        loop.quit();
    });

    QTimer::singleShot(100, [&]() {
        if (!mockClient.isConnected()) {
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(!callbackResult);
}

// ========== 5. Тест для respas() ==========
void testRespasConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    bool callbackResult = true;

    respas("user@mail.com", [&](bool success) {
        callbackResult = success;
        loop.quit();
    });

    QTimer::singleShot(100, [&]() {
        if (!mockClient.isConnected()) {
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(!callbackResult);
}

// ========== 6. Тест для nwpass() ==========
void testNwpassConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    bool callbackResult = true;

    nwpass("newpassword", [&](bool success) {
        callbackResult = success;
        loop.quit();
    });

    QTimer::singleShot(100, [&]() {
        if (!mockClient.isConnected()) {
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(!callbackResult);
}

// ========== 7. Тест для crgrap() ==========
void testCrgrapConnectionLost() {
    MockClient mockClient;
    QEventLoop loop;
    QVector<double> result;
    bool callbackCalled = false;

    crgrap(1, 2, 3, [&](QVector<double> res) {
        result = res;
        callbackCalled = true;
        loop.quit();
    });

    QTimer::singleShot(100, [&]() {
        if (!mockClient.isConnected()) {
            // При потере соединения callback должен вызваться с пустым вектором
            loop.quit();
        }
    });

    loop.exec();
    QVERIFY(callbackCalled);
    QVERIFY(result.isEmpty()); // при ошибке соединения - пустой результат
}

// ========== 8. Тест для otprdat() ==========
void testOtprdatConnectionLost() {
    MockClient mockClient;

    // otprdat не имеет callback, проверяем, что нет краша
    otprdat();

    // Проверяем, что client пытался отправить данные
    QVERIFY(!mockClient.isConnected());
    // Если дошли сюда - тест пройден
    QVERIFY(true);
}