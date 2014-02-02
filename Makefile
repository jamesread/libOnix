default:
	mkdir -p bin
	g++ -fPIC -Wall -pedantic src/*.cpp -shared -o bin/libOnix.so
	g++ -Wall -pedantic -I src -Lbin/ -l Onix examples/helloWorld.cpp -o examples/helloWorld.bin
	g++ -Wall -pedantic -I src -Lbin/ -l Onix examples/rotations.cpp -o examples/rotations.bin

clean:
	rm -rf bin
