# MIT License
#
# Copyright (c) 2018 Eridan Domoratskiy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC = g++
CFLAGS = -std=c++14 -Wall -O2 #-g
LDFLAGS +=

BUILDPATH = build
SOURCES = Stack.cpp Program.cpp Position.cpp main.cpp
HEADERS = Stack.h Program.h
TARGET = befunge

OBJECTS = $(SOURCES:%.cpp=$(BUILDPATH)/%.o)

ifeq ($(OS), Windows_NT)
LDFLAGS += -static-libgcc -static-libstdc++
endif

.PHONY: default all examples clean build

default: build
all: build examples

examples: $(BUILDPATH)/examples.zip

$(BUILDPATH)/examples.zip: $(wildcard *.befunge)
	zip $@ $^

clean:
ifneq ($(OS), Windows_NT)
	rm -rf $(BUILDPATH)
else
	del /F /S /Q $(BUILDPATH)
endif

build: $(BUILDPATH)/$(TARGET)

%.cpp:

$(BUILDPATH)/%.o: %.cpp $(HEADERS)
ifneq ($(OS), Windows_NT)
	mkdir -p $(dir $@)
else
	if not exist "$(subst /,\,$(dir $@))" mkdir $(subst /,\,$(dir $@))
endif
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILDPATH)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
