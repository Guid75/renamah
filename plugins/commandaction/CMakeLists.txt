INCLUDE(${QT_USE_FILE})

SET(COMMANDACTION_SOURCES
  command_action_factory.cpp
  command_action.cpp
  config_widget.cpp
  process_handler.cpp
)

SET(COMMANDACTION_FORMS
  config_widget.ui
)

QT4_WRAP_UI(COMMANDACTION_FORMS_H ${COMMANDACTION_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(COMMANDACTION_MOCH
  command_action.h
  command_action_factory.h
  config_widget.h
  process_handler.h
)

ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_NO_DEBUG)

QT4_WRAP_CPP(COMMANDACTION_MOC ${COMMANDACTION_MOCH})

SET(LIBRARY_OUTPUT_PATH ${RENAMAH_BINARY_DIR}/bin/plugins)

IF(WIN32)
	ADD_DEFINITIONS(-DZLIB_WINAPI)
ENDIF(WIN32)

# Translations rules
COMPUTE_QM_FILES(QM_FILES ${COMMANDACTION_SOURCES} ${COMMANDACTION_FORMS} ${COMMANDACTION_MOCH})
ADD_CUSTOM_TARGET(translations_commandaction DEPENDS ${QM_FILES})

ADD_LIBRARY(commandaction SHARED ${COMMANDACTION_SOURCES} ${COMMANDACTION_FORMS_H} ${COMMANDACTION_MOC})

IF(MSVC)
  TARGET_LINK_LIBRARIES(commandaction core ${QT_LIBRARIES})
ENDIF(MSVC)

ADD_DEPENDENCIES(commandaction translations_commandaction)
