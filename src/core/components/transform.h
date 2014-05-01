#ifndef ODIN_TRANSFORM_H
#define ODIN_TRANSFORM_H

namespace Odin {

	class Transform : public Component {

		private:
			int32 m_depth;
			Transform* m_parent;
			Transform* m_root;
			Array<Transform*> m_children;
			uint32 m_childCount;

			inline void m_UpdateDepth(Transform* transform, int32 index);

		protected:
			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Clear(void);

			inline void p_Sort(void);

		public:
			Vec3f position, scale;
			Quatf rotation;

			Mat4f matrix, matrixWorld, modelView;
			Mat3f normalMatrix;

			inline Transform(void);
			inline Transform(std::string name);
			inline Transform(const Transform& other);
			inline Transform(const Transform&& other);
			inline ~Transform(void);

			inline virtual Transform& Copy(const Transform& other);
			inline virtual Transform& Move(const Transform&& other);
			
			inline void Update(void);
			inline void UpdateMatrices(const Mat4f& viewMatrix);

			inline int32 GetDepth(void);
			inline uint32 GetChildCount(void);

			inline Transform& AddChild(Transform* child);
			inline Transform& RemoveChild(Transform* child);
			
			inline Transform& operator =(const Transform& other);
			inline Transform& operator =(const Transform&& other);
	};
}

#endif