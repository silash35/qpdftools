find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)

# Add Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent LinguistTools)

set(SRC
  main.cpp

  ../resources/fallback-icons/fallback-icons.qrc

  api/externalSoftware.cpp
  api/ghostscript.cpp
  api/qpdf.cpp

  interface/mainwindow.ui
  interface/mainwindow.cpp

  interface/utils/fileDialog.cpp

  interface/pages/0-menu/menu.ui
  interface/pages/0-menu/menu.cpp
  interface/pages/1-compress/compress.ui
  interface/pages/1-compress/compress.cpp
  interface/pages/2-split/split.ui
  interface/pages/2-split/split.cpp
  interface/pages/3-merge/merge.ui
  interface/pages/3-merge/merge.cpp
  interface/pages/4-rotate/rotate.ui
  interface/pages/4-rotate/rotate.cpp
)
add_executable(qpdftools
  ${SRC}
)

set(TS_FILES languages/qpdftools_pt_BR.ts)
qt6_add_translations(qpdftools TS_FILES ${TS_FILES})

target_link_libraries(qpdftools
  PRIVATE
  Qt6::Core
  Qt6::Concurrent
  Qt6::Widgets
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  install(TARGETS qpdftools DESTINATION ${KDE_INSTALL_BINDIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
