#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include <glib.h>
#include <jansson.h>
#include <unistd.h> // For access()

#include "plugin_manager/plugin_manager.h"

// Default configuration values
#define DEFAULT_PLUGIN_DIR "/usr/lib/qmi-daemon/plugins"
#define DEFAULT_CONFIG_FILE "/etc/qmi-daemon.conf"

// Function to load configuration from file (using GKeyFile)
static GKeyFile *load_config(const char *config_file, GError **error) {
    if (access(config_file, F_OK) != 0) {
        // Config file does not exist, return NULL without setting an error.
        return NULL;
    }

    GKeyFile *keyfile = g_key_file_new();
    if (!g_key_file_load_from_file(keyfile, config_file, G_KEY_FILE_NONE, error)) {
        g_key_file_free(keyfile);
        return NULL;
    }
    return keyfile;
}

int main() {
    printf("Starting qmi-daemon...\n");

    GError *error = NULL;

    // Load configuration
    GKeyFile *config = load_config(DEFAULT_CONFIG_FILE, &error);
    if (error) {
        g_printerr("Error loading config file: %s\n", error->message);
        g_error_free(error);
    }

    const gchar *plugin_dir = DEFAULT_PLUGIN_DIR;
    if (config) {
        if (g_key_file_has_group(config, "daemon") && g_key_file_has_key(config, "daemon", "plugin_dir", NULL)) {
            plugin_dir = g_key_file_get_string(config, "daemon", "plugin_dir", NULL);
        }
    }

    GPtrArray *plugins = load_plugins(plugin_dir, &error);

    if (error) {
        g_printerr("Error loading plugins from %s: %s\n", plugin_dir, error->message);
        g_error_free(error);
        if (config) g_key_file_free(config);
        return 1;
    }

    if (!plugins || plugins->len == 0) {
        g_printerr("No plugins loaded from %s. Exiting.\n", plugin_dir);
        if (config) g_key_file_free(config);
        return 1;
    }

    // Example request handling (replace with your actual logic)
    const char *request = "get_imei"; // Example request
    json_t *response = NULL;

    for (guint i = 0; i < plugins->len; i++) {
        plugin_t *plugin = g_ptr_array_index(plugins, i);
        if (plugin && plugin->modem_handle_request) {
            if (plugin->modem_handle_request(request, &response, &error) != 0) {
                g_printerr("Error handling request with plugin %s: %s\n", plugin->name, error->message);
                g_clear_error(&error); // Clear the error for the next plugin
            } else if (response) {
                char *response_str = json_dumps(response, JSON_INDENT(4));
                printf("Response from plugin %s: %s\n", plugin->name, response_str);
                free(response_str);
                json_decref(response);
                break; // Stop after the first successful response
            }
        }
    }

    if (plugins) {
        g_ptr_array_free(plugins, TRUE);
    }
    if (config) {
        g_key_file_free(config);
    }

    printf("qmi-daemon exiting.\n");
    return 0;
}