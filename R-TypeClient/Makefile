##
## Makefile for Makefile in /home/abgral_f/dev/R-Type/R-TypeClient
## 
## Made by abgral_f
## Login   <abgral_f@epitech.net>
## 
## Started on  Sun Nov 16 16:50:07 2014 abgral_f
## Last update Sat Dec 20 13:38:16 2014 abgral_f
##

NAME            = RTypeClient

PATH_SRC        = src/

SRC             = $(PATH_SRC)main.cpp                           \
		  $(PATH_SRC)Bonus.cpp                           \
		  $(PATH_SRC)Game.cpp                           \
		  $(PATH_SRC)Menus.cpp                           \
		  $(PATH_SRC)RoomNameWindow.cpp                 \
		  $(PATH_SRC)PortAndIpWindow.cpp                \
		  $(PATH_SRC)PopupGeneration.cpp                \
		  $(PATH_SRC)PlayerListWindow.cpp               \
		  $(PATH_SRC)NameWindow.cpp                     \
		  $(PATH_SRC)MainMenuWindow.cpp                 \
		  $(PATH_SRC)JoinRoomWindow.cpp                 \
		  $(PATH_SRC)ChooseMapWindow.cpp                \
		  $(PATH_SRC)Object.cpp                         \
		  $(PATH_SRC)Gui.cpp                            \
		  $(PATH_SRC)Missile.cpp                        \
		  $(PATH_SRC)Ennemy.cpp                         \
                  $(PATH_SRC)Player.cpp                         \
                  $(PATH_SRC)APlayer.cpp                        \
		  $(PATH_SRC)Select.cpp				\
		  $(PATH_SRC)ClientSend.cpp			\
		  $(PATH_SRC)Client.cpp				\
		  $(PATH_SRC)ASocket.cpp                        \
                  $(PATH_SRC)UnixSocket.cpp                     \
		  $(PATH_SRC)UnixThread.cpp                     \

OBJ             = $(SRC:.cpp=.o)

CXXFLAGS        = -std=c++11 -W -Wall -Werror -Wextra -I./inc -I./inc/unix -I../lib/SFML-2.1_linux/include

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -lpthread -L../lib/SFML-2.1_linux/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PATH_BIN)$(NAME)

re: fclean all

debug: CXXFLAGS += -g

debug: re
