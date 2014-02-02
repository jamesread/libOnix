default:
	mkdir -p bin
	g++ src/* -o bin/libOnix.bin -Wall -pedantic -g 
	./bin/libOnix.bin

clean:
	rm -rf bin
