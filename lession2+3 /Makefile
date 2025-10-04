CC = gcc
CFLAGS = -Wall -I.

SRC = main.c spws_controller.c hal_sensors.c hal_actuators.c hal_buttons.c
OBJ = $(SRC:.c=.o)
TARGET = spws

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
