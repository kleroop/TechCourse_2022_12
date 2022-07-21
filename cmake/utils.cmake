function(windeployqt target)
    if (NOT DEFINED _qt5Core_install_prefix)
        message(FATAL_ERROR "function can be only used after Qt5 Core component was found")
    endif ()
    if (WIN32)
        get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
        get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
        find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${WINDEPLOYQT_EXECUTABLE}
                --verbose 1
                "$<TARGET_FILE:${target}>"
                COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
                VERBATIM
                )
    endif ()
endfunction()