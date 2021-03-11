CC = gcc
CPP = g++
CFLAGS = -I . -std=c++17 -O3 -Wall -Wextra -Wpedantic -O3 -std=c++2a -pthread
OBJ =  build/drivetrain.o build/test.o build/Wheel.o
DEPS = 

build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

swerve_cpp_test: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f  drivetrain.o test.o Wheel.o
