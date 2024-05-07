cmake_minimum_required(VERSION 3.16)

project(levelz-cpp 
    LANGUAGES C CXX 
    VERSION 0.1.0 
    DESCRIPTION "C/C++ implementation of the LevelZ File Format"
    HOMEPAGE_URL "https://github.com/LevelZ-File/cpp-bindings"
)
set(CMAKE_CXX_STANDARD 17)

# Sources
add_library(levelz-cpp INTERFACE)

# Testing
enable_testing()
add_subdirectory(test)

# Documentation
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/build/Doxyfile.in)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# Installation
option(INSTALL_LEVELZ_CPP "Install ${PROJECT_NAME}" ON)

if (INSTALL_LEVELZ_CPP)
   include(GNUInstallDirs)
   install(TARGETS levelz-cpp
       EXPORT levelz-cpp-targets
       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
       ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   )

   include(CMakePackageConfigHelpers)
   write_basic_package_version_file("ConfigVersion.cmake"
       VERSION ${PROJECT_VERSION}
       COMPATIBILITY AnyNewerVersion
   )
   configure_package_config_file(
           "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
           "${PROJECT_BINARY_DIR}/Config.cmake"
           INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
   )

   install(EXPORT levelz-cpp-targets
       FILE ${PROJECT_NAME}Targets.cmake
       NAMESPACE ${PROJECT_NAME}::
       DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
   )
   install(FILES "${PROJECT_BINARY_DIR}/Config.cmake"
                 "${PROJECT_BINARY_DIR}/ConfigVersion.cmake"
           DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
   )
   install(DIRECTORY
           "${PROJECT_SOURCE_DIR}/include/levelz"
           "${PROJECT_SOURCE_DIR}/include/"
           DESTINATION include)
endif()