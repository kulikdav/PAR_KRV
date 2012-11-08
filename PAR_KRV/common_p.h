#include <string>
using namespace std;

void sendContainer(Container * c, int dest);
Container * recvContainer(int source,int size, int k);
void sendMessage(int m, int tag, int dest);
int getMessage();
void masPraciMessage(int rank,int dest);
void mamPraciMessage(int sum, int dest);
void nemamPraciMessage(int dest);
void bestResultMessage(int rank, int ranksize, Container * bestResult);
void finishMessage(int dest);
void sendToken(int color, int dest);
void logToFile(int rank,int rs, string m);
void logResult(string message);
string itos(double d);
string itos(int i);
