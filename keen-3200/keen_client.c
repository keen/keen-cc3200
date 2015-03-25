/*
 * keen_client.c
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#include "keen_client.h"

int add_event(const char *event_collection, const char *event_body) {
	int sock_id;
	int transfer_len;
	http_headers headers;

	headers.auth_header = 0;
	headers.contenttype_header = CONTENTTYPE_HEADER;
	headers.host_header = SERVER_NAME;
	headers.useragent_header = USERAGENT_HEADER;

	sock_id = http_connect(SERVER_NAME);

	if (sock_id < 0) {
		return sock_id;
	}

	transfer_len = http_post(sock_id, "", event_body, &headers);

	if (transfer_len < 0) {
		return transfer_len;
	}

	return HTTP_SUCCESS;
}

int add_events(const char *events) {
	int sock_id;
	int transfer_len;
	http_headers headers;

	headers.auth_header = 0;
	headers.contenttype_header = CONTENTTYPE_HEADER;
	headers.host_header = SERVER_NAME;
	headers.useragent_header = USERAGENT_HEADER;

	sock_id = http_connect(SERVER_NAME);

	if (sock_id < 0) {
		return sock_id;
	}

	transfer_len = http_post(sock_id, "", event_body, &headers);

	if (transfer_len < 0) {
		return transfer_len;
	}

	return HTTP_SUCCESS;
}
