# project-specific settings
EXECNAME:=table-spec
CCFLAGS:=-Werror -Wall -g
LDFLAGS:=-lstdc++

# boilerplate rules
SOURCES:=$(shell find src -name *.c -o -name *.cpp)
OBJECTS:=$(addsuffix .o,$(basename $(patsubst src/%,build/%,$(SOURCES))))
CCFLAGS+=-Isrc -MD -MP
TARGET:=build/$(EXECNAME)
default: $(TARGET)
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	g++ -o $@ $^ $(LDFLAGS)
build/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) -std=c++17 $(CCFLAGS) -c $< -o $@
build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) -std=c17 $(CCFLAGS) -c $< -o $@
clean:
	-rm -rf build
install:
	cp $(TARGET) /usr/bin/$(EXECNAME)
format:
	clang-format -i $(shell find src -name *.c -o -name *.cpp -o -name *.h)
.PHONY: clean install format
-include $(shell find build -name *.d)

