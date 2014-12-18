SUBDIRS = dnsblock

.PHONY : all clean install docs sync debian ubuntu $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

install:
	for dir in $(SUBDIRS); do \
		$(MAKE) install -C $$dir; \
	done

docs:
	./bin/docs.sh

debian:
	./bin/debian.sh

ubuntu:
	./bin/debian.sh

indent:
	./bin/indent.sh

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
