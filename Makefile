OBJS	= blue_and_gold_lock.o main.o
HEADER	= blue_and_gold_lock.h
OUT	= main
CC	 = gcc
CCFLAGS	= -pthread

all: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $(OUT)

blue_and_gold_lock.o : blue_and_gold_lock.c blue_and_gold_lock.h
	$(CC) $(CCFLAGS) -c $<

main.o : main.c blue_and_gold_lock.h
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f $(OBJS) $(OUT)

run:
	./$(OUT)