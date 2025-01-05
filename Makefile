cc=g++
lib= -lfltk -lm `pkg-config --cflags --libs opencv4` -lhpdf
ext: main.cpp mkpdf.cpp
	$(cc) $^ $(lib) -o $@
