ifneq ($(BUILD),release)
CFLAGS := -g -O0
else
CFLAGS := -O2
endif

PROJECT = bitstamp
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
CPP = $(PREFIX)g++
AR = $(PREFIX)ar
AS = $(PREFIX)as
LD = $(PREFIX)gcc
SIZE = $(PREFIX)size
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
LDFLAGS = -std=c++11 -lrexjson -lbitstampapi -lcrypto $(shell pkg-config --libs curlpp) -L../rexjson -L../api
CFLAGS += -c -Wall $(shell pkg-config --cflags curlpp) -I../  -I../include
CC_FLAGS = $(CFLAGS)
CXX_FLAGS = -std=c++11 $(CFLAGS)

PROJECT_SRC_C = $(wildcard *.c)
PROJECT_SRC_CXX = $(wildcard *.cxx)
PROJECT_SRC_CPP = $(wildcard *.cpp)
PROJECT_OBJ_C := $(PROJECT_SRC_C:.c=.o)
PROJECT_OBJ_CXX := $(PROJECT_SRC_CXX:.cxx=.o)
PROJECT_OBJ_CPP := $(PROJECT_SRC_CPP:.cpp=.o)

OBJECTS	:= \
	$(PROJECT_OBJ_C) \
	$(PROJECT_OBJ_CXX) \
	$(PROJECT_OBJ_CPP) \


DEPS := $(OBJECTS:.o=.d)


all : $(PROJECT)

clean:
	rm -f $(PROJECT) $(OBJECTS) $(DEPS)

.c.o:
	$(CC)  $(CC_FLAGS) $(INCLUDES) -o $@ $<

.cpp.o:
	$(CPP) $(CXX_FLAGS) $(INCLUDES) -o $@ $<

.cxx.o:
	$(CPP) $(CXX_FLAGS) $(INCLUDES) -o $@ $<

$(PROJECT) : $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

-include $(DEPS)


