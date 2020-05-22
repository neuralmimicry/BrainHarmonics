#include "MpiComm.h"
#include <iostream>

using namespace std;

MPI_Datatype MpiComm::register_mpi_type(AER_Msg_t const &) {
    constexpr std::size_t num_members = 3;
    int lengths[num_members] = { 1, 1, 1 };

    MPI_Aint offsets[num_members] = { offsetof(AER_Msg_t, NodeAddr),
		offsetof(AER_Msg_t, LocalUnitAddr), offsetof(AER_Msg_t, payload)
              };
    MPI_Datatype types[num_members] = { MPI_UNSIGNED, MPI_UNSIGNED, MPI_INT };
    MPI_Datatype type;
    MPI_Type_create_struct(num_members, lengths, offsets, types, &type);
    MPI_Type_commit(&type);
    return type;
}

void MpiComm::deregister_mpi_type(MPI_Datatype type)
{
    MPI_Type_free(&type);
}

void MpiComm::Send_Data(AER_Msg_t const& msg) {
    if(world_rank == 0) {
        MPI_Datatype type = register_mpi_type(msg);

	cout << "Calling MPI_Send()..." << endl;

        MPI_Send(
          /* data         = */ &msg, 
          /* count        = */ 1, 
          /* datatype     = */ type, 
          /* destination  = */ 1, 
          /* tag          = */ 0, 
          /* communicator = */ MPI_COMM_WORLD);

        deregister_mpi_type(type);
    }
}

AER_Msg_t& MpiComm::Recv_Data() {
    static AER_Msg_t rmsg;	

    if(world_rank == 1) {
        MPI_Status s;

        MPI_Datatype type = register_mpi_type(rmsg);    

        cout << "Calling MPI_Recv()..." << endl;	
	MPI_Recv(
          /* data         = */ &rmsg, 
          /* count        = */ 1, 
          /* datatype     = */ type, 
          /* source       = */ 0, 
          /* tag          = */ 0, 
          /* communicator = */ MPI_COMM_WORLD, 
          /* status       = */ &s);

        deregister_mpi_type(type);
    }
    return rmsg;
}
