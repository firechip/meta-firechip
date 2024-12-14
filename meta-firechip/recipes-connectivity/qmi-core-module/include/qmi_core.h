#ifndef QMI_CORE_H
#define QMI_CORE_H

#include <glib.h>

int qmi_send_command(const void *request, size_t req_len, void *response, size_t *resp_len, GError **error);
int qmi_get_imei(char *imei, GError **error);

#endif