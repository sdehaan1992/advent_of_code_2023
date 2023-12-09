CC=clang
CFLAGS=-g -o0 -lm

SOURCE_DIR=sources
BUILD_DIR=builds

SOURCES=$(shell find $(SOURCE_DIR) -name "*.c")
HEADERS=$(shell find $(SOURCE_DIR) -name "*.h")
LIBS=$(patsubst %.h,%.o,$(HEADERS))
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: day1 day2 day3 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

day%: $(SOURCE_DIR)/day%.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

clean:
	rm -rf $(OBJECTS)

remove: clean
	rm -rf $(BUILD_DIR)/*

.PRECIOUS: $(OBJECTS)
