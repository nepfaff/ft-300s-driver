SRC = src/
BIN = bin/
OBJ = obj/

.PHONY: clean

all: $(BIN)ft_300s_driver

$(BIN)ft_300s_driver: $(BIN)libRQSensorLinux.a
	gcc -c $(SRC)main.c -o $(OBJ)main.o
	gcc $(OBJ)main.o $< -L./$(BIN) -lRQSensorLinux -o $@

$(OBJ)%.o: $(SRC)%.c
	gcc -c -Wall -std=c99 -o $@ $<

$(BIN)libRQSensorLinux.a: $(OBJ)rq_sensor_com.o $(OBJ)rq_sensor_state.o
	ar rcs $@ $^

$(OBJ)rq_sensor_socket.o:
	gcc -c $(SRC)rq_sensor_socket.c -o $(OBJ)rq_sensor_socket.o

$(OBJ)%.o: $(SRC)%.c
	gcc -c -Wall -std=c99 -o $@ $<

clean:
	-rm $(OBJ)Thread/*o
	-rm $(OBJ)*o
	-rm $(BIN)*
