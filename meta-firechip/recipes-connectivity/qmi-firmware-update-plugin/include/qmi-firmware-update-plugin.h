#ifndef QMI_FIRMWARE_UPDATE_PLUGIN_H
#define QMI_FIRMWARE_UPDATE_PLUGIN_H

#include <glib.h>
#include <jansson.h>

int modem_init(void);
int modem_handle_request(const char *request, json_t **response, GError **error);

#endif