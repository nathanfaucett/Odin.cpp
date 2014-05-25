#ifndef ODIN_BONE_H
#define ODIN_BONE_H

namespace Odin {

	class Bone : public Component {

		private:
			friend class MeshFilter;
			
			int32 m_parentIndex;
            std::string m_name;

            bool m_skinned;
            Mat4f m_bindPose;
            Mat4f m_uniform;

            bool m_inheritPosition;
            bool m_inheritRotation;
            bool m_inheritScale;
			
			Mat4f m_updateMatrix;
			Vec3f m_updatePosition;
			Vec3f m_updateScale;
			Quatf m_updateRotation;
		protected:
			inline void p_Sort(void);

		public:
			
			inline Bone(void);
			inline Bone(const Bone&) = default;
			inline Bone(Bone&&) = default;
			inline ~Bone(void);

			inline virtual Bone* Clone(void);
			inline virtual Bone& Copy(const Bone& other);
			
			inline void Update(void);
			inline void Clear(void);
			inline static float32 Sort(Bone* a, Bone* b);
			
			inline Bone& operator=(const Bone&)& = default;
			inline Bone& operator=(Bone&&)& = default;
	};
}

#endif