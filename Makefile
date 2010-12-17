
include Makefile.config

include libmcapi/Makefile
include test/Makefile


all: $(TARGETS-y)

clean: $(CLEANDEPS)
	$(RM) -r $(CLEAN) $(TARGETS-y)

.DEFAULT_GOAL := all
.PHONY: clean
.SUFFIXES: .c .o
