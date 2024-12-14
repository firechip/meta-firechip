# Simcom Modem Support for Firechip

This directory contains Yocto recipes and supporting files for integrating Simcom cellular modems with the Firechip platform. We aim to provide robust and reliable connectivity solutions using Simcom modules.

## Currently Supported Modems

The following Simcom modems are currently supported:

*   **SIMCOM-7600:** This module offers multi-band LTE-FDD/TDD, HSPA+, GSM/GPRS/EDGE connectivity, making it suitable for a wide range of applications.

## Planned Modem Support

We are planning to expand support for other Simcom modules in the future, including:

*   **SIM7000/SIM7020/SIM7080 series:** These modules offer narrowband IoT (NB-IoT) and LTE-M connectivity for low-power wide-area network (LPWAN) applications.
*   **SIM800/SIM900 series:** These modules provide GSM/GPRS connectivity for basic data and voice communication.
*   Other Simcom modules based on project requirements and community contributions.

## Directory Structure

*   `simcom-7600/`: Contains the Yocto recipe (`simcom-7600_%.bbappend`), udev rules (`70-simcom-7600.rules`), and any necessary patches (`0001-add-udev-rules-for-simcom-7600.patch`) for the SIMCOM-7600 module.
*   `*-qmi-plugin/`: Contains the source code and build files for the QMI plugin specific to each modem.

## Important Note on Qualcomm Chipsets

Simcom modules are based on Qualcomm chipsets. Therefore, they are located under the `qualcomm` directory within the `recipes-connectivity` folder. This organization reflects the underlying hardware architecture and allows for consistent handling of Qualcomm-based modems.

## Contributing

We welcome contributions from the community! If you are interested in adding support for a new Simcom modem or improving existing support, please follow these steps:

1.  Fork this repository.
2.  Create a new branch for your changes.
3.  Implement the necessary changes, including Yocto recipes, udev rules, and QMI plugin code.
4.  Submit a pull request.

## Further Information

For more information about Simcom modems, please refer to the official Simcom website: [https://www.simcom.com/](https://www.simcom.com/)

This README provides a high-level overview of the Simcom modem support within the Firechip project. Please refer to the individual modem directories for more detailed information.