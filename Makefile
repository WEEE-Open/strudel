# Makefile for strudel

CC       = gcc
CXX      = g++

SIO_DIR  = socket.io-client-cpp-3.1.0

INCLUDES = -I$(SIO_DIR)/src \
           -I$(SIO_DIR)/lib/asio/asio/include \
           -I$(SIO_DIR)/lib/websocketpp \
           -I$(SIO_DIR)/lib/rapidjson/include \
		   -Iraylib-media/src

# Required by socket.io-client-cpp when using its bundled deps
DEFINES  = -DASIO_STANDALONE -D_WEBSOCKETPP_CPP11_STL_

# Separate C and C++ flag sets — this is the critical fix
CFLAGS   = -Wall -Wextra -O2 -std=c11   -MMD -MP $(INCLUDES) $(DEFINES)
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -MMD -MP $(INCLUDES) $(DEFINES)

LDFLAGS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDLIBS   = -lstdc++ -lssl -lcrypto -lavcodec -lavformat -lavutil -lswresample -lswscale

TARGET   = build/main

# --- Sources ---
C_SRCS   = $(wildcard src/*.c)
CXX_SRCS = $(wildcard src/*.cpp)

SIO_SRCS = $(SIO_DIR)/src/sio_client.cpp \
           $(SIO_DIR)/src/sio_socket.cpp \
           $(SIO_DIR)/src/internal/sio_client_impl.cpp \
           $(SIO_DIR)/src/internal/sio_packet.cpp

# --- Objects ---
C_OBJ    = $(C_SRCS:.c=.o)
CXX_OBJ  = $(CXX_SRCS:.cpp=.o) $(SIO_SRCS:.cpp=.o)

OBJ      = $(C_OBJ) $(CXX_OBJ)

# --- Rules ---
all: $(TARGET)

$(TARGET): $(OBJ) | build
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# C sources
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# C++ sources (both your wrapper and socket.io)
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SIO_DIR)/%.o: $(SIO_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -w -c $< -o $@

build:
	mkdir -p build

clean:
	rm -f $(C_OBJ) $(CXX_OBJ) $(OBJ:.o=.d) $(TARGET)

.PHONY: all clean
