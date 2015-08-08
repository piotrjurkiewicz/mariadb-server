# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

OPTION(DAEMON_MEMCACHED_ENABLE_SASL "Enable SASL on Daemon Memcached" OFF)
OPTION(DAEMON_MEMCACHED_ENABLE_SASL_PWDB "Enable SASL on Daemon Memcached" OFF)

CONFIGURE_FILE(include/config_daemon_memcached.h.in include/config_daemon_memcached.h)

# Common defines and includes
INCLUDE_DIRECTORIES(${LIBEVENT_INCLUDE_DIR}
		    ${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/sql
		    ${CMAKE_SOURCE_DIR}/bld/include
		    ${CMAKE_SOURCE_DIR}/regex
		    ${CMAKE_SOURCE_DIR}/libevent
		    ${CMAKE_SOURCE_DIR}/include/mysql
		    ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}
		    ${CMAKE_SOURCE_DIR}/plugin/daemon_memcached/daemon_memcached/include
		    ${CMAKE_BINARY_DIR}/plugin/daemon_memcached/daemon_memcached/include
		    ${CMAKE_SOURCE_DIR}/plugin/daemon_memcached/daemon_memcached/include/memcached
		    ${CMAKE_SOURCE_DIR}/plugin/daemon_memcached/daemon_memcached

		)

SET(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} ${CMAKE_SHARED_LIBRARY_C_FLAGS} -I${CMAKE_SOURCE_DIR}/plugin/daemon_memcached/daemon_memcached/utilities")

# If current CMAKE_C_FLAGS is with Werror, turn it off to compile successfully
IF(CMAKE_C_FLAGS MATCHES "-Werror")
  STRING(REGEX REPLACE "-Werror( |$)" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
ENDIF(CMAKE_C_FLAGS MATCHES "-Werror")

# Turn -Wdeclaration-after-statement off to reduce the number of warnings
STRING(REGEX REPLACE "-Wdeclaration-after-statement" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
STRING(REGEX REPLACE "-Wdeclaration-after-statement" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
STRING(REGEX REPLACE "-Wextra" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
STRING(REGEX REPLACE "-Wextra" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
STRING(REGEX REPLACE "-Wvla" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
STRING(REGEX REPLACE "-Wvla" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
STRING(REGEX REPLACE "-Wwrite-strings" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
STRING(REGEX REPLACE "-Wwrite-strings" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_SHARED_LIBRARY_C_FLAGS} -std=gnu99")

SET(DAEMON_MEMCACHED_UTILITIES_SOURCES
		include/memcached/config_parser.h
		include/memcached/util.h
		utilities/config_parser.c
		utilities/engine_loader.c
		utilities/engine_loader.h
		utilities/extension_loggers.c
		utilities/util.c)

ADD_LIBRARY(daemon_memcached_utilities STATIC ${DAEMON_MEMCACHED_UTILITIES_SOURCES})

SET(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} ${CMAKE_SHARED_LIBRARY_C_FLAGS} -I${CMAKE_SOURCE_DIR}/plugin/daemon_memcached/daemon_memcached/daemon")

SET(DAEMON_MEMCACHED_SOURCES
		daemon/memcached_mysql.h
		daemon/memcached_mysql.cc
		daemon/cache.h
		daemon/cache.c
		config_static.h
		daemon/daemon.c
		daemon/hash.c
		daemon/hash.h
		daemon/memcached.c
		daemon/memcached.h
		daemon/sasl_defs.c
		daemon/sasl_defs.h
		daemon/stats.c
		daemon/stats.h
		daemon/thread.c
		trace.h)

MYSQL_ADD_PLUGIN(daemon_memcached ${DAEMON_MEMCACHED_SOURCES}
		MODULE_ONLY MODULE_OUTPUT_NAME "daemon_memcached")

TARGET_LINK_LIBRARIES(daemon_memcached ${LIBEVENT_LIBRARY})
TARGET_LINK_LIBRARIES(daemon_memcached daemon_memcached_utilities)

IF(DAEMON_MEMCACHED_ENABLE_SASL)
  TARGET_LINK_LIBRARIES(daemon_memcached sasl2)
ENDIF()
