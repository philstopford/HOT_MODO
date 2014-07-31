# Copyright (c) 2008-2013 Luxology LLC

LXSDK = ../LXSDK_73095
LXSDK_INC = $(LXSDK)/include
LXSDK_BUILD = $(LXSDK)/samples/Makefiles/build
SRC_DIR=HOTModo
HOT_INC = dependencies/hot-master
OPENEXR_INC = /usr/include/OpenEXR
OBJ_DIR=Linux/obj
TARGET_DIR=Linux/build
MYCXX = g++-4.6
LINK = g++-4.6
CXXFLAGS = -g -c -I$(LXSDK_INC) -I$(HOT_INC) -I$(OPENEXR_INC) -fPIC -m64 -msse
LDFLAGS = -L$(TARGET_DIR) -L$(LXSDK_BUILD) -lcommon -shared

OBJS = $(OBJ_DIR)/hotModo_texture.o $(OBJ_DIR)/hotModo_chanmod.o $(OBJ_DIR)/hotModo_deformer.o
TARGET = $(TARGET_DIR)/hotModo.lx

all: $(TARGET)

lxsdk:
	cd $(LXSDK)/samples/Makefiles/common; make

$(OBJ_DIR):
	mkdir $@

.PRECIOUS :$(OBJ_DIR)/%.o 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MYCXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ_DIR) lxsdk $(OBJS)
	$(LINK) -o $@ $(OBJS) $(LDFLAGS)

clean:
	cd $(LXSDK)/samples/Makefiles/common; make clean
	rm -rf $(TARGET) $(OBJ_DIR)
