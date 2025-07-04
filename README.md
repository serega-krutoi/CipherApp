# CipherApp — GUI-приложение для шифрования и дешифрования

## Описание

**CipherApp** — это графическое приложение на языке **C++ (C++17)** с использованием **Qt Framework**, предназначенное для шифрования и дешифрования текстов и файлов. В качестве алгоритмов шифрования реализованы три классических метода:

- **Кодовое слово** 
- **Магический квадрат** 
- **Скитала** 

Программа поддерживает модульную архитектуру с загрузкой плагинов в рантайме и имеет встроенную систему авторизации по паролю.

---

## Возможности

- Шифрование и дешифрование файлов и текстовых строк
- Выбор одного из трёх алгоритмов шифрования
- Ввод параметров шифрования (кодовое слово, размерность квадрата, количество строк)
- Сохранение результатов в файл
- Копирование результата в буфер обмена
- Простая система аутентификации с возможностью смены пароля
- Динамическая загрузка плагинов (`.so`) для алгоритмов

---

## Структура проекта

```
RowCipherApp/
├── app/                        # Графический интерфейс на Qt
│   ├── main.cpp
│   ├── mainwindow.cpp/.h/.ui  # Главное окно приложения
│   ├── LoginDialog.cpp/.h/.ui # Авторизация по паролю
│   ├── CMakeLists.txt
│
├── include/                   # Заголовочные файлы интерфейсов и реализаций
│   ├── ICipher.h
│   ├── ICipherFactory.h
│   ├── CodeWordCipher.h
│   ├── MagicSquareCipher.h
│   ├── MagicSquareUtils.h
│   └── SkitalaCipher.h
│
├── Entities/                  # Основные реализации алгоритмов
│   ├── CodeWordCipher.cpp
│   ├── MagicSquareCipher.cpp
│   ├── MagicSquareUtils.cpp
│   └── SkitalaCipher.cpp
│
├── plugins/                   # Плагины шифров (динамически подгружаемые библиотеки)
│   ├── codeword/
│   │   ├── CodeWordCipherFactory.cpp/.h
│   │   └── CMakeLists.txt
│   ├── magic/
│   │   ├── MagicSquareCipherFactory.cpp/.h
│   │   └── CMakeLists.txt
│   ├── skitala/
│   │   ├── SkitalaCipherFactory.cpp/.h
│   │   └── CMakeLists.txt
│   └── test.cpp               # Тестирование плагинов
│
├── build/app/plugins/         # Собранные библиотеки плагинов
│   ├── libcodeword.so
│   ├── libmagic.so
│   └── libskitala.so
│   └── CipherApp             # Финальный исполняемый файл
│
├── README.md
└── CMakeLists.txt            # Главый сборочный скрипт
```

---

## Сборка и запуск

### Требования

- CMake ≥ 3.16
- Компилятор C++ с поддержкой C++17
- Qt ≥ 5.15 (установлен через Qt Creator или вручную)
- Linux (рекомендуется), поддержка `.so`-плагинов

### Сборка

```bash
git clone https://github.com/your-username/RowCipherApp.git
sudo dpkg -i CipherAppInstaller.deb
```
---
### Запуск
```bash
CipherApp
```
---

## Пароли

При первом запуске приложение предложит задать пароль. Файл с хэшем пароля создаётся автоматически. В дальнейшем можно изменить пароль через меню.

---
