export CODENAME = libnss_dnsblock.so.2
export CC = gcc
export CFLAGS = -O2
CFLAGS += -std=gnu99 -fPIC -DPIC
CFLAGS += -Wall -Wwrite-strings -pedantic
CFLAGS += -DTORRENTKINO -DNSS -DIPV6
export LDFLAGS = -lpcre
OBJS=nss.o main.o

.PHONY: all clean install

all: $(CODENAME)

%.o : ../src/%.c ../src/%.h
	$(CC) $(CFLAGS) -c $<

$(CODENAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$(CODENAME) $(OBJS) -o $(CODENAME) $(LDFLAGS)

clean:
	rm -f *.o $(CODENAME)

install:
	strip $(CODENAME)
	mkdir -p $(DESTDIR)/lib/$(DEB_HOST_MULTIARCH)/
	cp $(CODENAME) $(DESTDIR)/lib/$(DEB_HOST_MULTIARCH)/
	mkdir -p $(DESTDIR)/usr/share/dnsblock/
	cp ../docs/dnsblock.example $(DESTDIR)/usr/share/dnsblock/
