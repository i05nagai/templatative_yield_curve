
#LIB=
#CFLAGS=-Wall
INC_FLAGS=-IC:/Users/admin/Documents/Programming/cpp/libraries/boost_1_40_0
INC_FLAGS+=-I.
TEST_TARGET=main.exe

SOURCES=yc/date/Date.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEST_SOURCES=yc_test/main.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)
HEADERS=yc/date/Date.h
HEADERS+=yc/date/business_day_convention.h
HEADERS+=yc/date/business_center.h
TEST_HEADERS=yc_test/date/DateTest.h
TEST_HEADERS+=yc_test/date/jptk_calendar_test.h

#suffix rule
.SUFFIXES: .cpp .o
.cpp.o:	
	$(CXX) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

#make rule
$(TEST_TARGET): $(HEADERS) $(SOURCES) $(TEST_SOURCES) $(TEST_HEADERS) $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) -o $@ $(INC_FLAGS) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)

clean:
	rm -f $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

