SUMMARY = "u-blox LARA-R6 Cellular Module Support"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=d41d8cd98f00b204e9800998ecf8427e"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://0001-add-udev-rules-for-lara-r6.patch \
    "
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/lara-r6-qmi-plugin"

KERNEL_PATCHES += "${THISDIR}/${PN}/0001-add-udev-rules-for-lara-r6.patch"

do_install() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${THISDIR}/${PN}/70-lara-r6.rules ${D}${sysconfdir}/udev/rules.d/
}

FILES_${PN} += "${sysconfdir}/udev/rules.d/70-lara-r6.rules"