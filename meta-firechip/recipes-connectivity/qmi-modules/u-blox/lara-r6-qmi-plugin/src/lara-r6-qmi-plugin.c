#include <stdio.h>
#include <jansson.h>
#include <glib.h>
#include "qmi_core.h"

int modem_init(void) {
    printf("LARA-R6 plugin initialized!\n");
    return 0;
}

int modem_handle_request(const char *request, json_t **response, GError **error) {
    if (g_strcmp0(request, "get_lara_r6_info") == 0) { // Example command
        // Example of using the qmi_core module
        char imei[16];
        if (qmi_get_imei(imei, error) == 0) {
            *response = json_object();
            json_object_set_new(*response, "manufacturer", json_string("u-blox"));
            json_object_set_new(*response, "model", json_string("LARA-R6"));
            json_object_set_new(*response, "imei", json_string(imei));
        } else {
            return -1; // Error already set by qmi_get_imei
        }
        return 0;
    } else if (g_strcmp0(request, "get_signal_strength") == 0) {
        int rssi;
        if (qmi_get_signal_strength(&rssi, error) == 0) {
            *response = json_object();
            json_object_set_new(*response, "rssi", json_integer(rssi));
        } else {
            return -1;
        }
        return 0;
    }
    else {
        g_set_error(error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED, "Request %s not supported by this plugin", request);
        return -1;
    }
}

// Example function using the qmi_core module
int qmi_get_imei(char *imei, GError **error) {
    //Replace this with the real qmi call
    strcpy(imei, "123456789012345");
    return 0;
}

int qmi_get_signal_strength(int *rssi, GError **error){
    //Replace this with the real qmi call
    *rssi = -70;
    return 0;
}