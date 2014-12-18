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

#include "config.h"
#include "pcre.h"

#define OVECCOUNT 30

int _nss_dnsblock_lookup(const char *hostname, UCHAR * address,
			 int *af, int *address_size);
int _nss_dnsblock_pcre_match(const char *subject, const char *pattern);
void _nss_dnsblock_syslog(const char *format, ...);
