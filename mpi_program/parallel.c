#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>



int main(int argc, char const *argv[])
{
  // Initialize the MPI environment
  clock_t  start, end;
  int SIZE=200000;
  if(argc > 1) {
    SIZE=atoi(argv[1]);
  }
  double gap;
  int *a,*b,sum=0;
  int i=0;
  int index_start=0 , index_end=0, chunk=0;
  a = (int*)malloc(sizeof(int)*SIZE);
  b = (int*)malloc(sizeof(int)*SIZE);
  for ( i = 0; i < SIZE; i++)
  {
    a[i] = 1;
    b[i] = 2;
  }
  
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



  chunk = SIZE / world_size;
  index_start = world_rank * chunk;
  index_end = ((world_rank+1)*chunk < SIZE )? (world_rank+1)*chunk:SIZE;



  start = clock();
  for ( i = index_start; i < index_end; i++)
  {
    sum += a[i] *  b[i];
  }
  end = clock();
  gap = (double)(end - start);
  
  // Finalize the MPI environment.
  int *sums = (int * )malloc(sizeof(int)* world_size);
  double *gaps = (double * )malloc(sizeof(double)* world_size);
  MPI_Gather((void*)&sum,1,MPI_INT,
              sums,1,MPI_INT,
              0, MPI_COMM_WORLD

  );
  MPI_Gather(((void*)&gap),1,MPI_DOUBLE,
              gaps,1,MPI_DOUBLE,
              0, MPI_COMM_WORLD

  );
  int j=0, count=world_size;
  if( world_rank == 0) {
    int global_sum=0;
    double max_time=0;
    for (j = 0; j < count; j++)
  { 
      if(gaps[j] > max_time) max_time = gaps[j];
      global_sum += sums[j];
  }
    printf("size: %d,",SIZE);
    printf("parallel-degree: %d,",world_size);
    printf("global-sum: %d,",global_sum);
    printf("max-time:  %f\n",max_time/CLOCKS_PER_SEC);
  }
  MPI_Finalize();

  return 0;
  // commande: mpiexec --mca btl_tcp_if_include eth1 --np 1 -hostfile machines parallel
}
