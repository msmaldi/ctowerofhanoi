CC=gcc
SRC=src/main.c src/towerofhanoi.c src/towerofhanoi.h src/hanoihumanplayer.c src/hanoihumanplayer.h

all:
	$(CC) $(SRC) -O3 -o towerofhanoi

clean:
	rm towerofhanoi