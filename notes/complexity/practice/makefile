CXX      = g++
CXX_FILE = $(wildcard *.cpp)
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET).out
clean:
	rm -f $(TARGET) $(TARGET).out $(TARGET).exe
docs:
	pandoc --pdf-engine=xelatex -o output.pdf *.md
