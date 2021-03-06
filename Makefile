# Copyright (c) 2008-2013 Luxology LLC

LXSDK = ../LXSDK_73195
LXSDK_INC = $(LXSDK)/include
LXSDK_BUILD = $(LXSDK)/samples/Makefiles/build
SRC_DIR=HOTModo
HOT_INC = dependencies/hot-master
OPENEXR_INC = /usr/include/OpenEXR
OBJ_DIR=Linux/obj
TARGET_DIR=Linux/build
MYCXX = g++-4.1
LINK = g++-4.1
CXXFLAGS = -g -c -I$(LXSDK_INC) -I$(HOT_INC) -I$(OPENEXR_INC) -fPIC -m64 -msse
LDFLAGS = -L$(LXSDK_BUILD) -L/usr/lib -lcommon -lfftw3f -lfftw3f_threads -lImath -shared

OBJS = $(OBJ_DIR)/hotModo_init.o $(OBJ_DIR)/hotModo_texture.o $(OBJ_DIR)/hotModo_chanmod.o $(OBJ_DIR)/hotModo_deformer.o $(OBJ_DIR)/hotModo_command.o
TARGET = $(TARGET_DIR)/hotmodo.lx

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
