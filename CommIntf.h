#ifndef __COMMINTF_H__
#define __COMMINTF_H__

#include <cstdint>
#include <vector>

/*
 * Communication Type choice between OpenMPI or OpenMP
 */
typedef enum {
    BH_MPI = 0,
    MP,
    INVALID
} BH_CommType;

/* Encapsulation of Address Event Representation(AER) Message sent between 
 * nodes (in a cluster of neuromorphic units)
 * TODO:- Placeholder format defined to get started.Could be extended later
 */
typedef struct {
    uint32_t NodeAddr;
    uint32_t LocalUnitAddr;
    int payload; //spike info
} AER_Msg_t;

class CommIntf
{
    public:

	CommIntf() {}

	virtual ~CommIntf() {}

	virtual void Send_Data(AER_Msg_t const &) = 0;
	virtual AER_Msg_t& Recv_Data() = 0;
	virtual AER_Msg_t* Bcast_Data(AER_Msg_t const &, std::vector<int>ranks) = 0;
};

#endif
