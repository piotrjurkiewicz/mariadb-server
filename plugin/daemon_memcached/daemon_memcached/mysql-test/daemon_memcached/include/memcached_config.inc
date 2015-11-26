create database daemon_memcached;

use daemon_memcached;

#-- ------------------------------------------------------------------------
#-- Table `containers`
#--
#-- A container record describes an InnoDB table used for data storage by
#-- Daemon Memcached NoSQL plugin.
#-- There must be a unique index on the `key column`, and unique index name
#-- is specified in the `unique_idx_name_on_key` column of the table
#-- `value_columns` are comma-separated lists of the columns that make up
#-- the memcached key and value.
#-- ------------------------------------------------------------------------

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
	`sep` VARCHAR(32) NOT NULL DEFAULT "|"
) ENGINE = InnoDB;
