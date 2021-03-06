INCLUDE(${QT_USE_FILE})

SET(CASEFILTER_SOURCES
  case_filter_factory.cpp
  case_filter.cpp
  config_widget.cpp
)

SET(CASEFILTER_FORMS
  config_widget.ui
)

QT4_WRAP_UI(CASEFILTER_FORMS_H ${CASEFILTER_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(CASEFILTER_MOCH
  case_filter.h
  case_filter_factory.h
  config_widget.h
)

QT4_WRAP_CPP(CASEFILTER_MOC ${CASEFILTER_MOCH})

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${CASEFILTER_SOURCES} ${CASEFILTER_FORMS} ${CASEFILTER_MOCH})
ADD_CUSTOM_TARGET(translations_casefilter DEPENDS ${QM_FILES})

# Destination

SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/lib/renamah/plugins)

ADD_LIBRARY(casefilter SHARED ${CASEFILTER_SOURCES} ${CASEFILTER_FORMS_H} ${CASEFILTER_MOC})

IF(WIN32)
  TARGET_LINK_LIBRARIES(casefilter renamahcore ${QT_LIBRARIES})
ENDIF(WIN32)

ADD_DEPENDENCIES(casefilter translations_casefilter)

INSTALL(FILES ${QM_FILES}
  DESTINATION share/renamah/plugins)
