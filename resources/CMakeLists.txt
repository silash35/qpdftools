# Add ECM Modules
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)
include(KDEInstallDirs)

set(ICONS
  icons/16-apps-io.github.silash35.qpdftools.png
  icons/22-apps-io.github.silash35.qpdftools.png
  icons/24-apps-io.github.silash35.qpdftools.png
  icons/32-apps-io.github.silash35.qpdftools.png
  icons/36-apps-io.github.silash35.qpdftools.png
  icons/48-apps-io.github.silash35.qpdftools.png
  icons/64-apps-io.github.silash35.qpdftools.png
  icons/72-apps-io.github.silash35.qpdftools.png
  icons/96-apps-io.github.silash35.qpdftools.png
  icons/128-apps-io.github.silash35.qpdftools.png
  icons/192-apps-io.github.silash35.qpdftools.png
  icons/256-apps-io.github.silash35.qpdftools.png
  icons/512-apps-io.github.silash35.qpdftools.png
  icons/sc-apps-io.github.silash35.qpdftools.svg
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


  ecm_install_icons(ICONS ${ICONS}
    DESTINATION ${KDE_INSTALL_ICONDIR} THEME hicolor
  )

  install(PROGRAMS io.github.silash35.qpdftools.desktop  DESTINATION  ${KDE_INSTALL_APPDIR})
  install(FILES io.github.silash35.qpdftools.appdata.xml DESTINATION  ${KDE_INSTALL_METAINFODIR})

endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
