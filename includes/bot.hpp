/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:45:00 by wismith           #+#    #+#             */
/*   Updated: 2023/05/28 18:36:26 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BOT_HPP
# define BOT_HPP

# ifndef MSGFILE
# define MSGFILE std::string("msg.txt")
#endif

# define NPOLL(nfd) (struct pollfd){ .fd = nfd, .events = POLLIN | POLLOUT, .revents = 0 }

# include <poll.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <signal.h>
# include <vector>
# include <map>
# include <string>
# include <fstream>

# include "../ftServerUtils/includes/error.hpp"
#include "../includes/parser.hpp"

# define SEATED 0
# define BTH_BREAK 1
# define PRAR_BREAK 2
# define FINISHED 3

namespace ft
{
	typedef struct s_subj
	{
		int	bth;
		int	prar;
		int	status;

		s_subj (int bth_q, int prar_q);
		~s_subj ();
	}	t_subj;

	class bot
	{
		private :
			int								fd;
			struct pollfd					pfd;
			std::string						buffer;
			ft::parser						pars;
			std::vector<std::string>		msgs;
			std::vector<std::string>		backlog;
			std::vector<std::string>		chan;
			bool							sendingCmd;
			std::string						sendChan;

			std::map<std::string, t_subj *>	subj;

			void							add(std::string &subUser);
			void							remove(std::string &subUser);
			void							status(std::string &subUser);
			void							bth(std::string &subUser);
			void							prar(std::string &subUser);
			void							finish(std::string &subUser);
			void							list();

			void							catch_signals();
			std::string						Read(int fd);
			void							selCmd(std::vector<std::string>);
			std::string						toLower(const std::string);

		public	:
											bot ();
											~bot ();

			void							init (int, const std::string);
			void							Connect(std::string);
			void							run ();

			void							retrieveMsgs();
	};
};

#endif