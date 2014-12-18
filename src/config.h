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

#ifndef CONFIG_H
#define CONFIG_H

#define BUF_SIZE 1024
#define BUF_OFF1 1023

#define TRUE 1
#define FALSE 0

#define LOG_NAME "dnsblock"

typedef unsigned long int ULONG;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef long int LONG;

#ifdef IPV6
#define IP_SIZE_LIST 128
#define IP_SIZE_META_PAIR 18
#define IP_SIZE_META_PAIR8 144
#define IP_SIZE_META_TRIPLE 38
#define IP_SIZE_META_TRIPLE8 304
#define IP_ADDRLEN INET6_ADDRSTRLEN
typedef struct sockaddr_in6 IP;
typedef struct in6_addr IN_ADDR;
#elif IPV4
#define IP_SIZE_LIST 32
#define IP_SIZE_META_PAIR 6
#define IP_SIZE_META_PAIR8 48
#define IP_SIZE_META_TRIPLE 26
#define IP_SIZE_META_TRIPLE8 208
#define IP_ADDRLEN INET_ADDRSTRLEN
typedef struct sockaddr_in IP;
typedef struct in_addr IN_ADDR;
#endif

#endif				/* CONFIG_H */
