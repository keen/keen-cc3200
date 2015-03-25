/*
 * keen_client.h
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#ifndef KEEN_CLIENT_H_
#define KEEN_CLIENT_H_

#define	SERVER_NAME        "api.keen.io"
#define	CONTENTTYPE_HEADER "application/json"
#define	USERAGENT_HEADER   "CC3200/0.1a"

#include "http_client.h"

int add_event(const char *event_collection, const char *event_body);
int add_events(const char *events);

#endif /* KEEN_CLIENT_H_ */
