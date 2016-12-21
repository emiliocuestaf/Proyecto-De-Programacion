
CCFLAGS := -g -Wall -std=c99
EXE =  test1 pruebainterfaz

all: $(EXE) 

test1: test1.c space.o lineread.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	gcc $(CCFLAGS) test1.c space.o lineread.o -o test1

pruebainterfaz: pruebainterfaz.c interface.o rectangles.o world.o space.o object.o player.o npc.o lineread.o loading.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o pruebainterfaz pruebainterfaz.c interface.o rectangles.o world.o space.o object.o player.o npc.o lineread.o loading.o


rectangles.o : rectangles.c rectangles.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

interface.o : interface.c interface.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

world.o : world.c world.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

space.o : space.c space.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

object.o : object.c object.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

player.o : player.c player.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

npc.o : npc.c npc.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

lineread.o : lineread.c lineread.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

loading.o : loading.c loading.h
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o test1
