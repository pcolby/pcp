/*
 * Copyright (c) 2013 Red Hat.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef _CONTEXTS_H
#define _CONTEXTS_H

/*
 * Handle newly arriving clients, security attributes being set on 'em,
 * switching to alternative accounts (temporarily) and back, and client
 * termination.  State maintained in a global table, with a high-water
 * allocator and active/inactive entry tracking.
 *
 * The proc.control.perclient metrics also have state tracked here now.
 */

enum {
    CTX_INACTIVE = 0x0,
    CTX_ACTIVE   = 0x1,
    CTX_USERID   = 0x2,
    CTX_GROUPID  = 0x4,
    CTX_THREADS  = 0x8,
    CTX_CGROUPS  = 0x10,
};

typedef struct {
    unsigned int	state;
    uid_t		uid;
    gid_t		gid;
    unsigned int	threads;
    const char		*cgroups;
} proc_perctx_t;

extern void proc_ctx_init(void);
extern int proc_ctx_attrs(int, int, const char *, int, pmdaExt *);
extern void proc_ctx_end(int);
extern int proc_ctx_getuid(int);

extern int proc_ctx_access(int);
extern int proc_ctx_revert(int);

extern unsigned int proc_ctx_threads(int, unsigned int);
extern int proc_ctx_set_threads(int, unsigned int);

extern const char *proc_ctx_cgroups(int, const char *);
extern int proc_ctx_set_cgroups(int, const char *);

#endif	/* _CONTEXTS_H */
