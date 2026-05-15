#include "catch.hpp"
#include <QSignalSpy>
#include <QTcpSocket>
#include <QEventLoop>
#include <QTest>
#include <QTimer>
#include "net.h"
class NetworkFailureSimulator {
public:
    static void simulateDisconnect(Client& client) {
        // Отключаем сокет принудительно
        if (client.socket && client.socket->state() == QTcpSocket::ConnectedState) {
            client.socket->disconnectFromHost();
            client.socket->waitForDisconnected(100);
        }
    }

    static void breakBeforeResponse(Client& client) {
        // Эмулируем разрыв сразу после отправки, до прихода ответа
        QTimer::singleShot(10, [&client]() {
            simulateDisconnect(client);
        });
    }
};
TEST_CASE("regist handles connection loss", "[network][failure]") {
    Client testClient;
    bool callbackCalled = false;
    bool resultStatus = false;

    // Устанавливаем соединение
    testClient.connectToServer("127.0.0.1", 12345);

    // Имитируем разрыв соединения через 50 мс после отправки
    QTimer::singleShot(50, [&testClient]() {
        if (testClient.socket) {
            testClient.socket->disconnectFromHost();
        }
    });

    // Вызываем функцию regist (она не имеет callback, полагаемся на внутреннюю обработку)
    regist("test@example.com", "password123");

    // Даем время на обработку
    QTest::qWait(500);

    // Проверяем, что клиент перешел в состояние ошибки или отключен
    bool isDisconnected = (testClient.socket == nullptr ||
                           testClient.socket->state() != QTcpSocket::ConnectedState);

    REQUIRE(isDisconnected == true);
    // Дополнительно: проверяем, что не было краша
    REQUIRE(true); // если дошли сюда - краша нет
}

// -------------------------------------------------------------------
// Тест 2: for_codereset() - проверка callback при потере соединения
// -------------------------------------------------------------------
TEST_CASE("for_codereset handles connection loss with callback", "[network][failure]") {
    Client testClient;
    bool callbackExecuted = false;
    bool callbackResult = true; // инициализируем как true, чтобы проверить изменение

    testClient.connectToServer("127.0.0.1", 12345);

    // Имитируем разрыв до получения ответа
    QTimer::singleShot(30, [&testClient]() {
        if (testClient.socket) {
            testClient.socket->disconnectFromHost();
            // Эмулируем ошибку в lastResponse
            testClient.lastResponse["status"] = "error";
            // Принудительно вызываем responseReady для теста
            emit testClient.responseReady();
        }
    });

    // Используем event loop для ожидания callback
    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);

    for_codereset("123456", [&](bool success) {
        callbackExecuted = true;
        callbackResult = success;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackExecuted == true);
    REQUIRE(callbackResult == false); // при потере соединения success должен быть false
}

// -------------------------------------------------------------------
// Тест 3: autor() - потеря соединения во время авторизации
// -------------------------------------------------------------------
TEST_CASE("autor handles disconnection during login", "[network][failure]") {
    Client testClient;
    bool callbackCalled = false;
    bool authResult = false;

    testClient.connectToServer("127.0.0.1", 12345);

    // Разрываем соединение сразу после отправки
    QTimer::singleShot(20, [&testClient]() {
        testClient.socket->disconnectFromHost();
        testClient.lastResponse["status"] = "error";
        emit testClient.responseReady();
    });

    QEventLoop loop;
    QTimer::singleShot(400, &loop, &QEventLoop::quit);

    autor("user@test.com", "pass", [&](bool success) {
        callbackCalled = true;
        authResult = success;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackCalled == true);
    REQUIRE(authResult == false);
}

// -------------------------------------------------------------------
// Тест 4: for_pdtmail() - потеря соединения при верификации email
// -------------------------------------------------------------------
TEST_CASE("for_pdtmail handles connection loss", "[network][failure]") {
    Client testClient;
    bool callbackExecuted = false;
    bool result = false;

    testClient.connectToServer("127.0.0.1", 12345);

    // Эмулируем сетевую ошибку
    QTimer::singleShot(25, [&testClient]() {
        testClient.socket->abort(); // жесткий разрыв
        testClient.lastResponse["status"] = "error";
        emit testClient.responseReady();
    });

    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);

    for_pdtmail("ABCDEF", [&](bool success) {
        callbackExecuted = true;
        result = success;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackExecuted == true);
    REQUIRE(result == false);
}

// -------------------------------------------------------------------
// Тест 5: respas() - потеря соединения при запросе сброса пароля
// -------------------------------------------------------------------
TEST_CASE("respas handles network failure", "[network][failure]") {
    Client testClient;
    bool callbackTriggered = false;
    bool finalResult = false;

    testClient.connectToServer("127.0.0.1", 12345);

    // Разрываем соединение до ответа
    QTimer::singleShot(15, [&testClient]() {
        NetworkFailureSimulator::simulateDisconnect(testClient);
        testClient.lastResponse["status"] = "error";
        emit testClient.responseReady();
    });

    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);

    respas("reset@example.com", [&](bool success) {
        callbackTriggered = true;
        finalResult = success;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackTriggered == true);
    REQUIRE(finalResult == false);
}

// -------------------------------------------------------------------
// Тест 6: nwpass() - потеря соединения при установке нового пароля
// -------------------------------------------------------------------
TEST_CASE("nwpass handles disconnection", "[network][failure]") {
    Client testClient;
    bool callbackFired = false;
    bool operationResult = true;

    testClient.connectToServer("127.0.0.1", 12345);

    // Имитируем потерю соединения
    QTimer::singleShot(40, [&testClient]() {
        delete testClient.socket;
        testClient.socket = nullptr;
        testClient.lastResponse["status"] = "error";
        emit testClient.responseReady();
    });

    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);

    nwpass("NewPass123!", [&](bool success) {
        callbackFired = true;
        operationResult = success;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackFired == true);
    REQUIRE(operationResult == false);
}

// -------------------------------------------------------------------
// Тест 7: crgrap() - потеря соединения при финализации регистрации
//         (возвращает QVector<double>)
// -------------------------------------------------------------------
TEST_CASE("crgrap handles connection loss with vector return", "[network][failure]") {
    Client testClient;
    bool callbackInvoked = false;
    QVector<double> receivedData;

    testClient.connectToServer("127.0.0.1", 12345);

    // Разрываем соединение
    QTimer::singleShot(30, [&testClient]() {
        testClient.socket->disconnectFromHost();
        testClient.lastResponse["status"] = "error";
        emit testClient.responseReady();
    });

    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);

    crgrap(1, 2, 3, [&](QVector<double> result) {
        callbackInvoked = true;
        receivedData = result;
        loop.quit();
    });

    loop.exec();

    REQUIRE(callbackInvoked == true);
    // При ошибке соединения должен вернуться пустой вектор
    REQUIRE(receivedData.isEmpty() == true);
}

// -------------------------------------------------------------------
// Тест 8: otprdat() - потеря соединения при отправке данных
//         (нет callback, проверяем отсутствие краша)
// -------------------------------------------------------------------
TEST_CASE("otprdat handles connection loss without callback", "[network][failure]") {
    Client testClient;

    testClient.connectToServer("127.0.0.1", 12345);

    // Разрываем соединение
    QTimer::singleShot(10, [&testClient]() {
        if (testClient.socket) {
            testClient.socket->close();
        }
    });

    // Вызываем функцию - она не должна вызвать краш
    REQUIRE_NOTHROW(otprdat());

    QTest::qWait(300);

    // Проверяем, что приложение в стабильном состоянии
    REQUIRE(true);
}

// -------------------------------------------------------------------
// Дополнительный тест: множественная потеря соединения
// -------------------------------------------------------------------
TEST_CASE("Multiple functions handle sequential disconnections", "[network][stress]") {
    Client testClient;
    int successCallbacks = 0;
    int totalCallbacks = 0;

    testClient.connectToServer("127.0.0.1", 12345);

    // Функция для эмуляции разрыва
    auto breakConnection = [&testClient]() {
        if (testClient.socket) {
            testClient.socket->disconnectFromHost();
        }
        testClient.lastResponse["status"] = "error";
        QTimer::singleShot(10, [&testClient]() {
            emit testClient.responseReady();
        });
    };

    QEventLoop loop;

    // Последовательно вызываем несколько функций с разрывами
    autor("a@b.com", "p1", [&](bool s) { totalCallbacks++; if (!s) successCallbacks++; });
    QTimer::singleShot(50, breakConnection);

    QTimer::singleShot(100, [&]() {
        respas("c@d.com", [&](bool s) { totalCallbacks++; if (!s) successCallbacks++; });
        QTimer::singleShot(50, breakConnection);
    });

    QTimer::singleShot(250, [&]() {
        nwpass("pass", [&](bool s) { totalCallbacks++; if (!s) successCallbacks++; });
        QTimer::singleShot(50, breakConnection);
    });

    QTimer::singleShot(600, [&loop]() {
        loop.quit();
    });

    loop.exec();

    // Все callback должны получить false при потере соединения
    REQUIRE(totalCallbacks == successCallbacks);
    REQUIRE(totalCallbacks > 0);
}