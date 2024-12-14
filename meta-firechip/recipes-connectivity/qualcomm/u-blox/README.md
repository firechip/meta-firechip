# u-blox Modem Support for Firechip

This directory contains Yocto recipes and supporting files for integrating u-blox cellular modems with the Firechip platform. We aim to provide comprehensive support for a range of u-blox modules, enabling seamless connectivity and robust performance.

## Currently Supported Modems

The following u-blox modems are currently supported:

*   **LARA-R6:** This module provides LTE Cat 4 connectivity and is well-suited for various IoT applications.
*   **SARA-R510M8S:** This module offers LTE-M and NB-IoT connectivity, ideal for low-power wide-area network (LPWAN) deployments.
*   **TOBY-L200:** This module supports HSPA+ connectivity, providing a fallback option where LTE is not available.

## Planned Modem Support

We are actively working on adding support for more u-blox modems. Future additions may include:

*   **SARA-R4 series:** This series offers a range of LTE Cat 1 and LTE-M modules with different form factors and features.
*   **LISA series:** This series provides high-speed LTE Cat 6 and Cat 12 connectivity for demanding applications.
*   Other u-blox modules based on project needs and community contributions.

## Directory Structure

*   `lara-r6/`: Contains the Yocto recipe (`lara-r6_%.bbappend`), udev rules (`70-lara-r6.rules`), and any necessary patches (`0001-add-udev-rules-for-lara-r6.patch`) for the LARA-R6 module.
*   `sara-r510m8s/`: Contains the Yocto recipe, udev rules, and patches for the SARA-R510M8S module.
*   `toby-l200/`: Contains the Yocto recipe, udev rules, and patches for the TOBY-L200 module.
*   `*-qmi-plugin/`: Contains the source code and build files for the QMI plugin specific to each modem.

## Contributing

We welcome contributions from the community! If you are interested in adding support for a new u-blox modem or improving existing support, please follow these steps:

1.  Fork this repository.
2.  Create a new branch for your changes.
3.  Implement the necessary changes, including Yocto recipes, udev rules, and QMI plugin code.
4.  Submit a pull request.

## Further Information

For more information about u-blox modems, please refer to the official u-blox website: [https://www.u-blox.com/](https://www.u-blox.com/)

This README provides a high-level overview of the u-blox modem support within the Firechip project. Please refer to the individual modem directories for more detailed information.