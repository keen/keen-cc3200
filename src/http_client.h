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

#define HTTP_SUCCESS       0
#define HTTP_FAILURE       -1

#define HTTP_METHOD_GET      "GET"
#define HTTP_METHOD_POST     "POST"

#ifndef ASSERT_ON_ERROR
#define ASSERT_ON_ERROR(error_code)\
            {\
                 if(error_code < 0) \
                   {\
                        ;\
                        return error_code;\
                 }\
            }
#endif

#include "simplelink.h"

#include <string.h>

int get(const char *url);
int post(const char *url, const char *data);

int request(int socket);
int response(int socket);

int make_connect(const char *host);

void make_request(const char *method, const char *url, const char *data);

void clear_request_buffer();
void print_request_buffer();

#endif /* HTTP_CLIENT_H_ */
