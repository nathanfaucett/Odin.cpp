#ifndef ODIN_GAME_OBJECT_H
#define ODIN_GAME_OBJECT_H

namespace Odin {

    class GameObject : public Node {

        private:

        protected:

        public:

            GameObject() {

            }

            ~GameObject() {
                Destroy();
            }

            inline void virtual Destroy() {
                Node::Destroy();
            }
    };
}

#endif