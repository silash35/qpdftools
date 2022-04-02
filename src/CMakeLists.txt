find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)

# Add Qt
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(SRC
  main.cpp

  interface/mainwindow.ui
  interface/mainwindow.cpp

  interface/pages/0-menu.cpp
  interface/pages/1-compress.cpp
  interface/pages/2-split.cpp
  interface/pages/3-merge.cpp
  interface/pages/4-rotate.cpp

  utils/lastDirectory.cpp
)

set(TS_FILES languages/qpdftools_pt_BR.ts)
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

  install(TARGETS qpdftools DESTINATION ${KDE_INSTALL_BINDIR})
  install(FILES ${QM} DESTINATION ${KDE_INSTALL_LIBDIR}/qpdftools)

endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
