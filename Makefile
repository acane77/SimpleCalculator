parser: build/lexer.o build/token.o build/main.o build/parser.o build/symbols.o build/intermediate.o
	g++ -o parser build/lexer.o build/token.o build/main.o build/parser.o build/symbols.o build/intermediate.o

build/lexer.o: lexer.hpp lexer.cpp
	g++ -c lexer.cpp -std=c++14 -o build/lexer.o -g

build/parser.o: parser.hpp parser.cpp
	g++ -c parser.cpp -std=c++14 -o build/parser.o -g

build/token.o: token.hpp token.cpp
	g++ -c token.cpp -std=c++14 -o build/token.o -g

build/symbols.o: symbols.hpp symbols.cpp
	g++ -c symbols.cpp -std=c++14 -o build/symbols.o -g

build/intermediate.o: intermediate.hpp intermediate.cpp
	g++ -c intermediate.cpp -std=c++14 -o build/intermediate.o -g

build/main.o: main.cpp
	g++ -c main.cpp -std=c++14 -o build/main.o -g

clean:
	rm *.exe build/*.o -f