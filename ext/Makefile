BLD ?= bld
DST ?= dst
SRC ?= src

all:
	$(error 'all' is a dummy recipe; try 'ext')

$(BLD) $(DST) $(SRC):
	@mkdir -p $@

clean:
	$(RM) -r $(BLD) $(DST) $(SRC)

include hiredis.mk

ext: $(HIREDIS_LIB)
