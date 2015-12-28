#include "stdafx.h"
#include "MeshManager.h"
#include "LogManager.h"
#include "Mesh.h"
#include "FalconMath.h"

#include "assimp.hpp"
#include "aiScene.h"
#include "aiPostProcess.h"
#include "GameObject.h"
#include "ppl.h"

bool falcon::MeshManager::s_bInitialized = false;
falcon::MeshManager* falcon::MeshManager::s_Instance = 0;

falcon::MeshManager::MeshManager()
{
	s_bInitialized = true;
}

falcon::MeshManager::~MeshManager()
{
	std::map<std::string, Mesh*>::iterator iter = m_Meshes.begin();
	std::map<std::string, Mesh*>::iterator itEnd = m_Meshes.end();
	
	for(iter; iter != itEnd; ++iter)
	{
		delete (*iter).second;

		std::stringstream buffer;
		buffer << "Successfully deleted Mesh " << (*iter).first;
		LOG(LOG_Info, buffer.str());
	}
	m_Meshes.clear();
}

void falcon::MeshManager::Create()
{
	s_Instance = new falcon::MeshManager();
}

falcon::MeshManager* falcon::MeshManager::GetInstance()
{
	return s_Instance;
}

void falcon::MeshManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

void falcon::MeshManager::LoadMesh(std::string path, GameObject& object)
{	
	std::map<std::string, Mesh*>::iterator it = m_Meshes.find(path);

	if(it == m_Meshes.end())
	{
		const aiScene* scene = NULL;

		Assimp::Importer importer = Assimp::Importer();


		scene = importer.ReadFile(path, 
			aiProcess_CalcTangentSpace | 
			aiProcess_Triangulate | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_SortByPType);

		if(scene != NULL)
		{
			falcon::Mesh* fcMesh= new Mesh();

			aiMesh* aimesh = scene->mMeshes[0];

			VertexBuffer* vBuf = new VertexBuffer();
			IndexBuffer* iBuf = new IndexBuffer();
			BoundingSphere bounds;

 			for(unsigned int index = 0; index < aimesh->mNumVertices; ++index)
 			{
 				falcon::Vec3 position;
 				position.x = aimesh->mVertices[index].x;
 				position.y = aimesh->mVertices[index].y;
 				position.z = aimesh->mVertices[index].z;
 
 				falcon::Vec3 normal;
 				normal.x = aimesh->mNormals[index].x;
 				normal.y = aimesh->mNormals[index].y;
 				normal.z = aimesh->mNormals[index].z;
 
 				//multiple tex-channels not supported yet!
 				falcon::Vec2 tex;
 				tex.x = aimesh->mTextureCoords[0][index].x;
 				tex.y = aimesh->mTextureCoords[0][index].y;
 
 				vBuf->AddVertex(VertexStruct(position,normal, tex));
 
 				float distSq= position.lengthSq();
 				if (distSq > bounds.radius)
 					bounds.radius=distSq;
 			}
			//calculate boundingsphere (center is local (0,0,0))
			bounds.radius=sqrtf(bounds.radius);
			fcMesh->SetBoundingSphere(bounds);

			vBuf->Init(); //copy to Grafix Card
			fcMesh->SetVertexBuffer(vBuf);

			for(unsigned int faceIndex = 0; faceIndex < aimesh->mNumFaces; ++faceIndex)
			{
				aiFace face = aimesh->mFaces[faceIndex];

				for(unsigned int index = 0; index < face.mNumIndices; ++index)
				{
					iBuf->AddIndex(face.mIndices[index]);
				}
			}
			iBuf->Init(); //copy to Grafix Card
			fcMesh->SetIndexBuffer(iBuf);

			m_Meshes.insert(make_pair(path, fcMesh));

			std::stringstream buffer;
			buffer << "Successfully loaded Mesh " << path;
			LOG(LOG_Info, buffer.str());

			object.SetMesh(fcMesh);
		}else{
			LOG(LOG_Error, "Couldn't load Mesh "+path);
		}
	}else{
		object.SetMesh((*it).second);
	}
}

bool falcon::MeshManager::UnLoadMesh(std::string path)
{
	std::map<std::string, Mesh*>::iterator it = m_Meshes.find(path);

	if(it != m_Meshes.end())
	{
		delete (*it).second;
		m_Meshes.erase(it);

		std::stringstream buffer;
		buffer << "Successfully deleted Model " << path;
		LOG(LOG_Info, buffer.str());

		return true;
	}else{
		LOG(LOG_Error, "Mesh Doesn't Exist.\n" + path + "\n");
		return false;
	}
}