CXXFLAGS=-Wall -pedantic -ggdb -O0 -std=c++11 -Iproduct
LDFLAGS=-lgtest -lgmock -lgmock_main -lpthread

#Server application
SERVERSOURCES=$(wildcard src/server/*.cpp)
SERVERHEADERS=$(wildcard src/server/*.h)
SERVEROBJECTS=$(SERVERSOURCES:.cpp=.o)
SERVERTARGET=Server

#Client application
CLIENTSOURCES=$(wildcard src/client/*.cpp)
CLIENTHEADERS=$(wildcard src/client/*.h)
CLIENTOBJECTS=$(CLIENTSOURCES:.cpp=.o)
CLIENTTARGET=Client
	
TEST=test_$(SERVERTARGET) test_$(CLIENTTARGET)

TEST_SOURCES=$(filter-out src/server/ServerMain.cpp, $(SERVERSOURCES)) \
	$(filter-out src/client/ClientMain.cpp, $(CLIENTSOURCES)) \
	$(wildcard test/*.cpp)

TEST_HEADERS=$(SERVERHEADERS) $(CLIENTHEADERS) \
			 $(wildcard test/*.h)

CXX=g++

.PHONY: clean

all: $(SERVERTARGET) $(CLIENTTARGET)

$(SERVERTARGET): $(SERVEROBJECTS) Makefile
	@$(CXX) $(CXXFLAGS) $(SERVERSOURCES) -o $@
	@echo $(SERVERTARGET) is made

$(CLIENTTARGET): $(CLIENTOBJECTS) Makefile
	@$(CXX) $(CXXFLAGS) $(CLIENTSOURCES) -o $@
	@echo $(CLIENTTARGET) is made


$(TEST): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	@$(CXX) $(CXXFLAGS) -Itest $(TEST_SOURCES) -o $@ $(LDFLAGS)

#for installing it on the RPI
installServer: $(SERVERTARGET)
	scp $(SERVERTARGET) root@10.0.0.42:/bin

instalClient: $(CLIENTTARGET)
	scp $(CLIENTTARGET) root@10.0.0.42:/bin



clean:
	@rm -f $(SERVEROBJECTS) 
	@rm -f $(SERVERTARGET) 
	@rm -f $(CLIENTOBJECTS)
	@rm -f $(CLIENTTARGET)
	@rm -f $(TEST)
	@echo  cleaned

test: $(TEST)
	@./$(TEST)
	@echo test ran
