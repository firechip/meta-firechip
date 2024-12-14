# QMI Daemon

This is the QMI (Qualcomm Message Interface) daemon for the Firechip project. It manages communication with cellular modems using the QMI protocol, providing a modular and extensible architecture through plugins.

## Functionality

The `qmi-daemon` handles the following:

*   **Plugin Loading:** Dynamically loads modem-specific plugins from a configurable directory (default: `/usr/lib/qmi-daemon/plugins`).
*   **Request Handling:** Receives requests (e.g., get IMEI, get signal strength) and dispatches them to the appropriate plugin.
*   **Response Handling:** Receives responses from plugins and returns them to the requesting application.
*   **Configuration:** Loads configuration from `/etc/qmi-daemon.conf` (optional), allowing customization of plugin directory and other settings.
*   **Error Handling:** Provides robust error handling and reporting.
*   **Init System Support:** Supports both Systemd and SysVinit init systems for broad compatibility.

## Directory Structure

*   `src/`: Contains the daemon's source code.
    *   `qmi-daemon.c`: The main daemon source file.
    *   `plugin_manager/`: Contains plugin management code.
        *   `plugin_manager.c`: Plugin loading and management.
        *   `plugin_manager.h`: Plugin interface definition.
*   `include/`: Contains header files.
    *   `plugin_manager.h`: Plugin interface definition.
*   `files/`: Contains configuration files.
    *   `qmi-daemon.conf`: Example configuration file.
*   `qmi-daemon.service`: Systemd service file.
*   `qmi-daemon.init`: SysVinit init script.
*   `CMakeLists.txt`: CMake build file.

## Building

The `qmi-daemon` is built using CMake. The build process (within your Yocto build environment) is handled by the BitBake recipe.

## Configuration (`qmi-daemon.conf`)

The daemon can be configured using the `/etc/qmi-daemon.conf` file. An example configuration:

```ini
[daemon]
plugin_dir = /usr/lib/qmi-daemon/plugins
# log_level = DEBUG  ; DEBUG, INFO, WARNING, ERROR (Future enhancement)
# log_file = /var/log/qmi-daemon.log (Future enhancement)

[modem]
default_modem = lara-r6 # Not currently implemented, but reserved for future use
```

## Plugins

Modem-specific logic is implemented in dynamically loaded plugins. Each plugin *must* implement the following interface (defined in `plugin_manager.h`):

```c
int modem_init(void);
int modem_handle_request(const char *request, json_t **response, GError **error);
```

Plugins should be installed to the directory specified by the `plugin_dir` configuration option (or `/usr/lib/qmi-daemon/plugins` by default).

**Using RPATH for Plugin Loading (Recommended)**

Plugins should use the `RPATH` mechanism in their CMakeLists.txt to specify the location of dependent libraries (like `qmi-core-module`). This is the preferred method for resolving library dependencies.

**Example in plugin's CMakeLists.txt:**

```cmake
set_target_properties(your-plugin-name PROPERTIES
    RPATH "\$ORIGIN"
)
```

## Usage

The `qmi-daemon` is started as a system service by either Systemd or SysVinit, depending on your Yocto image configuration.

## Dependencies

*   GLib
*   Jansson
*   qmi-core-module

## Contributing

Contributions are welcome! Please follow the Firechip project's contribution guidelines.

## Further Information

For more information on QMI, refer to Qualcomm's documentation.

