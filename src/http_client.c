/*
 * http_client.c
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#include "http_client.h"

unsigned char request_buffer[BUFF_SIZE];

int get(const char *url) {
	int transfer_len = 0;
	int socket = 0;

	socket = make_connect("");
	ASSERT_ON_ERROR(socket);

	make_request(HTTP_METHOD_GET, url, 0);

	transfer_len = request(socket);
	ASSERT_ON_ERROR(transfer_len);

	return response(socket);
}

int post(const char *url, const char *data) {
	int transfer_len = 0;
	int socket = 0;

	socket = make_connect("");
	ASSERT_ON_ERROR(socket);

	make_request(HTTP_METHOD_POST, url, data);

	transfer_len = request(socket);
	ASSERT_ON_ERROR(transfer_len);

	return response(socket);
}

int make_connect(const char *host) {
	//SlSockAddrIn_t addr;
	//int addr_size;
	//unsigned char uc_method = SL_SO_SEC_METHOD_TLSV1_2;
	//unsigned int ui_ip, ui_cipher = SL_SEC_MASK_TLS_DHE_RSA_WITH_AES_256_CBC_SHA;
	//long error_code;
	//int socket;

	//error_code = sl_NetAppDnsGetHostByName(host, strlen((const char *)host), (unsigned long *)&ui_ip, SL_AF_INET);

	return 0;
}

void make_request(const char *method, const char *url, const char *data) {
	clear_request_buffer();

	strcpy((char *)request_buffer, method);
	strcat((char *)request_buffer, url);
	strcat((char *)request_buffer, " HTTP/1.1\r\n");
#ifdef SERVER_NAME
	strcat((char *)request_buffer, "Host: ");
	strcat((char *)request_buffer, SERVER_NAME);
	strcat((char *)request_buffer, "\r\n");
#endif
#ifdef AUTHORIZATION_HEADER
	strcat((char *)request_buffer, "Authorization: ");
	strcat((char *)request_buffer, AUTHORIZATION_HEADER);
	strcat((char *)request_buffer, "\r\n");
#endif
#ifdef USERAGENT_HEADER
	strcat((char *)request_buffer, "User-Agent: ");
	strcat((char *)request_buffer, USERAGENT_HEADER);
	strcat((char *)request_buffer, "\r\n");
#endif
#ifdef CONTENTTYPE_HEADER
	strcat((char *)request_buffer, "Content-Type: ");
	strcat((char *)request_buffer, CONTENTTYPE_HEADER);
	strcat((char *)request_buffer, "\r\n");
#endif
	if (data) {
		// TODO: sprintf and temp variable for Content-Length header
		// strcat((char *)request_buffer, "Content-Length: ");
		// strcat((char *)request_buffer, "\r\n");
		strcat((char *)request_buffer, "\r\n");
		strcat((char *)request_buffer, data);
	} else {
		strcat((char *)request_buffer, "Connection: close\r\n");
	}
	strcat((char *)request_buffer, "\r\n");
}

int request(int socket) {
	int transfer_len = 0;

	transfer_len = sl_Send(socket, request_buffer, strlen((const char *)request_buffer), 0);
	ASSERT_ON_ERROR(transfer_len);

	return HTTP_SUCCESS;
}

int response(socket) {
	int transfer_len = 0;

	clear_request_buffer();

	transfer_len = sl_Recv(socket, &request_buffer[0], MAX_BUFF_SIZE, 0);
	ASSERT_ON_ERROR(transfer_len);

	return HTTP_SUCCESS;
}

void print_request_buffer() {
#ifdef UART_PRINT
	UART_PRINT(request_buffer);
#endif
}

void clear_request_buffer() {
	memset(request_buffer, 0, sizeof(request_buffer));
}
