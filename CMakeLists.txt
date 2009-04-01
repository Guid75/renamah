PROJECT(RENAMAH)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

FIND_PACKAGE(Qt4 REQUIRED)

include_directories(
  ${RENAMAH_BINARY_DIR}/libcore
  )

option (UPDATE_TRANSLATIONS "Update source translation translations/*.ts files (WARNING: make clean will delete the source .ts files! Danger!)"
  "off")

ADD_SUBDIRECTORY(libcore)
ADD_SUBDIRECTORY(plugins)
ADD_SUBDIRECTORY(renamah)

# INSTALL(TARGETS renamah
#	RUNTIME DESTINATION bin)
#INSTALL(DIRECTORY share/renamah
#        DESTINATION share
#        PATTERN .svn
#        EXCLUDE)
#INSTALL(DIRECTORY share/applications
#        DESTINATION share
#        PATTERN .svn
#        EXCLUDE)
#INSTALL(DIRECTORY share/pixmaps
#        DESTINATION share
#        PATTERN .svn
#        EXCLUDE)