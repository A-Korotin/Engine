set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(VersionRange 1.2.3.4...5.6.7.8 CONFIG NAMES VersionRangeCfg)

if (NOT VersionRange_FOUND)
  message (FATAL_ERROR "Package VersionRange not found in CONFIG mode.")
endif()

if (NOT VersionRange_VERSION VERSION_EQUAL "2.3.4.5")
  message (SEND_ERROR "Wrong version : ${VersionRange_VERSION}")
endif()
if (NOT VersionRange_VERSION_MAJOR VERSION_EQUAL "2")
  message (SEND_ERROR "Wrong major version : ${VersionRange_VERSION_MAJOR}")
endif()
if (NOT VersionRange_VERSION_MINOR VERSION_EQUAL "3")
  message (SEND_ERROR "Wrong minor version : ${VersionRange_VERSION_MINOR}")
endif()
if (NOT VersionRange_VERSION_PATCH VERSION_EQUAL "4")
  message (SEND_ERROR "Wrong patch version : ${VersionRange_VERSION_PATCH}")
endif()
if (NOT VersionRange_VERSION_TWEAK VERSION_EQUAL "5")
  message (SEND_ERROR "Wrong tweak version : ${VersionRange_VERSION_TWEAK}")
endif()
