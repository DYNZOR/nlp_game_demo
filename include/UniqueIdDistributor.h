/**
The unique id distributor distributes unique integral ids. Ids start from 1, with 0
being used to represent an error during an attempt to retrieve a new unique id. The
id distributor only supports integral types.

@author Nathan Sainsbury */

#ifndef UNIQUE_ID_DISTRIBUTOR_H
#define UNIQUE_ID_DISTRIBUTOR_H

#include <assert.h>
#include <type_traits>
#include <limits>


	template <class IdType = unsigned int>
	class UniqueIdDistributor
	{
	private:
		IdType m_iNextUniqueId;
		IdType m_iMaximumId;

	protected:

	public:
		/**
		Constructs a UniqueIdDistributor. */
		UniqueIdDistributor()
		{
			assert(std::is_integral<IdType>::value
				&& "Only intregral types are supported for unique id distribution");

			m_iNextUniqueId = 1;
			m_iMaximumId = std::numeric_limits<IdType>::max();
		}

		/**
		Retrieves the next available unique id. Returns 0 if a unique id could not be assigned,
		which only occurs when all other unique ids have been consumed.
		@return A unique id, or 0 if an error occurred */
		IdType GetId()
		{
			IdType iReturningId = m_iNextUniqueId;
			if (iReturningId == m_iMaximumId)
			{
				iReturningId = 0;
			}
			else
			{
				++m_iNextUniqueId;
			}
			return iReturningId;
		}
	};

#endif