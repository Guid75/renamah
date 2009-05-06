INCLUDE(${QT_USE_FILE})

SET(REPLACEFILTER_SOURCES
  replace_filter_factory.cpp
  replace_filter.cpp
  config_widget.cpp
)

SET(REPLACEFILTER_FORMS
  config_widget.ui
)

QT4_WRAP_UI(REPLACEFILTER_FORMS_H ${REPLACEFILTER_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(REPLACEFILTER_MOCH
  replace_filter.h
  replace_filter_factory.h
  config_widget.h
)

ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_NO_DEBUG)

QT4_WRAP_CPP(REPLACEFILTER_MOC ${REPLACEFILTER_MOCH})

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${REPLACEFILTER_SOURCES} ${REPLACEFILTER_FORMS} ${REPLACEFILTER_MOCH})
ADD_CUSTOM_TARGET(translations_replacefilter DEPENDS ${QM_FILES})

# Destination
SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/lib/renamah/plugins)

ADD_LIBRARY(replacefilter SHARED ${REPLACEFILTER_SOURCES} ${REPLACEFILTER_FORMS_H} ${REPLACEFILTER_MOC})

IF(MSVC)
  TARGET_LINK_LIBRARIES(replacefilter core ${QT_LIBRARIES})
ENDIF(MSVC)

ADD_DEPENDENCIES(replacefilter translations_replacefilter)
