//
//  messages.cpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 22/03/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#include <cstdlib>
#include <cstring>
#include "messages.hpp"

Messages::Messages() :
m_messages  (NULL) {}

Messages::~Messages()
{
    cleanup();
}

bool Messages::loadFromFile(const std::string& filename)
{
}

const Messages::Info& Font::getInfo() const
{
    return m_info;
}

void Messages::cleanup()
{
        // Check if we must destroy the Message pointers
    if (m_refCount)
        {
            // Decrease the reference counter
        (*m_refCount)--;
        
            // Free the resources only if we are the last owner
        if (*m_refCount == 0)
            {
                // Delete the reference counter
            delete m_refCount;
            
                // Destroy the messages
            if (m_messages)
                delete static_cast<Messages>(m_messages);
            }
        }
    
        // Reset members
    m_messages   = NULL;
    m_refCount  = NULL;
}
