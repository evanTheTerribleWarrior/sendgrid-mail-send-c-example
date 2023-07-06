CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lcurl

TARGET = sendgrid_send_email
SRCS = main.c sendgrid.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
