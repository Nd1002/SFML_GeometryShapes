CXX = g++ 
CXX_FLAGS := -Wall -Wextra 

LIBS := -lsfml-graphics -lsfml-window -lsfml-system

all:  main 

main: main.o MainWindow.o 
	  $(CXX) $(CXX_FLAGS) main.o MainWindow.o -o applicate $(LIBS)
	  ./applicate

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp 

MainWindow.o: MainWindow.h MainWindow.cpp
	$(CXX) $(CXX_FLAGS) -c MainWindow.h MainWindow.cpp

clean: 
	rm -rf *.o *.gch ./applicate

