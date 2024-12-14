# Firechip Cellular Connectivity - QMI Stack

This repository provides Yocto Project recipes and configurations for enabling cellular connectivity using the Qualcomm MSM Interface (QMI) protocol. It supports various cellular modems from different vendors, offering a modular and extensible architecture.

## Overview

This project aims to simplify the integration of cellular modems into embedded Linux systems built with the Yocto Project. It provides a complete software stack, including:

*   **Core QMI Functionality:** A core library for sending and receiving QMI messages.
*   **QMI Daemon:** A daemon process that manages communication with the modem and loads modem-specific plugins.
*   **Modem-Specific Plugins:** Plugins that handle the specific details of communicating with different modem models.
*   **Kernel Support:** Recipes to ensure the necessary kernel modules and configurations are included in the image.
*   **Udev Rules:** Udev rules for dynamic device node creation and management.

## Directory Structure

*   `meta-firechip/`: This is the main Yocto layer containing the QMI recipes.
    *   `conf/`: Layer configuration files (e.g., `layer.conf`).
    *   `recipes-connectivity/`: Contains the recipes for the QMI stack.
        *   `qmi-core-module/`: Recipe for the core QMI library.
        *   `qmi-daemon/`: Recipe for the QMI daemon.
        *   `qmi-firmware-update-plugin/`: Recipe for a generic firmware update plugin.
        *   `qmi-wwan/`: Recipe for kernel modules and network configuration.
        *   `qualcomm/`: Contains recipes for specific Qualcomm-based modems.
            *   `fibocom/`, `inforce-computing/`, `meig/`, `neoway/`, `quectel/`, `sierra-wireless/`, `simcom/`, `telit/`, `u-blox/`, `variscite/`: Subdirectories for different vendors.
                *   `vendor/model/`: Subdirectories for specific modem models within each vendor.
                    *   `70-*.rules`: Udev rules for the modem.
                    *   `*.bbappend`: BitBake append files for customizing generic recipes.
                    *   `*-qmi-plugin/`: Subdirectories containing modem-specific QMI plugins.
                        *   `*.bbappend`: BitBake append files for customizing generic plugin recipes.
                        *   `CMakeLists.txt`: CMake build files for the plugin.
                        *   `include/`: Header files for the plugin.
                        *   `src/`: Source code for the plugin.

## Building

To build the QMI stack, you need to integrate the `meta-firechip` layer into your Yocto build environment. Then, you can build your image using the standard BitBake command:

```bash
bitbake <your-image-name>
```

Make sure that your kernel configuration includes the necessary options for QMI WWAN support (`CONFIG_USB_NET_QMI_WWAN`).

## Key Components and Their Roles

*   **qmi-core-module:** Provides low-level functions for sending and receiving QMI messages. It does *not* handle QMI message encoding/decoding for specific services.
*   **qmi-daemon:** A user-space daemon that manages communication with the modem. It loads modem-specific plugins and uses the `qmi-core-module` for QMI communication.
*   **Modem-Specific Plugins:** These plugins handle the details of communicating with specific modem models, including QMI message encoding/decoding, handling specific QMI services, and implementing modem-specific functionalities.
*   **qmi-wwan:** Ensures that the necessary kernel modules are included in the image and configures the network interface.
*   **Udev Rules:** Automatically create consistent device nodes for the modem, regardless of the USB port it's connected to.

## Adding Support for a New Modem

To add support for a new modem, you typically need to:

1.  Create a new directory under `meta-firechip/recipes-connectivity/qualcomm/<vendor>/<model>/`.
2.  Create udev rules (`70-*.rules`) for the modem.
3.  Create a modem-specific QMI plugin.
4.  Create a BitBake recipe for the plugin.
5.  If needed, create a `.bbappend` file to modify a generic recipe.
6.  Add any required firmware packages as dependencies.

## Dependencies

*   Yocto Project
*   GLib
*   Jansson
*   Linux kernel with QMI WWAN support (`CONFIG_USB_NET_QMI_WWAN`)

## Contributing

Contributions are welcome! Please follow the Firechip project's contribution guidelines.

## Further Information

*   Qualcomm QMI documentation (search online)
*   u-blox documentation (if using a u-blox modem)
*   Other modem vendor documentation

