/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_commands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:31:18 by wismith           #+#    #+#             */
/*   Updated: 2023/05/31 21:54:13 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

using namespace ft;

//! ------- COMMANDS --------- !//

void	bot::add(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) != this->subj.end())
		return this->channels[chan]->addPrivMsg(subUser + " IS ALREADY A MEMBER!");
	this->channels[chan]->addPrivMsg("ADDING USER : " + subUser);
	this->subj[subUser] = new t_subj(this->bthBreaks, this->prarBreaks);
	this->log << subUser + " added to bot!";
}

void	bot::remove(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");
	this->channels[chan]->addPrivMsg("REMOVING USER : " + subUser);
	delete this->subj[subUser];
	this->subj.erase(this->subj.find(subUser));
	this->log << subUser + " removed from bot!";
}

void	bot::status(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");

	t_subj	*sub = this->subj[subUser];
	std::string	bth;
	std::string prar;

	bth << sub->bth;
	prar << sub->prar;

	this->channels[chan]->addPrivMsg(subUser
								+ " status: [ "
								+ (sub->status == SEATED ?
								"SEATED" :
								sub->status == BTH_BREAK ?
								"WENT BATHROOM" :
								sub->status == PRAR_BREAK ?
								"WENT PRAYER BREAK" :
								sub->status == FINISHED ?
								"COMPLETED EXAM" :
								"NO CLUE???")
								+ " ]");
	this->channels[chan]->addPrivMsg("BTH BREAKS LEFT : [ "
								+ bth
								+ " ]");
	this->channels[chan]->addPrivMsg("PRAR BREAKS LEFT : [ "
								+ prar
								+ " ]");
}

void	bot::bth(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");

	t_subj	*sub = this->subj[subUser];
	if (sub->status == FINISHED)
	{
		this->log << subUser + " ALREADY FINISHED!";
		return this->channels[chan]->addPrivMsg(subUser + " ALREADY FINISHED!");
	}
	if (!sub->bth)
	{
		this->log << subUser + " : HAS NO MORE BATHROOM BREAKS LEFT!";
		return this->channels[chan]->addPrivMsg(subUser + " HAS NO MORE BATHROOM BREAKS LEFT!");
	}
	this->channels[chan]->addPrivMsg(subUser + " status set : [ WENT BATHROOM ]");
	sub->bth--;
	sub->status = BTH_BREAK;
	this->log << subUser + " : bathroom break";
}

void	bot::prar(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");

	t_subj	*sub = this->subj[subUser];
	if (sub->status == FINISHED)
	{
		this->log << subUser + " ALREADY FINISHED!";
		return this->channels[chan]->addPrivMsg(subUser + " ALREADY FINISHED!");
	}
	if (!sub->prar)
	{
		this->log << subUser + " : HAS NO MORE PRAYER BREAKS LEFT!";
		return this->channels[chan]->addPrivMsg(subUser + " HAS NO MORE PRAYER BREAKS LEFT!");
	}
	this->channels[chan]->addPrivMsg(subUser + " status set : [ WENT PRAYER BREAK ]");
	sub->prar--;
	sub->status = PRAR_BREAK;
	this->log << subUser + " : prayer break";
}

void	bot::finish(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");
	
	t_subj	*sub = this->subj[subUser];
	if (sub->status == FINISHED)
	{
		this->log << subUser + " ALREADY FINISHED!";
		return this->channels[chan]->addPrivMsg(subUser + " ALREADY FINISHED!");
	}
	this->channels[chan]->addPrivMsg(subUser + " status set : [ FINISHED ]");
	sub->status = FINISHED;
	this->log << subUser + " : finished exam";
}

void	bot::list( const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	std::map<std::string, t_subj *>::iterator	it;

	for (it = this->subj.begin(); it != this->subj.end(); it++)
		this->channels[chan]->addPrivMsg(" [ " + it->first + " ]");
}

void	bot::back(std::string &subUser, const std::string &chan)
{
	if (this->channels.find(chan) == this->channels.end())
		return ;
	if (this->subj.find(subUser) == this->subj.end())
		return this->channels[chan]->addPrivMsg("NO INSTANCE OF \"" + subUser + "\" EXISTS!");

	t_subj	*sub = this->subj[subUser];
	if (sub->status == FINISHED)
	{
		this->log << subUser + " ALREADY FINISHED!";
		return this->channels[chan]->addPrivMsg(subUser + " ALREADY FINISHED!");
	}

	this->channels[chan]->addPrivMsg(subUser + " status set : [ SEATED ]");
	sub->status = SEATED;
	this->log << subUser + " status set : [ SEATED ]";
}
