cmake_minimum_required(VERSION 3.5)
project(qpdftools VERSION 1.6.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(SRC
  src/main.cpp

  src/interface/mainwindow.hpp
  src/interface/mainwindow.ui
  src/interface/mainwindow.cpp

  src/interface/pages/0-menu.cpp
  src/interface/pages/1-compress.cpp
  src/interface/pages/2-split.cpp
  src/interface/pages/3-merge.cpp
  src/interface/pages/4-rotate.cpp

  src/api/externalSoftware.hpp
  src/api/ghostscript.hpp
  src/api/stapler.hpp

  src/utils/lastDirectory.cpp
)

set(TS_FILES src/languages/qpdftools_pt_BR.ts)
qt5_create_translation(QM ${SRC} ${TS_FILES})

add_executable(qpdftools
  ${SRC}
  ${QM}
)

target_link_libraries(qpdftools
  PRIVATE
    Qt5::Widgets
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

  install(TARGETS qpdftools DESTINATION /usr/bin)
  install(DIRECTORY resources/hicolor DESTINATION /usr/share/icons)
  install(FILES ${QM} DESTINATION /usr/lib/qpdftools)
  install(FILES resources/qpdftools.desktop DESTINATION /usr/share/applications)

endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
