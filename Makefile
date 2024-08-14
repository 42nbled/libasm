NAME = libasm.a
OBJ_DIR = objs
SRCS =  ft_write.s \
        ft_read.s \
        ft_strlen.s \
        ft_strcpy.s \
        ft_strcmp.s \
        ft_strdup.s \
		ft_atoi_base.s \
		ft_list_push_front.s \
		ft_list_size.s \
		ft_list_sort.s

OBJS = $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))

NA = nasm
NA_FLAGS = -f elf64 -g -F dwarf

CXX_SRCS = main.cpp
CXX_OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(CXX_SRCS))
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

# Rule to compile C++ source files into object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	g++ -c -fPIC -g $< -o $@

# Rule to link the executable using the static library
$(EXEC): $(CXX_OBJS) $(NAME)
	@echo "\033[0;34mLinking $(EXEC)...\033[0m"
	g++ $(CXX_OBJS) -L. -lasm -o $(EXEC) -lc -no-pie
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
