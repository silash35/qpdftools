find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)

# Add Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(SRC
  main.cpp

  api/ghostscript.cpp
  api/qpdf.cpp

  interface/mainwindow.ui
  interface/mainwindow.cpp

  interface/pages/2-split.cpp
  interface/pages/3-merge.cpp
  interface/pages/4-rotate.cpp

  interface/pages/0-menu/menu.ui
  interface/pages/0-menu/menu.cpp
  interface/pages/1-compress/compress.ui
  interface/pages/1-compress/compress.cpp

  utils/lastDirectory.cpp
)
add_executable(qpdftools
  ${SRC}
)

set(TS_FILES languages/qpdftools_pt_BR.ts)
qt6_add_translations(qpdftools TS_FILES ${TS_FILES})

target_link_libraries(qpdftools
  PRIVATE
  Qt6::Widgets
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  install(TARGETS qpdftools DESTINATION ${KDE_INSTALL_BINDIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
