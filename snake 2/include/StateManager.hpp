#pragma once
#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include<stack>
#include<memory>

#include "State.hpp"

namespace Engine{
    class StateManager
    {
        public:
            StateManager();
            ~StateManager();

            void Add(std::unique_ptr<State> toAdd,bool wantReplace =false);
            void PopCurrent();
            void ProcessStateChange();
            std::unique_ptr<State>& GetCurrent();
        private:
            std::stack<std::unique_ptr<State>> m_stateStack;
            std::unique_ptr<State> m_newState;
            bool m_add;
            bool m_remove;
            bool m_replace;

    };
}

#endif // STATEMANAGER_HPP
