#ifndef ODIN_MESH_CPP
#define ODIN_MESH_CPP

#include "model_parsers/obj_parser.hpp"


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
		
		m_vertexBuffer = 0;
		m_indexBuffer = 0;
		m_lineBuffer = 0;
	}
	inline Mesh::~Mesh(void) {
		Clear();
	}
	
	inline std::string Mesh::m_GetExt(void) {
		
		if (p_src.find_last_of(".") != std::string::npos) {
			return p_src.substr(p_src.find_last_of(".") + 1);
		}
		
		return "";
	}
	
	inline void Mesh::Load(void) {
		std::string ext = m_GetExt();
		
		if (ext == "obj") {
			m_LoadObj();
		}
	}

	inline void Mesh::Clear(void) {
		m_stride = 0;
		m_positionLocation = -1;
		m_colorLocation = -1;
		m_normalLocation = -1;
		m_tangentLocation = -1;
		m_uvLocation = -1;
		m_uv2Location = -1;
		
		m_vertexBuffer = 0;
		m_indexBuffer = 0;
		m_lineBuffer = 0;
		
		if (vertices.Length()) vertices.Clear();
		if (colors.Length()) colors.Clear();
		if (normals.Length()) normals.Clear();
		if (tangents.Length()) tangents.Clear();
		if (uv.Length()) uv.Clear();
		if (uv2.Length()) uv2.Clear();
		if (indices.Length()) indices.Clear();

		if (bones.Length()) bones.Clear();
		if (boneWeights.Length()) boneWeights.Clear();
		aabb.Clear();
	}
	
	inline void Mesh::TransformMat3(const Mat3f& m) {
		uint32 i, il;

		if ((il = vertices.Length()) != 0) {
			for (i = 0; i < il; i++) *(vertices[i]) *= m;
			m_needsUpdate = true;
		}
		if ((il = normals.Length()) != 0) {
			for (i = 0; i < il; i++) *(normals[i]) *= m;
			m_needsUpdate = true;
		}
	}
	inline void Mesh::TransformMat4(const Mat4f& m) {
		uint32 i, il;

		if ((il = vertices.Length()) != 0) {
			for (i = 0; i < il; i++) *(vertices[i]) *= m;
			m_needsUpdate = true;
		}
		if ((il = normals.Length()) != 0) {
			for (i = 0; i < il; i++) *(normals[i]) *= m;
			m_needsUpdate = true;
		}
	}
	inline void Mesh::TransformMat43(const Mat43f& m) {
		uint32 i, il;

		if ((il = vertices.Length()) != 0) {
			for (i = 0; i < il; i++) *(vertices[i]) *= m;
			m_needsUpdate = true;
		}
		if ((il = normals.Length()) != 0) {
			for (i = 0; i < il; i++) *(normals[i]) *= m;
			m_needsUpdate = true;
		}
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
			   a, b, c, i, il;
		
		if (vertexCount < normalCount) {
			for (i = vertexCount, il = normalCount; i > il; i--) {
				Vec3f* normal = normals[i];
				normals.Splice(i, 1);
				delete normal;
			}
		} else {
			i = vertexCount;
			normalCount = normals.Length();
			while(i-- > normalCount) normals.Push(new Vec3f());
			for (i = 0, il = vertexCount; i < il; i++) normals[i]->Set(0.0f, 0.0f, 0.0f);
		}

		for (i = 0, il = indices.Length(); i < il; i += 3) {
			a = indices[i];
			b = indices[i + 1];
			c = indices[i + 2];

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
		
		for (i = 0, il = indices.Length(); i < il; i += 3) {
			normals[indices[i]]->Normalize();
			normals[indices[i + 1]]->Normalize();
			normals[indices[i + 2]]->Normalize();
		}

		delete u;
		delete v;
		delete uv;
		m_needsUpdate = true;
	}
	inline void Mesh::CalculateTangents(void) {
		Vec3f v1, v2, v3;
		Vec2f w1, w2, w3;
		
		
		Array<Vec3f*> tan1, tan2;
		Vec3f sdir, tdir;
		Vec3f t, n;

		float32 x1, x2, y1, y2, z1, z2,
				s1, s2, t1, t2,
				r, w;

		uint32 vertexCount = vertices.Length(),
			   tangentCount = tangents.Length(),
			   uvCount = uv.Length(),
			   a, b, c,
			   i, il;

		for (i = 0, il = vertexCount; i < il; i++) {
			tan1.Push(new Vec3f);
			tan2.Push(new Vec3f);
		}
		if (vertexCount < tangentCount) {
			for (i = vertexCount, il = tangentCount; i > il; i--) {
				Vec4f* tangent = tangents[i];
				tangents.Splice(i, 1);
				delete tangent;
			}
		} else {
			i = vertexCount;
			tangentCount = tangents.Length();
			while(i-- > tangentCount) tangents.Push(new Vec4f());
		}
		
		if (vertexCount < uvCount) {
			for (i = vertexCount, il = uvCount; i > il; i--) {
				Vec2f* vUv = uv[i];
				uv.Splice(i, 1);
				delete vUv;
			}
		} else {
			i = vertexCount;
			uvCount = uv.Length();
			while(i-- > uvCount) uv.Push(new Vec2f());
		}

		for (i = 0, il = indices.Length(); i < il; i += 3) {
			a = indices[i];
			b = indices[i + 1];
			c = indices[i + 2];

			v1 = *(vertices[a]);
			v2 = *(vertices[b]);
			v3 = *(vertices[c]);

			w1 = *(uv[a]);
			w2 = *(uv[b]);
			w3 = *(uv[c]);

			x1 = v2.x - v1.x;
			x2 = v3.x - v1.x;
			y1 = v2.y - v1.y;
			y2 = v3.y - v1.y;
			z1 = v2.z - v1.z;
			z2 = v3.z - v1.z;

			s1 = w2.x - w1.x;
			s2 = w3.x - w1.x;
			t1 = w2.y - w1.y;
			t2 = w3.y - w1.y;

			r = s1 * t2 - s2 * t1;
			r = r != 0.0f ? 1.0f / r : 0.0f;

			sdir.Set(
				(t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r
			);

			tdir.Set(
				(s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r
			);

			*(tan1[a]) += sdir;
			*(tan1[b]) += sdir;
			*(tan1[c]) += sdir;

			*(tan2[a]) += tdir;
			*(tan2[b]) += tdir;
			*(tan2[c]) += tdir;
		}

		for (i = 0, il = vertexCount; i < il; i++) {
			t = *(tan1[i]);
			n = *(normals[i]);

			Vec3f tmp1 = t - n * n.Dot(t);
			tmp1.Normalize();

			Vec3f tmp2 = n.Cross(t);

			w = (tmp2.Dot(*(tan2[i])) < 0.0f) ? -1.0f : 1.0f;

			tangents[i]->Set(tmp1.x, tmp1.y, tmp1.z, w);
		}
		
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
		
		mesh->CalculateTangents();
		mesh->CalculateAABB();
		
		return mesh;
	}
	inline Mesh* Mesh::Plane(std::string name, float32 width, float32 height, int32 widthSegments, int32 heightSegments) {
		
        Mesh* mesh = new Mesh(name);
		Mesh::m_BuildPlane(mesh, 0, 1, 1, 1, width, widthSegments, height, heightSegments, 0, 0);
		
		mesh->CalculateTangents();
		mesh->CalculateAABB();
		
		return mesh;
	}
	inline Mesh* Mesh::Sphere(std::string name, float32 radius, uint32 segs, uint32 rgs) {
		Mesh* mesh = new Mesh(name);
		
		uint32 segments = Mathf.Max(segs, 3) + 1,
			   rings = Mathf.Max(rgs, 3) + 2;
		
		float32 PI = Mathf.PI,
				TWO_PI = PI * 2.0f,
				HALF_PI = PI * 0.5f,
				R = 1.0f / (rings - 1),
				S = 1.0f / (segments - 1),
				x, y, z;

		uint32 r, s,
			   a, b, c, d;

		Array<Vec3f*>& vertices = mesh->vertices;
		Array<Vec3f*>& normals = mesh->normals;
		Array<Vec2f*>& uv = mesh->uv;
		Array<Colorf*>& colors = mesh->colors;
		Array<uint32>& indices = mesh->indices;
		
		for (r = 0; r < rings; r++) {
			for (s = 0; s < segments; s++) {
				x = Mathf.Cos(TWO_PI * s * S) * Mathf.Sin(PI * r * R);
				y = Mathf.Sin(TWO_PI * s * S) * Mathf.Sin(PI * r * R);
				z = Mathf.Sin(-HALF_PI + PI * r * R);

				vertices.Push(new Vec3f(x * radius, y * radius, z * radius));
				normals.Push(new Vec3f(x, y, z));
				uv.Push(new Vec2f(s * S, r * R));
				colors.Push(new Colorf(s * S, r * R, 0.0f));
			}
		}

		for (r = 0; r < rings - 1; r++) {
			for (s = 0; s < segments - 1; s++) {
				a = r * segments + s;
				b = r * segments + (s + 1);
				c = (r + 1) * segments + (s + 1);
				d = (r + 1) * segments + s;
				
				indices.Push(a);
				indices.Push(b);
				indices.Push(c);
				indices.Push(a);
				indices.Push(c);
				indices.Push(d);
			}
		}
		
		mesh->CalculateTangents();
		mesh->CalculateAABB();
		
		return mesh;
	}
	
	inline void Mesh::m_BuildPlane(Mesh* mesh, int32 u, int32 v, int32 ud, int32 vd, float32 width, int32 ws, float32 height, int32 hs, float32 depth, int32 ds) {
		Array<Vec3f*>& vertices = mesh->vertices;
		Array<Vec3f*>& normals = mesh->normals;
		Array<Colorf*>& colors = mesh->colors;
		Array<Vec2f*>& uv = mesh->uv;
		Array<uint32>& indices = mesh->indices;
		
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

		(*normal)[w] = depth > 0.0f ? 1.0f : -1.0f;

		for (iy = 0.0f; iy < gridY; iy++) {
			for (ix = 0.0f; ix < gridX; ix++) {
				(*vertex)[u] = ((ix + 1.0f) * sw - hw) * udir;
				(*vertex)[v] = ((iy + 1.0f) * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				colors.Push(new Colorf((ix + 1.0f) / gridX, 1.0f - (iy + 1.0f) / gridY, 0.0f));
				uv.Push(new Vec2f((ix + 1.0f) / gridX, 1.0f - (iy + 1.0f) / gridY));

				(*vertex)[u] = (ix * sw - hw) * udir;
				(*vertex)[v] = ((iy + 1.0f) * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				colors.Push(new Colorf(ix / gridX, 1.0f - (iy + 1.0f) / gridY, 0.0f));
				uv.Push(new Vec2f(ix / gridX, 1.0f - (iy + 1.0f) / gridY));

				(*vertex)[u] = (ix * sw - hw) * udir;
				(*vertex)[v] = (iy * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				colors.Push(new Colorf(ix / gridX, 1.0f - iy / gridY, 0.0f));
				uv.Push(new Vec2f(ix / gridX, 1.0f - iy / gridY));

				(*vertex)[u] = ((ix + 1.0f) * sw - hw) * udir;
				(*vertex)[v] = (iy * sh - hh) * vdir;
				(*vertex)[w] = depth;
				vertices.Push(new Vec3f(*vertex));
				colors.Push(new Colorf((ix + 1.0f) / gridX, 1.0f - iy / gridY, 0.0f));
				uv.Push(new Vec2f((ix + 1.0f) / gridX, 1.0f - iy / gridY));

				uint32 a = vertexCount,
					   b = vertexCount + 1,
					   c = vertexCount + 2,
					   d = vertexCount + 3;
				
				indices.Push(a);
				indices.Push(b);
				indices.Push(c);
				indices.Push(a);
				indices.Push(c);
				indices.Push(d);
				
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));
				normals.Push(new Vec3f(*normal));

				vertexCount += 4;
			}
		}
		
		delete normal;
		delete vertex;
	}
}

#endif