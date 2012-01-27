CC = g++
INCLUDE = -I./ -I/usr/include/SDL
CFLAGS = -O2 $(INCLUDE)
LIBS = -lSDL -lSDL_image -lSDL_ttf -L./ -llua
TARGET = engine

OBJ = \
./Canvas.o \
./LuaObject.o \
./GameObject.o \
./GameSystem.o \
./GameSystemLuaAPI.o \
./ScreenLayer.o \
./EventHandler.o \
./SceneManager.o \
./SceneManagerLuaAPI.o \
./Helper.o \
./Font.o \
./Sprite.o \
./TextBox.o \
./TextBoxLuaAPI.o \
./main.o


.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJ) $(LIBS) 

clean:
	@rm $(OBJ)