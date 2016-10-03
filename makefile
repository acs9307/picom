picom:
	gcc -c i2c.c rpi.c
	ar -rc libpicom.a *.o
	rm *.o
	
install:
	mkdir -p /usr/local/include/picom
	rm -f /usr/local/include/picom/*.h
	cp *.h /usr/local/include/picom
	mv libpicom.a /usr/local/lib
	
all:
	make picom
	make install
