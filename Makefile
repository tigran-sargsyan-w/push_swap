# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iincludes -Ilibft

# -------------------------------
#   Directories
# -------------------------------
SRC_DIR     = src
LIBFT_DIR   = libft

# -------------------------------
#   Source Files
# -------------------------------
SRCS        = $(SRC_DIR)/chunk_sort.c \
              $(SRC_DIR)/indexing.c \
              $(SRC_DIR)/parsing.c \
              $(SRC_DIR)/reverse_rotate_utils.c \
              $(SRC_DIR)/stack.c \
              $(SRC_DIR)/chunk_sort_utils.c \
              $(SRC_DIR)/operations.c \
              $(SRC_DIR)/push_swap.c \
              $(SRC_DIR)/rotate_utils.c \
              $(SRC_DIR)/swap_utils.c \
              $(SRC_DIR)/chunk_utils.c \
              $(SRC_DIR)/optimization_utils.c \
              $(SRC_DIR)/push_utils.c \
              $(SRC_DIR)/small_sort.c \
              $(SRC_DIR)/validation.c

# -------------------------------
#   Object Files
# -------------------------------
OBJS        = $(SRCS:.c=.o)

# -------------------------------
#   Header Files
# -------------------------------
HEADERS     = includes/operations.h \
              includes/optimization.h \
              includes/parsing.h \
              includes/push_swap.h \
              includes/sorting.h \
              includes/stack.h \
              includes/validation.h

# -------------------------------
#   Library Dependency (libft)
# -------------------------------
LIBFT       = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                 Build Rules                                  #
# **************************************************************************** #

all: $(NAME)
	@echo "😊 Build completed successfully!"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "🚀 Executable $(NAME) created successfully!"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "🗑️ Push swap object files removed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "🔥 Executable and libft removed."

re: fclean all

.PHONY: all clean fclean re
