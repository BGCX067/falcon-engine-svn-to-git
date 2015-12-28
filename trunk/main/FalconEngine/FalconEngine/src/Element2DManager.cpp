#include "Element2DManager.h"
#include <algorithm>
#include <boost/foreach.hpp>
#include "Element2D.h"

falcon::Element2DManager* falcon::Element2DManager::m_Instance = 0;

falcon::Element2DManager::Element2DManager()
{

}

falcon::Element2DManager::~Element2DManager()
{

}

void falcon::Element2DManager::Create()
{
	m_Instance = new Element2DManager();
}

falcon::Element2DManager* falcon::Element2DManager::GetInstance()
{
	return m_Instance;
}

void falcon::Element2DManager::Destroy()
{
	delete m_Instance;
	m_Instance = 0;
}

void falcon::Element2DManager::Render()
{
	BOOST_FOREACH(Element2D* element, m_Elements)
	{
		element->Draw();
	}
}

void falcon::Element2DManager::AddElement( Element2D* element )
{
	m_Elements.insert(m_Elements.end(), element);
}
