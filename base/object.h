#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
    unsigned int ODIN_OBJECT_ID = 0;

    class Object {

        private:
            unsigned int m_id;
            std::string m_name;

        protected:


        public:

            Object() {
                m_id = ++ODIN_OBJECT_ID;
            }

            ~Object() {
                Destroy();
            }

            inline unsigned int GetID() {

                return m_id;
            }

            inline void virtual Destroy() {

            }

            inline std::string ToString() {

                return m_name;
            }
    };
}

#endif