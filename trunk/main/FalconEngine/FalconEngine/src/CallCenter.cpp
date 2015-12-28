#include "CallCenter.h"
#include "Callable.h"
#include <algorithm>
#include "boost\foreach.hpp"
#include "Element2D.h"

falcon::CallCenter* falcon::CallCenter::m_Instance = 0;

falcon::CallCenter::CallCenter()
{

}

falcon::CallCenter::~CallCenter()
{

}

void falcon::CallCenter::Create()
{
	m_Instance = new CallCenter();
}

falcon::CallCenter* falcon::CallCenter::GetInstance()
{
	return m_Instance;
}

void falcon::CallCenter::Destroy()
{
	delete m_Instance;
	m_Instance = 0;
}

void falcon::CallCenter::AddObserver(Callable& ptr, Element2D& element)
{
	if(m_Observers.find(&ptr) != m_Observers.end())
	{
		m_Observers.at(&ptr).push_back(&element);
	}
	else
	{
		std::vector<Element2D*> temp;
		temp.push_back(&element);

		m_Observers.insert(std::pair<Callable*, std::vector<Element2D*> >(&ptr, temp));
	}
}

void falcon::CallCenter::RemoveObserver(Callable& /*ptr*/)
{
}

void falcon::CallCenter::OnLMBClick( float x, float y )
{
	std::map<Callable*, std::vector<Element2D*> >::iterator it = m_Observers.begin();

	for (; it != m_Observers.end(); ++it)
	{
		BOOST_FOREACH(Element2D* myElement, it->second)
		{
			if(myElement->OnLMBClick(x,y))
			{
				it->first->Notify(myElement);
			}
		}
	}
}

void falcon::CallCenter::OnLMBReleased()
{
	std::map<Callable*, std::vector<Element2D*> >::iterator it = m_Observers.begin();

	for (; it != m_Observers.end(); ++it)
	{
		BOOST_FOREACH(Element2D* myElement, it->second)
		{
			myElement->OnLMBReleased();
		}
	}
}
