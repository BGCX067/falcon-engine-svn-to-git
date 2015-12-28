#ifndef FALCONENGINE_VERTEXBUFFER_H
#define FALCONENGINE_VERTEXBUFFER_H
#include <vector>
#include "FalconMath.h"
#include "GL/glew.h"

namespace falcon
{
	struct VertexStruct
	{
		VertexStruct(Vec3 pos, Vec3 norm, Vec2 tex): m_position(pos), m_normal(norm), m_texcoords(tex){}
		~VertexStruct(){};
		Vec3 m_position;
		Vec3 m_normal;
		Vec2 m_texcoords;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		void AddVertex(const VertexStruct& vert){m_buffer.push_back(vert);}
		const VertexStruct* GetData()const {return m_buffer.data();}
		std::vector<VertexStruct> GetBufferData()const {return m_buffer;}
		void SetBufferData(std::vector<VertexStruct> data){m_buffer = data;}
		void Clear(){m_buffer.clear();}

		void Init();
		void Activate();
		void Deactivate();

		int GetLength() const {return m_buffer.size();}

		//size in bytes
		int GetSize() const {return m_buffer.size()*sizeof(VertexStruct);}
	private:
		std::vector<VertexStruct> m_buffer;
		
		GLuint m_bufferID;

		VertexBuffer(const VertexBuffer& v);
		VertexBuffer& operator=(const VertexBuffer& v);
	};
}

#endif //FALCONENGINE_VERTEXBUFFER_H