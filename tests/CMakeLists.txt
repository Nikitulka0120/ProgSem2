cmake_minimum_required(VERSION 3.10)

project(TestSorting C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# Указываем директорию с исходными кодами
include_directories(${PROJECT_SOURCE_DIR})

# Поиск библиотеки CMocka
find_package(CMocka REQUIRED)

# Если find_package не находит CMocka, укажите путь вручную
if (NOT CMocka_FOUND)
    message(FATAL_ERROR "CMocka library not found!")
endif()

# Укажите список исходных файлов
set(SOURCES
    unit_tests.c
    sorting.c
)

# Создание исполнимого файла для тестов
add_executable(test_sorting ${SOURCES})

# Линковка с библиотекой cmocka
target_link_libraries(test_sorting PRIVATE cmocka)

# Для тестирования
enable_testing()

# Устанавливаем вывод сообщений для тестов
set(ENV{CMOCKA_MESSAGE_OUTPUT} "TAP")  # Использование формата TAP
add_test(NAME TestSorting COMMAND test_sorting)

# Альтернативно можно использовать "XML" для вывода в формате XML, если нужно.
# set(ENV{CMOCKA_MESSAGE_OUTPUT} "XML")

# При необходимости запускайте тесты с подробным выводом
