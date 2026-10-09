all: app

app: main.o DynamicArray.o
	g++ main.o DynamicArray.o -o app

main.o: src/main.cpp include/DynamicArray.h
	g++ -c src/main.cpp -I include -o main.o

DynamicArray.o: src/DynamicArray.cpp include/DynamicArray.h
	g++ -c src/DynamicArray.cpp -I include -o DynamicArray.o

clean:
	rm -rf *.o app