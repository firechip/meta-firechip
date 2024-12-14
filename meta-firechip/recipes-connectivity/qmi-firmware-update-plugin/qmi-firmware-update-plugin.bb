SUMMARY = "QMI Firmware Update Plugin"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=d41d8cd98f00b204e9800998ecf8427e" # Replace with actual checksum if needed.

SRC_URI = "file://qmi-firmware-update-plugin.c \
           file://qmi-firmware-update-plugin.h"

S = "${WORKDIR}/qmi-firmware-update-plugin"

inherit cmake

DEPENDS = "glib jansson qmi-core-module"

FILES_${PN} += "/lib/qmi-daemon/plugins/*"
FILES_${PN} += "/usr/include/qmi-firmware-update-plugin/*"

do_install_append() {
    install -d ${D}${libdir}/qmi-daemon/plugins
    install -m 0755 ${B}/libqmi-firmware-update-plugin.so ${D}${libdir}/qmi-daemon/plugins/

    install -d ${D}${includedir}/qmi-firmware-update-plugin
    install -m 0644 ${WORKDIR}/qmi-firmware-update-plugin/qmi-firmware-update-plugin.h ${D}${includedir}/qmi-firmware-update-plugin/
}

# Install RPATH to find qmi-core-module
CMAKE_INSTALL_RPATH_append = "${libdir}"