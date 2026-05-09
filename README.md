## Вариант 1: Сборка через Conan

Этот способ автоматически установит все зависимости (`Boost`, `nlohmann_json`, `cpp-httplib`) и подготовит окружение.

### Условия

- Python 3.x + Conan 2.x
- CMake 3.15 или выше
- Компилятор C++17 (GCC 9+, Clang 10+)

### Инструкция

1.  **Создайте профиль Conan** (если не создавали):
    ```bash
    conan profile detect --force
    ```
2.  **Установите зависимости:**
    ```bash
    conan install . --output-folder=build --build=missing -s build_type=Release
    ```
3.  **Соберите проект:**
    ```bash
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    ```

---

## Вариант 2: Ручная установка зависимостей

### Установка в Ubuntu

```bash
sudo apt update
sudo apt install build-essential cmake libboost-program-options-dev nlohmann-json3-dev libcpp-httplib-dev
```

## Использование

После сборки исполняемый файл app будет доступен в папке build.

### Параметры запуска

- --path: Путь к директории для мониторинга.
- --interval: Периодичность сканирования в секундах.

### Пример запуска

```bash
./app --path ~/Загрузки --interval 30
```

### Результаты сканирования

```bash
curl http://localhost:1234/media_files
```
