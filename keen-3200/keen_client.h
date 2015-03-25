/*
 * keen_client.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#ifndef KEEN_CLIENT_H_
#define KEEN_CLIENT_H_

#define MAX_URI_SIZE 128
#define URI_SIZE MAX_URI_SIZE + 1

#define	SERVER_NAME        "api.keen.io"
#define	CONTENTTYPE_HEADER "application/json"
#define	USERAGENT_HEADER   "CC3200/0.1a"

#include "http_client.h"

extern char *api_version;
extern char *project_id;
extern char *write_key;
extern char *read_key;
extern char *master_key;

char resource_buffer[URI_SIZE];

int add_event(const char *event_collection, const char *event_body);
int add_events(const char *events);

void build_resource(const char *event_collection);

#endif /* KEEN_CLIENT_H_ */
