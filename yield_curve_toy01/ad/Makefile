
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
TESTS=test/automatic_differentiation_test.h
TESTS+=test/dual_test.h
TESTS+=test/exp_test.h
TESTS+=test/expression_template_test.h
TESTS+=test/log_test.h
TESTS+=test/vector_dual_test.h

$(TARGET): $(HEADERS) $(SOURCES) $(TESTS)
	$(CXX) -o $@ $(INC_FLAGS) main.cpp

clean:
	rm -f $(TARGET) 

