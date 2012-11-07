/* 
 * File:   main.cpp
 * Author: dawe
 *
 * Created on October 3, 2012, 12:40 PM
 */
#define CHECK_MSG_AMOUNT  1
#define CHECK_WORK 1000

#define COLOR_W 100
#define COLOR_B 101

#define MSG_WORK_REQUEST 1000
#define MSG_WORK_SENT    1001
#define MSG_WORK_NOWORK  1002
#define MSG_TOKEN        1003
#define MSG_FINISH       1004
#define MSG_BEST_RESULT  1005

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include "Container.h"
#include "common.h"
#include "common_p.h"
#include "mpi.h"

using namespace std;

/*
 Výsledky
 * 16x16/45 - 3m16s
 * 16x16/55 - 10m37s
 * 15x15/17 - 4m3s
 * 16x16/44 - 31m40s
 * 
 * 
 */

FILE *vstup;
#define SOUBOR "data/TestFile-(10x10)-30.txt"

int main(int argc, char** argv) {
    /* inicializace MPI, nastaveni ranku( id procesu) a rank_size ( pocet procesu )*/
    MPI_Init(&argc, &argv);
    int flag, rank, rank_size;
    double t1, t2;
    string log;

    // barva procesoru pro ADUV;
    int proc_barva = COLOR_W;
    int pesek = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_size);
    MPI_Status status;
    /* !inicializace*/

    int size, k, Q, V;
    vstup = fopen(SOUBOR, "r");
    if (vstup == NULL) {
        puts("Error, file not found or something like that...");
        exit(1);
    } else printf("File opened for reading...\n");

    int * figures = NULL;

    fscanf(vstup, "%i\n", &size);
    fscanf(vstup, "%i\n", &k);
    //cout << "Size: " << size << " / Figures: " << k << "." << endl;
    fscanf(vstup, "%i\n", &Q);
    fscanf(vstup, "%i\n", &V);

    figures = new int[k];
    int fCount = 0;

    while ((!feof(vstup)) && (fCount < k)) {
        fscanf(vstup, "%i\n", &figures[fCount]);
        fCount++;
    }


    cout << "From " << k << " expected figures, " << fCount << " was loaded." << endl << endl;
    fclose(vstup);
    //    }

    int best_possible = k * 10;
    deque<Container *> zasobnik;
    Container * start = new Container(size, k);
    Container * best = new Container(size, k);
    Container * printex = new Container(size, k);
    best->setResult(k * 20);

    cout << "Initial best: " << best->getResult() << " " << k << endl;
    cout << "Best possible: " << best_possible << endl << endl;


    /* data nahrava pouze prvni proces */
    if (rank == 0) {
        cout << "nahravam data";
        pesek = COLOR_W;
        start->setVez(V);
        printex->setVez(V);
        start->setKral(Q);
        printex->setKral(Q);

        start->setInitialHistory(Q, V);

        for (int i = 0; i < k; i++) {
            start->addFig(figures[i]);
            printex->addFig(figures[i]);
        }

        cout << "Init state:" << endl;
        start->printf();
        zasobnik.push_back(start);

        t1 = MPI_Wtime();
    } else {
        pesek = 0;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    log = itos(rank) + " barrier start\n";
    logToFile(rank,log);    
    /* !data ...  */
    int p = 0;
    int pd = 0;

    // Hlavní programová smyčka
    int citac = 0;
    int message;
    Container * r = new Container(size, k);
    bool finish = false;

    while (!finish) {
        citac++;
        if ((citac % CHECK_MSG_AMOUNT) == 0) {

            if (zasobnik.empty()) {
                if (rank_size > 1) {
                    int next_proc = (rank + 1) % rank_size;
                    log = "empty, " + itos(rank) + " process zacina zadat o praci " + itos(next_proc) + " process\n";                    
                    logToFile(rank, log);
                    masPraciMessage(rank, next_proc);
                    proc_barva = COLOR_W;
                    // mel sem peska, posilam a nuluju
                    if (pesek > 1) {
                        log = itos(rank) + " odesila peska:" + itos(pesek) + " na " + itos(next_proc) + "\n";
                        logToFile(rank,log);
                        sendToken(pesek, next_proc);
                        pesek = 0;
                    }
                } else {
                    // pracuju sam;
                    finish = true;
                    break;
                }
            }
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (flag) {
                //prisla zprava, je treba ji obslouzit
                //v promenne status je tag (status.MPI_TAG), cislo odesilatele (status.MPI_SOURCE)
                //a pripadne cislo chyby (status.MPI_ERROR)
                message = getMessage();
                int ask = status.MPI_SOURCE;
                switch (status.MPI_TAG) {
                    case MSG_BEST_RESULT:
                        // nekdo nasel nejlepsi vysledek
                        // porovnat s vlastnim
                        r = recvContainer(message, size, k);
                        if (r->getResult() < best->getResult()) {
                            best = r;
                            best->setPole(r->getPole());
                            best->setHistoryQV(r->getHistoryQV());
                            log = itos(rank) + " received new best result from " + itos(message) + "\n";
                            logToFile(rank,log);
                        }
                        //cout << rank << " best result:  " << endl << best->getResult() << endl;
                        break;
                    case MSG_WORK_REQUEST:
                        // zadost o praci, prijmout a dopovedet
                        // zaslat rozdeleny zasobnik a nebo odmitnuti MSG_WORK_NOWORK
                        //cout << rank << " pozadan " << message << " o praci.  ";
                        if (zasobnik.size() > 1) {
                            r = zasobnik.front();
                            mamPraciMessage(rank, message, r);
                            // jestli Pi posle praci procesoru Pj, i>j, Pi nastavi barvu na B;
                            if (message < rank) { 
                                //cout << rank << " poslal praci na " << message << ", obarvuji " << rank << " na B" << endl;
                                proc_barva = COLOR_B;
                            }
                            zasobnik.pop_front();
                            //cout << rank << " odeslal praci na " << message << " stack remaining: " << zasobnik.size() << endl;
                        } else {
                            //cout << rank << " nema praci pro " << message << " stack remaining: " << zasobnik.size() << endl;
                            nemamPraciMessage(message);
                        }
                        break;
                    case MSG_WORK_SENT:
                        // prisel rozdeleny zasobnik, prijmout
                        // deserializovat a spustit vypocet
                        //cout << rank << " process prijal praci" << endl;
                        r = recvContainer(message, size, k);
                        zasobnik.push_back(r);
                        break;
                    case MSG_WORK_NOWORK:
                        // odmitnuti zadosti o praci
                        // zkusit jiny proces
                        // a nebo se prepnout do pasivniho stavu a cekat na token
                        //cout << rank << " dostal nowork od " << ask << endl;
                        ask = (ask + 1) % rank_size;
                        if (ask == rank) {
                            // nikdo uz nema pro me praci;
                        }
                        if (ask != rank) {
                            //cout << rank << " process zada o praci " << ask << " process" << endl;
                            masPraciMessage(rank, ask);
                        }
                        break;
                    case MSG_TOKEN:
                        //ukoncovaci token, prijmout a nasledne preposlat
                        // - bily nebo cerny v zavislosti na stavu procesu
                        // jestlize Pi obdrzi peska, a Pi ma barvu B, nastavi Peska na B
                        log = itos(rank) + " dostal peska " + itos(message) + " od " + itos(ask) + "\n";
                        logToFile(rank,log);
                        pesek = message;
                        if (proc_barva == COLOR_B) {
                            log = itos(rank) + " procesor obarvuje peska na B\n";
                            logToFile(rank,log);
                            pesek = COLOR_B;
                        }
                        // jestlize P1 obdrzi peska COLOR_W, ukonci ( rozesle vsem ostatnim zpravu finish
                        if (rank == 0 && pesek == COLOR_W) {
                            logToFile(0,"prvni procesor dostal peska W\n");;
                            for (int i = 0; i < rank_size; i++) {
                                logToFile(0,"procesor 0 rozesila zpravu finish na " + itos(i) + "\n");
                                finishMessage(i);
                            }
                        }
                        // prvni zacina nove kolo, prebarvuje peska na W
                        if (rank == 0 && pesek == COLOR_B) {
                            logToFile(0, "nove kolo, 0 dostal peska B, obarvuje na W\n");
                            pesek = COLOR_W;
                        }
                        break;
                    case MSG_FINISH:
                        //konec vypoctu - proces 0 pomoci tokenu zjistil, ze jiz nikdo nema praci
                        //a rozeslal zpravu ukoncujici vypocet
                        //mam-li reseni, odeslu procesu 0
                        //nasledne ukoncim spoji cinnost
                        //jestlize se meri cas, nezapomen zavolat koncovou barieru MPI_Barrier (MPI_COMM_WORLD)
                        //MPI_Finalize();
                        //exit(0);
                        logToFile(rank, itos(rank) + " received finish msg\n");
                        finish = true;
                        break;
                    default:
                        cout << "neznamy typ zpravy: " << status.MPI_TAG << endl;
                        cout << "message = " << message << endl;
                        break;
                }
            }
        }

        if (!zasobnik.empty()) {
            // branchuj vrsek zasobniku
            Container * top = zasobnik.back();
            zasobnik.pop_back();
            if (top->zbyvaFigurek() == 0 && top->getResult() < best->getResult()) {
                best->setResult(top->getResult());
                best->setKral(top->getKral());
                best->setVez(top->getVez());
                best->setPole(top->getPole());

                best->setHistoryCount(top->getHistoryCount());
                best->setHistoryQV(top->getHistoryQV());
                best->setTahCount(top->getTahCount());
                log = "newbest found: " + itos(best->getResult()) + " " + itos(rank) + ". procesorem\n";
                logToFile(rank,log);
                //cout << "newbest found: " << best->getResult() << " " << rank << ". procesorem" << endl;
                if (best->getResult() == best_possible) {
                    log = "nalezena spodni mez\n";
                    logToFile(rank,log);
                    bestResultMessage(rank, rank_size, best);
                    log = itos(rank) + " odesila peska W na 0\n";
                    logToFile(rank,log);
                    sendToken(COLOR_W,0);
                    //break;
                } else {
                    bestResultMessage(rank, rank_size, best);
                }
            }
            int mincena = top->getResult() + (top->zbyvaFigurek()*10);
            //cout << mincena << endl;
            if (mincena >= k * 20) {
                break;
            }
            //cout << zasobnik.size() << " " << top->getResult() << " " << top->zbyvaFigurek() << "   " << best->getResult() << " " << p << " " << pd << endl;
            if (mincena >= best->getResult()) {
                delete top;
                pd++;
            } else {
                int * branchvez = new int [4];
                int * branchkral = new int [8];
                int vez = top->getVez();
                int kral = top->getKral();
                //vez
                hledejVRadku(vez, top, branchvez);
                hledejVSloupci(vez, top, branchvez);
                //kralovna
                hledejVRadku(kral, top, branchkral);
                hledejVSloupci(kral, top, branchkral);
                hledejSikmo1(kral, top, branchkral);
                hledejSikmo2(kral, top, branchkral);
                //// posun veze
                int * posunSloup = new int [size];
                int * posunRadek = new int [size];
                for (int i = 0; i < size; i++) {
                    posunRadek[i] = 0;
                }
                for (int i = 0; i < size; i++) {
                    posunSloup[i] = -1;
                }
                int x = vez / size;
                int y = vez % size;
                int ky = kral % size;

                // posun vlevo
                for (int i = y - 1; i >= 0; i--) {
                    if (top->isFig(vez - y + i)) break;
                    if (jeVeSloupciFigurka(i, top) > 0)
                        posunRadek[i] = 1;
                }
                // posun vpravo
                for (int i = y + 1; i < size; i++) {
                    if (top->isFig(vez + i)) break;
                    if (jeVeSloupciFigurka(i, top) > 0)
                        posunRadek[i] = 1;
                }
                // posun nahorudolu
                if (posunRadek[ky] == 1) {
                    for (int j = 0; j < size; j++) {
                        if (top->isOne(ky + (j * size))) {
                            posunSloup[j] = y + (j * size);
                        }
                    }
                }

                bool checkvez = false;
                for (int i = 0; i < 4; i++) {
                    if (branchvez[i] != -1) checkvez = true;
                }
                if (checkvez) {
                    for (int i = 0; i < 4; i++) {
                        if (branchvez[i] != -1) {
                            Container *ps = new Container(size, k);
                            p++;
                            ps->setKral(top->getKral());
                            ps->setResult(top->getResult());
                            ps->setVez(top->getVez());
                            ps->setPole(top->getPole());

                            ps->setHistoryCount(top->getHistoryCount());
                            ps->setHistoryQV(top->getHistoryQV());
                            ps->setTahCount(top->getTahCount());

                            ps->posunFigurku(branchvez[i], 4);
                            ps->addResult(10);
                            int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                            if (cena < best->getResult()) {
                                //if (cena < k * 20) {
                                zasobnik.push_back(ps);
                            } else {
                                pd++;
                                delete ps;
                            }
                        }
                    }
                } else {
                    for (int i = 0; i < size; i++) {
                        if (posunRadek[i] == 1) {
                            Container *ps = new Container(size, k);
                            p++;
                            ps->setKral(top->getKral());
                            ps->setResult(top->getResult());
                            ps->setVez(top->getVez());
                            ps->setPole(top->getPole());

                            ps->setHistoryCount(top->getHistoryCount());
                            ps->setHistoryQV(top->getHistoryQV());
                            ps->setTahCount(top->getTahCount());

                            ps->posunFigurku(((x * size) + i), 4);
                            ps->addResult(10);
                            int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                            if (cena < best->getResult()) {
                                //if (cena < k * 20) {
                                zasobnik.push_back(ps);
                            } else {
                                delete ps;
                                pd++;
                            }
                        }
                    }
                    for (int i = 0; i < size; i++) {
                        if (posunSloup[i] != -1) {
                            Container *ps = new Container(size, k);
                            p++;
                            ps->setKral(top->getKral());
                            ps->setResult(top->getResult());
                            ps->setVez(top->getVez());
                            ps->setPole(top->getPole());

                            ps->setHistoryCount(top->getHistoryCount());
                            ps->setHistoryQV(top->getHistoryQV());
                            ps->setTahCount(top->getTahCount());

                            ps->posunFigurku(posunSloup[i], 4);
                            ps->addResult(10);
                            int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                            if (cena < best->getResult()) {
                                //if (cena < k * 20) {
                                zasobnik.push_back(ps);
                            } else {
                                delete ps;
                                pd++;
                            }
                        }
                    }
                    for (int i = 0; i < 8; i++) {
                        if (branchkral[i] != -1) {
                            Container *ps = new Container(size, k);
                            p++;
                            ps->setKral(top->getKral());
                            ps->setResult(top->getResult());
                            ps->setVez(top->getVez());
                            ps->setPole(top->getPole());

                            ps->setHistoryCount(top->getHistoryCount());
                            ps->setHistoryQV(top->getHistoryQV());
                            ps->setTahCount(top->getTahCount());

                            ps->posunFigurku(branchkral[i], 8);
                            ps->addResult(15);
                            int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                            if (cena < best->getResult()) {
                                //if (cena < k * 20) {
                                zasobnik.push_back(ps);
                            } else {
                                delete ps;
                                pd++;
                            }
                        }
                    }
                }
                // uklid
                delete branchvez;
                delete branchkral;
                delete posunSloup;
                delete posunRadek;
                delete top;
                pd++;

            }
        }
    }
    logToFile(rank, itos(rank) + " out of loop\n");
    if (rank == 0) {
        MPI_Barrier(MPI_COMM_WORLD);
        logToFile(0,"0 barrier end\n");
        t2 = MPI_Wtime();
        logResult("-------------------------------\nprocs:" + itos(rank_size) + " best:" + itos(best->getResult()) + "\nspotrebovany cas: " + itos(t2-t1) + "\n");
        /*
        cout << "Best " << rank << ": " << best->getResult();
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
        printf("Spotrebovany cas je %f.\n", t2 - t1);
        
        best->printf();
        best->printHistroy();
        best->printTahCount();

        cout << "Rozpis tahu: " << endl;

        int * tahy = best->getHistoryQV();

        int i = 2;
        printex->printf();

        while (tahy[i] != -2) {
            // every two fields apply
            // VK VK VK VK VK
            // Věž
            if (tahy[i] != -1) {
                cout << "Vez skace na pole " << tahy[i] << endl;
                printex->posunFigurkuBezHistorie(tahy[i], 4);
            }
            i++;

            // Královna
            if (tahy[i] != -1) {
                cout << "Kralovna skace na pole " << tahy[i] << endl;
                printex->posunFigurkuBezHistorie(tahy[i], 8);
            }

            i++;

            printex->printf();
        }
        cout << "Konec vizualizace tahu." << endl;
         */
    } else {
        MPI_Barrier(MPI_COMM_WORLD);
        logToFile(rank, itos(rank) + " barrier end\n");
    }
    MPI_Finalize();
}

