#ifndef FALCONENGINE_MESH_H
#define FALCONENGINE_MESH_H

#include "FalconMath.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderContext.h"
#include "FalconLuaBind.h"
#include "BoundingSphere.h"

namespace falcon
{
	
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::string test);
		virtual ~Mesh();

		void SetVertexBuffer(VertexBuffer* buffer){m_vBuffer = buffer;}
		VertexBuffer& GetVertexBuffer() const {return *m_vBuffer;}


		void SetIndexBuffer(IndexBuffer* buffer){m_iBuffer = buffer;}
		IndexBuffer* GetIndexBuffer() const {return m_iBuffer;}

		void SetBoundingSphere(BoundingSphere& bounds){m_boundingSphere = bounds;}
		const BoundingSphere& GetBoundingSphere() const {return m_boundingSphere;}

		falcon::Shader* GetShader() const { return m_shader; }
		void SetShader(falcon::Shader* shader) { m_shader = shader; }

		virtual void Draw(/*const RenderContext& / *renderContext* /*/);

		static luabind::scope Register();

	private:
		VertexBuffer* m_vBuffer;
		IndexBuffer* m_iBuffer;
		Shader* m_shader;
		BoundingSphere m_boundingSphere;
		Mesh(const Mesh& t);
		Mesh& operator=(const Mesh& t);
	};
}

#endif //FALCONENGINE_MESH_H
