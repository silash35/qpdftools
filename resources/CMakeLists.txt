# Add ECM Modules
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)
include(KDEInstallDirs)

set(ICONS
  icons/16-apps-br.eng.silas.qpdftools.png
  icons/22-apps-br.eng.silas.qpdftools.png
  icons/24-apps-br.eng.silas.qpdftools.png
  icons/32-apps-br.eng.silas.qpdftools.png
  icons/36-apps-br.eng.silas.qpdftools.png
  icons/48-apps-br.eng.silas.qpdftools.png
  icons/64-apps-br.eng.silas.qpdftools.png
  icons/72-apps-br.eng.silas.qpdftools.png
  icons/96-apps-br.eng.silas.qpdftools.png
  icons/128-apps-br.eng.silas.qpdftools.png
  icons/192-apps-br.eng.silas.qpdftools.png
  icons/256-apps-br.eng.silas.qpdftools.png
  icons/512-apps-br.eng.silas.qpdftools.png
  icons/sc-apps-br.eng.silas.qpdftools.svg
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  ecm_install_icons(ICONS ${ICONS}
    DESTINATION ${KDE_INSTALL_ICONDIR} THEME hicolor
  )

  install(PROGRAMS br.eng.silas.qpdftools.desktop DESTINATION ${KDE_INSTALL_APPDIR})
  install(FILES br.eng.silas.qpdftools.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
