PROJ = core
OBJECT = coag.o io.o conden.o evap.o frag.o sf.o main.o
CXXFLAGS = -g -Wall -pg

all: $(PROJ) 
$(PROJ) : $(OBJECT)
	$(CXX) -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) $(PROJ)
depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
