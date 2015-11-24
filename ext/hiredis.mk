HIREDIS_VER = 0.13.3
HIREDIS_SRC = $(SRC)/hiredis
HIREDIS_LIB = $(DST)/usr/local/lib/libhiredis.so
HIREDIS_URL = https://github.com/redis/hiredis.git

$(HIREDIS_SRC): $(SRC)
	test -d $@ || git clone $(HIREDIS_URL) $@
	cd $@ && git fetch && git checkout --force v$(HIREDIS_VER)

$(HIREDIS_LIB): $(HIREDIS_SRC) | $(DST)
	cd $(HIREDIS_SRC) && make
	cd $(HIREDIS_SRC) && DESTDIR=../../$(DST) make install
