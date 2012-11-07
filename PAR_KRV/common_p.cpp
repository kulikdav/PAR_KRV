#include <mpi.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "Container.h"

#define CONTAINER 1
#define POLE 2
#define HISTORY 3
#define MSG_WORK_REQUEST 1000
#define MSG_WORK_SENT    1001
#define MSG_WORK_NOWORK  1002
#define MSG_TOKEN        1003
#define MSG_FINISH       1004
#define MSG_BEST_RESULT  1005
#define LOGGER 0


MPI_Status status;

void sendContainer(Container * c, int dest) {
    int k = c->getK();
    int qvsize = c->getQVSize();
    MPI_Send(c, sizeof (class Container), MPI_BYTE, dest, CONTAINER, MPI_COMM_WORLD);
    MPI_Send(c->getPole(), (k * 4), MPI_BYTE, dest, POLE, MPI_COMM_WORLD);
    MPI_Send(c->getHistoryQV(), (qvsize * 4), MPI_BYTE, dest, HISTORY, MPI_COMM_WORLD);
}

Container * recvContainer(int source, int size, int k) {
    Container * c = new Container(size, k);
    MPI_Recv(c, sizeof (class Container), MPI_BYTE, source, CONTAINER, MPI_COMM_WORLD, &status);

    int * pole = new int[k];
    MPI_Recv(pole, (k * 4), MPI_BYTE, source, POLE, MPI_COMM_WORLD, &status);
    c->setPole(k, pole);

    int * history = new int[c->getQVSize()];
    MPI_Recv(history, (c->getQVSize()*4), MPI_BYTE, source, HISTORY, MPI_COMM_WORLD, &status);
    c->setHistoryQV(c->getQVSize(), history);
    return c;
}

void sendMessage(int m, int tag, int dest) {
    MPI_Send(&m, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
}

int getMessage() {
    int m = 0;
    MPI_Recv(&m, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    return m;
}
// posli pokud se ptas, jestli dest ma praci, v message je rank ( tam se posle ta prace )

void masPraciMessage(int rank, int dest) {
    sendMessage(rank, MSG_WORK_REQUEST, dest);
}
// odpoved, mam pripravenou praci, posilam container c

void mamPraciMessage(int rank, int dest, Container * c) {
    sendMessage(rank, MSG_WORK_SENT, dest);
    sendContainer(c, dest);
}
// odpoved, nemam zadnou praci

void nemamPraciMessage(int dest) {
    sendMessage(0, MSG_WORK_NOWORK, dest);
}

// nasel jsem lepsi vysledek, rozesilam vsem
// vsem krome sebe posli ze mas nejlepsi vysledek, posli Container best result

void finishMessage(int dest) {
    sendMessage(0, MSG_FINISH, dest);
}

void sendToken(int color, int dest) {
    sendMessage(color, MSG_TOKEN, dest);
}

void logToFile(int rank, string message) {
    if (LOGGER == 1) {
        ofstream myfile;
        char * name = new char[10];
        sprintf(name, "%d.txt", rank);
        myfile.open(name, ios::out | ios::app);
        myfile << message;
        myfile.close();
    }
}

void logResult(string message) {
    ofstream myfile;
    myfile.open("_result.txt", ios::out | ios::app);
    myfile << message;
    myfile.close();
}

string itos(double d) {
    stringstream s;
    s << d;
    return s.str();
}

string itos(int i) {
    stringstream s;
    s << i;
    return s.str();
}

void bestResultMessage(int rank, int ranksize, Container * bestResult) {
    for (int i = 0; i < ranksize; i++) {
        if (i != rank) {
            logToFile(rank, itos(rank) + "odesila best: " + itos(bestResult->getResult()) + " na " + itos(i) + "\n");
            sendMessage(rank, MSG_BEST_RESULT, i);
            sendContainer(bestResult, i);
        }
    }
}