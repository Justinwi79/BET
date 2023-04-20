proj4_driver: proj4_driver.o
	g++ -o proj4_driver -std=c++11 proj4_driver.o 
proj4_driver.o: proj4_driver.cpp
	g++ -c -std=c++11 proj4_driver.cpp

clean:
	-rm *.o
	-rm *.h.gch