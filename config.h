/************************************************************************
 *   IRC - Internet Relay Chat, support/config.h
 *   Copyright (C) 1990 Jarkko Oikarinen
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*  Type of host. Keep them undefined, unless you're using one of these OS.
 */

#undef	MIPS			/* MIPS Unix */
#undef 	SVR3			/* SVR3 stuff - being worked on where poss. */
#undef	ESIX			/* ESIX */

/* Do these work? I dunno... */

#undef	VMS			/* Should work for IRC client, not server */
#undef	MAIL50			/* If you're running VMS 5.0 */
#undef	PCS			/* PCS Cadmus MUNIX, use with BSD flag! */

/*
 * NOTE: On some systems, valloc() causes many problems.
 */
#undef	VALLOC			/* Define this if you have valloc(3) */

#ifdef APOLLO
#define	RESTARTING_SYSTEMCALLS
#endif 				  /* read/write are restarted after signals
				     defining this 1, gets siginterrupt call
				     compiled, which attempts to remove this
				     behaviour (apollo sr10.1/bsd4.3 needs
				     this) */

/*
 * Pathnames and defaults of irc system's support files. Please note that
 * these are only the recommened names and paths. Change as needed.
 * You must define these to something, even if you don't really want them.
 */
/* This is either full path or file within "server_bin_dir" (see Makefile) */
#define	SPATH	"ircd"		/* daemon path */
/* These are either full paths or files within "ircd_dir" (see Makefile) */
#define	CPATH	"ircd.conf"	/* configuration file */
#define	MPATH	"ircd.motd"	/* motd file */
#define	LPATH	"ircd.log"	/* debugging log */
#define	PPATH	"ircd.pid"	/* PID file */
#define	TPATH	"ircd.tune"	/* tuning file */

/*
 * If you don't want the server to keep reading the MOTD file from the disk,
 * define CACHED_MOTD.  The server will store the MOTD in memory, and only
 * read it again from the disk when rehashing if the file has changed.
 */
#define	CACHED_MOTD

/*
 * Define these filenames to maintain a list of persons who log
 * into this server. Logging will stop when the file does not exist.
 * Logging will be disable also if you do not define this.
 *	FNAME_USERLOG just logs user connections,
 *	FNAME_OPERLOG logs every successful use of /oper.
 *	FNAME_CONNLOG logs every user rejected or uncomplete connection
 * These are either full paths or files within "ircd_dir" (see Makefile).
 */
#define FNAME_USERLOG "users" /* */
#define FNAME_OPERLOG "opers" /* */
#define FNAME_CONNLOG "rejects" /* */

/* CHROOTDIR
 *
 * Define for value added security if you are a rooter.
 *
 * All files you access must be in the directory you define as IRCDDIR.
 * (This may effect the PATH locations above, though you can symlink it)
 *
 * You may want to define IRC_UID and IRC_GID
 */
#undef CHROOTDIR

/* ENABLE_SUMMON
 *
 * The SUMMON command requires the ircd to be run as group tty in order
 * to work properly in many cases.  If you are on a machine where it
 * won't work, or simply don't want local users to be summoned, undefine
 * this.
 */
#undef	ENABLE_SUMMON	/* local summon */
#undef	ENABLE_USERS	/* enables local /users (same as who/finger output) */

/* SHOW_INVISIBLE_LUSERS
 *
 * As defined this will show the correct invisible count for anyone who does
 * LUSERS on your server. On a large net this doesnt mean much, but on a
 * small net it might be an advantage to undefine it.
 */
#define	SHOW_INVISIBLE_LUSERS

/* NO_DEFAULT_INVISIBLE
 *
 * When defined, your users will not automatically be attributed with user
 * mode "i" (i == invisible). Invisibility means people dont showup in
 * WHO or NAMES unless they are on the same channel as you.
 */
#undef	NO_DEFAULT_INVISIBLE

/* OPER_KILL
 *
 * If you dont believe operators should be allowed to use the /KILL command
 * or believe it is uncessary for them to use it, then leave OPER_KILL
 * undefined. This will not affect other operators or servers issuing KILL
 * commands however.  OPER_REHASH and OPER_RESTART allow operators to
 * issue the REHASH and RESTART commands when connected to your server.
 * Left undefined they increase the security of your server from wayward
 * operators and accidents.  Defining OPER_REMOTE removes the restriction
 * that O-lines only become fully effective for people on the 'same network'
 * as the server.  Undefined, it increases the secrity of the server by
 * placing restrictions on where people can use operator powers from.
 * The 'LOCOP_' #defines are for making the respective commands available
 * to 'local' operators.
 */
#define	OPER_KILL
#define	OPER_REHASH
#undef	OPER_RESTART
#undef	OPER_DIE
#undef	OPER_REMOTE
#define	LOCOP_REHASH
#undef	LOCOP_RESTART
#undef	LOCOP_DIE

/*
 * Maximum number of network connections your server will allow.  This should
 * never exceed max. number of open file descrpitors and wont increase this.
 * Should remain LOW as possible. Most sites will usually have under 50 or so
 * connections.
 * if you have a lot of server connections, it may be worth splitting the load
 * over 2 or more servers.
 * 1 server = 1 connection, 1 user = 1 connection.
 * This should be at *least* 4: 2 listen ports (1 tcp, 1 udp)
 *				1 dns port, 1 client
 */
#define MAXCONNECTIONS	200

/* MAXIMUM LINKS
 *
 * This define is useful for leaf nodes and gateways. It keeps you from
 * connecting to too many places. It works by keeping you from
 * connecting to more than "n" nodes which you have C:blah::blah:6667
 * lines for.
 *
 * Note that any number of nodes can still connect to you. This only
 * limits the number that you actively reach out to connect to.
 *
 * Leaf nodes are nodes which are on the edge of the tree. If you want
 * to have a backup link, then sometimes you end up connected to both
 * your primary and backup, routing traffic between them. To prevent
 * this, #define MAXIMUM_LINKS 1 and set up both primary and
 * secondary with C:blah::blah:6667 lines. THEY SHOULD NOT TRY TO
 * CONNECT TO YOU, YOU SHOULD CONNECT TO THEM.
 *
 * Gateways such as the server which connects Australia to the US can
 * do a similar thing. Put the American nodes you want to connect to
 * in with C:blah::blah:6667 lines, and the Australian nodes with
 * C:blah::blah lines. Have the Americans put you in with C:blah::blah
 * lines. Then you will only connect to one of the Americans.
 *
 * This value is only used if you don't have server classes defined, and
 * a server is in class 0 (the default class if none is set).
 *
 */
#define MAXIMUM_LINKS 1

/*
 * A pure non-routing leaf server can undefine HUB for best performance.
 * If your server is running as a a HUB Server then define this.
 * A HUB Server has many servers connect to it at the same as opposed
 * to a leaf which just has 1 server (typically the uplink). Define this
 * correctly for performance reasons. If defined, value of 0 creates
 * biggest load on cpu, and bigger values decrease the cpu load on price
 * of user-friendlyness.
 *
 * The higher value (in seconds), the less often users will be polled (giving
 * a greater precedence to traffic to and from servers).
 */
/* #define	HUB	1 */

#ifdef HUB
/*
 * MAXSERVERS is the maximum number of servers that will be linked
 * to your server at the same time.  This number is not a limit,
 * it is used to allocate memory when ircd is started.
 */
# define	MAXSERVERS 3
#else
# define	MAXSERVERS 1
#endif

/* R_LINES:  The conf file now allows the existence of R lines, or
 * restrict lines.  These allow more freedom in the ability to restrict
 * who is to sign on and when.  What the R line does is call an outside
 * program which returns a reply indicating whether to let the person on.
 * Because there is another program involved, Delays and overhead could
 * result. It is for this reason that there is a line in config.h to
 * decide whether it is something you want or need. -Hoppie
 *
 * The default is no R_LINES as most people probably don't need it. --Jto
 */
#define	R_LINES

#ifdef	R_LINES
/* Also, even if you have R lines defined, you might not want them to be 
   checked everywhere, since it could cost lots of time and delay.  Therefore, 
   The following two options are also offered:  R_LINES_REHASH rechecks for 
   R lines after a rehash, and R_LINES_OFTEN, which rechecks it as often
   as it does K lines.  Note that R_LINES_OFTEN is *very* likely to cause 
   a resource drain, use at your own risk.  R_LINES_REHASH shouldn't be too
   bad, assuming the programs are fairly short. */
#define R_LINES_REHASH
#define R_LINES_OFTEN
#endif

/*
 * NOTE: defining CMDLINE_CONFIG and installing ircd SUID or SGID is a MAJOR
 *       security problem - they can use the "-f" option to read any files
 *       that the 'new' access lets them. Note also that defining this is
 *       a major security hole if your ircd goes down and some other user
 *       starts up the server with a new conf file that has some extra
 *       O-lines. So don't use this unless you're debugging.
 */
#undef	CMDLINE_CONFIG /* allow conf-file to be specified on command line */

/*
 * To use m4 as a preprocessor on the ircd.conf file, define M4_PREPROC.
 * The server will then call m4 each time it reads the ircd.conf file,
 * reading m4 output as the server's ircd.conf file.
 */
#undef	M4_PREPROC

/*
 * If you wish to have the server send 'vital' messages about server
 * through syslog, define USE_SYSLOG. Only system errors and events critical
 * to the server are logged although if this is defined with FNAME_USERLOG,
 * syslog() is used instead of the above file. It is not recommended that
 * this option is used unless you tell the system administrator beforehand
 * and obtain their permission to send messages to the system log files.
 */
#undef	USE_SYSLOG

#ifdef	USE_SYSLOG
/*
 * If you use syslog above, you may want to turn some (none) of the
 * spurious log messages for KILL/SQUIT off.
 */
#undef	SYSLOG_KILL	/* log all operator kills to syslog */
#undef	SYSLOG_SQUIT	/* log all remote squits for all servers to syslog */
#undef	SYSLOG_CONNECT	/* log remote connect messages for other all servs */
#undef	SYSLOG_USERS	/* send userlog stuff to syslog */
#undef	SYSLOG_OPER	/* log all users who successfully become an Op */
#undef	SYSLOG_CONN	/* log all uncomplete/rejected connections */

/*
 * If you want to log to a different facility than DAEMON, change
 * this define.
 */
#define LOG_FACILITY LOG_DAEMON
#endif /* USE_SYSLOG */

/*
 * define this if you want to use crypted passwords for operators in your
 * ircd.conf file. See ircd/crypt/README for more details on this.
 */
#undef	CRYPT_OPER_PASSWORD

/*
 * If you want to store encrypted passwords in N-lines for server links,
 * define this.  For a C/N pair in your ircd.conf file, the password
 * need not be the same for both, as long as hte opposite end has the
 * right password in the opposite line.  See INSTALL doc for more details.
 */
#undef	CRYPT_LINK_PASSWORD

/*
 * define this if you enable summon and if you want summon to look for the
 * least idle tty a user is logged in on.
 */
#undef	LEAST_IDLE

/*
 * IDLE_FROM_MSG
 *
 * Idle-time nullified only from privmsg, if undefined idle-time
 * is nullified from everything except ping/pong.
 * Added 3.8.1992, kny@cs.hut.fi (nam)
 */
#define	IDLE_FROM_MSG

/*
 * use these to setup a Unix domain socket to connect clients/servers to.
 */
#undef	UNIXPORT

/*
 * IRC_UID
 *
 * If you start the server as root but wish to have it run as another user,
 * define IRC_UID to that UID.  This should only be defined if you are running
 * as root and even then perhaps not.
 */
#undef	IRC_UID
#undef	IRC_GID

#ifdef	notdef
#define	IRC_UID	65534	/* eg for what to do to enable this feature */
#define	IRC_GID	65534
#endif

/*
 * CLIENT_FLOOD
 *
 * this controls the number of bytes the server will allow a client to
 * send to the server without processing before disconnecting the client for
 * flooding it.  Values greater than 8000 make no difference to the server.
 */
#define	CLIENT_FLOOD	1000

/* Remote query flood protection. */
#define	CHREPLLEN	8192

/* Default server for standard client */
#define	UPHOST	"irc"

/*
 * If you wish to run services, define USE_SERVICES. 
 * This can make the server noticeably bigger and slower.
 * services are not fully implemented yet, so don't use it unless you really
 * know what you are doing.
 */
#undef USE_SERVICES

/*
 * Define the following to make the delay for nicks random.
 * Some people believe a bot can exactly time the delay and don't like it,
 * I think this is a useless concern. -krys
 */
#define RANDOM_NDELAY

/*
 * You've read the BOFH saga and you liked it, then define the following.
 *
 * The two following will change the nick delay and channel delay features
 * making them totally user unfriendly but more efficient.
 */
#define BETTER_NDELAY
#define BETTER_CDELAY

/*
 * Defining this will enable the use of compressed server-server links.
 * In order to have it work, you must have the zlib version 1.0 or higher.
 * The library and the include files must have been found by configure,
 * if you have installed the zlib after running configure, run it again.
 */
#undef ZIP_LINKS

/*
 * Defining this will add an artificial 2 seconds delay for accepting
 * connections.  This is the OLD behaviour of the server.
 *
 * NOTE: Undefining this leads to a significant increase in CPU usage if
 * you reject client which keeps connecting.
 */
#define	SLOW_ACCEPT

/*
 * Defining this will make the server check for rapid connections from a single
 * host and reject new connections from this host if the limit is reached.
 *
 * NOTE: Enabling this feature will significantly increase the CPU usage
 * for servers carrying several hundred clients and getting many connections.
 *
 * IMPORTANT: This **MUST** defined if SLOW_ACCEPT is NOT defined
 */
#define	CLONE_CHECK

/* For broken mirc (win/pc) client. Enables old features:
 * 1) Send start-of-list numeric before LIST reply
 * 2) Revert combined "n JOIN #^Go" -> "n JOIN #" "MODE # o n"
 */
#define MIRC_KLUDGE

/*   STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP  */
/*   STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP  */
/*   STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP STOP  */

/* You shouldn't change anything below this line, unless absolutely needed. */

#ifdef	OPER_KILL
/* LOCAL_KILL_ONLY
 *
 * To be used, OPER_KILL must be defined.
 * LOCAL_KILL_ONLY restricts KILLs to clients which are connected to the
 * server the Operator is connected to (ie lets them deal with local
 * problem users or 'ghost' clients
 */
#define	LOCAL_KILL_ONLY
#endif

/* Default server port, used by client. */
#define	PORTNUM	6667

/* Maximum length the queue of pending connections to one port may grow to. */ 
#define LISTENQUEUE 128

/* define DEBUGMODE to enable debugging mode.*/
#undef	DEBUGMODE

/*
 * Time interval to wait and if no messages have been received, then check for
 * PINGFREQUENCY and CONNECTFREQUENCY 
 */
#define TIMESEC  60		/* Recommended value: 60 */

/*
 * If daemon doesn't receive anything from any of its links within
 * PINGFREQUENCY seconds, then the server will attempt to check for
 * an active link with a PING message. If no reply is received within
 * (PINGFREQUENCY * 2) seconds, then the connection will be closed.
 */
#define PINGFREQUENCY    120	/* Recommended value: 120 */

/*
 * If the connection to to uphost is down, then attempt to reconnect every 
 * CONNECTFREQUENCY  seconds.
 */
#define CONNECTFREQUENCY 600	/* Recommended value: 600 */

/*
 * Often net breaks for a short time and it's useful to try to
 * establishing the same connection again faster than CONNECTFREQUENCY
 * would allow. But, to keep trying on bad connection, we require
 * that connection has been open for certain minimum time
 * (HANGONGOODLINK) and we give the net few seconds to steady
 * (HANGONRETRYDELAY). This latter has to be long enough that the
 * other end of the connection has time to notice it broke too.
 */
#define HANGONRETRYDELAY 10	/* Recommended value: 10 seconds */
#define HANGONGOODLINK 300	/* Recommended value: 5 minutes */

/*
 * Number of seconds to wait for write to complete if stuck.
 */
#define WRITEWAITDELAY     15	/* Recommended value: 15 */

/*
 * Number of seconds to wait for a connect(2) call to complete.
 * NOTE: this must be at *LEAST* 10.  When a client connects, it has
 * CONNECTTIMEOUT - 10 seconds for its host to respond to an ident lookup
 * query and for a DNS answer to be retrieved.
 */
#define	CONNECTTIMEOUT	30	/* Recommended value: 30 */

/*
 * Max time from the nickname change that still causes KILL
 * automaticly to switch for the current nick of that user. (seconds)
 */
#define KILLCHASETIMELIMIT 90   /* Recommended value: 90 */

/*
 * Max time for the channel history and nick delay to be effective.
 * It should be the same value on all servers of a same net, and
 * be greater than the split durations usually seen.
 */
#define DELAYCHASETIMELIMIT 900   /* Recommended value: 900 */

/*
 * Max number of channels a user is allowed to join.
 */
#define MAXCHANNELSPERUSER  100	/* Recommended value: 10 */

/*
 * SendQ-Always causes the server to put all outbound data into the sendq and
 * flushing the sendq at the end of input processing. This should cause more
 * efficient write's to be made to the network.
 * There *shouldn't* be any problems with this method.
 * -avalon
 */
#define	SENDQ_ALWAYS

#ifdef ZIP_LINKS
/*
 * the compression level used. (Suggested values: 3, 4, 5)
 * Above 5 will only give a *very* marginal increase in compression for a
 * *very* large increase in CPU usage.
 */ 
# define	ZIP_LEVEL	5
#endif

#ifdef	CLONE_CHECK
/*
 * If CLONE_CHECK has been defined, these control how the checks are performed,
 * and how the alarm is triggered.
 */
# define	CLONE_MAX	2
# define	CLONE_PERIOD	10
#endif

/*
 * define NO_IDENT if you don't want to support ident (RFC1413).
 * it is a VERY bad idea to do so, since this will make it impossible to
 * efficientely track abusers.
 * NO_PREFIX should always be undefined.
 */
/* #undef	NO_IDENT */
/* #undef	NO_PREFIX */

/* ------------------------- END CONFIGURATION SECTION -------------------- */
#define	MYNAME SPATH
#define	CONFIGFILE CPATH
#define	IRCD_PIDFILE PPATH

#ifdef DEBUGMODE
# define LOGFILE LPATH
#endif

#ifndef ENABLE_SUMMON
#  undef LEAST_IDLE
#endif

#define SEQ_NOFILE    128	/* For Dynix (sequent OS) users : 
				 * set to your current kernel impl,
				 * max number of socket connections;
				 * ignored on other OS.	
				 */
/*
 * safety margin so we can always have one spare fd, for motd/authd or
 * whatever else.  -5 allows "safety" margin of 1 and space reserved.
 */
#define	MAXCLIENTS	(MAXCONNECTIONS-5)

#if defined(CLIENT_FLOOD)
# if	(CLIENT_FLOOD > 8000) || (CLIENT_FLOOD < 512)
error CLIENT_FLOOD needs redefining.
# endif
#else
error CLIENT_FLOOD undefined
#endif

#if defined(ZIP_LINKS)
# if	(ZIP_MINIMUM > ZIP_MAXIMUM)
error ZIP_MINIMUM needs redefining.
# endif
#endif

#if !defined(SLOW_ACCEPT) && !defined(CLONE_CHECK)
# define	CLONE_CHECK
# define	CLONE_MAX       2                                     
# define	CLONE_PERIOD    10       
#endif

/*
** you wouldn't want to compress messages one by one.. would you?
** (it's not implemented anyways)
*/
#ifdef	ZIP_LINKS
# define	SENDQ_ALWAYS
#endif

#if ! USE_POLL
# if (MAXCONNECTIONS > FD_SETSIZE)
error FD_SETSIZE must be bigger than MAXCONNECTIONS
# endif
#endif
