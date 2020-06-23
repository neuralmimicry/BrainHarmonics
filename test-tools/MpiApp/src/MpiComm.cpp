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

AER_Msg_t* MpiComm::Bcast_Data(AER_Msg_t const& msg, vector<int>nodes) {
    int new_rank = -1;
    int new_size;
    int *ranks = &nodes[0];
    static AER_Msg_t rmsg = {0,0,0};

    MPI_Group  world_group, new_group;
    MPI_Comm   new_comm;

    // extract the original group handle
    // Get the group of processes in MPI_COMM_WORLD
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    MPI_Group_incl(world_group, nodes.size(), ranks, &new_group);

    // create new new communicator based on groups and then perform collective communications
    MPI_Comm_create_group(MPI_COMM_WORLD, new_group, 0, &new_comm);

    // If this rank isn't in the new communicator, it will be
    // MPI_COMM_NULL. Using MPI_COMM_NULL for MPI_Comm_rank or
    // MPI_Comm_size is erroneous
    if (MPI_COMM_NULL != new_comm) {
	MPI_Comm_rank(new_comm, &new_rank);
	MPI_Comm_size(new_comm, &new_size);
	// get rank in new group
        MPI_Group_rank (new_group, &new_rank);

	MPI_Datatype type = register_mpi_type(msg);
	cout << "Calling MPI_Bcast()..." << endl;
	if(new_rank == 0)
	    MPI_Bcast((void *)&msg, 1, type, 0, new_comm);
	else
	    MPI_Bcast(&rmsg, 1, type, 0, new_comm);

        MPI_Barrier(new_comm);

	deregister_mpi_type(type);
    }

    if (MPI_COMM_NULL != new_comm) {
	if(new_rank != 0) {
	    cout << "world_rank/size = " << world_rank << "/" << world_size << "\t";
	    cout << "new rank/size = " << new_rank << "/" << new_size << endl;
	}
    }

    MPI_Group_free(&world_group);
    MPI_Group_free(&new_group);
    if (MPI_COMM_NULL != new_comm)
        MPI_Comm_free(&new_comm);

    if(new_rank == 0) {
        return NULL;
    } else {
        return &rmsg;
    }
}
