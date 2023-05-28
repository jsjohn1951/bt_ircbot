/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:46:59 by wismith           #+#    #+#             */
/*   Updated: 2023/05/28 17:52:14 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

/** @brief bt_ircbot (break time irc bot) executable
**		Execute as follows : ./bt_ircbot <ip> <port> <password>
**
**			Example :
**				./bt_ircbot 127.0.0.1 6667 pass
**
**		Will not connect if incorrect ip or port is given.
**		Correct password must be provided for authentication.
*/

/** @brief use
**		Execute server, then followed by the bot.
**		Server and bot should share the same <ip>, <port>, and <password>.
**
**		Connect to server using irssi (specifically!!! With other behavior may be undefined).
**		Create a new channel with /join command, or join a default channel ( #btBot ).
**			When creating a new channel use command: /invite bot
**
**				Example :
**					/join #btBot
**				Or :
**					/join #chan
**					/invite bot
**
**			Once the bot has joined a channel you can perform following commands:
**				ADD		<login>		//! Adds a new student/pisciner to bot session
**				REMOVE	<login>		//! Removes a student/pisciner from bot session
**				REVIEW	<login>		//! See last status, and quantity of breaks already used
**				BTH		<login>		//! Sets last status of student/pisciner if break is available, else sends "break unavailable"
**				PRAR	<login>		//! Sets last status of student/pisciner if break is available, else sends "break unavailable"
**				FINISH	<login>		//! Sets status of student/pisciner to finished exam
**				LIST				//! Lists all students/pisciners and status
**				HELP				//! Displays available commands
**				
*/

int	main(int argc, char **argv)
{
	int			port;

	if (argc != 4)
	{
		std::cerr << "Incorrect num arguments" << std::endl;
		return (-1);
	}

	ft::bot	bot;
	error	err;

	try{
		port = err.port(argv[2]);
	} catch (const std::exception &e)
	{
		std::cerr << e.what();
		return (-1);
	}

	bot.init(port, argv[1]);
	bot.Connect(argv[3]);
	bot.retrieveMsgs();
	bot.run();
}
