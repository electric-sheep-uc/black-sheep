# Makefile for Mixed Team Communication example

CC           := g++
CPPFLAGS     := -DMITECOM_EXAMPLE \
                -Wno-multichar \
                -ggdb3 \
                -Werror -Wfatal-errors -Wpointer-arith -Wcast-qual -Wwrite-strings -Wno-long-long -Wno-variadic-macros -Woverloaded-virtual -Wctor-dtor-privacy -Wstrict-null-sentinel -Wsign-promo -Wsign-conversion

TARGET       := mitecom

SOURCE_FILES := mitecom-handler.cpp mitecom-network.cpp mitecom-main.cpp
HEADER_FILES := mitecom-data.h mitecom-handler.h mitecom-network.h

OBJECT_FILES := $(SOURCE_FILES:%.cpp=%.o)


all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) -o $(TARGET) $(OBJECT_FILES)

$(OBJECT_FILES): $(HEADER_FILES)

clean:
	$(RM) $(OBJECT_FILES) $(TARGET)
