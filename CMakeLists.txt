# Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

cmake_minimum_required(VERSION 3.31)
project(Bar
  VERSION 1.0.0
  LANGUAGES C
  )

find_package(Qux 1.0 REQUIRED)

add_library(bar)
add_library(Bar::bar ALIAS bar)

include(GenerateExportHeader)
generate_export_header(bar)

target_sources(bar
  PUBLIC
    FILE_SET HEADERS
      FILES bar.h
    FILE_SET generated_headers
      TYPE HEADERS
      BASE_DIRS ${Bar_BINARY_DIR}
      FILES ${Bar_BINARY_DIR}/bar_export.h
  PRIVATE
    bar.c
  )

target_link_libraries(bar PRIVATE Qux::qux)

set_target_properties(bar PROPERTIES
  C_VISIBILITY_PRESET hidden
  )

include(GNUInstallDirs)
if(WIN32)
  set(cmake_package_config_dir "cmake")
else()
  set(cmake_package_config_dir "${CMAKE_INSTALL_LIBDIR}/cmake/Bar")
endif()

install(TARGETS bar EXPORT bar-targets
  FILE_SET HEADERS
  FILE_SET generated_headers
  )

get_target_property(bar_type bar TYPE)
if(bar_type STREQUAL "STATIC_LIBRARY")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/bar-config.cmake"
    "include(CMakeFindDependencyMacro)\n"
    "find_dependency(Qux ${Qux_VERSION})\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/bar-targets.cmake\")\n"
    )
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bar-config.cmake"
    DESTINATION "${cmake_package_config_dir}"
    )
  set(bar_targets_file "bar-targets.cmake")
else()
  set(bar_targets_file "bar-config.cmake")
endif()

install(EXPORT bar-targets DESTINATION "${cmake_package_config_dir}"
  FILE "${bar_targets_file}"
  NAMESPACE Bar::
  )

include(CPack)
