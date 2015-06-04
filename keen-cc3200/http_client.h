/*
 * http_client.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#define MAX_BUFF_SIZE      1460
#define BUFF_SIZE          MAX_BUFF_SIZE + 1

// MAX_BUFF_SIZE_DIGITS = floor( log10( (float) BUFF_SIZE ) + 1.0 )
#define MAX_BUFF_DIGITS   4
#define BUFF_DIGITS       MAX_BUFF_DIGITS + 1

#define HTTP_SUCCESS       0
#define HTTP_FAILURE       -1

#define HTTP_METHOD_GET    "GET"
#define HTTP_METHOD_POST   "POST"

#define HTTPS_PORT         443

#define CA_CERT_FILE_NAME  "/cert/DigiCertHighAssuranceEVRootCA.cer"

#include "simplelink.h"

#include <stdio.h>
#include <string.h>

extern unsigned char request_buffer[BUFF_SIZE];

typedef struct {
	const char *auth_header;
	const char *contenttype_header;
	const char *host_header;
	const char *useragent_header;
} http_headers;

int http_connect(char *host);
int http_get(int sock_id, const char *url, http_headers *headers);
int http_post(int sock_id, const char *url, const char *data, http_headers *headers);
int http_request(int sock_id, const char *method, const char *url, const char *data, http_headers *headers);
int http_response(int sock_id);

void clear_request_buffer();

#endif /* HTTP_CLIENT_H_ */
