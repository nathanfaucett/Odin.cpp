#ifndef ODIN_MESH_CPP
#define ODIN_MESH_CPP

namespace Odin {

	inline Mesh::Mesh(std::string name, std::string src) : Asset(name, src) {
		m_needsUpdate = true;
		useBones = false;
		
		m_stride = 0;
		m_positionLocation = -1;
		m_colorLocation = -1;
		m_normalLocation = -1;
		m_tangentLocation = -1;
		m_uvLocation = -1;
		m_uv2Location = -1;
		triangleCount = 0;
		
		m_vertexBuffer = 0;
		m_indexBuffer = 0;
	}
	inline Mesh::~Mesh(void) {
		Clear();
	}
	
	inline void Mesh::Load(void) {
		
	}

	inline void Mesh::Clear(void) {
		vertices.Clear();
		colors.Clear();
		normals.Clear();
		tangents.Clear();
		uv.Clear();
		uv2.Clear();

		bones.Clear();
		boneWeights.Clear();
		aabb.Clear();
	}
	inline void Mesh::CalculateAABB(void) {
		aabb.FromPoints(vertices);
	}
	inline void Mesh::CalculateNormals(void) {
		Vec3f* u = new Vec3f();
		Vec3f* v = new Vec3f();
		Vec3f* uv = new Vec3f();
		Vec3f* faceNormal;
		Vec3f* va;
		Vec3f* vb;
		Vec3f* vc;

		uint32 vertexCount = vertices.Length(),
			   normalCount = normals.Length(),
			   triangleCount = vertexCount / 3,
			   a, b, c, i, il;
		
		if (vertexCount < normalCount) {
			for (i = vertexCount, il = normalCount; i > il; i--) {
				Vec3f* normal = normals[i];
				normals.Splice(i, 1);
				delete normal;
			}
		}
		i = vertexCount;
		normalCount = normals.Length();
		while(i-- > normalCount) normals.Push(new Vec3f());
		for (i = 0, il = vertexCount; i < il; i++) normals[i]->Set(0.0f, 0.0f, 0.0f);

		for (i = 0, il = triangleCount; i < il; i += 3) {
			a = triangles[i];
			b = triangles[i + 1];
			c = triangles[i + 2];

			va = vertices[a];
			vb = vertices[b];
			vc = vertices[c];
			
			Vec3Sub<float32>(*vc, *vb, *u);
			Vec3Sub<float32>(*va, *vb, *v);
			
			Vec3Cross<float32>(*u, *v, *uv);

			faceNormal = uv;
			faceNormal->Normalize();

			*(normals[a]) += *faceNormal;
			*(normals[b]) += *faceNormal;
			*(normals[c]) += *faceNormal;
		}
		
		for (i = 0, il = triangleCount; i < il; i += 3) {
			normals[triangles[i]]->Normalize();
			normals[triangles[i + 1]]->Normalize();
			normals[triangles[i + 2]]->Normalize();
		}

		delete u;
		delete v;
		delete uv;
		m_needsUpdate = true;
	}
}

#endif