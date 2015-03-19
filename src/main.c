/*
Copyright 2014 Aiko Barz

This file is part of dnsblock.

dnsblock is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

dnsblock is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with dnsblock.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <pcre.h>

#include "main.h"

int _nss_dnsblock_lookup(const char *hostname, UCHAR * address,
			 int *af, int *address_size)
{
	int result = 0;
	char filename[256];

	/* 1st: Load global file */
	result = _nss_dnsblock_load("/etc/dnsblock", hostname, address,
				    af, address_size);

	if (result == 1) {
		return 1;
	}

	/* 2nd: Load local file */
	if (getenv("HOME") == NULL) {
		return 0;
	}

	snprintf(filename, 256, "%s/.dnsblock", getenv("HOME"));

	result = _nss_dnsblock_load(filename, hostname, address,
				    af, address_size);

	if (result == 1) {
		return 1;
	}

	return 0;
}

int _nss_dnsblock_load(const char *filename, const char *hostname,
		       UCHAR * address, int *af, int *address_size)
{
	FILE *fp = NULL;
	char str[BUF_SIZE];
	char regex[256];
	char target[256];
	int result = 0, match = 0, is_ip = 0;
	UCHAR buf[sizeof(struct in6_addr)];

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return 0;
	}

	while (fgets(str, BUF_SIZE, fp) != NULL) {
		/* Too big fo regex/target */
		if (strlen(str) >= BUF_SIZE) {
			continue;
		}

		switch (str[0]) {
		case '#':
		case ' ':
		case '\t':
		case '\n':
		case '\0':
			continue;
			break;
		}

		/* Parse /etc/dnsblock */
		sscanf(str, "%255s%*[ \t]%255s", target, regex);

		/* Match requested hostname against my regular expressions */
		match = _nss_dnsblock_pcre_match(hostname, regex);

		/* No match: Go on */
		if (match == 0) {
			continue;
		}

		/* Whitelist: Passthrough */
		if (*target == '-') {
			result = 1;
			break;
		}

		/* Try to convert the IP address to a binary representation. Start with
		   IPv6. Try IPv4 later. */
		is_ip = inet_pton(AF_INET6, target, buf);
		if (is_ip == 1) {
			*af = AF_INET6;
		} else {
			is_ip = inet_pton(AF_INET, target, buf);
			if (is_ip == 1) {
				*af = AF_INET;
			}
		}

		if (is_ip == 1) {
			*address_size = (*af == AF_INET6) ? 16 : 4;
			memcpy(address, buf, *address_size);
			result = 2;
			break;
		} else {
			_nss_dnsblock_syslog("ERROR: Parsing %s failed", target);
			continue;
		}
	}
	fclose(fp);

	/* Some debugging */
	switch(result) {
	case 0:
		_nss_dnsblock_syslog("PASS: %s", hostname);
		break;
	case 1:
		_nss_dnsblock_syslog("PASSTHROUGH: %s", hostname);
		break;
	default:
		_nss_dnsblock_syslog("DENY: %s -> %s", hostname, target);
	}

	/* Return 0 or 1 only */
	return(result <= 1) ? 0 : 1;
}

int _nss_dnsblock_pcre_match(const char *subject, const char *pattern)
{
	pcre *re = NULL;
	const char *error = NULL;
	int erroffset = 0;
	int ovector[OVECCOUNT];
	int size = 0;
	int rc = 0;

	size = strlen(subject);

	re = pcre_compile(pattern,	/* the pattern */
			  0,	/* default options */
			  &error,	/* for error message */
			  &erroffset,	/* for error offset */
			  NULL);	/* use default character tables */

	if (re == NULL) {
		_nss_dnsblock_syslog
		    ("ERROR: PCRE compilation failed at offset %d: %s\n",
		     erroffset, error);
		return 0;
	}

	rc = pcre_exec(re, NULL, subject, size, 0, 0, ovector, OVECCOUNT);

	if (rc < 0) {
		switch (rc) {
		case PCRE_ERROR_NOMATCH:
			break;
		default:
			/* Matching error */
			break;
		}
		pcre_free(re);
		return 0;
	}

	pcre_free(re);
	return 1;
}

void _nss_dnsblock_syslog(const char *format, ...)
{
	char log_buf[BUF_SIZE];
	char va_buf[BUF_SIZE];
	va_list vlist;

	va_start(vlist, format);
	vsnprintf(va_buf, BUF_SIZE, format, vlist);
	va_end(vlist);

	strncpy(log_buf, va_buf, BUF_OFF1);

	openlog(LOG_NAME, LOG_PID | LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "%s", log_buf);
	closelog();
}

int _nss_dnsblock_valid_hostname(const char *hostname, int hostsize)
{
	int i = 0;

	for (i = 0; i < hostsize; i++) {
		if (hostname[i] >= '0' && hostname[i] <= '9') {
			continue;
		} else if (hostname[i] >= 'A' && hostname[i] <= 'Z') {
			continue;
		} else if (hostname[i] >= 'a' && hostname[i] <= 'z') {
			continue;
		} else if (hostname[i] == '-') {
			continue;
		} else if (hostname[i] == '_') {
			continue;
		} else if (hostname[i] == '.') {
			continue;
		} else {
			return 0;
		}
	}

	return 1;
}
