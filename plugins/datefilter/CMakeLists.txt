INCLUDE(${QT_USE_FILE})

SET(DATEFILTER_SOURCES
  date_filter_factory.cpp
  date_filter.cpp
  config_widget.cpp
)

SET(DATEFILTER_FORMS
  config_widget.ui
  help_widget.ui
)

QT4_WRAP_UI(DATEFILTER_FORMS_H ${DATEFILTER_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(DATEFILTER_MOCH
  date_filter.h
  date_filter_factory.h
  config_widget.h
)

ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_NO_DEBUG)

QT4_WRAP_CPP(DATEFILTER_MOC ${DATEFILTER_MOCH})

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${DATEFILTER_SOURCES} ${DATEFILTER_FORMS} ${DATEFILTER_MOCH})

ADD_CUSTOM_TARGET(translations_datefilter DEPENDS ${QM_FILES})

# Destination
SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/lib/renamah/plugins)

ADD_LIBRARY(datefilter SHARED ${DATEFILTER_SOURCES} ${DATEFILTER_FORMS_H} ${DATEFILTER_MOC})

IF(MSVC)
  TARGET_LINK_LIBRARIES(datefilter core ${QT_LIBRARIES})
ENDIF(MSVC)

ADD_DEPENDENCIES(datefilter translations_datefilter)

INSTALL(FILES ${QM_FILES}
  DESTINATION share/renamah/plugins)
