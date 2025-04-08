all:
	gcc src/main.c src/board.c src/pieces.c src/textures.c -static-libgcc -static-libstdc++ -o build/main.exe -I./raylib/include -Isrc/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
