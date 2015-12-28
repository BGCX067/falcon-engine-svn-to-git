#ifndef FALCONENGINE_FALCONUTILS_H
#define FALCONENGINE_FALCONUTILS_H
#include <algorithm>
namespace falcon
{
	template <typename T>
	class SearchItem
	{
	public:
		SearchItem(T* item)
		{
			m_pItem = item;
		}

		bool operator()(T* item)
		{
			if(item == m_pItem) return true;
			else return false;
		}

	private:
		T* m_pItem;
	};
}

#endif //FALCONENGINE_FALCONUTILS_H