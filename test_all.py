import socket
import json
import time

HOST = '127.0.0.1'
PORT = 8080

def send_request(sock, payload):
    """Отправляет JSON на сервер и читает ответ."""
    print(f"\n[>>>] Отправляем: {payload['action']}")
    # Преобразуем словарь в JSON и добавляем символ переноса строки
    message = json.dumps(payload) + "\n"
    sock.sendall(message.encode('utf-8'))
    
    # Читаем ответ (упрощенное чтение, предполагаем, что ответ влезет в 4096 байт)
    response_data = sock.recv(4096).decode('utf-8').strip()
    if not response_data:
        return {"status": "error", "message": "No response from server"}
        
    response = json.loads(response_data)
    print(f"[<<<] Получено: {json.dumps(response, indent=2, ensure_ascii=False)}")
    return response

def main():
    # Настройки тестового пользователя
    TEST_EMAIL = "test_user_123@example.com" # Укажите здесь свой РЕАЛЬНЫЙ email для получения кода!
    TEST_PASSWORD = "SuperSecurePassword123"
    NEW_PASSWORD = "NewSuperSecurePassword456"

    print("=== Запуск интеграционного теста ===")
    
    # Создаем сокет
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            sock.connect((HOST, PORT))
            print(f"Успешно подключились к {HOST}:{PORT}")
        except ConnectionRefusedError:
            print(f"Ошибка: Сервер не доступен по адресу {HOST}:{PORT}. Убедитесь, что Docker-контейнер запущен.")
            return

        # 1. Проверка защиты: попытка вычислить без авторизации
        print("\n--- ТЕСТ 1: Доступ без авторизации ---")
        send_request(sock, {"action": "calc", "a": 10, "b": 20, "c": 30})
        time.sleep(1)

        # 2. Флоу регистрации
        print("\n--- ТЕСТ 2: Регистрация ---")
        res = send_request(sock, {"action": "register_request", "email": TEST_EMAIL})
        
        if res.get("status") == "success":
            code = input("\n[!] Проверьте почту и введите код регистрации: ").strip()
            
            # Подтверждаем код
            res_verify = send_request(sock, {
                "action": "register_verify", 
                "email": TEST_EMAIL, 
                "code": code
            })
            
            if res_verify.get("status") == "success":
                # Завершаем регистрацию
                send_request(sock, {
                    "action": "register_finalize", 
                    "email": TEST_EMAIL, 
                    "password": TEST_PASSWORD
                })
        else:
            print("Скипаем процесс регистрации (возможно, пользователь уже существует).")

        # 3. Авторизация (Login)
        print("\n--- ТЕСТ 3: Авторизация ---")
        login_res = send_request(sock, {
            "action": "login", 
            "email": TEST_EMAIL, 
            "password": TEST_PASSWORD
        })

        if login_res.get("status") == "success":
            # 4. Вычисления (теперь должно сработать)
            print("\n--- ТЕСТ 4: Математические вычисления (Успех) ---")
            send_request(sock, {"action": "calc", "a": 10, "b": 20, "c": 30})
        
        # 5. Флоу сброса пароля
        print("\n--- ТЕСТ 5: Сброс пароля ---")
        reset_req = send_request(sock, {"action": "reset_request", "email": TEST_EMAIL})
        
        if reset_req.get("status") == "success":
            code = input("\n[!] Проверьте почту и введите код сброса пароля: ").strip()
            
            res_verify = send_request(sock, {
                "action": "reset_verify", 
                "email": TEST_EMAIL, 
                "code": code
            })
            
            if res_verify.get("status") == "success":
                send_request(sock, {
                    "action": "reset_finalize", 
                    "email": TEST_EMAIL, 
                    "password": NEW_PASSWORD,
                    "password_confirm": NEW_PASSWORD
                })
                
                # Проверяем вход с новым паролем
                print("\n--- ТЕСТ 6: Вход с новым паролем ---")
                send_request(sock, {
                    "action": "login", 
                    "email": TEST_EMAIL, 
                    "password": NEW_PASSWORD
                })

    print("\n=== Тестирование завершено ===")

if __name__ == "__main__":
    main()
