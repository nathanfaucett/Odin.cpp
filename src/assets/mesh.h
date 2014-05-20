#ifndef ODIN_MESH_H
#define ODIN_MESH_H

namespace Odin {
	
	class Mesh : public Asset {
		
		class Bone {
			public:
				std::string name;
				int32 parentIndex;
				bool skinned;
				Vec3f position;
				Quatf rotation;
				Vec3f scale;
				Mat4f bindPose;
				
				inline Bone(int32 ParentIndex = -1, std::string Name = "") {
					parentIndex = ParentIndex;
					name = Name;
					skinned = false;
				}
		};
		class BoneWeight {
			public:
				uint32 boneIndex0, boneIndex1, boneIndex2, boneIndex3;
				float32 boneWeight0, boneWeight1, boneWeight2, boneWeight3;
				
				inline BoneWeight(void) {
					boneIndex0 = 0;
					boneIndex1 = 0;
					boneIndex2 = 0;
					boneIndex3 = 0;
					boneWeight0 = 0.0f;
					boneWeight1 = 0.0f;
					boneWeight2 = 0.0f;
					boneWeight3 = 0.0f;
				}
		};
		
		private:
			friend class OpenGLRenderer;
			bool m_needsUpdate;
			
			float32* m_vertexArray;
			
			uint32 m_vertexBuffer;
			uint32 m_indexBuffer;
			
			int32 m_stride;
			int32 m_positionLocation;
			int32 m_colorLocation;
			int32 m_normalLocation;
			int32 m_tangentLocation;
			int32 m_uvLocation;
			int32 m_uv2Location;
			
			inline static void m_BuildPlane(Mesh* mesh, int32 u, int32 v, int32 udir, int32 vdir, float32 width, int32 ws, float32 height, int32 hs, float32 depth, int32 ds);
		protected:

		public:
			bool useBones;
			
			Array<Vec3f*> vertices;
			Array<Colorf*> colors;
			Array<Vec3f*> normals;
			Array<Vec4f*> tangents;
			Array<Vec2f*> uv;
			Array<Vec2f*> uv2;
			uint32* triangles;
			uint32 triangleCount;
			
			Array<Bone*> bones;
			Array<BoneWeight*> boneWeights;
			AABB3f aabb;
			
			inline Mesh(std::string name, std::string src = "");
			inline ~Mesh(void);
			
			inline static Mesh* Cube(std::string name, float32 width = 1.0f, float32 height = 1.0f, float32 depth = 1.0f, int32 widthSegments = 1, int32 heightSegments = 1, int32 depthSegments = 1);
			inline static Mesh* Plane(std::string name, float32 width = 1.0f, float32 height = 1.0f, int32 widthSegments = 1, int32 heightSegments = 1);
			
			
			inline void Load(void);
			
			inline void Clear(void);
			inline void CalculateAABB(void);
			inline void CalculateNormals(void);
	};
}

#endif