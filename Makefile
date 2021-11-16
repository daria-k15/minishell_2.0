NAME = minishell

CC = gcc 
FLAGS = -Wall -Wextra  -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include 

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)include/

HEADER =	minishell.h

SOURCES =	main.c\
			ast.c\
			ast_2.c\
			printAst.c\
			builtins.c\
			builtins_cd.c\
			builtins_export_exit.c\
			dollar_parse.c\
			env_functions.c\
			tree_handling.c\
			parsingAstArray.c\
			parsingAstArray2.c\
			parsingAstArray3.c\
			utils.c \
			utils_2.c\
			signals.c \
			signals_2.c\
			binary_command.c \
			exit_status.c \
			redirects.c


OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) Makefile
	@make -C $(LIBFT_DIRECTORY)
	@$(CC) $(FLAGS) $(OBJECTS) -L. libft/libft.a -o $(NAME) -lreadline
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER)
	@mkdir -p $(OBJECTS_DIRECTORY)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

test:	all
		./minishell


clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	