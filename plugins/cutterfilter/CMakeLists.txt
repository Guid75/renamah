INCLUDE(${QT_USE_FILE})

SET(CUTTERFILTER_SOURCES
  cutter_filter_factory.cpp
  cutter_filter.cpp
  config_widget.cpp
)

SET(CUTTERFILTER_FORMS
  config_widget.ui
)

QT4_WRAP_UI(CUTTERFILTER_FORMS_H ${CUTTERFILTER_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(CUTTERFILTER_MOCH
  cutter_filter.h
  cutter_filter_factory.h
  config_widget.h
)

QT4_WRAP_CPP(CUTTERFILTER_MOC ${CUTTERFILTER_MOCH})

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${CUTTERFILTER_SOURCES} ${CUTTERFILTER_FORMS} ${CUTTERFILTER_MOCH})
ADD_CUSTOM_TARGET(translations_cutterfilter DEPENDS ${QM_FILES})

# Destination
SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/lib/renamah/plugins)

ADD_LIBRARY(cutterfilter SHARED ${CUTTERFILTER_SOURCES} ${CUTTERFILTER_FORMS_H} ${CUTTERFILTER_MOC})

IF(WIN32)
  TARGET_LINK_LIBRARIES(cutterfilter renamahcore ${QT_LIBRARIES})
ENDIF(WIN32)

ADD_DEPENDENCIES(cutterfilter translations_cutterfilter)

INSTALL(FILES ${QM_FILES}
  DESTINATION share/renamah/plugins)
