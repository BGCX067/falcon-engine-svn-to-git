#include "Button.h"
#include "CallCenter.h"
#include "ResourceManager.h"
#include "Shader.h"


falcon::Button::Button( float x, float y, float width, float height )
	:Element2D(x, y, width, height)
{
}

bool falcon::Button::OnLMBClick(float x, float y)
{
	Vec3 color;
	if(x > m_pos.x && x < m_pos.x+m_width && y > m_pos.y && y < m_pos.y + m_height)
	{
		//Button has been clicked
		color = Vec3(1.0f,0,0);
		m_shaderData->SetDiffuseColor(color);
		return true;
	}
	color = Vec3(0,0,1.0f);
	m_shaderData->SetDiffuseColor(color);
	return false;
}

void falcon::Button::AddCallListener( Callable* ptr )
{
	CallCenter::GetInstance()->AddObserver(*ptr, *this);
}

void falcon::Button::OnLMBReleased()
{
	Vec3 color = Vec3(0,0,1.0f);
	m_shaderData->SetDiffuseColor(color);
}
