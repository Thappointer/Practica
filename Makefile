FLAGS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

G++ = g++

program.exe: program.o riu.o ciutat.o inventari.o vaixell.o producte.o 
	$(G++) -o program.exe program.o riu.o ciutat.o inventari.o vaixell.o producte.o

program.o: program.cc
	$(G++) -c program.cc $(FLAGS)

riu.o: riu.cc
	$(G++) -c riu.cc $(FLAGS)

ciutat.o: ciutat.cc
	$(G++) -c ciutat.cc $(FLAGS)
	
inventari.o: inventari.cc
	$(G++) -c inventari.cc $(FLAGS)

vaixell.o: vaixell.cc
	$(G++) -c vaixell.cc $(FLAGS)

producte.o: producte.cc
	$(G++) -c producte.cc $(FLAGS)

clean:
	rm -f *.o
	rm -f *.exe