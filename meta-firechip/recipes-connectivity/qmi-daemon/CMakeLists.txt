cmake_minimum_required(VERSION 3.10)
project(qmi-daemon)

find_package(GLib REQUIRED)
find_package(Jansson REQUIRED)

add_executable(qmi-daemon src/qmi-daemon.c src/plugin_manager/plugin_manager.c)
target_link_libraries(qmi-daemon PRIVATE GLib::GLib Jansson::Jansson)

install(TARGETS qmi-daemon DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)