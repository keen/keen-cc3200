/*
 * keen_client.c
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#include "keen_client.h"

char resource_buffer[URI_SIZE];

int add_event(const char *event_collection, const char *event_body) {
	int sock_id;
	int transfer_len;
	http_headers headers;

	headers.contenttype_header = CONTENTTYPE_HEADER;
	headers.host_header = SERVER_NAME;
	headers.useragent_header = USERAGENT_HEADER;

	if (write_key) {
		headers.auth_header = write_key;
	} else {
		return HTTP_FAILURE;
	}

	sock_id = http_connect(SERVER_NAME);

	if (sock_id < 0) {
		return sock_id;
	}

	build_resource(event_collection);

	transfer_len = http_post(sock_id, resource_buffer, event_body, &headers);

	if (transfer_len < 0) {
		return transfer_len;
	}

	return HTTP_SUCCESS;
}

int add_events(const char *events) {
	int sock_id;
	int transfer_len;
	http_headers headers;

	headers.contenttype_header = CONTENTTYPE_HEADER;
	headers.host_header = SERVER_NAME;
	headers.useragent_header = USERAGENT_HEADER;

	if (write_key) {
		headers.auth_header = write_key;
	} else {
		return HTTP_FAILURE;
	}

	sock_id = http_connect(SERVER_NAME);

	if (sock_id < 0) {
		return sock_id;
	}

	build_resource(0);

	transfer_len = http_post(sock_id, resource_buffer, events, &headers);

	if (transfer_len < 0) {
		return transfer_len;
	}

	return HTTP_SUCCESS;
}

void build_resource(const char *event_collection) {
	memset(resource_buffer, 0, sizeof(resource_buffer));

	strncpy((char *)resource_buffer, "https://api.keen.io/", MAX_URI_SIZE);
	strncat((char *)resource_buffer, api_version, MAX_URI_SIZE - strlen((const char *)resource_buffer));
	strncat((char *)resource_buffer, "/projects/", MAX_URI_SIZE - strlen((const char *)resource_buffer));
	strncat((char *)resource_buffer, project_id, MAX_URI_SIZE - strlen((const char *)resource_buffer));
	strncat((char *)resource_buffer, "/events", MAX_URI_SIZE - strlen((const char *)resource_buffer));

	if (event_collection) {
		strncat((char *)resource_buffer, "/", MAX_URI_SIZE - strlen((const char *)resource_buffer));
		strncat((char *)resource_buffer, event_collection, MAX_URI_SIZE - strlen((const char *)resource_buffer));
	}
}
