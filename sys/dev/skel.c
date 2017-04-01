/*	$NetBSD: pseudo_dev_skel.c,v 1.2 2009/05/21 15:07:41 cube Exp $	*/

/*-
 * Copyright (c) 1998-2006 Brett Lymn (blymn@NetBSD.org)
 * All rights reserved.
 *
 * This code has been donated to The NetBSD Foundation by the Author.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software withough specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/device.h>
#include <sys/conf.h>
#include <sys/skel.h>

/* Autoconfiguration glue */
void	skelattach(int num);
int     skelopen(dev_t device, int flags, int fmt, struct lwp *process);
int     skelclose(dev_t device, int flags, int fmt, struct lwp *process);
int     skelioctl(dev_t device, u_long command, void *data,
		      int flags, struct lwp *process);

/* just define the character device handlers because that is all we need */
const struct cdevsw skel_cdevsw = {
        .d_open = skelopen,
	.d_close = skelclose,
	.d_read = noread,
	.d_write = nowrite,
        .d_ioctl = skelioctl,
	.d_stop = nostop,
	.d_tty = notty,
	.d_poll = nopoll,
	.d_mmap = nommap,
	.d_kqfilter = nokqfilter,
};

/*
 * Attach for autoconfig to find.  The parameter is the number given in
 * the configuration file, and defaults to 1.  New code should not expect
 * static configuration from the kernel config file, and thus ignore that
 * parameter.
 */
void
skelattach(int num)
{
	  /* nothing to do for skeleton, this is where resources that
	     need to be allocated/initialised before open is called
	     can be set up */
}

/*
 * Handle an open request on the device.
 */
int
skelopen(dev_t device, int flags, int fmt, struct lwp *process)
{
	return 0; /* this always succeeds */
}

/*
 * Handle the close request for the device.
 */
int
skelclose(dev_t device, int flags, int fmt, struct lwp *process)
{
	return 0; /* again this always succeeds */
}

/*
 * Handle the ioctl for the device
 */
int
skelioctl(dev_t device, u_long command, void *data, int flags,
	      struct lwp *process)
{
	int error;
	struct skel_params *params = (struct skel_params *)data;

	error = 0;
	switch (command) {
		case SKELTEST:
			printf("Got number of %d and string of %s\n",
			       params->number, params->string);
			break;

		default:
			error = ENODEV;
	}

	return (error);
}
