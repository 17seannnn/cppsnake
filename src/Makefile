SRCMODULES = main.cpp curses.cpp game.cpp snake.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lncurses
RM = rm

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

snake: $(OBJMODULES)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(CXX) -MM $^ > $@

clean:
	$(RM) -rf *.o snake deps.mk
