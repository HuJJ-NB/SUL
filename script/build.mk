# Directorys
OBJ_DIR = object
CLEAN += $(OBJ_DIR)

ASM_DIR = asm
CLEAN += $(ASM_DIR)

OBJS = $(ASMS:$(ASM_DIR)/%.s=$(OBJ_DIR)/%.o) $(SSRCS:%.s=$(OBJ_DIR)/%.o)
ASMS = $(CSRCS:%.c=$(ASM_DIR)/%.s)


# Compile rules
INCLUDES  = $(addprefix -I, $(INC_PATH))
CCFLAGS   = $(C_SETS) $(INCLUDES)

$(ASM_DIR)/%.s: %.c
	@echo '+ CC $<'
	@mkdir -p $(dir $@)
	@$(CC) -S $(CCFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s
	@echo '+ AS $<'
	@mkdir -p $(dir $@)
	@$(CC) -c $(CCFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: %.s
	@echo '+ AS $<'
	@mkdir -p $(dir $@)
	@$(CC) -c $(CCFLAGS) -o $@ $<

