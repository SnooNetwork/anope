/* Prototypes and external variable declarations.
 *
 * (C) 2003-2010 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for furhter details.
 *
 * Based on the original code of Epona by Lara.
 * Based on the original code of Services by Andy Church.
 */

#ifndef EXTERN_H
#define EXTERN_H

#define E extern CoreExport
#define EI extern DllExport

#include "hashcomp.h"

E void ModuleRunTimeDirCleanUp();

/* IRC Variables */

E IRCDVar *ircd;
E int UseTSMODE; /* hack to get around bahamut clones that don't send TSMODE */
E IRCDProto *ircdproto;

/**** actions.c ****/

E void kill_user(const std::string &source, const std::string &user, const std::string &reason);
E bool bad_password(User *u);
E void common_unban(ChannelInfo *ci, const std::string &nick);

E BotInfo *BotServ;
E BotInfo *ChanServ;
E BotInfo *Global;
E BotInfo *HostServ;
E BotInfo *MemoServ;
E BotInfo *NickServ;
E BotInfo *OperServ;

/**** botserv.c ****/

E void get_botserv_stats(long *nrec, long *memuse);
E void bs_init();
E void botserv(User *u, BotInfo *bi, const std::string &buf);
E void botchanmsgs(User *u, ChannelInfo *ci, const std::string &buf);
E BotInfo *findbot(const char *nick);
E BotInfo *findbot(const std::string &nick);
E BotInfo *findbot(const ci::string &nick);

/** Finds a pseudoclient, given a UID. Useful for TS6 protocol modules.
 * @param uid The UID to search for
 * @return The pseudoclient structure, or NULL if one could not be found
 */
E void bot_join(ChannelInfo *ci);
E char *normalizeBuffer(const char *);

E void bot_raw_ban(User * requester, ChannelInfo *ci, char *nick, const char *reason);
E void bot_raw_kick(User * requester, ChannelInfo *ci, char *nick, const char *reason);
E void bot_raw_mode(User * requester, ChannelInfo *ci, const char *mode, char *nick);

/**** channels.c ****/

E void get_channel_stats(long *nrec, long *memuse);

E Channel *findchan(const char *chan);
E Channel *findchan(const std::string &chan);
E Channel *findchan(const ci::string &chan);

E void ChanSetInternalModes(Channel *c, int ac, const char **av);

E User *nc_on_chan(Channel *c, NickCore *nc);

E char *chan_get_modes(Channel *chan, int complete, int plus);

E int get_access_level(ChannelInfo *ci, NickAlias *na);
E int get_access_level(ChannelInfo *ci, NickCore *nc);
E const char *get_xop_level(int level);

E void do_cmode(const char *source, int ac, const char **av);
E void do_join(const char *source, int ac, const char **av);
E void do_kick(const std::string &source, int ac, const char **av);
E void do_part(const char *source, int ac, const char **av);
E void do_topic(const char *source, int ac, const char **av);
E void MassChannelModes(BotInfo *bi, const std::string &modes);

E void chan_set_correct_modes(User *user, Channel *c, int give_modes);
E void restore_unsynced_topics();

E Entry *entry_create(char *mask);
E Entry *entry_add(EList *list, const char *mask);
E void entry_delete(EList *list, Entry *e);
E EList *list_create();
E int entry_match(Entry *e, const ci::string &nick, const ci::string &user, const ci::string &host, uint32 ip);
E int entry_match_mask(Entry *e, const char *mask, uint32 ip);
E Entry *elist_match(EList *list, const char *nick, const char *user, const char *host, uint32 ip);
E Entry *elist_match_mask(EList *list, const char *mask, uint32 ip);
E Entry *elist_match_user(EList *list, User *u);
E Entry *elist_find_mask(EList *list, const char *mask);
E long get_memuse(EList *list);

#define whosends(ci) ((!(ci) || !((ci)->botflags.HasFlag(BS_SYMBIOSIS)) || !(ci)->bi || !(ci)->c || (ci)->c->users.size() < Config.BSMinUsers) ? findbot(Config.s_ChanServ) : (ci)->bi)

/**** chanserv.c ****/

E LevelInfo levelinfo[];

E void get_chanserv_stats(long *nrec, long *memuse);

E void reset_levels(ChannelInfo *ci);
E void cs_init();
E void chanserv(User *u, const std::string &buf);
E void expire_chans();
E void cs_remove_nick(const NickCore *nc);

E void check_modes(Channel *c);
E int check_valid_admin(User *user, Channel *chan, int servermode);
E int check_valid_op(User *user, Channel *chan, int servermode);
E void record_topic(const char *chan);
E void restore_topic(const char *chan);
E int check_topiclock(Channel *c, time_t topic_time);

E ChannelInfo *cs_findchan(const char *chan);
E ChannelInfo *cs_findchan(const std::string &chan);
E ChannelInfo *cs_findchan(const ci::string &chan);
E int check_access(User *user, ChannelInfo *ci, int what);
E bool IsFounder(User *user, ChannelInfo *ci);
E int get_access(User *user, ChannelInfo *ci);
E void update_cs_lastseen(User *user, ChannelInfo *ci);
E int get_idealban(ChannelInfo *ci, User *u, char *ret, int retlen);
E AutoKick *is_stuck(ChannelInfo *ci, const char *mask);
E void stick_mask(ChannelInfo *ci, AutoKick *akick);
E void stick_all(ChannelInfo *ci);

E int levelinfo_maxwidth;
E char *get_mlock_modes(ChannelInfo *ci, int complete);

/**** compat.c ****/

#if !HAVE_STRICMP && !HAVE_STRCASECMP
E int stricmp(const char *s1, const char *s2);
E int strnicmp(const char *s1, const char *s2, size_t len);
#endif
#ifdef _WIN32
char *sockstrerror(int error);
#endif

/**** config.c ****/

E ci::string services_conf;
E ServerConfig Config;
E int read_config(int reload);

/* hostserv.c */
E void do_on_id(User *u);
E void hostserv(User *u, const std::string &buf);
E void HostServSyncVhosts(NickAlias *na);

/**** encrypt.c ****/
E int enc_encrypt(const std::string &src, std::string &dest);
E int enc_encrypt_in_place(std::string &buf);
E int enc_decrypt(const std::string &src, std::string &dest);
E int enc_check_password(std::string &plaintext, std::string &password);

/**** hostserv.c  ****/
E void get_hostserv_stats(long *nrec, long *memuse);
E void hostserv_init();

/**** init.c ****/

E void introduce_user(const std::string &user);
E bool GetCommandLineArgument(const std::string &name, char shortname = 0);
E bool GetCommandLineArgument(const std::string &name, char shortname, std::string &param);
E int init_primary(int ac, char **av);
E int init_secondary(int ac, char **av);
E Uplink *uplink_server;

/**** ircd.c ****/
E void pmodule_ircd_proto(IRCDProto *);
E void pmodule_ircd_var(IRCDVar *ircdvar);
E void pmodule_ircd_version(const char *version);
E void pmodule_ircd_useTSMode(int use);

/**** language.c ****/

E char **langtexts[NUM_LANGS];
E char *langnames[NUM_LANGS];
E int langlist[NUM_LANGS];

E void lang_init();
E int strftime_lang(char *buf, int size, User *u, int format, struct tm *tm);
E void syntax_error(char *service, User *u, const char *command, int msgnum);
E const char *getstring(NickAlias *na, int index);
E const char *getstring(NickCore *nc, int index);
E const char *getstring(User *nc, int index);
E const char *getstring(int index);

/**** log.c ****/

E int open_log();
E void close_log();
E void log_perror(const char *fmt, ...) FORMAT(printf,1,2);
E void fatal(const char *fmt, ...) FORMAT(printf,1,2);
E void fatal_perror(const char *fmt, ...) FORMAT(printf,1,2);

/**** main.c ****/

E char *version_protocol;

E std::string services_dir;
E std::string log_filename;
E int debug;
E int readonly;
E bool LogChan;
E int nofork;
E int forceload;
E int nothird;
E int noexpire;
E int protocoldebug;

E int is44;
E int quitting;
E int shutting_down;
E const char *quitmsg;
E int save_data;
E int got_alarm;
E time_t start_time;

E Socket *UplinkSock;

E void save_databases();
E void expire_all();
E void sighandler(int signum);
E void do_restart_services();

/**** memory.c ****/

E void *smalloc(long size);
E void *scalloc(long elsize, long els);
E void *srealloc(void *oldptr, long newsize);
E char *sstrdup(const char *s);

/**** memoserv.c ****/

E void ms_init();
E void memoserv(User *u, const std::string &buf);
E void rsend_notify(User *u, Memo *m, const char *chan);
E void check_memos(User *u);
E MemoInfo *getmemoinfo(const char *name, int *ischan, int *isforbid);
E void memo_send(User *u, const char *name, const char *text, int z);
E int delmemo(MemoInfo *mi, int num);

/**** messages.c ****/

E int m_nickcoll(const char *user);
E int m_away(const char *source, const char *msg);
E int m_kill(const std::string &nick, const char *msg);
E int m_motd(const char *source);
E int m_privmsg(const std::string &source, const std::string &receiver, const std::string &message);
E int m_stats(const char *source, int ac, const char **av);
E int m_whois(const char *source, const char *who);
E int m_time(const char *source, int ac, const char **av);
E int m_version(const char *source, int ac, const char **av);

/**** misc.c ****/

E bool IsFile(const std::string &filename);
E int toupper(char);
E int tolower(char);
E char *strscpy(char *d, const char *s, size_t len);
#ifndef HAVE_STRLCPY
E size_t strlcpy(char *, const char *, size_t);
#endif
#ifndef HAVE_STRLCAT
E size_t strlcat(char *, const char *, size_t);
#endif
E const char *stristr(const char *s1, const char *s2);
E char *strnrepl(char *s, int32 size, const char *old, const char *nstr);
E const char *merge_args(int argc, char **argv);
E const char *merge_args(int argc, const char **argv);

E time_t dotime(const char *s);
E const char *duration(NickCore *nc, char *buf, int bufsize, time_t seconds);
E const char *expire_left(NickCore *nc, char *buf, int len, time_t expires);
E int doValidHost(const char *host, int type);

E int isValidHost(const char *host, int type);
E int isvalidchar(const char c);

E char *myStrGetToken(const char *str, const char dilim, int token_number);
E char *myStrGetOnlyToken(const char *str, const char dilim, int token_number);
E char *myStrSubString(const char *src, int start, int end);
E char *myStrGetTokenRemainder(const char *str, const char dilim, int token_number);
E char *stripModePrefix(const char *str);
E int myNumToken(const char *str, const char dilim);
E void doCleanBuffer(char *str);
E void EnforceQlinedNick(const std::string &nick, const char *killer);
E int nickIsServices(const char *nick, int bot);

E void add_entropy_userkeys();
E void rand_init();
E unsigned char getrandom8();
E uint16 getrandom16();
E uint32 getrandom32();

E char *str_signed(unsigned char *str);

E void ntoa(struct in_addr addr, char *ipaddr, int len);

E std::list<std::string> BuildStringList(const std::string &);
E std::list<ci::string> BuildStringList(const ci::string &);
E std::vector<std::string> BuildStringVector(const std::string &);

E void binary_to_hex(unsigned char *bin, char *hex, int length);

E uint32 cidr_to_netmask(uint16 cidr);
E uint16 netmask_to_cidr(uint32 mask);

E int str_is_wildcard(const char *str);
E int str_is_pure_wildcard(const char *str);

E uint32 str_is_ip(char *str);
E int str_is_cidr(char *str, uint32 * ip, uint32 * mask, char **host);

/**** modes.cpp ****/
/* Number of generic modes we support */
E unsigned GenericChannelModes, GenericUserModes;
E Flags<ChannelModeName> DefMLockOn;
E Flags<ChannelModeName> DefMLockOff;
E std::map<ChannelModeName, std::string> DefMLockParams;
/* Modes to set on bots when they join the channel */
E std::list<ChannelModeStatus *> BotModes;
E void SetDefaultMLock();

/**** nickserv.c ****/

E NickRequest *findrequestnick(const char *nick);
E NickRequest *findrequestnick(const std::string &nick);
E NickRequest *findrequestnick(const ci::string &nick);
E void get_aliases_stats(long *nrec, long *memuse);
E void get_core_stats(long *nrec, long *memuse);
E void change_core_display(NickCore *nc);
E void change_core_display(NickCore *nc, const char *newdisplay);
E int do_setmodes(User *u);

E void ns_init();
E void nickserv(User *u, const std::string &buf);
E int validate_user(User *u);
E void expire_nicks();
E void expire_requests();
E NickAlias *findnick(const char *nick);
E NickAlias *findnick(const std::string &nick);
E NickAlias *findnick(const ci::string &nick);
E NickCore *findcore(const char *nick);
E NickCore *findcore(const std::string &nick);
E NickCore *findcore(const ci::string &nick);
E bool is_on_access(User *u, NickCore *nc);

/**** process.c ****/

E int allow_ignore;
E IgnoreData *ignore;

E void add_ignore(const char *nick, time_t delta);
E IgnoreData *get_ignore(const char *nick);
E int delete_ignore(const char *nick);
E int clear_ignores();

E int split_buf(char *buf, const char ***argv, int colon_special);
E void process(const std::string &buf);

/**** send.c ****/

E void send_cmd(const char *source, const char *fmt, ...) FORMAT(printf,2,3);
E void send_cmd(const std::string &source, const char *fmt, ...) FORMAT(printf,2,3);

E void notice_server(char *source, Server * s, const char *fmt, ...) FORMAT(printf,3,4);

E void notice_list(const char *source, const char *dest, char **text); // MARK_DEPRECATED;
E void notice_lang(const std::string &source, User *dest, int message, ...); // MARK_DEPRECATED;
E void notice_help(const char *source, User *dest, int message, ...); // MARK_DEPRECATED;

/**** sessions.c ****/

E Exception *exceptions;
E int16 nexceptions;

E void get_session_stats(long *nrec, long *memuse);
E void get_exception_stats(long *nrec, long *memuse);

E int add_session(const char *nick, const char *host, char *hostip);
E void del_session(const char *host);

E void expire_exceptions();

E Session *findsession(const std::string &host);

E Exception *find_host_exception(const char *host);
E Exception *find_hostip_exception(const char *host, const char *hostip);
E int exception_add(User *u, const char *mask, const int limit, const char *reason, const char *who, const time_t expires);

/**** sockets.cpp ****/

E SocketEngine socketEngine;
E int32 TotalRead;
E int32 TotalWritten;

/**** users.c ****/

E int32 opcnt;
E uint32 maxusercnt, usercnt;
E time_t maxusertime;

E void get_user_stats(long *nusers, long *memuse);

E User *finduser(const char *nick);
E User *finduser(const std::string &nick);
E User *finduser(const ci::string &nick);

E Server *findserver_uid(Server *s, const char *name);
E char *TS6SID;

E User *do_nick(const char *source, const char *nick, const char *username, const char *host, const char *server, const char *realname, time_t ts, uint32 ip, const char *vhost, const char *uid);

E void do_umode(const char *source, int ac, const char **av);
E void do_quit(const char *source, int ac, const char **av);
E void do_kill(const std::string &source, const std::string &reason);

E int is_oper(User *user);

E int is_excepted(ChannelInfo *ci, User * user);
E int is_excepted_mask(ChannelInfo *ci, const char *mask);

E int match_usermask(const char *mask, User *user);
E char *create_mask(User *u);

E void UserSetInternalModes(User *user, int ac, const char **av);

/******************************************************************************/

E const char *base64enc(long i);
E long base64dec(const char *b64);
E long base64dects(const char *ts);
E int b64_encode(const char *src, size_t srclength, char *target, size_t targsize);
E int b64_decode(const char *src, char *target, size_t targsize);
E const char *encode_ip(unsigned char *ip);
E int decode_ip(const char *buf);

E char *host_resolve(char *host);

#ifdef _WIN32
E char *GetWindowsVersion() ;
E int SupportedWindowsVersion();
#endif

#endif /* EXTERN_H */
