
CFLAGS=-g

C_SRCS = el_port_posix.c
C_SRCS += el_event.c el_looper.c el_timer.c
CFLAGS = -g
LDFLAGS = -lpthread

HEADERS = $(wildcard %.h)
OBJS = $(patsubst %.c,build/%.o,$(C_SRCS))

build/example1:example1.c build/libeventlooper.a
	echo $(C_SRCS)
	gcc -g $(LDFLAGS) -o $@ $^

build/libeventlooper.a:$(OBJS)
	ar -rc $@ $(OBJS)

$(OBJS):build/%.o:%.c $(HEADERS)
	-@mkdir build
	gcc $(CFLAGS) -c -o $@ $<
