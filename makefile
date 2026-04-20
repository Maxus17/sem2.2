SRC = err.c inp.c prog.c main.c
HEADERS = $(wildcard *.h)
VECQUEUE_SRC = vecqueue.c
LISTQUEUE_SRC = listqueue.c

TARGET1 = prog1
TARGET2 = prog2

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC) $(VECQUEUE_SRC)
	gcc -o $(TARGET1) $(SRC) $(VECQUEUE_SRC) -lreadline -g

$(TARGET2): $(SRC) $(LISTQUEUE_SRC)
	gcc -o $(TARGET2) $(SRC) $(LISTQUEUE_SRC) -lreadline -g
%.o: %.c $(HEADERS)
	gcc -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2)
