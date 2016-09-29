picom:
	gcc -c i2c.c rpi.c
	ar -rc libpicom.a *.o
	rm *.o
	
install:
	mkdir -p /usr/local/picom
	rm -f /usr/local/picom/*.h
	cp *.h /usr/local/picom
	mv libpicom.a /usr/local/lib
	
all:
	make picom
	make install
