# qmi-core-module

This module provides core functionality for interacting with QMI (Qualcomm Message Interface) devices. It offers a set of functions for sending and receiving QMI messages, handling errors, and managing communication with QMI modems.

## Functionality

The `qmi-core-module` provides the following:

*   **QMI Message Sending:** Functions for sending QMI requests to the modem.
*   **QMI Message Receiving:** Functions for receiving QMI responses from the modem.
*   **Error Handling:** Robust error handling using `GError` from GLib.
*   **Basic QMI Device Communication:** Low-level functions for opening, writing to, and reading from the QMI device node (e.g., `/dev/qmi-control`).

**Important Note:** This module provides *basic* QMI communication. It *does not* include specific QMI message encoding/decoding for individual services (e.g., DMS, WDS, NAS). That functionality is handled by the modem-specific plugins.

## Directory Structure

*   `src/`: Contains the source code.
    *   `qmi_core_module.c`: The main source file.
*   `include/`: Contains the header file.
    *   `qmi_core.h`: The header file defining the public interface.
*   `CMakeLists.txt`: The CMake build file.

## Building

The `qmi-core-module` is built using CMake within the Yocto build environment. The BitBake recipe handles the build process.

## Usage

This module is intended to be used by other applications or plugins that need to communicate with QMI devices. To use it, you need to link against the `qmi-core-module` library and include the `qmi_core.h` header file.

**Example (Conceptual):**

```c
#include "qmi_core.h"
#include <glib.h>

int main() {
    GError *error = NULL;
    char imei[20] = {0};

    if (qmi_get_imei(imei, &error) == 0) {
        printf("IMEI: %s\n", imei);
    } else {
        g_printerr("Error getting IMEI: %s\n", error->message);
    }

    return 0;
}
```

## Dependencies

*   GLib

## Implementation Notes

*   **QMI Message Encoding/Decoding:** As mentioned above, this module *does not* handle QMI message encoding/decoding. Plugins are responsible for this.
*   **Asynchronous I/O:** The current implementation uses basic blocking I/O. For production use, it's *essential* to implement asynchronous I/O using `select`, `poll`, or other non-blocking mechanisms.
*   **Dynamic Device Discovery:** The QMI device path (e.g., `/dev/qmi-control`) should be discovered dynamically rather than being hardcoded. This can be done using udev rules or by checking `/sys/class/net`.

## Contributing

Contributions are welcome! Please follow the Firechip project's contribution guidelines.
