CC = clang

NAME = doom_nukem

KEYS = #-Wall -Wextra -Werror

FLAGS = -flto -O3 $(KEYS)

IDIR = ./inc

EXTENSIONS = $(addprefix $(IDIR)/,$(EXT))

EXT =	doomNukem.h

CFLAGS = -I$(IDIR) \
		-I./libft/inc \
		-I./libCL/inc \
		-I./libSDL/SDL2.framework/Headers/ \
		-I./libSDL/SDL2_image.framework/Headers/ \
		-I./libSDL/SDL2_ttf.framework/Headers/ \
		-I./libftSDL/inc \
		-I./libJson/inc \
		-I./libmy_math/inc

LIBFT = libft

LIBJSON = libJson

LIBFTSDL = libftSDL

LIBMMATH = libmy_math

SDL2_F		= -framework SDL2 -framework SDL2_image -framework SDL2_ttf -F ./libSDL/

SDL2_P		= -rpath @loader_path/libSDL/

DIR_S = src

DIR_O = obj

HEADER = inc

_DEPS = doomNukem.h

DEPS = $(patsubst %,$(HEADER)/%,$(_DEPS))

SOURCES =   main.c \
			sdl_handle.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: obj $(NAME)

$(NAME): $(OBJS) $(EXTENSIONS)
		make libs
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(CFLAGS) -L $(LIBFT) -lft -L $(LIBMMATH) -lmy_math -L $(LIBJSON) -lJSON $(SDL2_P) $(SDL2_F) -L $(LIBFTSDL) -lftsdl

		

libs: 
	make -C $(LIBFT)
	make -C $(LIBJSON)
	make -C $(LIBMMATH)
	make -C $(LIBFTSDL)

obj:
	mkdir -p obj

$(DIR_O)/%.o: $(DIR_S)/%.c $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)

norme:
		make norme -C $(LIBFT)
		make norme -C $(LIBFTSDL)
		make norme -C $(LIBMMATH)
		echo "--------------------Checking header files $(NAME)"
		norminette ./$(HEADER)
		echo "--------------------Checking source files $(NAME)"
		norminette ./$(DIR_S)

clean:
		rm -f $(OBJS)
		make clean -C $(LIBFT)
		make clean -C $(LIBFTSDL)
		make clean -C $(LIBJSON)
		make clean -C $(LIBMMATH)
		rm -rf $(DIR_O)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)
		make fclean -C $(LIBFTSDL)
		make fclean -C $(LIBJSON)
		make fclean -C $(LIBMMATH)

re: fclean all

.PHONY: all, obj, norme, clean, fclean, re
.NOTPARALLEL:  all, obj, norme, clean, fclean, re
.SILENT: