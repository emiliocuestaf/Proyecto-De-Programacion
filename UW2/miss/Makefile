
CCFLAGS := -g -Wall -ansi -pedantic -std=c99
EXE = pruebacop

all: $(EXE) 

pruebacop: pruebacop.c  copfunctions.o shoot.o cop.o animations.o interface.o rectangles.o world.o space.o object.o player.o npc.o lineread.o loading.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CCFLAGS) -o ../install/game pruebacop.c animations.c copfunctions.o shoot.o cop.o interface.o rectangles.o world.o space.o object.o player.o npc.o lineread.o loading.o -lpthread
	cp  cop.txt ../install
	cp  maps.txt ../install
	cp  npcs.txt ../install
	cp objetos.txt ../install

rectangles.o : rectangles.c rectangles.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

interface.o : interface.c interface.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

cop.o : cop.c cop.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

world.o : world.c world.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

space.o : space.c space.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

object.o : object.c object.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

player.o : player.c player.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

npc.o : npc.c npc.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

lineread.o : lineread.c lineread.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

loading.o : loading.c loading.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<


shoot.o : shoot.c shoot.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<


copfunctions.o : copfunctions.c copfunctions.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<


animations.o : animations.c animations.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o pruebacop
	rm -r ../install/*
