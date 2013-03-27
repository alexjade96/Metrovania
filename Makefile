# Automatically generated Makefile for project: sdl_maps
# Created on  by gaten for sdltutorials.com
# Comments, suggestions and bugs email: gaten DOT net AT gmail DOT com

# this is modified makefile from 7th tutorial
# 2009-06-07 haqu

# Compiler
CC=g++

# Objects
OBJECTS=CAnimation.o CApp.o CApp_OnCleanup.o CApp_OnEvent.o CApp_OnInit.o CApp_OnLoop.o CApp_OnRender.o CArea.o CCamera.o CEntity.o CEvent.o CFPS.o CMap.o CSamus.o CSurface.o CTile.o CEntityCol.o

# Compiler flags
CPPFLAGS=-Wall -g `sdl-config --cflags`

# Linker flags
LDFLAGS=`sdl-config --libs` -lSDL -lSDL_image

main: CApp.cpp
	$(CC) $(CPPFLAGS) -c CAnimation.cpp CApp.cpp CApp_OnCleanup.cpp CApp_OnEvent.cpp CApp_OnInit.cpp CApp_OnLoop.cpp CApp_OnRender.cpp CArea.cpp CCamera.cpp CEntity.cpp CEvent.cpp CFPS.cpp CMap.cpp CSamus.cpp CSurface.cpp CTile.cpp CEntityCol.cpp
	$(CC) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) -o metroid

# cleanup
clean:
	rm -rf $(OBJECTS) *~

# EOF
