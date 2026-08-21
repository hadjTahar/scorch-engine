#ifndef INPUTEVENTCOMPONENT_H
#define INPUTEVENTCOMPONENT_H

#include "corecomponent.h"

#include "keycomponent.h"
#include "mousecomponent.h"
#include <core/graphicsitem.h>

#include <misc/mouseevent.h>
#include <misc/keyevent.h>
#include <misc/sequenceevent.h>

/// ## Godot like inputs
/// ## Not implemented yet



namespace Qx
{


template<typename ActionType>
class InputEventComponent : public prv::CoreComponent
{
public:
    InputEventComponent(prv::GraphicsItem *parentItem):
        CoreComponent{ parentItem }
    {
        auto mCmp = parentItem->attach<MouseComponent>();
        auto kCmp = parentItem->attach<KeyComponent>();
        mCmp->setMousePolicy( MousePolicy::AlwaysCapture );
        kCmp->setFocusPolicy( FocusPolicy::Always );
        // kCmp->setFocused( true );


        mCmp->pressed = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };
        mCmp->released = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };
        mCmp->clicked = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };


        mCmp->move = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };


        mCmp->enter = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };


        mCmp->leave = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };


        mCmp->wheel = [this]( const MouseEvent &evt)
        {
            pushMouseAction( evt );
            /// ## Return accepted as false
            return false;
        };



        /// ## -------------------------------------------------------

        kCmp->keyPressed = [this]( const KeyEvent &evt)
        {
            const x_string tmp = SDL_GetKeyName(evt.key());
            if( !m_keyInputs.contains( tmp ) )
                return true;
            m_actions.push_back( m_keyInputs[tmp] );
            return true;
        };

        kCmp->sequence = [this]( const SequenceEvent &evt)
        {
            /// ## x_sequenceCallback from string Eg: Ctrl+R
            return true;
        };

        /// ## -------------------------------------------------------

    }

    void reset()
    {
        m_keyInputs.clear();
        m_mouseInputs.clear();
        m_actions.clear();
        m_mouseEvents.clear();
    }
    void addInput(const ActionType   &action,
                  const x_string &input )
    {
        m_keyInputs[ input] = action;
    }

    void addInput(const ActionType &action,
                  MouseButton button,
                  MouseEventType eventType)
    {
        m_mouseInputs[ {button,eventType}] = action;
    }

    bool checkAction(const ActionType &act)
    {
        bool ret = false;
        auto actIt = std::find(m_actions.begin(), m_actions.end(), act);
        if (actIt != m_actions.end()) {
            m_actions.erase(actIt);
            ret = true;
        }
        return ret;
    }

    bool checkAction(const ActionType &act, x_vector3 &pt)
    {
        bool ret = false;
        auto actIt = std::find(m_actions.begin(), m_actions.end(), act);
        if (actIt != m_actions.end()) {
            m_actions.erase(actIt);
            ret = true;
            pt = m_mouseEvents[*actIt];
        }
        return ret;
    }



private:
    void pushMouseAction(const MouseEvent &evt)
    {
        const std::pair<MouseButton,MouseEventType> tmp = { evt.button(), evt.eventType() };
        if( !m_mouseInputs.contains( tmp ) )
            return;
        const auto act = m_mouseInputs[tmp];
        m_actions.push_back( act );
        m_mouseEvents[act] = {evt.x(), evt.y(), 0 };
    }

private:
    /// ## Key Input, Action
    std::map<x_string, ActionType > m_keyInputs;
    /// ## MouseInput, Action
    std::map<std::pair<MouseButton,MouseEventType>, ActionType> m_mouseInputs;
    std::vector<ActionType> m_actions;

    std::map<ActionType, x_vector3> m_mouseEvents;

};

}

#endif // INPUTEVENTCOMPONENT_H
