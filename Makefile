NAME = libasm.a
OBJ_DIR = objs
SRCS =	ft_write.s \
		ft_read.s \
		ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s
OBJS = $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))

NA = nasm
NA_FLAGS = -f elf64

C_SRCS = main.c
C_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_SRCS))
EXEC = test_program

# Rule to create the static library
$(NAME): $(OBJS)
	@echo "\033[0;34mCreating $(NAME)...\033[0m"
	ar rcs $(NAME) $(OBJS)
	@echo "\033[0;32mLibrary $(NAME) created.\033[0m"

# Rule to compile assembly files into object files
$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(@D)
	$(NA) $(NA_FLAGS) $< -o $@

# Rule to compile C source files into object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $< -o $@

# Rule to link the executable using the static library
$(EXEC): $(C_OBJS) $(NAME)
	@echo "\033[0;34mLinking $(EXEC)...\033[0m"
	gcc $(C_OBJS) -L. -lasm -o $(EXEC)
	@echo "\033[0;32mExecutable $(EXEC) created.\033[0m"

# Rule to build the library only
libasm: $(NAME)

# Rule to build the executable only
exe: $(EXEC)

# Default rule to build everything
all: libasm exe

clean:
	@echo "\033[0;34mCleaning objects...\033[0m"
	rm -rf $(OBJ_DIR)
	@echo "\033[0;32mObjects cleaned.\033[0m"

fclean: clean
	@echo "\033[0;34mCleaning library and executable...\033[0m"
	rm -f $(NAME) $(EXEC)
	@echo "\033[0;32mLibrary and executable cleaned.\033[0m"

re: fclean all

.PHONY: all clean fclean re libasm exe
