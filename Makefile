totp: main.o base32.o totp.o
	gcc main.o base32.o totp.o -o totp -lcrypto

main.o: main.c base32.h totp.h
	gcc -c main.c

base32.o: base32.c base32.h
	gcc -c base32.c

totp.o: totp.c totp.h
	gcc -c totp.c

clean:
	rm -f *.o totp
