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
	int sock_id = 0;

#ifdef SERVER_NAME
	sock_id = make_connect(SERVER_NAME);
#else
	sock_id = make_connect("");
#endif
	ASSERT_ON_ERROR(sock_id);

	make_request(HTTP_METHOD_GET, url, 0);

	transfer_len = request(sock_id);
	ASSERT_ON_ERROR(transfer_len);

	return response(sock_id);
}

int post(const char *url, const char *data) {
	int transfer_len = 0;
	int sock_id = 0;

#ifdef SERVER_NAME
	sock_id = make_connect(SERVER_NAME);
#else
	sock_id = make_connect("");
#endif
	ASSERT_ON_ERROR(sock_id);

	make_request(HTTP_METHOD_POST, url, data);

	transfer_len = request(sock_id);
	ASSERT_ON_ERROR(transfer_len);

	return response(sock_id);
}

int make_connect(char *host) {

	SlSockAddrIn_t addr;
	int addr_size;
	unsigned char uc_method = SL_SO_SEC_METHOD_TLSV1_2;
	unsigned int ui_ip, ui_cipher = SL_SEC_MASK_TLS_DHE_RSA_WITH_AES_256_CBC_SHA;
	long error_code;
	int sock_id;

	error_code = sl_NetAppDnsGetHostByName((signed char *)host, strlen((const char *)host), (unsigned long *)&ui_ip, SL_AF_INET);
	ASSERT_ON_ERROR(error_code);

	addr.sin_family = SL_AF_INET;
	addr.sin_port = sl_Htons(HTTPS_PORT);
	addr.sin_addr.s_addr = sl_Htonl(ui_ip);
	addr_size = sizeof(SlSockAddrIn_t);

	sock_id = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, SL_SEC_SOCKET);

	ASSERT_ON_ERROR(error_code);
	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECMETHOD, &uc_method, sizeof(uc_method));
	ASSERT_ON_ERROR(error_code);

	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &ui_cipher, sizeof(ui_cipher));
	ASSERT_ON_ERROR(error_code);

	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECURE_FILES_CA_FILE_NAME, CA_CERT_FILE_NAME, strlen(CA_CERT_FILE_NAME));
	ASSERT_ON_ERROR(error_code);

	error_code = sl_Connect(sock_id, (SlSockAddr_t *)&addr, addr_size);

	return sock_id;
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

int request(int sock_id) {
	int transfer_len = 0;

	transfer_len = sl_Send(sock_id, request_buffer, strlen((const char *)request_buffer), 0);
	ASSERT_ON_ERROR(transfer_len);

	return HTTP_SUCCESS;
}

int response(sock_id) {
	int transfer_len = 0;

	clear_request_buffer();

	transfer_len = sl_Recv(sock_id, &request_buffer[0], MAX_BUFF_SIZE, 0);
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
