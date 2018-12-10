CXXFLAGS=-Wall -pedantic -ggdb -O0 -std=c++11 -Iproduct
LDFLAGS=-lgtest -lgmock -lgmock_main -lpthread

CONSOLESELECTORSOURCES=$(wildcard AllNeeded/*.cpp) $(wildcard SystemController/*.cpp) $(Comminucation.cpp)
CONSOLESELECTORHEADERS=$(wildcard AllNeeded/*.h) $(wildcard SystemController/*.h)
CONSOLESELECTOROBJECTS=$(SOURCES:.cpp=.o)
CONSOLESELECTORTARGET=ConsoleSelector

REMOTECONTROLLERSOURCES=$(wildcard AllNeeded/*.cpp) $(wildcard RemoteController/*.cpp) $(Comminucation.cpp)
REMOTECONTROLLERHEADERS=$(wildcard AllNeeded/*.h) $(wildcard RemoteController/*.h)
REMOTECONTROLLEROBJECTS=$(SOURCES:.cpp=.o)
REMOTECONTROLLERTARGET=RemoteApplication
	
TEST=test_$(CONSOLESELECTORTARGET) test_$(REMOTECONTROLLERTARGET)

TEST_SOURCES=$(filter-out RemoteController/RemoteMain.cpp, $(REMOTECONTROLLERSOURCES)) \
	$(filter-out SystemController/SystemMain.cpp, $(REMOTECONTROLLERSOURCES)) \
	$(wildcard test/*.cpp)

TEST_HEADERS=$(CONSOLESELECTORHEADERS) $(REMOTECONTROLLERHEADERS) \
			 $(wildcard test/*.h)

CXX=g++

.PHONY: all clean test

all: $(REMOTECONTROLLERTARGET) $(CONSOLESELECTORTARGET)

$(REMOTECONTROLLERTARGET): $(REMOTECONTROLLEROBJECTS) Makefile
	@$(CXX) $(CXXFLAGS) $(REMOTECONTROLLERSOURCES) -o $@
	@echo $(REMOTECONTROLLERTARGET) is made

$(CONSOLESELECTORTARGET): $(CONSOLESELECTOROBJECTS) Makefile
	@$(CXX) $(CXXFLAGS) $(CONSOLESELECTORSOURCES) -o $@
	@echo $(CONSOLESELECTORTARGET) is made


$(TEST): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	@$(CXX) $(CXXFLAGS) -Itest $(TEST_SOURCES) -o $@ $(LDFLAGS)

installConsoleSelector: $(CONSOLESELECTORTARGET)
	scp $(CONSOLESELECTORTARGET) root@10.0.0.42:/bin

installRemoteController: $(REMOTECONTROLLERTARGET)
	scp $(REMOTECONTROLLERTARGET) root@10.0.0.42:/bin



clean:
	@rm -f $(CONSOLESELECTOROBJECTS) 
	@rm -f $(CONSOLESELECTORTARGET) 
	@rm -f $(REMOTECONTROLLEROBJECTS)
	@rm -f $(REMOTECONTROLLERTARGET)
	@rm -f $(TEST)
	@echo  cleaned

test: $(TEST)
	@./$(TEST)
	@echo test ran
