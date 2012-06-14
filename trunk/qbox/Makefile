CXX32 = g++


INCLUDE :=

SRC_COMM = IServer.cpp\
		   msgBase.cpp\
		   msgHandler.cpp\
		   status.cpp\
		   commModel.cpp\
		   entSetting.cpp\
		   main.cpp 
			

                      
OBJ_COMM = $(SRC_COMM:.cpp=.o)
OBJ_COMM_R = $(SRC_COMM:.cpp=.ro)


.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX32) -c -o $@ $<

PROGRAM = qbox
all: qbox 
qbox:$(OBJ_COMM) 
	$(CXX32)  -o $@ $(OBJ_COMM) $(INCLUDE) 

depend:
	mkdep $(INCLUDE) $(SRC_COMM) $(CXXFLAG)

clean: 
	rm -f *.o
	rm -f *.ro
	rm -f $(PROGRAM)
