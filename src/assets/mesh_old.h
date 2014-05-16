#ifndef ODIN_MESH_H
#define ODIN_MESH_H

namespace Odin {
	
	enum class MeshAttributeType : uint32 {
		None = 0,
		Float32 = 1, Float64 = 2,
		Int32 = 3, Int64 = 4,
		Uint32 = 5, Uint64 = 6
	};
	enum class MeshAttributeUsage : uint32 {
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY
	};
	enum class MeshAttributeTarget : uint32 {
		ArrayBuffer = GL_ARRAY_BUFFER,
		ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
	};
	
	class MeshAttribute {
		private:
			friend class OpenGLRenderer;
			friend class Mesh;

		protected:
			uint32 p_buffer;
			MeshAttributeType p_type;
			std::string p_name;
			
		public:
			inline MeshAttribute(void) {
				p_buffer = 0;
				p_type = MeshAttributeType::None;
			}
			inline virtual ~MeshAttribute(void) {}
			inline MeshAttributeType GetType(void) {
				return p_type;
			}
			inline uint32& GetBuffer(void) {
				return p_buffer;
			}
	};
	
	template <typename Type, MeshAttributeType AttributeType> class BaseMeshAttribute : public MeshAttribute {
		private:
			friend class OpenGLRenderer;
			friend class Mesh;
			Type* m_array;
            uint32 m_size;
            uint32 m_itemSize;
            MeshAttributeUsage m_usage;
            MeshAttributeTarget m_target;
            bool m_needsUpdate;
			
		public:
			inline BaseMeshAttribute(std::string Name, uint32 Size, uint32 ItemSize);
			inline ~BaseMeshAttribute(void);
			
			inline uint32 Length(void);
			
			inline void SetTarget(MeshAttributeTarget value);
			inline MeshAttributeTarget GetTarget(void);
			
			inline void SetUsage(MeshAttributeUsage value);
			inline MeshAttributeUsage GetUsage(void);
			
			inline void Set(Type* array, uint32 size, uint32 itemSize);
			inline void SetSize(uint32 size);
			inline void SetItemSize(uint32 itemSize);
			
			inline void SetX(uint32 index, Type x);
			inline void SetY(uint32 index, Type y);
			inline void SetZ(uint32 index, Type z);
			inline void SetXY(uint32 index, Type x, Type y);
			inline void SetXYZ(uint32 index, Type x, Type y, Type z);
			inline void SetXYZW(uint32 index, Type x, Type y, Type z, Type w);
			
			inline const Type* GetArray(void);
	};
	
	typedef BaseMeshAttribute<int32, MeshAttributeType::Int32> MeshAttributei;
	typedef BaseMeshAttribute<int64, MeshAttributeType::Int64> MeshAttributei64;
	typedef BaseMeshAttribute<uint32, MeshAttributeType::Uint32> MeshAttributeui;
	typedef BaseMeshAttribute<uint64, MeshAttributeType::Uint64> MeshAttributeui64;
	typedef BaseMeshAttribute<float32, MeshAttributeType::Float32> MeshAttributef;
	typedef BaseMeshAttribute<float64, MeshAttributeType::Float64> MeshAttributef64;
	
	
	class Mesh : public Asset {
		
		private:
			friend class OpenGLRenderer;
			
			bool m_needsUpdate;
		protected:

		public:
			std::unordered_map<std::string, MeshAttribute*> attributes;
			
			inline Mesh(std::string name, std::string src = "");
			inline virtual ~Mesh(void);
			
			inline virtual void Load(void);
			
			inline MeshAttribute* GetAttribute(const char* name);
			inline MeshAttribute* GetAttribute(std::string& name);
			inline void AddAttribute(MeshAttribute* attribute);
			inline void RemoveAttribute(MeshAttribute* attribute);
	};
}

#endif