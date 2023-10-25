# I am a comment, and I want to say that the variable CC will be # the compiler to use. 

CC=g++ 

# Hey!, I am comment number 2. I want to say that CFLAGS will be the # options I'll pass to the compiler. 

CFLAGS=  -g -c -Wall -std=c++14
EXENAME= Final

default: SemanticDescriptor.o SemanticDictionary.o main.o
	$(CC) -g SemanticDescriptor.o SemanticDictionary.o main.o -o $(EXENAME)

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 

SemanticDescriptor.o: SemanticDescriptor.cpp
	$(CC) $(CFLAGS) SemanticDescriptor.cpp 

SemanticDictionary.o: SemanticDictionary.cpp
	$(CC) $(CFLAGS) SemanticDictionary.cpp 

clean: 
	rm *.o $(EXENAME)

run:
	./$(EXENAME)
