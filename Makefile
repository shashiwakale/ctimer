SRC:=$(wildcard ./src/*.cpp)
INC:=$(wildcard ./include)
COMPILE:=g++
LIBS:= rt
BINDIR:=./bin
BIN:=$(BINDIR)/CTimer

CTimer:
	$ test -d $(BINDIR) || mkdir $(BINDIR)
	$(COMPILE) $(SRC) -I$(INC) -l$(LIBS) -o$(BIN)

clean:
	rm -rf $(BINDIR)
