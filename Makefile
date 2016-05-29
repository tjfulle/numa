IFLAG = -I/anaconda/include/python3.5m
CXXFLAGS = -O2 -fPIC $(IFLAG)
LFLAGS =  -L/anaconda/lib/ -lpython3.5m
CXX = g++
PYTHON = python3.5
PYTEST = py.test


build: numa.cpython-35m-darwin.so

.PHONY: test
test:
	$(PYTEST) test.py

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

numa.cpython-35m-darwin.so:
	$(RM) -r numa.cpp build
	$(PYTHON) setup.py build_ext --inplace
	$(RM) -r numa.cpp build

.PHONY: clean
clean:
	$(RM) numa.cpp
	$(RM) *.o *.so
	$(RM) -r build __pycache__
