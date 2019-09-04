# used so that you don't have to write the long command each time
# X 90 degrees is a plus
# g++ is gnu c++ compiler
# should only be used with one cpp file

CXX      = g++
CXX_FILE = $(wildcard *.cpp)
# target gets substring
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
# target defaults to a.out, not a meaningful name
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0
# -g includes debug info in executable (for gdb usage). -O3 removes debug (production, more speed)
# -std=c++11 makes the c++ standard 11. not using 14 or 17 (we can change it if we want, just need to submit correct makefile)
# -Wall warns when code is wrong (no gray areas)
# -Werror turns warnings into errors (doesn't build project)
# -pedantic-errors catch even more mistakes and don't build project
# -fmessage-length=0 formats error messages (not important)

# include dependencies here, make instructions, etc.
all: # g++ -g ... *.cpp -o <thename>.cpp
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET).out
clean: # remove all build files
	rm -f $(TARGET) $(TARGET).out $(TARGET).exe
