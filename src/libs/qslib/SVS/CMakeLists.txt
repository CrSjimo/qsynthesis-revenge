project(QsSVS
    VERSION ${SUB_VERSION}
    LANGUAGES C CXX
)

set(_extra_includes ${QASTOOL_INCLUDE_DIRS})

ck_add_files(_src
    ALLDIRS
    PATTERNS *.h *.hpp *.cpp *.cc
)

configure_library()

ck_target_components(${PROJECT_NAME}
    INCLUDE_CURRENT INCLUDE_SUBDIRS
    SOURCES ${_src}
    QT_LINKS Core
    QT_INCLUDES_PRIVATE Core
    LINKS QMCoreLib
    LINKS_PRIVATE mrq
    INCLUDES ${_extra_includes}
)

include(Dspx/qasc.cmake)