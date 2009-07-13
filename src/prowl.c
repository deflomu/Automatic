/*
 * Copyright (C) 2008 Frank Aurich (1100101+automatic@gmail.com
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


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>

#ifdef MEMWATCH
#include "memwatch.h"
#endif

#include "prowl.h"
#include "web.h"
#include "output.h"
#include "utils.h"


#define PROWL_URL "https://prowl.weks.net"
#define PROWL_ADD "/publicapi/add"
#define PROWL_VERIFY "/publicapi/verify"

static char* createProwlMessage(const char* apikey, const char* event, const char* desc, int32_t *size) {
  int32_t result, apikey_length, event_length, desc_length, total_size;

  char *msg = NULL;

  *size = 0;

  if(!apikey || (!event && !desc)) {
    *size = 0;
    return NULL;
  }

  apikey_length = strlen(apikey);
  event_length  = event ? strlen(event) : 0;
  desc_length   = desc  ? strlen(desc)  : 0;

  total_size = apikey_length + event_length + desc_length + 80;
  msg = (char*)am_malloc(total_size);

  if(msg) {
    result = snprintf(msg, total_size, "apikey=%s&priority=0&application=Automatic&event=%s&description=%s",
        apikey, event, desc);
    *size = result;
  }
  return msg;
}

int8_t sendProwlNotification(const char* apikey, const char* event, const char* desc) {
  int32_t data_size;
  char url[128];
  char *response = NULL;
  char *data = NULL;

  data = createProwlMessage(apikey, event, desc, &data_size);

  if(data) {
    snprintf(url, 128, "%s%s", PROWL_URL, PROWL_ADD);
    response = sendHTTPData(url, NULL, data, data_size);
  }

  am_free(response);
  am_free(data);
  return 0; //FIXME: return actual value
}

int8_t verifyProwlAPIKey(const char* apikey) {

  int8_t result = 0;
  char url[128];
  HTTPResponse *response = NULL;

  if(apikey) {
    snprintf(url, 128, "%s%s&apikey=%s", PROWL_URL, PROWL_ADD, apikey);
    response = getHTTPData(url);
  }

  HTTPResponse_free(response);
  return result;
}

