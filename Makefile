all: app

app: src/main.cpp include/DynamicArray.h
	g++ -std=c++17 -Wall -Wextra src/main.cpp -I include -o app

clean:
	rm -f app