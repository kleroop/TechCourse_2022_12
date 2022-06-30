function(windeployqt target)
    if (NOT DEFINED _qt5Core_install_prefix)
        message(FATAL_ERROR "function can be only used after Qt5 Core component was found")
    endif ()
    if (WIN32)
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND "${_qt5Core_install_prefix}/bin/windeployqt.exe"
                --verbose 1
                "$<TARGET_FILE:${target}>"
                COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
                VERBATIM
                )
    endif ()
endfunction()