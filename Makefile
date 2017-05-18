###########################################################################
##                        Makefile for ISOMORPH  			             ##
###########################################################################

CXX      = clang++ -std=c++11
CXXFLAGS = -g3 -Wall -Wextra
LDFLAGS  = -g3

Isomorph: Isomorph.o Graph.o Encryption.o Decryption.o Compressor.o
	${CXX} ${LDFLAGS} -o isomorph Isomorph.o \
						Graph.o Encryption.o \
						Decryption.o Compressor.o
testGraph: testGraph.o Graph.o
	${CXX} ${LDFLAGS} -o testGraph testGraph.o \
						Graph.o

Bruteforce: Bruteforce.o Graph.o termfuncs.o
	${CXX} ${LDFLAGS} -o bruteforce Bruteforce.o \
						Graph.o termfuncs.o

testCompressor:   Compressor.o testCompressor.o
		${CXX} ${LDFLAGS} -o testCompressor Compressor.o \
			testCompressor.o


Isomorph.o: 	  Isomorph.cpp Graph.h Graph.cpp Encryption.h Encryption.cpp \
						Decryption.h Decryption.cpp
testGraph.o:	  testGraph.cpp Graph.h Graph.cpp
Bruteforce.o:     Bruteforce.cpp Graph.h Graph.cpp termfuncs.h termfuncs.cpp
Graph.o:		Graph.h Graph.cpp
Encryption.o:     Encryption.h Encryption.cpp Graph.h Graph.cpp Compressor.h \
		  Compressor.cpp
Decryption.o:	  Decryption.h Decryption.cpp Graph.h Graph.cpp Compressor.h \
	          Compressor.cpp
Compressor.o:	  Compressor.h Compressor.cpp
termfuncs.o:      termfuncs.h termfuncs.cpp
testCompressor.o: testCompressor.cpp Compressor.h Compressor.cpp

clean:
	rm -rf *.o *.dSYM

provide:
	provide comp15 proj2ind Encryption.h Encryption.cpp Decryption.h \
				Decryption.cpp Graph.h Graph.cpp testGraph.cpp \
				termfuncs.h termfuncs.cpp Isomorph.cpp \
				Bruteforce.cpp \
				README Makefile
