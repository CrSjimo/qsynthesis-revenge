set(CURRENT_PLUGIN_CATEGORY defaultplugins)
set(CURRENT_PLUGIN_DESC "QSynthesis Library Plugin")

# Use `PROJECT_NAME` as name and `PROJECT_VERSION` as version by default

function(configure_plugin _plugin _author)
    # Begin parse
    set(options)
    set(oneValueArgs MACRO_PREFIX LIBRARY_MACRO TYPE_MACRO PLUGIN_NAME PLUGIN_VERSION)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(_add_lib_args)

    if(FUNC_MACRO_PREFIX)
        list(APPEND _add_lib_args MACRO_PREFIX ${FUNC_MACRO_PREFIX})
    endif()

    if(FUNC_LIBRARY_MACRO)
        list(APPEND _add_lib_args LIBRARY_MACRO ${FUNC_LIBRARY_MACRO})
    endif()

    if(FUNC_TYPE_MACRO)
        list(APPEND _add_lib_args TYPE_MACRO ${FUNC_TYPE_MACRO})
    endif()

    if(FUNC_PLUGIN_NAME)
        set(_name ${FUNC_PLUGIN_NAME})
    else()
        set(_name ${PROJECT_NAME})
    endif()

    if(FUNC_PLUGIN_VERSION)
        set(_version ${FUNC_PLUGIN_VERSION})
    else()
        set(_version ${PROJECT_VERSION})
    endif()

    # End parse
    set(_target ${SUB_PROJECT}_${PROJECT_NAME})
    ck_add_library(${_target} SHARED AUTOGEN SKIP_INSTALL ${_add_lib_args})
    add_library(${SUB_PROJECT}::${PROJECT_NAME} ALIAS ${_target})

    ck_configure_plugin(${_target}
        PARENT ${SUB_PROJECT}
        CATEGORY ${CURRENT_PLUGIN_CATEGORY}
        ${FUNC_UNPARSED_ARGUMENTS}
    )

    ck_target_res(${_target}
        NAME ${_name}
        VERSION ${_version}
        DESCRIPTION ${CURRENT_PLUGIN_DESC}
        COPYRIGHT "Copyright ${_author}"
    )

    set(${_plugin} ${_target} PARENT_SCOPE)
endfunction()

add_subdirectory(AudioDecoder)
add_subdirectory(AudioEncoder)
add_subdirectory(AudioPlayback)
add_subdirectory(WindowHandle)