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
		triangles = NULL;
		
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
	
	inline Mesh* Mesh::Cube(std::string name, float32 width, float32 height, float32 depth, int32 widthSegments, int32 heightSegments, int32 depthSegments) {
		float32 hw = width * 0.5,
                hh = height * 0.5,
                hd = depth * 0.5;
		
        Mesh* mesh = new Mesh(name);
		Mesh::m_BuildPlane(mesh, 2, 1, -1, 1, depth, depthSegments, height, heightSegments, hw, widthSegments);
		Mesh::m_BuildPlane(mesh, 2, 1, 1, 1, depth, depthSegments, height, heightSegments, -hw, widthSegments);
		Mesh::m_BuildPlane(mesh, 0, 2, 1, -1, width, widthSegments, depth, depthSegments, hh, heightSegments);
		Mesh::m_BuildPlane(mesh, 0, 2, 1, 1, width, widthSegments, depth, depthSegments, -hh, heightSegments);
		Mesh::m_BuildPlane(mesh, 0, 1, 1, 1, width, widthSegments, height, heightSegments, hd, depthSegments);
		Mesh::m_BuildPlane(mesh, 0, 1, -1, 1, width, widthSegments, height, heightSegments, -hd, depthSegments);
		mesh->CalculateAABB();
		
		return mesh;
	}
	inline Mesh* Mesh::Plane(std::string name, float32 width, float32 height, int32 widthSegments, int32 heightSegments) {
		
        Mesh* mesh = new Mesh(name);
		Mesh::m_BuildPlane(mesh, 0, 1, 1, 1, width, widthSegments, height, heightSegments, 0, 0);
		mesh->CalculateAABB();
		
		return mesh;
	}
	
	inline void Mesh::m_BuildPlane(Mesh* mesh, int32 u, int32 v, int32 ud, int32 vd, float32 width, int32 ws, float32 height, int32 hs, float32 depth, int32 ds) {
		Array<Vec3f*>& vertices = mesh->vertices;
		Array<Vec3f*>& normals = mesh->normals;
		Array<Vec2f*>& uv = mesh->uv;
		
		int32 gridX = ws < 1 ? 1 : ws,
			  gridY = hs < 1 ? 1 : hs;

		float32 hw = width * 0.5f,
				hh = height * 0.5f,
				udir = ud,
				vdir = vd,
				w, ix, iy;

		if ((u == 0 && v == 2) || (u == 2 && v == 0)) {
			w = 1;
			gridY = ds < 1 ? 1 : ds;
		} else if ((u == 0 && v == 1) || (u == 1 && v == 0)) {
			w = 2;
		} else if ((u == 1 && v == 2) || (u == 2 && v == 1)) {
			w = 0;
			gridX = ds < 1 ? 1 : ds;
		}

		float32 sw = width / gridX,
				sh = height / gridY;

		Vec3f* normal = new Vec3f();
		Vec3f* vertex = new Vec3f();

		uint32 vertexCount = vertices.Length();
		uint32 indexCount = mesh->triangleCount + (gridX * gridY * 6),
			   index = mesh->triangleCount;

		uint32* indices = new uint32[indexCount];
		for (uint32 i = 0, il = mesh->triangleCount; i < il; i++) indices[i] = mesh->triangles[i];
		
		(*normal)[w] = depth > 0.0f ? 1.0f : -1.0f;

		for (iy = 0.0f; iy < gridY; iy++) {
			for (ix = 0.0f; ix < gridX; ix++) {
				(*vertex)[u] = ((ix + 1.0f) * sw - hw) * udir;
				(*vertex)[v] = ((iy + 1.0f) * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				uv.Push(new Vec2f((ix + 1.0f) / gridX, 1.0f - (iy + 1.0f) / gridY));

				(*vertex)[u] = (ix * sw - hw) * udir;
				(*vertex)[v] = ((iy + 1.0f) * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				uv.Push(new Vec2f(ix / gridX, 1.0f - (iy + 1.0f) / gridY));

				(*vertex)[u] = (ix * sw - hw) * udir;
				(*vertex)[v] = (iy * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				uv.Push(new Vec2f(ix / gridX, 1.0f - iy / gridY));

				(*vertex)[u] = ((ix + 1.0f) * sw - hw) * udir;
				(*vertex)[v] = (iy * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				uv.Push(new Vec2f((ix + 1.0f) / gridX, 1.0f - iy / gridY));

				indices[index] = vertexCount;
				indices[index + 1] = vertexCount + 1;
				indices[index + 2] = vertexCount + 2;
				indices[index + 3] = vertexCount;
				indices[index + 4] = vertexCount + 2;
				indices[index + 5] = vertexCount + 3;
				
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));

				vertexCount += 4;
				index += 6;
			}
		}
		
		if (mesh->triangles != NULL) delete []mesh->triangles;
		mesh->triangles = indices;
		mesh->triangleCount = indexCount;
		
		delete normal;
		delete vertex;
	}
}

#endif