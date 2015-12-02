#
#	This is the LabAssignment4 (Prime Threads)
#	

Labassignment4: Labassignment4.o
	g++ Labassignment4.o -pthread -o Labassignment4

Labassignment4.o: Labassignment4.cpp
	g++ -c -fpermissive Labassignment4.cpp

clean:
	rm Labassignment4.o Labassignment4
