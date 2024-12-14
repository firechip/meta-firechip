cmake_minimum_required(VERSION 3.10)
project(qmi-firmware-update-plugin)

find_package(GLib REQUIRED)
find_package(Jansson REQUIRED)

# Find the qmi-core-module
find_library(QMI_CORE_LIB qmi-core-module)
if(NOT QMI_CORE_LIB)
    message(FATAL_ERROR "qmi-core-module library not found!")
endif()

add_library(qmi-firmware-update-plugin SHARED qmi-firmware-update-plugin.c)
target_include_directories(qmi-firmware-update-plugin PUBLIC .)
target_link_libraries(qmi-firmware-update-plugin PRIVATE GLib::GLib Jansson::Jansson ${QMI_CORE_LIB})
set_target_properties(qmi-firmware-update-plugin PROPERTIES SUFFIX ".so")

install(TARGETS qmi-firmware-update-plugin DESTINATION lib/qmi-daemon/plugins)
install(DIRECTORY . DESTINATION include/qmi-firmware-update-plugin FILES_MATCHING PATTERN "*.h")

# Install RPATH to find qmi-core-module
set_target_properties(qmi-firmware-update-plugin PROPERTIES
    RPATH "\$ORIGIN"
)