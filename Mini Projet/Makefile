CC=clang -Wall -g

PROGRAMMES=test_terrain test_robot robot_terrain curiosity curiosity-test \
 main test_generation_terrains curiosity-perf curiosity-obs

all: main $(PROGRAMMES)

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: %.c
	$(CC) -c $<

test_terrain.o: test_terrain.c terrain.h

test_robot.o: test_robot.c robot.h

robot_terrain.o: robot_terrain.c terrain.h robot.h

robot.o: robot.c robot.h

terrain.o: terrain.c terrain.h

environnement.o: environnement.c environnement.h robot.h terrain.h observateur.h

environnement.1.o: environnement.1.c environnement.1.h robot.h terrain.h

programme.o: programme.c programme.h type_pile.h

interprete.o: interprete.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

interprete%.o: interprete%.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

type_pile.o: type_pile.c type_pile.h

curiosity.o: curiosity.c environnement.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

curiosity-test.o: curiosity-test.c environnement.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

main.o: main.c environnement.h interprete.h programme.h

generation_terrains.o: generation_terrains.c generation_terrains.h terrain.h terrain_alea.h

test_generation_terrains.o : test_generation_terrains.c generation_terrains.h

terrain_alea.o: terrain_alea.c terrain_alea.h terrain.h

observateur.o: observateur.c observateur.h

curiosity-perf.o: curiosity-perf.c terrain_alea.h terrain.h environnement.h interprete.h programme.h generation_terrains.h


######################################################################
#                       Règles d'édition de liens                    #
######################################################################

test_terrain: test_terrain.o terrain.o
	$(CC) $^ -o $@

test_robot: test_robot.o robot.o
	$(CC) $^ -o $@

robot_terrain: robot_terrain.o terrain.o robot.o
	$(CC) $^ -o $@

curiosity: curiosity.o environnement.o observateur.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test: curiosity-test.o environnement.o observateur.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-obs: curiosity-obs.o environnement.o observateur.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test%: curiosity-test.o environnement.o observateur.o programme.o interprete%.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

main: main.o environnement.o observateur.o interprete.o programme.o terrain.o robot.o type_pile.o observateur.o

#test_complet: test_complet.o environnement.o observateur.o interprete.o programme.o terrain.o robot.o type_pile.o

test_generation_terrains: test_generation_terrains.o terrain.o generation_terrains.o terrain_alea.o
	$(CC) $^ -o $@

curiosity-perf: curiosity-perf.o terrain_alea.o terrain.o environnement.o observateur.o \
	interprete.o programme.o generation_terrains.o robot.o type_pile.o
	$(CC) $^ -o $@

clean:
	rm -f $(PROGRAMMES) *.o
