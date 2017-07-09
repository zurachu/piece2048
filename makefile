#===============================================================================
# project makefile
#===============================================================================

.PHONY: all lib pex clean

#=======================================
# �v���W�F�N�g�ݒ�
#=======================================
include project.mak

#=======================================
# �T�t�B�b�N�X���[���𖳎�
#=======================================
.SUFFIXES:

#=======================================
# �����R�}���h�E�I�v�V����
#=======================================
CC := pcc33
CFLAGS := -c -g -gp=0x0 -near -O2 -Wall
AS := pcc33
ASFLAGS := -c -g -gp=0x0 -near
LD := pcc33
LDFLAGS := -g -ls -lm

LIB := lib33
CPP := cpp

#=======================================
# �����t�@�C��
#=======================================
TARGET := $(PROJECT_NAME).srf
IMAGE := $(PROJECT_NAME).pex
SYMBOL := $(PROJECT_NAME).sym
MEMMAP := $(PROJECT_NAME).map

all : $(TARGET)

#=======================================
# �\���t�@�C��
#=======================================
# zurapce library
ZURAPCE_LIBRARY_DIR := zurapce
ZURAPCE_LIBRARY := $(ZURAPCE_LIBRARY_DIR)/zurapce.lib

SOURCES := $(wildcard *.c)
DEPENDS := $(patsubst %.c,%.depend,$(SOURCES))
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
LIBRARIES := $(ZURAPCE_LIBRARY)

#=======================================
# 16�K���`��֘A�R�[�h������ RAM �ɔz�u����ꍇ
#=======================================
ifeq ($(strip $(USE_LDIRECT_ON_FRAM)),true)

FRAM_LDIRECT := Ldirect.o
FRAM_OBJECTS += $(FRAM_LDIRECT)

$(FRAM_LDIRECT) : $(ZURAPCE_LIBRARY)
	$(LIB) -x $< $@

endif

#=======================================
# �����t�H���g�֘A�R�[�h������ RAM �ɔz�u����ꍇ
#=======================================
ifeq ($(strip $(USE_FONT_FUCHI_ON_FRAM)),true)

FRAM_FONT_FUCHI := FontFuchi.o
FRAM_OBJECTS += $(FRAM_FONT_FUCHI)

$(FRAM_FONT_FUCHI) : $(ZURAPCE_LIBRARY)
	$(LIB) -x $< $@

endif

#=======================================
# ���� RAM �ɔz�u����ꍇ
#=======================================
ifneq ($(strip $(FRAM_OBJECTS)),)

FRAM_OBJECT_TOP := FramObject_Top.o
LDFLAGS +=	+codeblock FRAMC {$(FRAM_OBJECT_TOP) $(FRAM_OBJECTS)} \
			+bssblock FRAMB {$(FRAM_OBJECT_TOP) $(FRAM_OBJECTS)} \
			+addr 0x1000 {@FRAMC FRAMB} 
OBJECTS := $(FRAM_OBJECT_TOP) $(FRAM_OBJECTS) $(filter-out $(FRAM_OBJECTS),$(OBJECTS))

$(FRAM_OBJECT_TOP) : $(ZURAPCE_LIBRARY)
	$(LIB) -x $< $@

endif

#=======================================
# �ˑ��֌W
#=======================================

$(TARGET) : $(OBJECTS) $(LIBRARIES)
	$(LD) $(LDFLAGS) -e$@ $(subst /,\,$^)

%.o : %.c
	$(CC) $(CFLAGS) $<

#=======================================
# �����ˑ��֌W����
#=======================================
%.depend : %.c
	$(CPP) -MM -I$(PIECE_INC_DIR) $< > $@

-include $(DEPENDS)

#=======================================
# zurapce library
#=======================================

lib : $(ZURAPCE_LIBRARY)

$(ZURAPCE_LIBRARY) :
	make -C $(ZURAPCE_LIBRARY_DIR)

#=======================================
# �t���b�V���������݃C���[�W����
#=======================================

pex : $(IMAGE)

$(IMAGE) : $(TARGET) $(ICON)
	ppack -e $< -o$@ -n$(CAPTION) -i$(ICON)

#=======================================
# �N���[���A�b�v
#=======================================
clean :
	del $(IMAGE)
	del $(TARGET)
	del $(SYMBOL)
	del $(MEMMAP)
	del *.o
	del *.depend

