CC=clang
CFLAGS=-g -o0 -lm

SOURCE_DIR=sources
BUILD_DIR=builds

SOURCES=$(shell find $(SOURCE_DIR) -name "*.c")
HEADERS=$(shell find $(SOURCE_DIR) -name "*.h")
LIBS=$(patsubst %.h,%.o,$(HEADERS))
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: day1 day2 day3 day4 day5 day6 day7 day8 day9

day%: $(BUILD_DIR)/day%
	

%.o: %.c 
	$(CC) $(CFLAGS) $(CUSTOM_FLAGS) -c $< -o $@

$(BUILD_DIR)/day%: $(SOURCE_DIR)/day%.o $(LIBS)
	$(CC) $(CFLAGS) $(CUSTOM_FLAGS) $^ -o $@

clean:
	rm -rf $(OBJECTS)

remove: clean
	rm -rf $(BUILD_DIR)/*

.PRECIOUS: $(OBJECTS) $(BUILD_DIR)/day%
