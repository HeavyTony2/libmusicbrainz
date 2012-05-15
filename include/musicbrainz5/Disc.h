/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ5_DISC_H
#define _MUSICBRAINZ5_DISC_H

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/ReleaseList.h"

#include "musicbrainz5/Lifespan.h"

#include <string>
#include <iostream>

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CDiscPrivate;

	class CDisc: public CEntity
	{
	public:
		CDisc(const XMLNode& Node=XMLNode::emptyNode());
		CDisc(const CDisc& Other);
		CDisc& operator =(const CDisc& Other);
		virtual ~CDisc();

		virtual CDisc *Clone();

		std::string ID() const;
		int Sectors() const;
		CReleaseList *ReleaseList() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CDiscPrivate * const m_d;
	};
}

#endif