
BLD ?= bld

SVC1_DIR = $(BLD)/svc1
SVC1_BIN = $(SVC1_DIR)/svc1
SVC1_SRC = $(wildcard svc1/*.c)
SVC1_OBJ = $(subst svc1,$(SVC1_DIR),$(SVC1_SRC:.c=.o))

CPPFLAGS += -I include

CFLAGS += -g
CFLAGS += -Wall -Wextra

LDFLAGS += -lhiredis

.PHONY: all
all: $(SVC1_BIN)

$(SVC1_DIR):
	@mkdir -p $@

$(SVC1_BIN): $(SVC1_OBJ) | $(SVC1_DIR)
	$(LINK.c) $^ -o $@

$(SVC1_DIR)/%.o: svc1/%.c | $(SVC1_DIR)
	$(COMPILE.c) $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BLD)

PREFIX ?= /usr/local
.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -a $(SVC1_BIN) $(DESTDIR)$(PREFIX)/bin/svc1
