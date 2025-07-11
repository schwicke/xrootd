add_library(
  XrdPosix
  SHARED
  XrdPosixAdmin.cc        XrdPosixAdmin.hh
  XrdPosixCache.cc        XrdPosixCache.hh
  XrdPosixCallBack.cc     XrdPosixCallBack.hh
  XrdPosixConfig.cc       XrdPosixConfig.hh
  XrdPosixDir.cc          XrdPosixDir.hh
  XrdPosixExtra.cc        XrdPosixExtra.hh
  XrdPosixFile.cc         XrdPosixFile.hh
  XrdPosixFileRH.cc       XrdPosixFileRH.hh
  XrdPosixMap.cc          XrdPosixMap.hh
                          XrdPosixObjGuard.hh
  XrdPosixObject.cc       XrdPosixObject.hh
                          XrdPosixOsDep.hh
  XrdPosixPrepIO.cc       XrdPosixPrepIO.hh
                          XrdPosixStats.hh
                          XrdPosixTrace.hh
  XrdPosixXrootd.cc       XrdPosixXrootd.hh
  XrdPosixXrootdPath.cc   XrdPosixXrootdPath.hh
)

target_link_libraries(XrdPosix PRIVATE XrdCl XrdUtils ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(XrdPosix PROPERTIES VERSION 3.0.0 SOVERSION 3)

add_library(XrdPosixPreload SHARED
  XrdPosix.cc           XrdPosix.hh
                        XrdPosixExtern.hh
  XrdPosixLinkage.cc    XrdPosixLinkage.hh
                        XrdPosixOsDep.hh
  XrdPosixPreload.cc
  XrdPosixPreload32.cc
)

target_link_libraries(XrdPosixPreload PRIVATE XrdPosix ${CMAKE_DL_LIBS})
set_target_properties(XrdPosixPreload PROPERTIES VERSION 2.0.0 SOVERSION 2)

install(
  TARGETS
    XrdPosix
    XrdPosixPreload
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
