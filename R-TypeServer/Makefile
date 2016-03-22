##
## Makefile for Makefile in /home/chauch_a/depotBabel/depot/BabelServer
## 
## Made by CHAUCHET Alan
## Login   <chauch_a@epitech.net>
## 
## Started on  Sat Nov  8 12:13:52 2014 CHAUCHET Alan
## Last update Sat Dec 20 13:38:29 2014 abgral_f
##

NAME		= RTypeServer

PATH_SRC	= src/

SRC		= $(PATH_SRC)main.cpp				\
		  $(PATH_SRC)Bonus.cpp				\
		  $(PATH_SRC)Game.cpp				\
		  $(PATH_SRC)Object.cpp				\
		  $(PATH_SRC)Missile.cpp			\
		  $(PATH_SRC)Ennemy.cpp				\
		  $(PATH_SRC)Player.cpp				\
		  $(PATH_SRC)APlayer.cpp			\
		  $(PATH_SRC)ServerSend.cpp			\
		  $(PATH_SRC)ClientInfo.cpp			\
		  $(PATH_SRC)ASocket.cpp			\
		  $(PATH_SRC)UnixSocket.cpp			\
		  $(PATH_SRC)Select.cpp				\
		  $(PATH_SRC)Server.cpp				\
		  $(PATH_SRC)UnixThread.cpp                     \

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	= -std=c++11 -W -Wall -Werror -Wextra -I./inc -I./inc/unix

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -lpthread
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PATH_BIN)$(NAME)

re: fclean all

debug: CXXFLAGS += -g

debug: re
