CC := gcc
#CFLAGS := 
DEST := ./build/

all: calc_bill.c
	mkdir -p build
	$(CC) calc_bill.c -lcs50 -o $(DEST)/calc_bill 