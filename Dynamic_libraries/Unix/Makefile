NAME		= Ennemy.so

PATH_SRC	= src/

SRC		=	$(PATH_SRC)Ennemy.cpp		\
			$(PATH_SRC)Player.cpp		\
			$(PATH_SRC)APlayer.cpp		\
			$(PATH_SRC)Object.cpp		\

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -std=c++11 -fPIC -W -Wall -Werror -Wextra -I./inc -I./inc/unix

all     :       $(NAME)

$(NAME) :	$(OBJ)
		g++ -shared -fPIC $(OBJ) -o $(NAME)

clean   :
		rm -rf $(OBJ)

fclean  :	clean
		rm -rf $(NAME)

re	:	fclean all
