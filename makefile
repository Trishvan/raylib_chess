all:
	gcc src/main.c -static-libgcc -static-libstdc++ -o build/main.exe -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
