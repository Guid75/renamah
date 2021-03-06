INCLUDE(${QT_USE_FILE})

SET(NUMBERINGFILTER_SOURCES
  numbering_filter_factory.cpp
  numbering_filter.cpp
  config_widget.cpp
)

SET(NUMBERINGFILTER_FORMS
  config_widget.ui
)

QT4_WRAP_UI(NUMBERINGFILTER_FORMS_H ${NUMBERINGFILTER_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(NUMBERINGFILTER_MOCH
  numbering_filter.h
  numbering_filter_factory.h
  config_widget.h
)

QT4_WRAP_CPP(NUMBERINGFILTER_MOC ${NUMBERINGFILTER_MOCH})

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${NUMBERINGFILTER_SOURCES} ${NUMBERINGFILTER_FORMS} ${NUMBERINGFILTER_MOCH})
ADD_CUSTOM_TARGET(translations_numberingfilter DEPENDS ${QM_FILES})

# Destination
SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/lib/renamah/plugins)

ADD_LIBRARY(numberingfilter SHARED ${NUMBERINGFILTER_SOURCES} ${NUMBERINGFILTER_FORMS_H} ${NUMBERINGFILTER_MOC})

IF(WIN32)
  TARGET_LINK_LIBRARIES(numberingfilter renamahcore ${QT_LIBRARIES})
ENDIF(WIN32)

ADD_DEPENDENCIES(numberingfilter translations_numberingfilter)

INSTALL(FILES ${QM_FILES}
  DESTINATION share/renamah/plugins)
