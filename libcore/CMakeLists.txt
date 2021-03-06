INCLUDE(${QT_USE_FILE})

SET(LIBCORE_SOURCES
  interfaces/modifier_config_widget.cpp
  interfaces/modifier.cpp
)

SET(LIBCORE_FORMS)

QT4_WRAP_UI(LIBCORE_FORMS_H ${LIBCORE_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(LIBCORE_MOCH
  interfaces/modifier_config_widget.h
  interfaces/modifier.h
  interfaces/filter.h
  interfaces/action.h
)

ADD_DEFINITIONS(-DRENAMAH_LIBCORE_LIBRARY)

QT4_WRAP_CPP(LIBCORE_MOC ${LIBCORE_MOCH})

SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/bin)

IF(WIN32)
	ADD_DEFINITIONS(-DZLIB_WINAPI)
ENDIF(WIN32)

ADD_LIBRARY(renamahcore SHARED ${LIBCORE_SOURCES} ${LIBCORE_FORMS_H} ${LIBCORE_MOC})

IF(WIN32)
  TARGET_LINK_LIBRARIES(renamahcore ${QT_LIBRARIES})
ENDIF(WIN32)

IF(NOT WIN32)
  INSTALL(TARGETS renamahcore
    LIBRARY DESTINATION lib)
ENDIF(NOT WIN32)
