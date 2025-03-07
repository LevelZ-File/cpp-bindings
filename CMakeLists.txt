cmake_minimum_required(VERSION 3.16)

set(PROJECT_VERSION "0.3.0")
project(levelz-cpp 
    LANGUAGES CXX 
    VERSION 0.3.0
    DESCRIPTION "C++ implementation of the LevelZ File Format"
    HOMEPAGE_URL "https://github.com/LevelZ-File/cpp-bindings"
)
set(PROJECT_DOCUMENTATION "https://levelz-file.github.io/cpp-bindings")

set(CMAKE_CXX_STANDARD 17)

# Sources
add_library(levelz-cpp INTERFACE)

# Testing
enable_testing()

if (WIN32)
    add_subdirectory(test)
else()
    add_subdirectory(test EXCLUDE_FROM_ALL)
endif()

# Documentation
option(DOCS_LEVELZ_CPP "Build API documentation with Doxygen" ON)

if (DOCS_LEVELZ_CPP)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/build/Doxyfile.in)
    
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    
        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    endif()
endif()

# Installation
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(CMAKE_INSTALL_PREFIX "C:/Program Files/${CMAKE_PROJECT_NAME}")
    else()
        set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/${CMAKE_PROJECT_NAME}")
    endif()
elseif(APPLE)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
else()
    set(CMAKE_INSTALL_PREFIX "/usr")
endif()

option(INSTALL_LEVELZ_CPP "Install ${PROJECT_NAME}" ON)

if (INSTALL_LEVELZ_CPP)
    include(GNUInstallDirs)
    install(TARGETS levelz-cpp
        EXPORT levelz-cpp-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION include
    )
    install(EXPORT levelz-cpp-targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    )

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
    )

    install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}
    )
    install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include COMPONENT library)

    if (DOCS_LEVELZ_CPP)
        if (EXISTS "${PROJECT_SOURCE_DIR}/build/docs/html")
            install(DIRECTORY
                "${PROJECT_SOURCE_DIR}/build/docs/html"
                DESTINATION ${CMAKE_INSTALL_DOCDIR}
                COMPONENT htmlDocs
            )
        endif()

        if (EXISTS "${PROJECT_SOURCE_DIR}/build/docs/latex")
            install(DIRECTORY
                "${PROJECT_SOURCE_DIR}/build/docs/latex"
                DESTINATION ${CMAKE_INSTALL_DOCDIR}
                COMPONENT latexDocs
            )
        endif()
        
        install(FILES
            "${PROJECT_SOURCE_DIR}/README.md"
            "${PROJECT_SOURCE_DIR}/LICENSE"
            "${PROJECT_SOURCE_DIR}/LICENSE.rtf"
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
            COMPONENT attribution
        )
    endif()
endif()

# Packaging
option(PACKAGE_LEVELZ_CPP "Package ${PROJECT_NAME}" ON)

if (PACKAGE_LEVELZ_CPP)
    set(ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

    if (ARCHITECTURE STREQUAL "AMD64" OR ARCHITECTURE STREQUAL "x86_64")
        set(ARCHITECTURE "x64")
    endif()

    if (ARCHITECTURE STREQUAL "aarch64")
        set(ARCHITECTURE "arm64")
    endif()

    set(CPACK_THREADS 0) # Use all available threads
    set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/build/package")
    set(CPACK_PACKAGE_CHECKSUM SHA256)

    if (DEFINED PROJECT_VERSION_SUFFIX)
        set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}-${PROJECT_VERSION_SUFFIX}")
    else()
        set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    endif()

    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
    set(CPACK_PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
    set(CPACK_PACKAGE_VENDOR "Gregory Mitchell")
    set(CPACK_PACKAGE_CONTACT "me@gmitch215.xyz")

    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

    if (WIN32)
        set(CPACK_GENERATOR "ZIP;NSIS;TGZ;WIX")

        set(CPACK_SYSTEM_NAME "windows-${ARCHITECTURE}")

        # NSIS
        set(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
        set(CPACK_NSIS_DISPLAY_NAME_SET ON)
        set(CPACK_NSIS_PACKAGE_NAME ${PROJECT_NAME})

        set(CPACK_NSIS_MENU_LINKS "GitHub" ${PROJECT_HOMEPAGE_URL} "Documentation" ${PROJECT_DOCUMENTATION})
        set(CPACK_NSIS_MODIFY_PATH ON)

        # WiX
        set(CPACK_WIX_VERSION 4)
       set(CPACK_WIX_LICENSE_RTF "${PROJECT_SOURCE_DIR}/LICENSE.rtf")

        set(CPACK_WIX_UPGRADE_GUID "1b6b1ddc-31e1-473c-b79f-9e511fb19aea")
        set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY ${PROJECT_NAME})
    elseif(APPLE)
        set(CPACK_GENERATOR "TGZ;ZIP;productbuild")

        set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
        set(CPACK_SYSTEM_NAME "macOS-${ARCHITECTURE}")

        set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.rtf")

        set(CPACK_PRODUCTBUILD_IDENTIFIER "dev.gmitch215.${PROJECT_NAME}")
    elseif(UNIX)
        set(CPACK_GENERATOR "TGZ;TXZ;DEB;RPM")

        set(CPACK_SYSTEM_NAME "linux-${ARCHITECTURE}")

        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <${CPACK_PACKAGE_CONTACT}>")

        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    endif()

    include(CPack)

    cpack_add_component(library DISPLAY_NAME "LevelZ C++ Library" DESCRIPTION "The core library" REQUIRED ON)
    cpack_add_component(attribution DISPLAY_NAME "Attribution" DESCRIPTION "Attribution files" REQUIRED ON)

    cpack_add_component_group(docs DISPLAY_NAME "Documentation" DESCRIPTION "Documentation for the library" EXPANDED ON)
    cpack_add_component(htmlDocs DISPLAY_NAME "HTML Documentation" DESCRIPTION "HTML documentation" GROUP docs DISABLED ON)
    cpack_add_component(latexDocs DISPLAY_NAME "LaTeX Documentation" DESCRIPTION "LaTeX documentation" GROUP docs DISABLED ON)
endif()
