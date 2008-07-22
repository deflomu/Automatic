#ifndef AUTOMATIC_H__
#define AUTOMATIC_H__

/*
 * Copyright (C) 2008 Frank Aurich (1100101+automatic@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifdef MEMWATCH
	#include "memwatch.h"
#endif


#include <stdint.h>
#include "downloads.h"
#include "feed_item.h"
#include "rss_feed.h"

struct auto_handle {

	char *transmission_path;
	char *statefile;
	char *torrent_folder;
	rss_feeds feeds;
	simple_list downloads;
	simple_list filters;
	uint8_t max_bucket_items;
	uint8_t bucket_changed;
	uint8_t check_interval;
	uint8_t use_transmission;
};

typedef struct auto_handle auto_handle;

const char* am_get_statefile(void);
uint8_t am_get_verbose(void);
uint8_t am_get_nofork(void);
uint8_t am_get_bucket_size(void);
void am_set_bucket_size(uint8_t size);
void am_set_interval(int interval);
int am_get_interval(void);
void applyFilters(feed_item item);
#endif