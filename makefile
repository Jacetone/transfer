all: integrate


integrate: integrate.cpp
	g++ -Wall -Wextra -pedantic -pthread integrate.cpp -o $@

clean:
		rm -rf integrate
