/*****************************************************************************

Copyright (C) 2013 SkySQL Ab. All Rights Reserved.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

*****************************************************************************/

/******************************************************************//**
@file include/fsp0pageencryption.h
Helper functions for extracting/storing page encryption information to file space.

Created 08/28/2014 Florin Fugaciu
***********************************************************************/

#ifndef FSP0PAGEENCRYPTION_H_
#define FSP0PAGEENCRYPTION_H_



/********************************************************************//**
Determine if the tablespace is page encrypted from dict_table_t::flags.
@return	TRUE if page encrypted, FALSE if not page encrypted */
UNIV_INLINE
ibool
fsp_flags_is_page_encrypted(
/*=========================*/
	ulint	flags);	/*!< in: tablespace flags */


/********************************************************************//**
Extract the page encryption key from tablespace flags.
A tablespace has only one physical page encryption key
whether that page is encrypted or not.
@return	page encryption key of the file-per-table tablespace,
or zero if the table is not encrypted.  */
UNIV_INLINE
ulint
fsp_flags_get_page_encryption_key(
/*=================================*/
	ulint	flags);	/*!< in: tablespace flags */


#ifndef UNIV_NONINL
#include "fsp0pageencryption.ic"
#endif


#endif /* FSP0PAGEENCRYPTION_H_ */
