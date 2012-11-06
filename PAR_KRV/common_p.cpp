#include <mpi.h>
#include "Container.h"

#define CONTAINER 1
#define POLE 2

int rank;
int rank_size;
MPI_Status status;

void init_p() {
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_size);
}

void sendContainer(Container * c, int dest) {
    int k = c->getK();
    MPI_Send(c, sizeof (class Container), MPI_BYTE, dest, CONTAINER, MPI_COMM_WORLD);
    MPI_Send(c->getPole(), (k*4), MPI_BYTE, dest, POLE, MPI_COMM_WORLD);
}

Container * recvContainer(int source,int size,int k) {
    Container * c = new Container(size, k);
    MPI_Recv(c, sizeof (class Container), MPI_BYTE, source, CONTAINER, MPI_COMM_WORLD, &status);
    int * pole = new int[k];
    MPI_Recv(pole, (k*4), MPI_BYTE, source, POLE, MPI_COMM_WORLD, &status);
    c->setPole(k, pole);
    return c;

}