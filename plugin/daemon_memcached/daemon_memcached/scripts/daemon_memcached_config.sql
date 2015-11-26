CREATE DATABASE IF NOT EXISTS daemon_memcached;

USE daemon_memcached;

-- ------------------------------------------------------------------------
-- Following are set of "configuration tables" that used to configure
-- the Daemon Memcached NoSQL interface plugin.
-- ------------------------------------------------------------------------

-- ------------------------------------------------------------------------
-- Table `containers`
--
-- A container record describes an InnoDB table used for data storage by
-- the Daemon Memcached NoSQL plugin.
-- There must be a unique index on the `key column`, and unique index name
-- is specified in the `unique_idx_name_on_key` column of the table
-- `value_columns` are comma-separated lists of the columns that make up
-- the memcached key and value.
-- ------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS `containers` (
	`name` varchar(50) not null primary key,
	`db_schema` VARCHAR(250) NOT NULL,
	`db_table` VARCHAR(250) NOT NULL,
	`key_columns` VARCHAR(250) NOT NULL,
	`value_columns` VARCHAR(250),
	`flags` VARCHAR(250) NOT NULL DEFAULT "0",
	`cas_column` VARCHAR(250),
	`expire_time_column` VARCHAR(250),
	`unique_idx_name_on_key` VARCHAR(250) NOT NULL,
	`sep` VARCHAR(32) NOT NULL DEFAULT "|")
ENGINE = InnoDB;

-- ------------------------------------------------------------------------
-- This is an example
--
-- We create a InnoDB table `demo_test` is the `test` database
-- and insert an entry into contrainers' table to tell Daemon Memcached
-- that we has such InnoDB table as back store:
-- c1 -> key
-- c2 -> value
-- c3 -> flags
-- c4 -> cas
-- c5 -> exp time
-- PRIMARY -> use primary key to search
-- | -> use this character as separator
-- ------------------------------------------------------------------------

INSERT INTO containers VALUES ("tcp://*:11211", "test", "demo_test",
			       "c1", "c2", "c3", "c4", "c5", "PRIMARY", "|");

INSERT INTO containers VALUES ("udp://*:11211", "test", "demo_test",
			       "c1", "c2", "c3", "c4", "c5", "PRIMARY", "|");

CREATE DATABASE IF NOT EXISTS test;
USE test;

-- ------------------------------------------------------------------------
-- Key   (c1) -- must be VARCHAR or CHAR type, memcached supports key up to
--               255 bytes
-- Value (c2) -- must be VARCHAR or CHAR type
-- Flag  (c3) -- is a 32 bits integer
-- CAS   (c4) -- is a 64 bits integer, per memcached define
-- Exp   (c5) -- is again a 32 bits integer
-- ------------------------------------------------------------------------

CREATE TABLE demo_test (c1 VARCHAR(32),
			c2 VARCHAR(1024),
			c3 INT, c4 BIGINT UNSIGNED, c5 INT, primary key(c1))
ENGINE = InnoDB;

INSERT INTO demo_test VALUES ("AA", "HELLO, HELLO", 8, 0, 0);
