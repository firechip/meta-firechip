#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include <glib.h>

#include "plugin_manager.h"

GPtrArray *load_plugins(const char *plugin_dir, GError **error) {
    GPtrArray *plugins = g_ptr_array_new_with_free_func((GDestroyNotify)free_plugin);
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(plugin_dir)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".so") != NULL) {
                char plugin_path[PATH_MAX];
                snprintf(plugin_path, PATH_MAX, "%s/%s", plugin_dir, ent->d_name);

                void *handle = dlopen(plugin_path, RTLD_LAZY);
                if (!handle) {
                    g_set_error(error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "Failed to load plugin %s: %s\n", ent->d_name, dlerror());
                    closedir(dir);
                    g_ptr_array_free(plugins, TRUE);
                    return NULL;
                }

                plugin_t *plugin = g_malloc0_n(1, sizeof(plugin_t));
                plugin->handle = handle;
                plugin->name = g_strdup(ent->d_name);
                plugin->modem_init = dlsym(handle, "modem_init");
                plugin->modem_handle_request = dlsym(handle, "modem_handle_request");

                if (!plugin->modem_init || !plugin->modem_handle_request) {
                    g_printerr("Plugin %s does not have required symbols\n", ent->d_name);
                    dlclose(handle);
                    free_plugin(plugin);
                    closedir(dir);
                    g_ptr_array_free(plugins, TRUE);
                    return NULL;
                }
                g_ptr_array_add(plugins, plugin);
            }
        }
        closedir(dir);
    }
    return plugins;
}

void free_plugin(void *data){
    plugin_t *plugin = (plugin_t*) data;
    if (plugin){
        dlclose(plugin->handle);
        g_free(plugin->name);
        g_free(plugin);
    }
}