NAME = libasm.a
OBJ_DIR = objs
SRCS =  libasm/ft_write.s \
        libasm/ft_read.s \
        libasm/ft_strlen.s \
        libasm/ft_strcpy.s \
        libasm/ft_strcmp.s \
        libasm/ft_strdup.s
BONUS_SRCS = libasm/ft_atoi_base.s \
             libasm/ft_list_push_front.s \
             libasm/ft_list_size.s \
             libasm/ft_list_sort.s \
             libasm/ft_list_remove_if.s

OBJS = $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS = $(patsubst %.s, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

NA = nasm
NA_FLAGS = -f elf64 -g -F dwarf -DPIC

CXX_SRCS = tester/main.cpp \
        tester/ft_write_tester.cpp \
        tester/ft_read_tester.cpp \
        tester/ft_strlen_tester.cpp \
        tester/ft_strcpy_tester.cpp \
        tester/ft_strcmp_tester.cpp \
        tester/ft_strdup_tester.cpp \
        tester/ft_atoi_base_tester.cpp \
        tester/utils.cpp

CXX_OBJS = $(CXX_SRCS:%.cpp=$(OBJ_DIR)/%.o)
EXEC = test_program

# Rule to create the static library
$(NAME): $(OBJS)
	@echo "\033[0;34mCreating $(NAME)...\033[0m"
	ar rcs $(NAME) $(OBJS)
	@echo "\033[0;32mLibrary $(NAME) created.\033[0m"

# Rule to create the static library with bonus objects
bonus: $(OBJS) $(BONUS_OBJS)
	@echo "\033[0;34mCreating $(NAME) with bonus...\033[0m"
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "\033[0;32mLibrary $(NAME) with bonus created.\033[0m"

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
	g++ -pie -fPIE $(CXX_OBJS) -L. -lasm -o $(EXEC) -lc
	@echo "\033[0;32mExecutable $(EXEC) created.\033[0m"

# Rule to build the library only
libasm: $(NAME)

# Rule to build the executable only
exe: $(EXEC)

# Default rule to build everything
all: libasm bonus exe

clean:
	@echo "\033[0;34mCleaning objects...\033[0m"
	rm -rf $(OBJ_DIR)
	@echo "\033[0;32mObjects cleaned.\033[0m"

fclean: clean
	@echo "\033[0;34mCleaning library and executable...\033[0m"
	rm -f $(NAME) $(EXEC)
	@echo "\033[0;32mLibrary and executable cleaned.\033[0m"

re: fclean all

.PHONY: all clean fclean re libasm exe bonus