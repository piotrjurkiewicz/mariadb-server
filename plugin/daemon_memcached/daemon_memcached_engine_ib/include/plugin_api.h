/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include "innodb_api.h"

#ifdef  __cplusplus
extern "C" {
#endif

ib_cb_t** obtain_innodb_cb();

#ifdef  __cplusplus
}
#endif

#endif  /* PLUGIN_API_H */
