cmake_minimum_required(VERSION 3.10)
project(qmi-core-module)

find_package(GLib REQUIRED)

add_library(qmi-core-module SHARED src/qmi_core_module.c)
target_include_directories(qmi-core-module PUBLIC include)
target_link_libraries(qmi-core-module PRIVATE GLib::GLib)
set_target_properties(qmi-core-module PROPERTIES SUFFIX ".so")

install(TARGETS qmi-core-module DESTINATION lib)
install(FILES include/qmi_core.h DESTINATION include)