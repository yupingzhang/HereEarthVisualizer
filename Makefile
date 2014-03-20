CXX = g++

# files and intermediate files we create
OBJS  = main.o View.o Input.o Marker.o
PROG  = Demo


INCLUDES  += -Iinclude -Icore
CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
CFLAGS    += $(CPPFLAGS) $(ARCH) -g -Wall -m64
CXXFLAGS  += $(CFLAGS) 
LDFLAGS   += -framework OpenGL -framework GLUT


# program from .o files
$(PROG): $(OBJS)
	$(CXX) $(OPT) -o $(PROG) $(OBJS) $(LDFLAGS) $(LDLIBS)

# .o from .c or .cxx
%.o: %.cpp
	$(CXX) $(OPT) -c -o $@ $< $(CXXFLAGS)
%.o: %.c
	$(CXX) $(OPT) -c -o $@ $< $(CFLAGS)


# remove everything but the program
clean:
	rm -f *~ *.o *.d

# remove everything including program
clobber: clean
	rm -f $(PROG)


main.o: main.cpp
View.o: View.cpp View.hpp 
Input.o: Input.cpp Input.hpp
Marker.o: Marker.cpp Marker.hpp