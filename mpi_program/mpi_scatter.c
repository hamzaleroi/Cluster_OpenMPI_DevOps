#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    int data[8] = {101,102,103,104,105,106,107,108};
    int  recv_data[2];
    int root=0;
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // // Print off a hello world message
    // printf("Hello world from processor %s, rank %d out of %d processors\n",
    //        processor_name, world_rank, world_size);
    if(world_rank == root) {
        data = 12345678;
    }
    MPI_Scatter(
        data,1,MPI_INT
        recv_data,1,MPI_INT,
        root,MPI_COMM_WORLD
    )
    MPI_Bcast(&data,1,MPI_INT,root,MPI_COMM_WORLD);

    printf("Me processor having rank = %d, received %d from root  =  %d\n",world_rank, data,root);
    // Finalize the MPI environment.
    MPI_Finalize();
}