# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 16:36:29 by adi-nata          #+#    #+#              #
#    Updated: 2023/11/14 00:11:13 by adi-nata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRC_DIR		=	src

OBJ_DIR		=	.obj

SRCS		=   ${SRC_DIR}/cub3d.c			${SRC_DIR}/tools.c\
				${SRC_DIR}/checkinnit.c\
\
				${SRC_DIR}/parser.c			${SRC_DIR}/parser_tools.c\
				${SRC_DIR}/parser_map.c\
\
				${SRC_DIR}/mlx.c\
#				${SRC_DIR}/dda_ray.c\		${SRC_DIR}/dda_ray_utils.c\

OBJS        =	${patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SRCS}}

CC			=	gcc

RM			=	rm -rf

FLAGS		=	-g -I./ -Ilibft/include/ -Wall -Wextra -Werror

LIBFLAGS	=	-L./libft/include/ -lft

LIB			=	libft

LIBX		=	minilibx-linux


#	Flags for Mac

MAC_CFLAGS	=	-g -Wall -Wextra -Werror -I./ -Ilibft/include/ -I${LIBX}

LIBXFLAGS	=	-L${LIBX} -lmlx -framework OpenGL -framework AppKit -lX11

X11FLAGS	=	-L/usr/X11/lib -lXext -lX11



ARG			=	prova.cub

MAKEFLAGS	+=	--silent

CLR_RMV		=	\033[0m
RED		    =	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN 		=	\033[1;36m


${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
				@mkdir -p ${@D}
				${CC} ${FLAGS} -c $< -o $@

${NAME}:		${OBJS}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${LIB} ${CLR_RMV}..."
				@make -C ./libft
				@echo "${GREEN}${LIB} created[0m ✔️"

				@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(LIBX) ${CLR_RMV}..."
				@make -sC ./${LIBX}
				@echo "$(GREEN)$(LIBX) created[0m ✔️"

				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${FLAGS} ${OBJS} ${LIBFLAGS} -o ${NAME} -L minilibx-linux -lmlx -lXext -lX11 -lm -pthread
				@echo "${GREEN}${NAME} created[0m ✔️"

all:			${NAME}

objs:
				@mkdir -p obj

clean:
				@ echo "${RED}Deleting ${CYAN}${LIB} ${CLR_RMV}libft objs ✔️"
				@make clean -C ./libft

				@ echo "$(RED)fclean $(CYAN)$(LIBX) ✔️"
				@make clean -C ./${LIBX}

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"
				@${RM} ${OBJ_DIR}


fclean:			clean
				@ echo "${RED}Deleting ${CYAN}${LIB} ${CLR_RMV}binary ✔️"
				@make fclean -C ./libft

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"
				@${RM} ${NAME}

re:				fclean all

run:			all
				./${NAME} prova.cub

mac:			${OBJS}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${LIB} ${CLR_RMV}..."
				@make -C ./libft
				@echo "${GREEN}${LIB} created[0m ✔️"

				@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(LIBX) ${CLR_RMV}..."
				@make -sC ./${LIBX}
				@echo "$(GREEN)$(LIBX) created[0m ✔️"

				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${MAC_CFLAGS} ${OBJS} ${LIBXFLAGS} ${X11FLAGS} ${LIBFLAGS} -o ${NAME}
				@echo "${GREEN}${NAME} created[0m ✔️"

mem:			all
				export MallocStackLogging=1
				leaks --atExit --list -- ./${NAME} ${ARG}

.PHONY:			all clean fclean re bonus