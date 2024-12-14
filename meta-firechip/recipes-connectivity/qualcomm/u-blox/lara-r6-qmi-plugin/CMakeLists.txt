cmake_minimum_required(VERSION 3.10)
project(lara-r6-qmi-plugin)

find_package(GLib REQUIRED)
find_package(Jansson REQUIRED)

add_library(lara-r6-qmi-plugin SHARED src/lara-r6-qmi-plugin.c)
target_link_libraries(lara-r6-qmi-plugin PRIVATE GLib::GLib Jansson::Jansson qmi-core-module) #Link with the core module
set_target_properties(lara-r6-qmi-plugin PROPERTIES SUFFIX ".so")

install(TARGETS lara-r6-qmi-plugin DESTINATION lib/qmi-daemon/plugins)