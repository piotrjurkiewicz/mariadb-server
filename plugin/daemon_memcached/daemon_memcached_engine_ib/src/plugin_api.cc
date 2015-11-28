/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#include "config.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "sql_plugin.h"
#include "handler.h"

#include "plugin_api.h"

static my_bool get_innodb_cb(THD *unused, plugin_ref plugin, void *arg)
{
	ib_cb_t*** innodb_cb_ptr = (ib_cb_t***) arg;

	if (strcmp(plugin_name(plugin)->str, "InnoDB") == 0)
	{
		*innodb_cb_ptr = (ib_cb_t**) plugin_data(plugin, handlerton*)->data;
		return 1;
	}
	return 0;
}

ib_cb_t** obtain_innodb_cb()
{
	ib_cb_t** innodb_cb = NULL;

	plugin_foreach(NULL, get_innodb_cb,
		       MYSQL_STORAGE_ENGINE_PLUGIN, &innodb_cb);

	return innodb_cb;
}
