BLD ?= bld
DST ?= dst
SRC ?= src

.PHONY: all
all:
	$(error 'all' is a dummy recipe; try 'ext')

$(BLD) $(DST) $(SRC):
	@mkdir -p $@

.PHONY: clean
clean:
	$(RM) -r $(BLD) $(DST) $(SRC)

include hiredis.mk

.PHONY: ext
ext: $(HIREDIS_LIB)
