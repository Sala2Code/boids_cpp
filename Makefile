all: compile link

compile:
	g++ -c main.cpp -I"C:\librairies\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"C:/librairies/SFML-2.5.1/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main -lsfml-audio

clean:
	rm -f main *.o