
# Zhu's template

# Define the C compiler to use
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g  # -Wall: Enable all warning messages, -g: Add debugging information

# Define the target executable name
TARGET=lab2

# 'all' is the default target. It's customary to have it as the first target.
# This target will be executed when you just type 'make' in the terminal.
all: $(TARGET)

# This is a rule for creating the target executable.
# It depends on the source file (TARGET.c). If the source file is changed,
# the target will be rebuilt when 'make' is run.
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c  
# Compile the source file into an executable

