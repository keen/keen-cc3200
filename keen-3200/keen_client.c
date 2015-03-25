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

	transfer_len = http_post(sock_id, "", events, &headers);

	if (transfer_len < 0) {
		return transfer_len;
	}

	return HTTP_SUCCESS;
}

void build_resource(const char *event_collection) {
	memset(resource_buffer, 0, sizeof(resource_buffer));

	strcpy((char *)resource_buffer, "https://api.keen.io/");
	strcat((char *)resource_buffer, api_version);
	strcat((char *)resource_buffer, "/projects/");
	strcat((char *)resource_buffer, project_id);
	strcat((char *)resource_buffer, "/events");

	if (event_collection) {
		strcat((char *)resource_buffer, "/");
		strcat((char *)resource_buffer, event_collection);
	}
}
