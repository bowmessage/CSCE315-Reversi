all:
	g++ -ggdb -lfltk -lfltk_images -lX11 -w -fpermissive -o game *.cpp *.h *.cxx
