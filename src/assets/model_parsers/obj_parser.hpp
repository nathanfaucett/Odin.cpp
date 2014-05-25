#ifndef ODIN_OBJ_PARSER_HPP
#define ODIN_OBJ_PARSER_HPP

namespace Odin {
	
	namespace ObjParser {
		struct VertexIndex {
			int32 v_idx, vt_idx, vn_idx;
			
			VertexIndex() {};
			VertexIndex(int32 idx) {
				v_idx = idx;
				vt_idx = idx;
				vn_idx = idx;
			};
			VertexIndex(int32 vidx, int32 vtidx, int32 vnidx) {
				v_idx = vidx;
				vt_idx = vtidx;
				vn_idx = vnidx;
			};
		};
		
		static inline bool operator<(const VertexIndex& a, const VertexIndex& b) {
			if (a.v_idx != b.v_idx) return (a.v_idx < b.v_idx);
			if (a.vn_idx != b.vn_idx) return (a.vn_idx < b.vn_idx);
			if (a.vt_idx != b.vt_idx) return (a.vt_idx < b.vt_idx);

			return false;
		}
		
		Array<std::string> Explode(std::string aStr, char aDelim) {
			Array<std::string> res;
			std::string str = aStr.substr(0, aStr.find(aDelim));
			
			while (str.size() < aStr.size()) {
				res.Push(str);
				aStr = aStr.substr(aStr.find(aDelim) + 1);
				str = aStr.substr(0, aStr.find(aDelim));
			}
			
			res.Push(str);
			return res;
		}
		
		static inline bool IsSpace(const char c) {
			return (c == ' ') || (c == '\t');
		}
		
		static inline bool IsNewLine(const char c) {
			return (c == '\r') || (c == '\n') || (c == '\0');
		}
		
		static inline int32 FixIndex(int32 idx, int32 n) {
			int32 i;
		  
			if (idx > 0) {
				i = idx - 1;
			} else if (idx == 0) {
				i = 0;
			} else {
				i = n + idx;
			}
			
			return i;
		}
		  
		static inline std::string ParseString(const char*& token) {
			std::string s;
			int32 b = strspn(token, " \t");
			int32 e = strcspn(token, " \t\r");
			s = std::string(&token[b], &token[e]);
		  
			token += (e - b);
			return s;
		}

		static inline int32 ParseInt(const char*& token) {
			token += strspn(token, " \t");
			int32 i = atoi(token);
			token += strcspn(token, " \t\r");
			return i;
		}

		static inline float32 ParseFloat(const char*& token) {
			token += strspn(token, " \t");
			float32 f = static_cast<float32>(atof(token));
			token += strcspn(token, " \t\r");
			return f;
		}
		
		static inline void ParseFloat2(float& x, float& y, const char*& token) {
			x = ParseFloat(token);
			y = ParseFloat(token);
		}

		static inline void ParseFloat3(float& x, float& y, float& z, const char*& token) {
			x = ParseFloat(token);
			y = ParseFloat(token);
			z = ParseFloat(token);
		}
		
		static VertexIndex ParseTriple(const char* &token, int32 vsize, int32 vnsize, int32 vtsize) {
			VertexIndex vi(-1);
		
			vi.v_idx = FixIndex(atoi(token), vsize);
			token += strcspn(token, "/ \t\r");
			if (token[0] != '/') {
				return vi;
			}
			token++;
		
			if (token[0] == '/') {
				token++;
				vi.vn_idx = FixIndex(atoi(token), vnsize);
				token += strcspn(token, "/ \t\r");
				return vi;
			}
			
			vi.vt_idx = FixIndex(atoi(token), vtsize);
			token += strcspn(token, "/ \t\r");
			if (token[0] != '/') {
				return vi;
			}

			token++;
			vi.vn_idx = FixIndex(atoi(token), vnsize);
			token += strcspn(token, "/ \t\r");
			return vi; 
		}
		
		static uint32 UpdateVertex(
			std::map<VertexIndex, uint32>& vertexCache,
			Array<Vec3f*>& vertices,
			Array<Vec3f*>& normals,
			Array<Vec2f*>& uvs,
			const Array<Vec3f*>& in_vertices,
			const Array<Vec3f*>& in_normals,
			const Array<Vec2f*>& in_uvs,
			const VertexIndex& i)
		{
			const std::map<VertexIndex, uint32>::iterator it = vertexCache.find(i);
		  
			if (it != vertexCache.end()) {
				return it->second;
			}

			vertices.Push(in_vertices[i.v_idx]);
		  
			if (i.vn_idx >= 0) {
				normals.Push(in_normals[i.vn_idx]);
			}

			if (i.vt_idx >= 0) {
				uvs.Push(in_uvs[i.vt_idx]);
			}

			uint32 idx = vertices.Length() - 1;
			vertexCache[i] = idx;

			return idx;
		}
	}
	
	inline void Mesh::m_LoadObj(void) {
		Clear();
		
		Array<Vec3f*> v;
		Array<Vec3f*> vn;
		Array<Vec2f*> vt;
		std::vector<std::vector<ObjParser::VertexIndex>> faceGroup;
		
		std::string file = LoadFile(p_src);
		std::istringstream stream(file);
		
		while (!stream.eof()) {
			std::string line;
			std::getline(stream, line);
			
			if (line.size() > 0) {
				if (line[line.size()-1] == '\n') line.erase(line.size()-1);
			}
			if (line.size() > 0) {
				if (line[line.size()-1] == '\r') line.erase(line.size()-1);
			}
			
			if (line.empty()) continue;
			
			const char* token = line.c_str();
			token += strspn(token, " \t");

			assert(token);
			if (token[0] == '\0') continue;
			if (token[0] == '#') continue;
			
			if (token[0] == 'v' && ObjParser::IsSpace((token[1]))) {
				token += 2;
				Vec3f* vertex = new Vec3f;
				ObjParser::ParseFloat3(vertex->x, vertex->y, vertex->z, token);
				v.Push(vertex);
				continue;
			}
			
			if (token[0] == 'v' && token[1] == 'n' && ObjParser::IsSpace((token[2]))) {
				token += 3;
				Vec3f* normal = new Vec3f;
				ObjParser::ParseFloat3(normal->x, normal->y, normal->z, token);
				vn.Push(normal);
				continue;
			}
			
			if (token[0] == 'v' && token[1] == 't' && ObjParser::IsSpace((token[2]))) {
				token += 3;
				Vec2f* uvCoord = new Vec2f;
				ObjParser::ParseFloat2(uvCoord->x, uvCoord->y, token);
				vt.Push(uvCoord);
				continue;
			}
			
			if (token[0] == 'f' && ObjParser::IsSpace((token[1]))) {
				token += 2;
				token += strspn(token, " \t");
		  
				std::vector<ObjParser::VertexIndex> face;
				while (!ObjParser::IsNewLine(token[0])) {
					ObjParser::VertexIndex vi = ObjParser::ParseTriple(token, v.Length(), vn.Length(), vt.Length());
					face.push_back(vi);
					int32 n = strspn(token, " \t\r");
					token += n;
				}
		  
				faceGroup.push_back(face);
				
				continue;
			}
		}
		
		std::map<ObjParser::VertexIndex, uint32> vertexCache;
		for (size_t i = 0; i < faceGroup.size(); i++) {
			const std::vector<ObjParser::VertexIndex>& face = faceGroup[i];

			ObjParser::VertexIndex i0 = face[0];
			ObjParser::VertexIndex i1(-1);
			ObjParser::VertexIndex i2 = face[1];

			size_t npolys = face.size();

			for (size_t k = 2; k < npolys; k++) {
				i1 = i2;
				i2 = face[k];

				uint32 v0 = ObjParser::UpdateVertex(vertexCache, vertices, normals, uv, v, vn, vt, i0);
				uint32 v1 = ObjParser::UpdateVertex(vertexCache, vertices, normals, uv, v, vn, vt, i1);
				uint32 v2 = ObjParser::UpdateVertex(vertexCache, vertices, normals, uv, v, vn, vt, i2);
		  
				indices.Push(v0);
				indices.Push(v1);
				indices.Push(v2);
			}
		}
	}
}

#endif