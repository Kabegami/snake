SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++ -std=c++17
EXECNAME = snake
OPTIM_FLAG = -O2
EIGEN_PATH =
SFML_PATH = 

$(EXECNAME): gameObjects.o gameEngine.o game.o
	$(CC) gameObjects.o gameEngine.o game.o -o snake $(OPTIM_FLAG) $(SFML_FLAGS) $(SFML_PATH)
	rm -f *.o

game.o:
	$(CC) game.cpp -c $(OPTIM_FLAG) $(SFML_FLAGS) $(SFML_PATH)

gameObjects.o:
	$(CC) gameObjects.cpp -c $(OPTIM_FLAG) $(SFML_FLAGS) $(SFML_PATH)

gameEngine.o:
	$(CC) gameEngine.cpp -c $(OPTIM_FLAG) $(SFML_FLAGS) $(SFML_PATH)

clean:
	rm -f *.o
	rm -f $(EXECNAME)
