
#LIB=
INC_FLAGS=-IC:/Users/admin/Documents/Programming/cpp/libraries/boost_1_40_0
TARGET=ad.exe

SOURCES=main.cpp
HEADERS=dual.h
HEADERS+=function.h
HEADERS+=functor.h
HEADERS+=helper_macro.h
HEADERS+=type_traits.h
HEADERS+=vector.h
HEADERS+=vector_expression.h

$(TARGET): $(HEADERS) $(SOURCES)
	$(CXX) -o $@ $(INC_FLAGS) main.cpp

