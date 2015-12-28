#ifndef FALCONENGINE_INDEXBUFFER_H
#define FALCONENGINE_INDEXBUFFER_H
#include <vector>
#include "GL/glew.h"

namespace falcon
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		virtual ~IndexBuffer();

		void AddIndex(unsigned int index){m_buffer.push_back(index);}
		const unsigned int* GetData()const {return m_buffer.data();}

		void Init();
		void Activate();
		void Deactivate();

		int GetLength() const {return m_buffer.size();}
		//size in bytes
		int GetSize()const{return m_buffer.size()*sizeof(unsigned int);}
	private:
		std::vector<unsigned int> m_buffer;
		GLuint m_bufferID;

		IndexBuffer(const IndexBuffer& v);
		IndexBuffer& operator=(const IndexBuffer& v);
	};
}

#endif //FALCONENGINE_INDEXBUFFER_H