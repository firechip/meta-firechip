# qmi-firmware-update-plugin

This plugin for the `qmi-daemon` provides firmware update functionality for cellular modems using the QMI protocol.

## Functionality

This plugin enables the following operations:

*   **Firmware Update:** Initiates the firmware update process on the modem. (Placeholder implementation provided, requires actual QMI code).
*   **Get Firmware Version:** Retrieves the current firmware version of the modem. (Placeholder implementation provided, requires actual QMI code).

## Directory Structure

*   `qmi-firmware-update-plugin.c`: The main source file containing the plugin logic.
*   `qmi-firmware-update-plugin.h`: The header file defining the plugin interface.
*   `CMakeLists.txt`: The CMake build file.

## Building

This plugin is built using CMake within the Yocto build environment. The BitBake recipe handles the build process.

## Usage

The plugin is dynamically loaded by the `qmi-daemon` at runtime. It exposes the following requests:

*   `firmware_update`: Initiates the firmware update process.
*   `get_firmware_version`: Retrieves the current firmware version.

To use these requests, send them to the `qmi-daemon`. The daemon will then dispatch them to this plugin.

**Example (Conceptual):**

A request to the `qmi-daemon` might look like this (the actual implementation depends on how you interact with the daemon):

```json
{
  "request": "firmware_update",
  "modem": "lara-r6" // Or another modem identifier
}
```

The plugin would then respond with a JSON object indicating the status of the update:

```json
{
  "status": "Update initiated" // Or "Update successful", "Update failed", etc.
}
```

Or for firmware version:

```json
{
  "request": "get_firmware_version",
  "modem": "lara-r6"
}
```

Response:

```json
{
  "firmware_version": "00.01.07.02"
}
```

## Dependencies

*   GLib
*   Jansson
*   qmi-core-module

## Implementation Notes

*   **QMI Communication:** The current implementation provides placeholder logic for firmware update and version retrieval. You *must* implement the actual QMI message encoding/decoding and communication using the `qmi-core-module`.
*   **Error Handling:** The plugin uses `GError` for error reporting.
*   **RPATH:** The CMakeLists.txt uses `RPATH` to ensure that the plugin can find the `qmi-core-module` at runtime. This is the recommended approach for handling library dependencies.

## Contributing

Contributions are welcome! Please follow the Firechip project's contribution guidelines.
