/**
 * $Id: CTR_List.h 14444 2008-04-16 22:40:48Z hos $
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */


#ifndef CTR_LIST_H
#define CTR_LIST_H

class CTR_Link {
public:
    CTR_Link(
	) ;

    CTR_Link(
		CTR_Link *next,
		CTR_Link *prev
	) ;
    
		CTR_Link *
	getNext(
	) const ;
  
		CTR_Link *
	getPrev(
	) const ;

		bool 
	isHead(
	) const ;

		bool 
	isTail(
	) const ;

		void 
	insertBefore(
		CTR_Link *link
	) ;

		void 
	insertAfter(
		CTR_Link *link
	) ;

		void 
	remove(
	) ;

private:  
    CTR_Link  *m_next;
    CTR_Link  *m_prev;
};

class CTR_List {
public:

    CTR_List(
	) ;

		CTR_Link *
	getHead(
	) const ;
 
		CTR_Link *
	getTail(
	) const ;

		void 
	addHead(
		CTR_Link *link
	) ;

		void 
	addTail(
		CTR_Link *link
	) ;
    
private:
    CTR_Link m_head;
    CTR_Link m_tail;
};

#endif

