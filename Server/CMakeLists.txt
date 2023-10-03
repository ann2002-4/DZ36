cmake_minimum_required(VERSION 3.12)

project(QT_CHAT_SERVER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#опция CMAKE_INCLUDE_CURRENT_DIR обязательно должна быть включена,
#если вы не меняли пути генерации файлов для Qt.
#при использовании .ui файлов, Qt на их основе генерирует промежуточные
#файлы исходников, и будет складывать их в директории сборки.
#Чтобы среда их видела, необходимо добавить в директории для включения
#(include, директории, хранящие подключаемые .h файлы), директорию сборки:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

#здесь мы создаем переменную QT_CHAT_SERVER_LIBRARIES, в которой будем хранить
#все подключаемые к проекту библиотеки, в т.ч. и библиотеки Qt
set(QT_CHAT_SERVER_LIBRARIES)

#Создать и заполнить список подключаемых модулей sources/mainwindow.h sources/mainwindow.cpp sources/mainwindow.ui Qt

#здесь мы создаем и заполняем список подключаемых модулей Qt
#если нужно добавить модули, добавьте их в этот список по образцу:
#set(Qt5Modules [модуль 1] [модуль 2] ... [модуль n])
set(Qt5Modules Core Widgets)

#здесь мы формируем из списка модулей список библиотек,
#которые требуется подключить, и складываем их в QT_CHAT_SERVER_LIBRARIES
foreach(QtModule IN LISTS Qt5Modules)
    list(APPEND QT_CHAT_SERVER_LIBRARIES Qt5::${QtModule})
endforeach(QtModule)

#здесь проверяется наличие всех необходимых модулей и компонентов Qt
find_package(Qt5 COMPONENTS ${Qt5Modules} REQUIRED LinguistTools REQUIRED Sql)#Sql - для SQL#LinguistTools-для перевода

#здесь мы формируем список всех исходников, ассоциированных с
#проектом QT_CHAT_SERVER.
#на самом деле, обязательными являются только SRC RC и UI,
#но я добавляю так же HEADERS, что бы они так же отображались
#в дереве проектов.

#!!! не забывайте, что при добавлении/удалении файлов  обязательно
#нужно запускать CMake
#подключаем ресурсные файлы(qrc) и ui формы(.ui)
file(GLOB_RECURSE SRC_FILES sources/*.cpp)
file(GLOB_RECURSE HEADERS_FILES sources/*.h)
file(GLOB_RECURSE RC_FILES sources/*.qrc)
file(GLOB_RECURSE UI_FILES sources/*.ui)

#здесь мы включаем обязательные для нас опции
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#указывает где искать заголовочные файлы
include_directories(sources/)


#вызываем обработку .ui и .qrc файлов. Здесь же происходит генерация
#промежуточных исходников.
qt5_wrap_ui(QUI ${UI_FILES})
qt5_add_resources(QRC ${RC_FILES})

#здесь происходит создание файлов переводов и установка зависимостей,
#чтобы эти файлы генерировались во время билда проекта
set(TS_FILES
 ${CMAKE_CURRENT_SOURCE_DIR}/translations/my_ru.ts)# Содержит переводы в формате XML, перед сборкой создать папку translations в папке рядом с CMakeLists.txt
file(GLOB_RECURSE TS_SOURCES "*.cpp" "*.h" ".ui")
add_custom_target(translations)
#по сути, при билде для каждого .ts файла вызывается
#утилита lupdate.exe
foreach(_ts_file ${TS_FILES})
 get_filename_component(_ts_name ${_ts_file} NAME_WE)
 add_custom_command(
   OUTPUT "${_ts_file}"
   DEPENDS ${TS_SOURCES}
#вот тут как раз описывается путь к вызываемой утилите lupdate.exe
#и ее входные аргументы:
   COMMAND ${Qt5_LUPDATE_EXECUTABLE} -recursive #подключаем LUPDATE.exe для создания xml
   ${CMAKE_CURRENT_SOURCE_DIR} -ts ${_ts_file}
   )
 add_custom_target(translate_${_ts_name} DEPENDS $ {_ts_file})
 add_dependencies(translations translate_${_ts_name})
endforeach()

#подключаем файлы трансляции(переводов)
qt5_add_translation(QM_FILES ${TS_FILES})#собранные переводы, которые подключаются


#Эта строка кода создает исполняемый файл с названием "QT_CHAT_SERVER" из списка файлов,
#включая файлы перевода (.qm), исходный код (.cpp), заголовочные файлы (.h), файлы ресурсов (.qrc) и файлы интерфейса (.ui).
add_executable(QT_CHAT_SERVER ${QM_FILES} ${SRC_FILES} ${HEADERS_FILES} ${RC_FILES} ${UI_FILES}
    sources/mainwindow.h sources/mainwindow.cpp sources/mainwindow.ui
    sources/Database.h
    sources/Database.cpp
    sources/connect.h sources/connect.cpp sources/connect.ui

)

#подключаем к проекту библиотеки
target_link_libraries(QT_CHAT_SERVER
    PUBLIC
    ${QT_CHAT_SERVER_LIBRARIES})

target_link_libraries(QT_CHAT_SERVER PUBLIC Qt5::Sql)#для SQL
