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

int add_event();
int add_events();

#endif /* KEEN_CLIENT_H_ */
