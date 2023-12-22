# Makefile
# Nama program
TARGET = build/WangkuApp.exe

# Compiler
CC = g++

# Direktori sumber
SRC_DIR = src

# File sumber
SOURCES = $(SRC_DIR)/main.cpp

# Objek yang dihasilkan dari file sumber
# OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) -Wall -Wextra -g3 $(SOURCES) -o $(TARGET)

# Rule untuk meng-compile file sumber menjadi objek
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# run: $(TARGET)
#     ./$(TARGET)