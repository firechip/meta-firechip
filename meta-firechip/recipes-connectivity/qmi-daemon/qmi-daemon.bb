SUMMARY = "QMI Daemon"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=d41d8cd98f00b204e9800998ecf8427e"

SRC_URI = "file://qmi-daemon.c \
           file://plugin_manager/plugin_manager.c \
           file://include/plugin_manager.h \
           file://qmi-daemon.service \
           file://qmi-daemon.init \
           file://files/qmi-daemon.conf"

S = "${WORKDIR}/qmi-daemon"

inherit cmake

DEPENDS = "glib jansson"

FILES_${PN} += "/etc/qmi-daemon.conf"
FILES_${PN} += "/lib/qmi-daemon/plugins/*"

do_install_append() {
    install -d ${D}${sysconfdir}/
    install -m 0644 ${WORKDIR}/qmi-daemon/files/qmi-daemon.conf ${D}${sysconfdir}/qmi-daemon.conf

    # Install SysVinit script
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/qmi-daemon/qmi-daemon.init ${D}${sysconfdir}/init.d/qmi-daemon

    # Install Systemd service file (only if systemd is the init system)
    if ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', True, False, d)}; then
        install -d ${D}${systemd_unitdir}/system
        install -m 0644 ${WORKDIR}/qmi-daemon/qmi-daemon.service ${D}${systemd_unitdir}/system
        SYSTEMD_SERVICE_${PN} = "qmi-daemon.service"
    fi
}

# Remove this if you are using RPATH
# Environment="LD_LIBRARY_PATH=/usr/lib/qmi-daemon/plugins:$LD_LIBRARY_PATH"