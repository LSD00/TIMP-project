#include <stdint.h>
#include <stddef.h>
#include <QByteArray>
#include "../src/Server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Инициализация QCoreApplication не требуется, если мы тестируем только парсинг JSON
    QByteArray payload(reinterpret_cast<const char*>(Data), Size);
    
    Server srv;
    // Скармливаем случайные байты в изолированную функцию парсинга
    srv.processPayload(payload);
    
    return 0; 
}
