# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 09:28:30 by wismith           #+#    #+#              #
#    Updated: 2023/06/01 11:10:12 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bt_ircbot

UTILSDIR = ftServerUtils
UTILS = $(UTILSDIR)/ServerUtils.a

SRCS = main \
	bot \
	parser \
	bot_commands \
	parse_config \
	channel \

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CXX = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -g3

$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@printf "\033[A\033[2K\r"

	@tput setaf 2
	@printf "\tGenerating ... "
	@tput init

	$(CXX) $(CPPFLAGS) -c $< -o $@

all : $(NAME)
	@clear

	@tput setaf 1
	@printf "___.    __     .__              ___.           __    \n"
	@printf "\_ |___/  |_   |__|______   ____\_ |__   _____/  |_  \n"
	@printf " | __ \   __\  |  \_  __ \_/ ___\| __ \ /  _ \   __\ \n"
	@printf " | \_\ \  |    |  ||  | \/\  \___| \_\ (  <_> )  |   \n"
	@printf " |___  /__|____|__||__|    \___  >___  /\____/|__|   \n"
	@printf "     \/  /_____/               \/    \/              \n"
	@tput init

	@tput setaf 2
	@printf "\tExecutable Provided\n\n"
	@tput init

	@printf "\tExecute with:\n\n\t\t"
	@printf "./bt_ircbot <"

	@tput setaf 1
	@printf "IPv4"
	@tput init
	
	@printf "> <"

	@tput setaf 1
	@printf "port"
	@tput init
	
	@printf "> <"

	@tput setaf 1
	@printf "password"
	@tput init

	@printf ">\n"

$(NAME) : utility $(OBJ)
	@printf "\t"
	$(CXX) $(CPPFLAGS) $(OBJ) $(UTILS) -o $(NAME)
	@printf "\n"

utility :
	@make -C $(UTILSDIR)

clean :
	@make clean -C $(UTILSDIR)
	rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C $(UTILSDIR)
	rm -rf $(NAME)
	rm -rf bot.log

re : fclean all

.PHONY : all clean fclean re
	