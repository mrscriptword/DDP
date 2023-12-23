# Nama program
TARGET = build/WangkuApp.exe
DLL_FILE = build/msys-2.0.dll

# Compiler
CC = g++
CFLAGS = -Wall -Wextra -g3 -std=c++11
STATIC_LIB = -static-libgcc -static-libstdc++
UPX_FLAGS = --lzma --ultra-brute --overlay=strip --compress-exports=0 --force
# LDFLAGS = -ltermcolor

# Direktori sumber
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIR = include

# File sumber
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Objek yang dihasilkan dari file sumber
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

all: $(TARGET) compress

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(STATIC_LIB)

# Rule untuk meng-compile file sumber menjadi objek
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compress:
	upx $(UPX_FLAGS) $(TARGET) $(DLL_FILE)

clean:
	rm -rf $(BIN_DIR)/*.o $(BUILD_DIR)/WangkuApp.exe