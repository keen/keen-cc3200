/*
 * http_client.c
 *
 *  Created on: Feb 24, 2015
 *      Author: Doug Cox
 */

#include "http_client.h"

unsigned char request_buffer[BUFF_SIZE];

int http_get(int sock_id, const char *url, http_headers *headers) {
	int transfer_len = 0;

	transfer_len = http_request(sock_id, HTTP_METHOD_GET, url, 0, headers);

	if (transfer_len < 0) {
		return transfer_len;
	} else {
		return HTTP_SUCCESS;
	}
}

int http_post(int sock_id, const char *url, const char *data, http_headers *headers) {
	int transfer_len = 0;

	transfer_len = http_request(sock_id, HTTP_METHOD_POST, url, data, headers);

	if (transfer_len < 0) {
		return transfer_len;
	} else {
		return HTTP_SUCCESS;
	}
}

int http_connect(char *host) {

	SlSockAddrIn_t addr;
	int addr_size;
	unsigned char uc_method = SL_SO_SEC_METHOD_TLSV1_2;
	unsigned int ui_ip, ui_cipher = SL_SEC_MASK_TLS_DHE_RSA_WITH_AES_256_CBC_SHA;
	long error_code;
	int sock_id;

	error_code = sl_NetAppDnsGetHostByName((signed char *)host, strlen((const char *)host), (unsigned long *)&ui_ip, SL_AF_INET);

	if (error_code < 0) {
		return error_code;
	}

	addr.sin_family = SL_AF_INET;
	addr.sin_port = sl_Htons(HTTPS_PORT);
	addr.sin_addr.s_addr = sl_Htonl(ui_ip);
	addr_size = sizeof(SlSockAddrIn_t);

	sock_id = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, SL_SEC_SOCKET);

	if (error_code < 0) {
		return error_code;
	}

	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECMETHOD, &uc_method, sizeof(uc_method));

	if (error_code < 0) {
		return error_code;
	}

	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &ui_cipher, sizeof(ui_cipher));

	if (error_code < 0) {
		return error_code;
	}

	error_code = sl_SetSockOpt(sock_id, SL_SOL_SOCKET, SL_SO_SECURE_FILES_CA_FILE_NAME, CA_CERT_FILE_NAME, strlen(CA_CERT_FILE_NAME));

	if (error_code < 0) {
		return error_code;
	}

	error_code = sl_Connect(sock_id, (SlSockAddr_t *)&addr, addr_size);

	if (error_code < 0) {
		return error_code;
	}

	return sock_id;
}

int http_request(int sock_id, const char *method, const char *url, const char *data, http_headers *headers) {
	int transfer_len = 0;

	clear_request_buffer();

	strncpy((char *)request_buffer, method, MAX_BUFF_SIZE);
	strncat((char *)request_buffer, " ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	strncat((char *)request_buffer, url, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	strncat((char *)request_buffer, " HTTP/1.1\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));

	if (headers->host_header) {
		strncat((char *)request_buffer, "Host: ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, headers->host_header, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	}

	if (headers->auth_header) {
		strncat((char *)request_buffer, "Authorization: ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, headers->auth_header, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	}

	if (headers->useragent_header) {
		strncat((char *)request_buffer, "User-Agent: ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, headers->useragent_header, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	}

	if (headers->contenttype_header) {
		strncat((char *)request_buffer, "Content-Type: ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, headers->contenttype_header, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	}

	if (data) {
		char content_length[BUFF_DIGITS];
		snprintf(content_length, BUFF_DIGITS, "%d", strlen((const char *)data));
		strncat((char *)request_buffer, "Content-Length: ", MAX_BUFF_SIZE - strlen((const char *)request_buffer));

		strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
		strncat((char *)request_buffer, data, MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	} else {
		strncat((char *)request_buffer, "Connection: close\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));
	}
	strncat((char *)request_buffer, "\r\n", MAX_BUFF_SIZE - strlen((const char *)request_buffer));

	transfer_len = sl_Send(sock_id, request_buffer, strlen((const char *)request_buffer), 0);

	if (transfer_len < 0) {
		return transfer_len;
	} else {
		return HTTP_SUCCESS;
	}
}

int http_response(sock_id) {
	int transfer_len = 0;

	clear_request_buffer();

	transfer_len = sl_Recv(sock_id, &request_buffer[0], MAX_BUFF_SIZE, 0);

	if (transfer_len < 0) {
		return transfer_len;
	} else {
		return HTTP_SUCCESS;
	}
}

void clear_request_buffer() {
	memset(request_buffer, 0, sizeof(request_buffer));
}
