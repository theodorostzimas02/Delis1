# Compiler
CC = g++

# Compile Options
CFLAGS = -g -lm

EXECUTABLE = main
OBJV = Bucket.cpp HashTable.cpp InvertedIndex.cpp mvote.cpp Node.cpp Voter.cpp ZIPNode.cpp main.cpp
ARGSV = -f voters5000.csv -b 2


$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJV) -o $(EXECUTABLE) -lm -g

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGSV)

clean:
	rm -f $(OBJ) $(EXECUTABLE)
