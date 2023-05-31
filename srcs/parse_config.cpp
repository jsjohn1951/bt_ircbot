/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:10 by wismith           #+#    #+#             */
/*   Updated: 2023/05/31 21:30:53 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

using namespace ft;

void	bot::bot_Break(const std::string &str)
{
	std::stringstream			ss(str);
	std::string					line;
	std::vector<std::string>	vec;

	while (!ss.eof())
	{
		getline(ss, line, ' ');
		vec.push_back(line);
	}

	if (vec.size() == 2)
	{
		if (vec[0] == "BTH")
			this->bthBreaks = std::atoi(vec[1].c_str());
		else if (vec[0] == "PRAR")
			this->prarBreaks = std::atoi(vec[1].c_str());
	}
}

void	bot::bot_NAMES(const std::string &str)
{
	std::stringstream			ss(str);
	std::string					line;
	std::vector<std::string>	vec;

	while (!ss.eof())
	{
		getline(ss, line, ' ');
		vec.push_back(line);
	}

	if (vec.size() == 1)
		this->subj[vec[0]]
			= new t_subj(this->bthBreaks, this->prarBreaks);
}

void	bot::retrieveConfig()
{
	std::ifstream	infile(CONFIG.c_str());
	bool			botBreaks = false;
	bool			botNAMES = false;

	if (!infile.good())
	{
		std::cout << "No file exists!\n";
		return ;
	}

	for (std::string line; getline(infile, line);)
	{
		if (line.size())
		{
			if (line == "BOT BREAKS")
				botBreaks = true;
			else if (line == "BOT BREAKS END")
				botBreaks = false;
			else if (line == "BOT NAMES")
				botNAMES = true;
			else if (line == "BOT NAMES END")
				botNAMES = false;

			if (botBreaks)
				this->bot_Break(line);
			else if (botNAMES)
				this->bot_NAMES(line);
		}
	}
	infile.close();
}
