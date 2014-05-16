#ifndef ODIN_MESH_CPP
#define ODIN_MESH_CPP
namespace Odin {

	template <typename Type, MeshAttributeType AttributeType> inline BaseMeshAttribute<Type, AttributeType>::BaseMeshAttribute(std::string Name, uint32 Size, uint32 ItemSize) : MeshAttribute() {
		p_name = Name;
		m_size = Size;
		m_itemSize = ItemSize;
		m_array = new Type[m_size * m_itemSize];
		m_target = MeshAttributeTarget::ArrayBuffer;
		m_usage = MeshAttributeUsage::StaticDraw;
		m_needsUpdate = true;
		p_type = AttributeType;
	}
	template <typename Type, MeshAttributeType AttributeType> inline BaseMeshAttribute<Type, AttributeType>::~BaseMeshAttribute(void) {
		delete []m_array;
	}
	
	template <typename Type, MeshAttributeType AttributeType> inline uint32 BaseMeshAttribute<Type, AttributeType>::Length(void) {
		return m_size;
	}
	
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetTarget(MeshAttributeTarget value) {
		m_target = value;
		m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline MeshAttributeTarget BaseMeshAttribute<Type, AttributeType>::GetTarget(void) {
		return m_target;
	}
	
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetUsage(MeshAttributeUsage value) {
		m_usage = value;
		m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline MeshAttributeUsage BaseMeshAttribute<Type, AttributeType>::GetUsage(void) {
		return m_usage;
	}
	
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::Set(Type* array, uint32 size, uint32 itemSize) {
		delete []m_array;
		m_array = array;
		m_size = size;
		m_itemSize = itemSize;
		m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetSize(uint32 size) {
		if (m_size == size) return;
		m_size = size;
		delete []m_array;
		m_array = new Type[m_size * m_itemSize];
		m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetItemSize(uint32 itemSize) {
		if (m_itemSize == itemSize) return;
		m_itemSize = itemSize;
		delete []m_array;
		m_array = new Type[m_size * m_itemSize];
		m_needsUpdate = true;
	}

	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetX(uint32 index, Type x) {
		m_array[index * m_itemSize] = x;
        m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetY(uint32 index, Type y) {
		m_array[index * m_itemSize + 1] = y;
        m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetZ(uint32 index, Type z) {
		m_array[index * m_itemSize + 2] = z;
        m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetXY(uint32 index, Type x, Type y) {
		index *= m_itemSize;
		m_array[index] = x;
		m_array[index + 1] = y;
        m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetXYZ(uint32 index, Type x, Type y, Type z) {
		index *= m_itemSize;
		m_array[index] = x;
		m_array[index + 1] = y;
		m_array[index + 2] = z;
        m_needsUpdate = true;
	}
	template <typename Type, MeshAttributeType AttributeType> inline void BaseMeshAttribute<Type, AttributeType>::SetXYZW(uint32 index, Type x, Type y, Type z, Type w) {
		index *= m_itemSize;
		m_array[index] = x;
		m_array[index + 1] = y;
		m_array[index + 2] = z;
		m_array[index + 3] = w;
        m_needsUpdate = true;
	}
	
	template <typename Type, MeshAttributeType AttributeType> inline const Type* BaseMeshAttribute<Type, AttributeType>::GetArray(void) {
		return m_array;
	}
	
	
	inline Mesh::Mesh(std::string name, std::string src) : Asset(name, src) {
		m_needsUpdate = true;
	}
	inline Mesh::~Mesh(void) {
		attributes.clear();
	}
	
	inline void Mesh::Load(void) {
		
	}
	
	inline MeshAttribute* Mesh::GetAttribute(const char* name) {
		return attributes[name];
	}
	inline MeshAttribute* Mesh::GetAttribute(std::string& name) {
		return attributes[name];
	}
	inline void Mesh::AddAttribute(MeshAttribute* attribute) {
		MeshAttribute* index = attributes[attribute->p_name];

		if (index == NULL) {
			attributes[attribute->p_name] = attribute;
		}
	}
	inline void Mesh::RemoveAttribute(MeshAttribute* attribute) {
		MeshAttribute* index = attributes[attribute->p_name];

		if (index != NULL) {
			attributes[attribute->p_name] = NULL;
		}
	}
}

#endif