# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 09:28:30 by wismith           #+#    #+#              #
#    Updated: 2023/05/28 18:50:44 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bt_ircbot

UTILSDIR = ftServerUtils
UTILS = $(UTILSDIR)/ServerUtils.a

SRCS = main \
	bot \
	parser \

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CXX = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@printf "\033[A\033[2K\r"

	@tput setaf 2
	@printf "\tGenerating ... "
	@tput init

	$(CXX) $(CPPFLAGS) -c $< -o $@

all : $(NAME)
	@tput setaf 2
	@printf "\t'bt_ircbot' Executable Generated\n"
	@tput init
	@printf "\tExecute with:\n\n\t\t"
	@printf "./bt_ircbot <IPv4> <port> <password>\n"

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

re : fclean all

.PHONY : all clean fclean re
	