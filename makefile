all:
	g++ src/Main.cpp src/AI.cpp src/Board.cpp src/Game.cpp src/Renderer.cpp \
	src/pieces/Bishop.cpp src/pieces/King.cpp src/pieces/Knight.cpp \
	src/pieces/Peon.cpp src/pieces/Piece.cpp src/pieces/Queen.cpp src/pieces/Rook.cpp \
	-static-libgcc -static-libstdc++ -o build/main.exe \
	-I./src -I./src/pieces -I./raylib/include \
	-L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
