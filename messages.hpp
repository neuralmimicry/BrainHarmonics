//
//  messages.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 22/03/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef messages_hpp
#define messages_hpp

#include <stdio.h>
#include <iostream>

class Messages
{
public:
    /** Default constructor */
    Messages();
    /** Default destructor */
    virtual ~Messages();
    bool loadFromFile(const std::string& filename) {
        char * dir = getcwd(NULL, 0);
        g_messages.clear();
        std::string entry;
        while (std::getline(messageFile, entry))
            {
            g_messages.push_back(entry);
            }
        

        return true; }
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    /** Set m_Counter
     * \param val New value to set
     */
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Message list created." << std::endl; }
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
};

#endif /* messages_hpp */
