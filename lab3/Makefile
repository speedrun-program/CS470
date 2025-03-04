
CC=gcc


CFLAGS=-Wall -g  # -Wall: Enable all warning messages, -g: Add debugging information


TARGET_SJF=lab3_sjf
TARGET_RR=lab3_rr
SOURCE_SJF=SJF_inital
SOURCE_RR=RR_inital


all: $(TARGET_SJF) $(TARGET_RR)


$(TARGET_SJF): $(SOURCE_SJF).c
	$(CC) $(CFLAGS) -o $(TARGET_SJF) $(SOURCE_SJF).c

$(TARGET_RR): $(SOURCE_RR).c
	$(CC) $(CFLAGS) -o $(TARGET_RR) $(SOURCE_RR).c

