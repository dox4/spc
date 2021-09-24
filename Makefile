CXXFLAGS=-std=c++20 -g -Wall
CXX=clang++


LIBS=$(patsubst %.cc, %.o, $(wildcard *.cc))

TEST_DIR=test
TESTS=$(patsubst %.cc, %.out, $(wildcard $(TEST_DIR)/*.cc))

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

%.out: %.cc $(LIBS) test/test.h Makefile
	$(CXX) $(CXXFLAGS) $< $(LIBS) -o $@

.SECONDARY:
test: $(TESTS)
	@for t in $^; do echo processing $$t; ./$$t; done;

clean:
	@rm -f $(TEST_DIR)/*.out
	@rm -f *.o
.PHONY: test clean


