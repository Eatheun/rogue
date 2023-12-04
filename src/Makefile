CC = clang
CXXFLAGS = -Wall -Werror -Wvla -g
FILES = rogue.cxx enemies.cxx floorGen.cxx inputs.cxx lfsr.cxx movements.cxx playerPos.cxx

###############################################################

build: $(FILES)
	$(CC) $(CXXFLAGS) $(FILES) -o ../rogue

###############################################################

.PHONY: clean
clean:
	rm ../rogue

###############################################################

.PHONY: run
run:
	../rogue
