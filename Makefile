default:
	mkdir -p bin
	g++ -fPIC -Wall -pedantic src/*.cpp -shared -o bin/libOnix.so
	g++ -Wall -pedantic -I src/ -L bin -l Onix -l cppunit tests/test.cpp -o tests/test.bin
	#./tests/test.bin 
	g++ -Wall -pedantic -I src/ -L bin/ -l Onix examples/helloWorld.cpp -o examples/helloWorld.bin
	g++ -Wall -pedantic -I src/ -L bin/ -l Onix examples/rotations.cpp -o examples/rotations.bin
	g++ -Wall -pedantic -I src/ -L bin/ -l Onix examples/drawing.cpp -o examples/drawing.bin

clean:
	rm -rf bin
	rm -rf src/*.gch
	rm -rf src/*.bin
	rm -rf examples/*.bin
