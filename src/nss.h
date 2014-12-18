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

#ifndef NSS_H
#define NSS_H

#include "config.h"
#include "main.h"

#define _public_ __attribute__( ( visibility( "default")))
#define _hidden_ __attribute__( ( visibility( "hidden")))

enum nss_status _nss_dnsblock_gethostbyname_r(const char *hostname,
					      struct hostent *host,
					      char *buffer, size_t buflen,
					      int *errnop,
					      int *h_errnop) _public_;

enum nss_status _nss_dnsblock_gethostbyname2_r(const char *hostname, int af,
					       struct hostent *host,
					       char *buffer, size_t buflen,
					       int *errnop,
					       int *h_errnop) _public_;

enum nss_status _nss_dnsblock_gethostbyname3_r(const char *hostname, int af,
					       struct hostent *host,
					       char *buffer, size_t buflen,
					       int *errnop, int *h_errnop,
					       int32_t * ttlp,
					       char **canonp) _public_;

enum nss_status _nss_dnsblock_gethostbyname4_r(const char *hostname,
					       struct gaih_addrtuple **pat,
					       char *buffer, size_t buflen,
					       int *errnop, int *h_errnop,
					       int32_t * ttlp) _public_;

enum nss_status _nss_dnsblock_hostent(const char *hostname, int hostsize,
				      int af, struct hostent *host,
				      char *buffer, size_t buflen, int *errnop,
				      int *h_errnop, int32_t * ttlp,
				      char **canonp);

enum nss_status _nss_dnsblock_gaih_tuple(const char *hostname, int hostsize, struct
					 gaih_addrtuple **pat, char *buffer,
					 size_t buflen, int *errnop,
					 int *h_errnop, int32_t * ttlp);

int _nss_dnsblock_valid_hostname(const char *hostname, int hostsize);

#endif				/* NSS_H */
