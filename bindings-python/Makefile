default:
	g++ -Wall -pedantic -shared -fPIC -o bin/pyonix.so -I../src -I/usr/include/python2.7/ -lboost_python -lonix src/* 

install:
	sudo cp bin/pyonix.so /lib64/python2.7/site-packages/

clean:
	rm -rf bin
	mkdir bin
