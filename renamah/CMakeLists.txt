SET(QT_USE_QTXML TRUE)
# SET(QT_USE_QTNETWORK TRUE)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(RENAMAH_SOURCES
  main.cpp
  main_window.cpp
  form_twinning.cpp
  simple_dir_model.cpp
  twinning_widget.cpp
  widget_simple.cpp
  file_model.cpp
  filter_model.cpp
  filter_manager.cpp
  plugin_manager.cpp
  form_last_operations.cpp
  task_manager.cpp
  modifier_delegate.cpp
  led_widget.cpp
  processor.cpp
  widget_modifiers.cpp
  modifier_manager.cpp
  modifier_model.cpp
  finalizer_model.cpp
  action_manager.cpp
  widget_extension_policy.cpp
  extension_policy.cpp
  widget_filters.cpp
  widget_actions.cpp
  dialog_manual_rename.cpp
  profile.cpp
  undo_manager.cpp
  global.cpp
  paths.cpp
)

SET(RENAMAH_FORMS
  main_window.ui
  form_twinning.ui
  widget_simple.ui
  form_last_operations.ui
  widget_modifiers.ui
  widget_extension_policy.ui
  dialog_manual_rename.ui
)

QT4_WRAP_UI(RENAMAH_FORMS_H ${RENAMAH_FORMS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/staticlibs)

SET(RENAMAH_MOCH
  main_window.h
  form_twinning.h
  simple_dir_model.h
  twinning_widget.h
  widget_simple.h
  file_model.h
  filter_model.h
  form_last_operations.h
  modifier_delegate.h
  led_widget.h
  processor.h
  widget_modifiers.h
  modifier_model.h
  finalizer_model.h
  widget_extension_policy.h
  widget_filters.h
  widget_actions.h
  dialog_manual_rename.h
  undo_manager.h
)

# Translations stuff
COMPUTE_QM_FILES(QM_FILES ${RENAMAH_SOURCES} ${RENAMAH_FORMS} ${RENAMAH_MOCH})
ADD_CUSTOM_TARGET(translations_renamah DEPENDS ${QM_FILES})

QT4_WRAP_CPP(RENAMAH_MOC ${RENAMAH_MOCH})

QT4_ADD_RESOURCES(RENAMAH_RES renamah.qrc)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(renamah ${RENAMAH_SOURCES} ${RENAMAH_FORMS_H} ${RENAMAH_MOC} ${RENAMAH_RES})

ADD_DEPENDENCIES(renamah translations_renamah)

TARGET_LINK_LIBRARIES(
  renamah renamahcore ${QT_LIBRARIES}
)

INSTALL(TARGETS renamah
  RUNTIME DESTINATION bin)

INSTALL(FILES ${QM_FILES}
  DESTINATION share/renamah/)

#INSTALL(DIRECTORY share/applications
#        DESTINATION share
#        PATTERN .svn
#        EXCLUDE)
#INSTALL(DIRECTORY share/pixmaps
#        DESTINATION share
#        PATTERN .svn
#        EXCLUDE)
