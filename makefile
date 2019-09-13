CC=g++
CFLAGS= -I.
LIBS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpugixml

# all:
# 	$(CC) $(CFLAGS) $(LIBS) src/*/*pp

# sfml:
# 	sudo apt-get install libsfml-dev

# ├── engine
# │   ├── audio
# │   ├── menu
# ├── game
# │   ├── music_player
# │   ├── pltfmr
# │   ├── show_cards
# │   └── snake_game
# ├── graphics
# │   ├── animations
# │   └── ui
# ├── model
# ├── previous_game
# ├── test
# │   ├── menu
# │   └── tools
# └── tools

# %.o: %.cpp %.hpp
# 	$(CC) $(CFLAGS) -c $?

%.o: %.cpp %.hpp
	echo -e '\033[93m'Building '\033[95m'$@'\033[m' from '\033[96m'$? '\033[m'
	$(CC) $(CFLAGS) -c $?

all: model tools pipeline graphics engine test
	# $(CC) $(CFLAGS) $(LIBS) main.cpp
	$(CC) $(CFLAGS) *.o model/*.hpp $(LIBS) main.cpp

model: model/drawable.o

engine: engine/timer.o \
		pipeline \
		engine/settings.o \
		engine/scene.o \
		engine/audio/sound.o \
		engine/menu/menu.o \
		tools \
		graphics
	$(CC) $(CFLAGS) -c engine/engine.*pp

pipeline: tools/xml_document.o \
		game/music_player/music_player.o \
		game/show_cards/show_cards.o \
		game/snake_game/snake_game.o
	$(CC) $(CFLAGS) -c engine/pipeline.*pp

graphics: ui
	$(CC) $(CFLAGS) -c graphics/*pp
	
ui:
	$(CC) $(CFLAGS) -c graphics/ui/*pp

tools: tools/xml_document.o \
		tools/color.o \
		tools/strmanip.o

test: test/test.o \
	test/test_time.o \
	test/test_xml.o \
	test/snake_tests.o \
	test/menu/test_menu.o \
	test/tools/test_strmanip.o
	echo 1

clean:
	find -name "*.o" | xargs rm
	find -name "*.gch" | xargs rm

objs:
	find -name "*.o"