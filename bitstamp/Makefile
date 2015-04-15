SUBDIRS += api
SUBDIRS += rexjson
SUBDIRS += bitstampcmd
SUBDIRS += bitstampapy

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
