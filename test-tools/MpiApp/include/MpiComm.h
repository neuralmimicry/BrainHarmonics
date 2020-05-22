#ifndef __MPICOMM_H__
#define __MPICOMM_H__

#include "CommIntf.h"
#include <mpi.h>

class MpiComm: public CommIntf
{
    public:
        MpiComm() {
            //Intialize the MPI Environment    
            MPI_Init(NULL,NULL);

	    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        }

        ~MpiComm() {
            MPI_Finalize();
	}

	void Send_Data(AER_Msg_t const &);
	AER_Msg_t& Recv_Data();

    private:
    	int world_rank;
        int world_size;

        MPI_Datatype register_mpi_type(AER_Msg_t const &);
	void deregister_mpi_type(MPI_Datatype type);
};

#endif
