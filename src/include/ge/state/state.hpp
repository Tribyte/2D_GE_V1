#ifndef STATE_HPP
#define STATE_HPP

namespace ge {
    class State {
    public:
        virtual void update() = 0;
        virtual void render() = 0;
    };
}

#endif // !STATE_HPP

#include "handler.hpp"