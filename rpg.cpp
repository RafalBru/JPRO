#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <windows.h>
using namespace std;

char** mapa;
int kolumny = 121;
int wiersze = 27;
struct task
{
    int numer_misji;
    char opis[50];
};
struct przedmiot
{
    int atak;
    int leczenie;
    char opis[50];
    int waga;
    int wartosc;
    int obrona;
    int dlugosc, szerokosc;
    int poz_x, poz_y;
    int ID;
    przedmiot* parent;

};
struct ekwipunek
{
    int waga;
    int dlugosc, szerokosc;
    przedmiot eq[10][30];
};
struct bohater
{
    char nazwa[30];
    int pozycjaX;
    int pozycjaY;
    int zdrowie;
    int obrazenia;
    char punkt;
    int doswiadczenie;
    ekwipunek* eq[10][30];
    void (*move)(bohater*, bohater*);
};
bohater* Wojownik(struct bohater& wojownik)
{
    wojownik = *(bohater*)malloc(sizeof(bohater));
    wojownik.zdrowie = 100;
    wojownik.obrazenia = 15;
    wojownik.doswiadczenie = 0;
    wojownik.punkt = '@';
    return &wojownik;
}
bohater* Paladyn(struct bohater& paladyn)
{
    paladyn = *(bohater*)malloc(sizeof(bohater));
    paladyn.zdrowie = 80;
    paladyn.obrazenia = 20;
    paladyn.doswiadczenie = 0;
    paladyn.punkt = '@';
    return &paladyn;
}
bohater* Barbarzynca(struct bohater& barbarzynca)
{
    barbarzynca = *(bohater*)malloc(sizeof(bohater));
    barbarzynca.zdrowie = 110;
    barbarzynca.obrazenia = 25;
    barbarzynca.doswiadczenie = 0;
    barbarzynca.punkt = '@';
    return &barbarzynca;
}
bohater* PrzeciwnikGoblin(struct bohater& goblin)
{
    goblin = *(bohater*)malloc(sizeof(bohater));
    goblin.obrazenia = 10;
    goblin.zdrowie = 70;
    goblin.punkt = '*';
    strcpy_s(goblin.nazwa, "Goblib");
    return &goblin;
}
bohater* PrzeciwnikRycerz(struct bohater& rycerz)
{
    rycerz = *(bohater*)malloc(sizeof(bohater));
    rycerz.obrazenia = 25;
    rycerz.zdrowie = 100;
    rycerz.punkt = '*';
    strcpy_s(rycerz.nazwa, "Goblin");
    return &rycerz;
}
/*
void ruch_pasywny(bohater* Hero, bohater* Enemy)
{
    int obszar = 1;
    for (int x = Enemy->pozycjaX - obszar; x < Enemy->pozycjaX + obszar; x++)
    {
        for (int y = Enemy->pozycjaY - obszar; y < Enemy->pozycjaY + obszar; y++)
        {
            if (Hero->pozycjaX == x && Hero->pozycjaY == y)
            {
                if (x < Enemy->pozycjaX)
                {
                    Enemy->pozycjaX--;
                }
                else
                {
                    Enemy->pozycjaX++;
                }
                if (y < Enemy->pozycjaX)
                {
                    Enemy->pozycjaX--;
                }
                else
                {
                    Enemy->pozycjaX++;
                }
            }
        }
    }
}
void ruch_atak(bohater* Hero, bohater* Enemy)
{
    int obszar = 5;
    for (int x = Enemy->pozycjaX - obszar; x < Enemy->pozycjaX + obszar; x++)
    {
        for (int y = Enemy->pozycjaY - obszar; y < Enemy->pozycjaY + obszar; y++)
        {
            if (Hero->pozycjaX == x && Hero->pozycjaY == y)
            {
                if (x < Enemy->pozycjaX)
                {
                    Enemy->pozycjaX = Enemy->pozycjaX + 3;
                }
                else
                {
                    Enemy->pozycjaX = Enemy->pozycjaX - 2;
                }
                if (y < Enemy->pozycjaX)
                {
                    Enemy->pozycjaY = Enemy->pozycjaX + 3;
                }
                else
                {
                    Enemy->pozycjaY = Enemy->pozycjaY - 2;
                }
            }
        }
    }
}
void ruch_defensywny(bohater* Hero, bohater* Enemy)
{
    int obszar = 3;
    for (int x = Enemy->pozycjaX - obszar; x < Enemy->pozycjaX + obszar; x++)
    {
        for (int y = Enemy->pozycjaY - obszar; y < Enemy->pozycjaY + obszar; y++)
        {
            if (Hero->pozycjaX == x && Hero->pozycjaY == y)
            {
                if (x < Enemy->pozycjaX)
                {
                    Enemy->pozycjaX++;
                }
                else
                {
                    Enemy->pozycjaX--;
                }
                if (y < Enemy->pozycjaY)
                {
                    Enemy->pozycjaY++;
                }
                else
                {
                    Enemy->pozycjaY--;
                }
            }
        }
    }
}
*/
void licznik()
{
    int czas = 0;
    for (int i = 0;; i++)
    {
        Sleep(1000);
        czas++;
    }
    printf("Czas: %d sek.", czas);
}
void MapAllocation()
{
    mapa = (char**)malloc(wiersze * sizeof(char*));
    for (int i = 0; i < wiersze; i++)
    {
        mapa[i] = (char*)malloc(kolumny * sizeof(char));
    }
}
void MapGeneration()
{
    FILE* plik = NULL;
    plik = fopen("mapka.txt", "r"); 
    if (plik == NULL)
    {
        perror("Nie mozna otworzyc pliku");
    }
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            if(feof(plik) == 0)
            {
                mapa[i][j] = fgetc(plik);
                if (mapa[i][j] == '#')
                {
                    mapa[i][j] = 219;
                }
                printf("%c", mapa[i][j]);
            }
        }
    }
    fclose(plik);
}
task* Misja1(struct task& Misja1)
{
    Misja1.numer_misji = 1;
    strcpy_s(Misja1.opis, "Zabij 20 przeciwników");
    return &Misja1;
}
task* Misja2(struct task& Misja2)
{
    Misja2.numer_misji = 2;
    strcpy_s(Misja2.opis, "Zabij 50 przeciwników");
    return &Misja2;
}
void WybierzKlase()
{
    bohater* Hero;
    Hero = (bohater*)malloc(sizeof(bohater));
    printf("\n");
    printf("Wybierz klase postaci:\n");
    printf("[1] Wojownik\n");
    printf("[2] Paladyn\n");
    printf("[3] Barbarzynca\n");
    printf("\n");
    int wybor;
    wybor = getch();
    switch (wybor)
    {
    case '1':
        bohater* wojownik;
        wojownik = (bohater*)malloc(sizeof(bohater));
        Wojownik(*wojownik);
        Hero = wojownik;
        system("cls");
        printf("Wybrales klase Wojownik\n");
        printf("Zdrowie: %d\n", Hero->zdrowie);
        printf("Obrazenia: %d\n", Hero->obrazenia);
        printf("\n");
        printf("Ladowanie mapy...\n");
        Sleep(2000);
        system("cls");
        break;
    case '2':
        bohater* paladyn;
        paladyn = (bohater*)malloc(sizeof(bohater));
        Paladyn(*paladyn);
        Hero = paladyn;
        system("cls");
        printf("Wybrales klase Paladyn\n");
        printf("Zdrowie: %d\n", Hero->zdrowie);
        printf("Obrazenia: %d\n", Hero->obrazenia);
        printf("\n");
        printf("Ladowanie mapy...\n");
        Sleep(2000);
        system("cls");
        break;
    case '3':
        bohater* barbarzynca;
        barbarzynca = (bohater*)malloc(sizeof(bohater));
        Barbarzynca(*barbarzynca);
        Hero = barbarzynca;
        system("cls");
        printf("Wybrales klase Barbarzynca\n");
        printf("Zdrowie: %d\n", Hero->zdrowie);
        printf("Obrazenia: %d\n", Hero->obrazenia);
        printf("\n");
        printf("Ladowanie mapy...\n");
        Sleep(2000);
        system("cls");
        break;
    default:
        printf("Wybierz klase!");
    }
   
}
void Menu()
{
    printf("********************************************************************************************************************\n");
    printf("*                                               RPG ADVENTURE                                                      *\n");
    printf("*                                               Wcisnij P zeby zagrac.                                             *\n");
    printf("*                                               Wcisnij Q zeby wyjsc.                                              *\n");
    printf("********************************************************************************************************************\n");
}
void CzyGrac()
{
    char wybor;
    wybor = getch();
    switch (wybor)
    {
    case 'p':
        printf("Ladowanie..");
        Sleep(1000);
        system("cls");
        WybierzKlase();
        break;
    case 'q':
        exit(0);
        break;
    }
}
void RefreshMap()
{
    system("cls");
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            printf("%c", mapa[i][j]);
        }
    }
    printf("\n");
}
void MovingSystem()
{
    char klawisz;
    klawisz = getch();
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            switch (mapa[i][j])
            {
            case '@':
                if (klawisz == 'w' )
                {
                    int i2 = i - 1;
                    mapa[i][j] = ' ';
                    mapa[i2][j] = '@';
                    system("cls");
                    RefreshMap();
                }
                break;
            }
        }
    }
    Sleep(1000);
}
 ////////////////////////////////////////////////////////////////  FIFO (dynamiczna struktura danych)
struct MisjeStos
{
    int nr;
    MisjeStos* biezaca;
    MisjeStos* nastepna;
};
MisjeStos* dodaj(int nr, MisjeStos* koniec)
{
    MisjeStos* wsk;
    wsk = (MisjeStos*)malloc(sizeof(MisjeStos));
    wsk->nr = 1;
    wsk->nastepna = NULL;
    return wsk;
}
MisjeStos* usun(int *nr, MisjeStos* poczatek)
{
    if (poczatek)
    {
        MisjeStos* wsk;
        *nr = poczatek->nr;
        wsk = poczatek->nastepna;
        free(poczatek);
        return wsk;
    }
}
////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////   zapis do plików
void zapis()
{
    FILE* plik = NULL;
    FILE* plik2 = NULL;
    plik = fopen("zapis.txt", "w");
    plik2 = fopen("statystyki.txt", "w");
    if (plik == NULL)
    {
        printf("Problem z zapisem mapy");
    }
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            fprintf(plik, "%c", mapa[i][j]);
        }
    }
    fprintf(plik2, "123456789");
    fclose(plik);
    fclose(plik2);
    /*
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            fprintf(plik, "%c", mapa[i][j]);
        }
    }
    if (plik2 == NULL)
    {
        printf("Problem z zapisem postepu");
    }
    */

}
/////////////////////////////////////////////////////////////
void GenerowanieMobow(bohater* Enemy)
{
    int przeciwnicy = 40;
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        { 
            switch (mapa[i][j])
            {
            case ' ':
                for (int k = 0; k < przeciwnicy; k++)
                {
                    mapa[i][j] = Enemy->punkt;
                }
                break;
            }
        }
    }
}
void walka(bohater* Hero, bohater* Enemy)
{
    Hero->zdrowie = Hero->zdrowie - Enemy->obrazenia;
    Enemy->zdrowie = Enemy->zdrowie - Hero->obrazenia;
    Sleep(1000);
}
void czyKoniec(bohater* Hero, bohater* Enemy)
{
    if (Hero->zdrowie <= 0)
    {
        mapa[Hero->pozycjaX][Hero->pozycjaY] = ' ';
        printf("Game Over");
    }
    else if (Enemy->zdrowie <= 0)
    {
        mapa[Enemy->pozycjaX][Enemy->pozycjaY] = ' ';
    }
}
przedmiot* podniescTopor(struct przedmiot& topor) /* referencja (&), generowanie obiektu */
{
    topor = *(przedmiot*)malloc(sizeof(przedmiot)); 
    topor.atak = 30;
    topor.wartosc = 250;
    topor.dlugosc = 2;
    topor.szerokosc = 3;
    topor.ID = 1;
    strcpy_s(topor.opis, "Potezny topor barbarzyncy");
    return &topor;
}
przedmiot* podniescMiecz(struct przedmiot& miecz)
{
    miecz = *(przedmiot*)malloc(sizeof(przedmiot));
    miecz.atak = 50;
    miecz.wartosc = 100;
    miecz.dlugosc = 1;
    miecz.szerokosc = 3;
    strcpy_s(miecz.opis, "Miecz");
    return &miecz;
}
przedmiot* podniescMlot(struct przedmiot& mlot)
{
    mlot = *(przedmiot*)malloc(sizeof(przedmiot));
    mlot.atak = 30;
    mlot.wartosc = 100;
    mlot.dlugosc = 2;
    mlot.szerokosc = 3;
    strcpy_s(mlot.opis, "Młot");
    return &mlot;
}
void generuj_obiekt(przedmiot* topor) //generowanie obiektu w strukturze ekwipunek
{
    przedmiot* eq[10][30];
    topor = (przedmiot*)malloc(sizeof(przedmiot));
    // topor->ID = 1;
    int i, j;
    for (i = 0; i < topor->dlugosc; i++)
    {
        for (j = 0; j < topor->szerokosc; j++)
        {
            eq[topor->poz_x + i][topor->poz_y + j] = topor;
        }
    }
}
przedmiot* zerowanie(struct przedmiot& topor)
{
    topor.atak = 0;
    topor.leczenie = 0;
    topor.obrona = 0;
    topor.waga = 0;
    topor.wartosc = 0;
    topor.dlugosc = 0;
    topor.szerokosc = 0;
    strcpy_s(topor.opis, " ");
    return &topor;
}
int main()
{
    task* Misja1, Misja2;
    bohater* goblin, rycerz;
    przedmiot* topor, miecz, mlot;
    Menu();
    CzyGrac();
    MapAllocation();
    MapGeneration();
    while (1)
    {
        MovingSystem();
    } 
    
  /*
    topor = (przedmiot*)malloc(sizeof(przedmiot));
    moj_luk = (przedmiot*)malloc(sizeof(przedmiot));
    moj_luk2 = (przedmiot*)malloc(sizeof(przedmiot));

    podniescTopor(*topor);
    generuj_obiekt(topor);
    podniescLuk(*moj_luk);
 //   Enemy(*Barbarzynca); //generowanie przeciwnika
    zerowanie(*topor);
    */
   // moj_luk2 = moj_luk;                 //kopiowanie struktury
/*
    free(Barbarzynca);
    free(topor);                    
    free(moj_luk);
    free(moj_luk2);
    FreeMap();
    topor = NULL;
    moj_luk = NULL;
    moj_luk2 = NULL;
    Barbarzynca = NULL;
 */
    //return 0;
}
//ZAL (zrobić zapis do pliku, wskaźnik do funkcji)
/* 
15.03.22r.
przenoszenie do eq

długosc boków: width, height
kordynaty: x, y

struct przedmiot
{
...
przedmiot* parent = &przedmiot[1][1];
pos_X = parent->pos_x;
pos_Y = parent->pos_y;
}
 (
*/
/*for (int i = 0; i < moj_topor.dlugosc; i++)
 {
     for (int j = 0; j < moj_topor.szerokosc; j++)
     {
         obiekt[i][j] = 1;
     }
 }
 return ;
 */