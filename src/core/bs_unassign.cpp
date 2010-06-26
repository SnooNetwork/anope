/* BotServ core functions
 *
 * (C) 2003-2010 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for further details.
 *
 * Based on the original code of Epona by Lara.
 * Based on the original code of Services by Andy Church.
 */

/*************************************************************************/

#include "module.h"

class CommandBSUnassign : public Command
{
 public:
	CommandBSUnassign() : Command("UNASSIGN", 1, 1)
	{
	}

	CommandReturn Execute(User *u, const std::vector<ci::string> &params)
	{
		const char *chan = params[0].c_str();
		ChannelInfo *ci = cs_findchan(chan);
		ChannelMode *cm = ModeManager::FindChannelModeByName(CMODE_PERM);

		if (readonly)
			notice_lang(Config.s_BotServ, u, BOT_ASSIGN_READONLY);
		else if (!u->Account()->HasPriv("botserv/administration")  && !check_access(u, ci, CA_ASSIGN))
			notice_lang(Config.s_BotServ, u, ACCESS_DENIED);
		else if (!ci->bi)
			notice_help(Config.s_BotServ, u, BOT_NOT_ASSIGNED);
		else if (ci->HasFlag(CI_PERSIST) && !cm)
			notice_help(Config.s_BotServ, u, BOT_UNASSIGN_PERSISTANT_CHAN);
		else
		{
			ci->bi->UnAssign(u, ci);
			notice_lang(Config.s_BotServ, u, BOT_UNASSIGN_UNASSIGNED, ci->name.c_str());
		}
		return MOD_CONT;
	}

	bool OnHelp(User *u, const ci::string &subcommand)
	{
		notice_help(Config.s_BotServ, u, BOT_HELP_UNASSIGN);
		return true;
	}

	void OnSyntaxError(User *u, const ci::string &subcommand)
	{
		syntax_error(Config.s_BotServ, u, "UNASSIGN", BOT_UNASSIGN_SYNTAX);
	}

	void OnServHelp(User *u)
	{
		notice_lang(Config.s_BotServ, u, BOT_HELP_CMD_UNASSIGN);
	}
};

class BSUnassign : public Module
{
 public:
	BSUnassign(const std::string &modname, const std::string &creator) : Module(modname, creator)
	{
		this->SetAuthor("Anope");
		this->SetType(CORE);
		this->AddCommand(BotServ, new CommandBSUnassign);
	}
};

MODULE_INIT(BSUnassign)
