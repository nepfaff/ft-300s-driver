SRC = src/
BIN = bin/
OBJ = obj/

.PHONY: clean

################################
# Rules to compile under linux
linux: Linux/$(BIN)driverSensor

Linux/$(BIN)driverSensor: Linux/$(BIN)libRQSensorLinux.a
	gcc -c Linux/$(SRC)main.c -o Linux/$(OBJ)main.o
	gcc Linux/$(OBJ)main.o $< -L./Linux/bin/ -lRQSensorLinux -o $@

Linux/$(OBJ)%.o: Linux/$(SRC)%.c
	gcc -c -Wall -std=c99 -o $@ $<

# regle pour creer la libRQSensorLinux
Linux/$(BIN)libRQSensorLinux.a: $(OBJ)rq_sensor_com.o $(OBJ)rq_sensor_state.o
	@for i in $^; do cp $$i Linux/$$i; done
	ar rcs $@ $(addprefix Linux/,$^)

# regle pour creer la libRQSensorUR
Linux/UR/$(BIN)libRQSensorUR.a: $(OBJ)rq_sensor_com.o $(OBJ)rq_sensor_state.o Linux/$(OBJ)rq_sensor_socket.o
	ar rcs $@ $^

Linux/$(OBJ)rq_sensor_socket.o:
	gcc -c Linux/$(SRC)rq_sensor_socket.c -o Linux/$(OBJ)rq_sensor_socket.o

# regle pour compiler les .c en .o
$(OBJ)%.o: $(SRC)%.c
	gcc -c -Wall -std=c99 -o $@ $<

clean:
	-rm $(OBJ)Thread/*o
	-rm $(OBJ)*o
	# -rm $(BIN)*
	-rm Linux/$(OBJ)*o
	-rm Linux/$(BIN)*
