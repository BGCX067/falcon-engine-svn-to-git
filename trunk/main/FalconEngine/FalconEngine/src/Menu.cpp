#include "Menu.h"
#include "Element2D.h"
#include "Button.h"
#include "boost\foreach.hpp"
#include "Shader.h"

falcon::Menu::Menu()
{

}

falcon::Menu::~Menu()
{

}

void falcon::Menu::AddButton( Button* button )
{
	m_Buttons.push_back(button);
	button->AddCallListener(this);
}

void falcon::Menu::Draw()
{
	BOOST_FOREACH(Button* button, m_Buttons)
	{
		button->Draw();
	}
}


