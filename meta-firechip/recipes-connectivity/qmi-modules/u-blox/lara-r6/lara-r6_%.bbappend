require recipes-connectivity/qmi-wwan/qmi-wwan.bb
require recipes-connectivity/qmi-daemon/qmi-daemon.bb

SUMMARY = "u-blox LARA-R6 Cellular Module Support"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://0001-add-udev-rules-for-lara-r6.patch \
    git://github.com/firechip/lara-r6-qmi-plugin.git;protocol=https;branch=main;destsuffix=lara-r6-qmi-plugin \
    "
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/lara-r6-qmi-plugin"

DEPENDS += "qmi-daemon glib-2.0 jansson"
RDEPENDS_${PN} += "qmi-daemon glib-2.0 jansson"

KERNEL_PATCHES += "${THISDIR}/${PN}/0001-add-udev-rules-for-lara-r6.patch"

CFLAGS += "-fPIC"
LDFLAGS += "-shared"

PLUGIN_DIR = "${libdir}/qmi-daemon/plugins"

do_install() {
    install -d ${D}${PLUGIN_DIR}
    install -m 0755 ${S}/liblara-r6-qmi-plugin.so ${D}${PLUGIN_DIR}

    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${THISDIR}/${PN}/70-lara-r6.rules ${D}${sysconfdir}/udev/rules.d/
}

FILES_${PN} += "${PLUGIN_DIR}/liblara-r6-qmi-plugin.so"
FILES_${PN} += "${sysconfdir}/udev/rules.d/70-lara-r6.rules"