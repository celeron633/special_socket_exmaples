TARGET := tun_device
SRCS := tun_device.c
OBJS := tun_device.o

CC := gcc

${TARGET}: ${OBJS}
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

.phony: clean

all: ${TARGET}

clean:
	rm -f *.o \
	rm -f ${TARGET}