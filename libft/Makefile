LIB		= libft.a

SRC_FT_IS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c
SRC_LISTS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 
SRC_MEMORY = ft_memset.c ft_memmove.c ft_memcpy.c ft_memcmp.c ft_memchr.c \
				ft_calloc.c ft_bzero.c
SRC_OTHER = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_tolower.c ft_toupper.c
SRC_STRING = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
				ft_strncmp.c ft_atoi.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_itoa.c ft_strmapi.c ft_strcmp.c ft_split.c

GNL  =	get_next_line.c get_next_line_utils.c

SRC_D = $(addprefix ft_is/, $(SRC_FT_IS)) \
		$(addprefix lists/, $(SRC_LISTS)) \
		$(addprefix memory/, $(SRC_MEMORY)) \
		$(addprefix other/, $(SRC_OTHER)) \
		$(addprefix string/, $(SRC_STRING)) \
		$(addprefix gnl/, $(GNL))

SRCS = $(SRC_FT_IS) $(SRC_LISTS) $(SRC_MEMORY) $(SRC_OTHER) $(SRC_STRING) $(GNL)

OBJ_D = objs
OBJS		= $(addprefix $(OBJ_D)/, $(SRCS:.c=.o))

HEADER		= libft.h
HEADER_D = $(addprefix include/, $(HEADER))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

GREEN = \033[0;32m

			
$(LIB):		$(SRC_D) 
			@$(CC) $(CFLAGS) -c $(SRC_D) -I ./include
			@mkdir -p $(OBJ_D) && mv $(SRCS:.c=.o) ./$(OBJ_D)
			@ar rc $(LIB) $(OBJS)
			@ranlib $(LIB)
			@echo "$(LIB): $(GREEN)$(LIB) was successfully built!"

all:		$(LIB)

clean:
			@rm -rf $(OBJ_D)

fclean:		clean
			@rm -rf $(LIB)

re:			fclean all

.PHONY:		all clean fclean re
