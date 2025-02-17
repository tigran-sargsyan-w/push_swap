# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME        = push_swap
BONUS_NAME  = checker
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS     = -Wl,--allow-multiple-definition

# -------------------------------
#   Directories
# -------------------------------
SRC_DIR     = src
LIBFT_DIR   = libft

# -------------------------------
#   Source Files for push_swap
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
#   Common source
# -------------------------------
COMMON_SRCS = $(SRC_DIR)/common_utils.c

# -------------------------------
#   Object Files for push_swap
# -------------------------------
OBJS        = $(SRCS:.c=.o)
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

# -------------------------------
#   Source Files for bonus
# -------------------------------
BONUS_SRCS  = $(SRC_DIR)/checker_bonus.c

# -------------------------------
#   Object Files for bonus
# -------------------------------
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

# -------------------------------
# For the bonus build, exclude push_swap.o from OBJS,
# to avoid conflict with main.
# ------------------------------
BONUS_COMMON_OBJS = $(filter-out $(SRC_DIR)/push_swap.o, $(OBJS))

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

$(NAME): $(OBJS) $(COMMON_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(COMMON_OBJS) $(LIBFT) -o $(NAME)
	@echo "🚀 Executable $(NAME) created successfully!"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)
	@echo "🚀 Executable $(BONUS_NAME) created successfully!"

$(BONUS_NAME): $(BONUS_OBJS) $(BONUS_COMMON_OBJS) $(COMMON_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(BONUS_COMMON_OBJS) $(COMMON_OBJS) $(LIBFT) -o $(BONUS_NAME) $(LDFLAGS)

clean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(COMMON_OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "🗑️ $(NAME) object files removed."

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "😒 $(NAME) removed."

re: fclean all

.PHONY: all bonus clean fclean re
