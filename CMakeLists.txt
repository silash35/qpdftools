cmake_minimum_required(VERSION 3.5)
project(qpdftools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES languages/qpdftools_pt_BR.ts)

set(SRC
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
)

qt5_create_translation(QM ${SRC} ${TS_FILES})
qt5_add_translation(QM ${TS_FILES})

add_executable(qpdftools
    ${SRC}
    ${QM}
)

target_link_libraries(qpdftools
    PRIVATE
        Qt5::Widgets
)

#qt5_create_translation(QM ${TS_FILES})
