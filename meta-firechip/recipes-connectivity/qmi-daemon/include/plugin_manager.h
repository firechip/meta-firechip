#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <glib.h>
#include <jansson.h>

// Structure to represent a loaded plugin
typedef struct {
    void *handle;       // Handle to the loaded library (from dlopen)
    char *name;        // Name of the plugin (filename)
    int (*modem_init)(void);                          // Pointer to the plugin's init function
    int (*modem_handle_request)(const char *request, json_t **response, GError **error); // Pointer to the request handler
} plugin_t;

// Loads plugins from the specified directory
GPtrArray *load_plugins(const char *plugin_dir, GError **error);

// Frees the memory allocated for a plugin
void free_plugin(void *data);

#endif // PLUGIN_MANAGER_H