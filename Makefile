
include Makefile.config

include libmcapi/Makefile
include test/Makefile


all: $(TARGETS-y)

clean:
	$(RM) $(CLEAN) $(TARGETS-y)

.DEFAULT_GOAL := all
.PHONY: clean
.SUFFIXES: .c .o
