NAME=Soft

$(NAME): main.o robot.o socket.o ultrasonic.o
	g++ main.o robot.o socket.o ultrasonic.o -o $(NAME) -lwiringPi -lpthread

main.o: main.cpp
	g++ -c main.cpp -std=c++0x

robot.o: robot.cpp robot.h
	g++ -c robot.cpp

socket.o: socket.cpp socket.h
	g++ -c socket.cpp

ultrasonic.o: ultrasonic.cpp ultrasonic.h
	g++ -c ultrasonic.cpp -std=c++11
 	
clean:
	rm -rf *.cpp~
	rm -rf *.h~
	rm -rf *.o
	rm -rf $(NAME)
