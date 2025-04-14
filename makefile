all:
	gcc src/main.c src/board.c src/pieces.c src/assets.c src/linked_list.c -static-libgcc -static-libstdc++ -o build/main.exe -I./src/include -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
