#ifndef FALCONENGINE_CALLCENTER_H
#define FALCONENGINE_CALLCENTER_H
#include <map>
#include <vector>

namespace falcon
{
	class Callable;
	class Element2D;

	class CallCenter
	{
	public:
		static void Create();
		static CallCenter* GetInstance();
		static void Destroy();

		void AddObserver(Callable& ptr, Element2D& element);
		void RemoveObserver(Callable& ptr);
		void OnLMBClick(float x, float y);
		void OnLMBReleased();

	private:
		static CallCenter* m_Instance;
		std::map<Callable*, std::vector<Element2D*> > m_Observers;

		CallCenter();
		virtual ~CallCenter();
	};
}

#endif //FALCONENGINE_CALLCENTER_H
