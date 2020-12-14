#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "state.hpp"
#include <vector>

namespace ge {
    namespace state {
        class Handler {
        public:
            Handler(){}
            ~Handler(){ clearStates(); }

            void update(){ for(State *state : states){ state->update(); } }
            void render(){ for(State *state : states){ state->render(); } }

            void addState(State *state){
                states.push_back(state);
            }

            void removeState(){
                if(states.empty()){ return; }
                delete states.at(states.size() - 1);
                states.erase(states.begin() + (states.size() - 1));
            }

            void clearStates(){
                for(State *state : states){ delete state; }
                states.clear();
            }

        private:
            std::vector<State *> states;
        };
    }
}

#endif // !HANDLER_HPP