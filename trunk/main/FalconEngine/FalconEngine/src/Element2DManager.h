#ifndef FALCONENGINE_ELEMENT2DMANAGER_H
#define FALCONENGINE_ELEMENT2DMANAGER_H
#include <set>
#include "FalconLuaBind.h"

namespace falcon
{
	class Element2D;
	class Element2DManager
	{
	public:
		static void Create();
		static Element2DManager* GetInstance();
		static void Destroy();

		void AddElement(Element2D* element);
		void Render();

		Element2DManager();
		virtual ~Element2DManager();

	private:
		std::set<Element2D*> m_Elements;
		static Element2DManager* m_Instance;
	};
}
#endif //FALCONENGINE_ELEMENT2DMANAGER_H