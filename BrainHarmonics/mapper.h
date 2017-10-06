#ifndef MAPPER_H
#define MAPPER_H

// Signatures

class mapper : public ArAction // Class action inherits from ArAction
{
 public:
   mapper(); // Constructor
   virtual ~mapper() {}  // Destructor
   virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
   ArActionDesired desiredState; // Holds state of the robot that we wish to action
 protected:
   int speed; // Speed of the robot in mm/s
};

#endif
