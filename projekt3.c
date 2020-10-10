#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct Lista1
{
    char katalog[16];
    struct Lista1 *nast, *pop;
    struct Lista2 *pierwsza, *ostatnia;
} Katalog;

typedef struct Lista2
{
    char tytul[21];
    char kraj[16];
    char numer[6];
    struct Lista2 *nast, *pop;
} Ksiazka;

struct Handler
{
     Katalog *glowa, *ogon;
};


void dodajKatalog (struct Handler *h)
{
    char tab[16];
    int k,czydobry;
    Katalog *tmp;
    do
    {
        printf ("Katalog: ");
        fflush (stdin);
        tmp=h->glowa;
        czydobry=1;
        scanf ("%16s", tab);
        tab[0]=toupper(tab[0]);
        while (tmp!=NULL)
        {
            if (strcmp(tmp->katalog, tab)==0)
            {
                printf ("Taki ktalog juz istnieje.\n");
                czydobry=0;
                break;
            }
            tmp=tmp->nast;
        }
        if (((strlen(tab)))>15)
        {
            printf ("Nazwa katalogu jest za dluga. \n");
            czydobry=0;
        }
        for (k=0; k<strlen(tab); ++k)
        if ( ( tab[k]<65 || tab[k]>90 ) && ( tab[k]<97 || tab[k]>122 ) && tab[k]!=32 )
        {
            printf ("Podano zly format danych. \n");
            czydobry=0;
            break;
        }
    } while (czydobry==0);

    Katalog *temp;
    temp=(Katalog*)malloc(sizeof(Katalog));
    strcpy (temp->katalog, tab);
    temp->pierwsza=NULL;
    temp->ostatnia=NULL;
    if (h->ogon==NULL)
    {
        h->glowa=temp;
        h->ogon=temp;
        temp->nast=NULL;
        temp->pop=NULL;
        return;
    }
    h->ogon->nast=temp;
    temp->pop=h->ogon;
    h->ogon=temp;
    temp->nast=NULL;
}


void dodajKsiazke (struct Handler h)
{
    int k,czydobry;
    char tmp[16], tabtyt[21], tabnum[6], tabkraj[16];
    Katalog *tmp1;
    Ksiazka *tmp2;
    Katalog *tmp3;
    Ksiazka *tmp4;
    Ksiazka *tmp5;
    printf ("Podaj nazwe katalogu, do ktorego chcesz dodac ksiazke: ");
    fflush(stdin);
    scanf ("%16s", tmp);
	tmp1=h.glowa;
	while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
        {
            tmp2=(Ksiazka*)malloc(sizeof(Ksiazka));

            do
            {
                printf ("Tytul: ");
                fflush (stdin);
                czydobry=1;
                scanf ("%21s", tabtyt);
                if (((strlen(tabtyt)))>20)
                {
                    printf ("Tytul jest za dlugi. \n");
                    czydobry=0;
                }
            } while (czydobry==0);
            tabtyt[0]=toupper(tabtyt[0]);
            strcpy (tmp2->tytul, tabtyt);

            do
            {
                printf ("Numer: ");
                fflush (stdin);
                tmp3=h.glowa;
                while (tmp3!=NULL)
                {
                    tmp4=tmp3->pierwsza;
                    if (tmp4!=NULL)
                        break;
                    tmp3=tmp3->nast;
                }
                czydobry=1;
                scanf ("%6s", tabnum);
                while (tmp3!=NULL)
                {
                    if (strcmp(tmp4->numer, tabnum)==0)
                    {
                        printf ("Taki numer juz znajduje sie w bazie.\n");
                        czydobry=0;
                        break;
                    }
                    tmp4=tmp4->nast;
                    if (tmp4==NULL)
                    {
                        tmp3=tmp3->nast;
                        while (tmp3!=NULL)
                        {
                            tmp4=tmp3->pierwsza;
                            if (tmp4!=NULL)
                                break;
                            tmp3=tmp3->nast;
                        }
                    }
                }
                if (((strlen(tabnum)))!=5)
                {
                    printf ("Nieprawidlowa dlugosc. \n");
                    czydobry=0;
                }
                for (k=0; k<strlen(tabnum); ++k)
                    if ( ( tabnum[k]<48 || tabnum[k]>57 )  )
                {
                    printf ("Podano zly format danych. \n");
                    czydobry=0;
                    break;
                }
            } while (czydobry==0);
            strcpy (tmp2->numer, tabnum);

            do
            {
                printf ("Kraj: ");
                fflush (stdin);
                czydobry=1;
                scanf ("%16s", tabkraj);
                if (((strlen(tabkraj)))>15)
                {
                    printf ("Nazwa kraju jest za dluga. \n");
                    czydobry=0;
                }
                for (k=0; k<strlen(tabkraj); ++k)
                    if ( ( tabkraj[k]<65 || tabkraj[k]>90 ) && ( tabkraj[k]<97 || tabkraj[k]>122 ) && tabkraj[k]!=32   )
                    {
                        printf ("Podano zly format danych. \n");
                        czydobry=0;
                        break;
                    }
            } while (czydobry==0);
            tabkraj[0]=toupper(tabkraj[0]);
            strcpy (tmp2->kraj, tabkraj);
            tmp2->nast=NULL;
            if (tmp1->ostatnia==NULL)
            {
                tmp1->pierwsza=tmp2;
                tmp1->ostatnia=tmp2;
                tmp2->pop=NULL;
            }
                else
                {
                    tmp5=tmp1->ostatnia;
                    tmp5->nast=tmp2;
                    tmp2->pop=tmp5;
                    tmp1->ostatnia=tmp2;
                }


            return;
        }
        tmp1=tmp1->nast;
    }
    printf ("Nie ma takiego katalogu.\n");
    dodajKsiazke (h);

}


void zmienNazwe (struct Handler *h)
{
    int k,czydobry;
    char tmp[16], nazwa[16];
    Katalog *tmp1;
    printf ("Podaj nazwe katalogu, ktorego nazwe chcesz zmienic: ");
    fflush(stdin);

    scanf ("%16s", tmp);

	tmp1=h->glowa;
	while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
        {
            do
            {
                printf ("Nowa nazwa katalogu: ");
                fflush (stdin);
                czydobry=1;
                scanf ("%16s", nazwa);
                if (((strlen(nazwa)))>15)
                {
                    printf ("Nieprawidlowa dlugosc. \n");
                    czydobry=0;
                }
                for (k=0; k<strlen(nazwa); ++k)
                    if ( ( nazwa[k]<65 || nazwa[k]>90 ) && ( nazwa[k]<97 || nazwa[k]>122 ) && nazwa[k]!=32 )
                    {
                        printf ("Podano zly format danych. \n");
                        czydobry=0;
                        break;
                    }
            } while (czydobry==0);
            nazwa[0]=toupper(nazwa[0]);
            strcpy (tmp1->katalog, nazwa);
            return;
        }
        tmp1=tmp1->nast;
    }
    printf ("Nie ma takiego katalogu.\n");
    zmienNazwe (h);
}

void poprawDane (struct Handler *h)
{
    int k,czyjest,czydobry;
    char tmp[16], tyt[21], a, w[2], tabtyt[21], tabnum[6], tabkraj[16];
    Katalog *tmp1;
    Ksiazka *tmp2;
    Katalog *tmp3;
    Ksiazka *tmp4;
    printf ("Wybierz ksiazke:\nKatalog: ");
    fflush(stdin);
    scanf ("%16s", tmp);
	tmp1=h->glowa;
	while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
        {
                do
                {
                    tmp2=tmp1->pierwsza;
                    printf ("Tytul: ");
                    scanf ("%21s", tyt);
                    if (strcmp(tmp2->tytul, tyt)==0)
                        break;
                    else
                    {
                        tmp2=tmp2->nast;
                        if (tmp2==NULL)
                        {
                            printf ("Nie ma takiej ksiazki w tym katalogu.\n");
                        }
                    }
                } while (1);
                do
                {
                    czyjest=1;
                    printf ("Wybierz dana do poprawienia:\n1- Tytul\n2- Numer\n3- Kraj: ");
                    scanf ("%2s", w);
                    if (( w[0]!='1' && w[0]!='2' && w[0]!='3' ) || strlen(w)!=1)
                    {
                        printf ("Nie ma takiej czynnosci.\n\n");
                        czyjest=0;
                        fflush (stdin);
                    }
                }   while (czyjest==0);
            a=w[0];
            switch (a)
            {
            case '1':
                {
                    do
                    {
                        printf ("Tytul: ");
                        fflush (stdin);
                        czydobry=1;
                        scanf ("%21s", tabtyt);
                        if (((strlen(tabtyt)))>20)
                        {
                            printf ("Tytul jest za dlugi. \n");
                            czydobry=0;
                        }
                    } while (czydobry==0);
                    tabtyt[0]=toupper(tabtyt[0]);
                    strcpy (tmp2->tytul, tabtyt);
                    break;
                }
            case '2':
                {
                    do
                    {
                        printf ("Numer: ");
                        fflush (stdin);
                        tmp3=h->glowa;
                        tmp4=tmp3->pierwsza;
                        czydobry=1;
                        scanf ("%6s", tabnum);
                        while (tmp3!=NULL)
                        {
                            if (tmp4==NULL)
                            {
                                break;
                            }
                            if (strcmp(tmp4->numer, tabnum)==0)
                            {
                                printf ("Taki numer juz znajduje sie w bazie.\n");
                                czydobry=0;
                                break;
                            }
                            else
                            {
                                tmp4=tmp4->nast;
                                if (tmp4==NULL)
                                {
                                    tmp3=tmp3->nast;
                                    if (tmp3!=NULL)
                                tmp4=tmp1->pierwsza;
                                }
                            }
                        }
                        if (((strlen(tabnum)))!=5)
                        {
                            printf ("Nieprawidlowa dlugosc. \n");
                            czydobry=0;
                        }
                            for (k=0; k<strlen(tabnum); ++k)
                            if ( ( tabnum[k]<48 || tabnum[k]>57 )  )
                        {
                            printf ("Podano zly format danych. \n");
                            czydobry=0;
                            break;
                        }
                    } while (czydobry==0);
                    strcpy (tmp2->numer, tabnum);
                    break;
                }
            case '3':
                {
                    do
                    {
                        printf ("Kraj: ");
                        fflush (stdin);
                        czydobry=1;
                        scanf ("%16s", tabkraj);
                        if (((strlen(tabkraj)))>15)
                        {
                            printf ("Nazwa kraju jest za dluga. \n");
                            czydobry=0;
                        }
                        for (k=0; k<strlen(tabkraj); ++k)
                            if ( ( tabkraj[k]<65 || tabkraj[k]>90 ) && ( tabkraj[k]<97 || tabkraj[k]>122 ) && tabkraj[k]!=32   )
                            {
                                printf ("Podano zly format danych. \n");
                                czydobry=0;
                                break;
                            }
                    } while (czydobry==0);
                    tabkraj[0]=toupper(tabkraj[0]);
                    strcpy (tmp2->kraj, tabkraj);
                    break;
                }
            }

            return;
        }
        tmp1=tmp1->nast;
    }
    printf ("Nie ma takiego katalogu.\n");
    poprawDane (h);
}

void usunKatalog (struct Handler *h)
{
    char tmp[16];
    Katalog *tmp1;
    Katalog *tmp2;
    printf ("Podaj nazwe katalogu, ktory chcesz usunac: ");
    fflush(stdin);

    scanf ("%16s", tmp);
    tmp1=h->glowa;
    while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
            break;
        else tmp1=tmp1->nast;
        if (tmp1==NULL)
        {
            printf ("Nie ma takiego katalogu.\n");
            usunKatalog(h);
        }
    }
	tmp1=h->glowa;
	while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
        {
            if (tmp1==h->glowa && tmp1==h->ogon)
            {
                h->glowa=NULL;
                h->ogon=NULL;
                free (tmp1);
                return;
            }
            if (tmp1==h->glowa)
            {
                h->glowa=tmp1->nast;
                tmp1->nast->pop=NULL;
                free (tmp1);
                return;
            }
        }
        if (strcmp(tmp1->nast->katalog, tmp)==0)
        {
            if (tmp1->nast==h->ogon)
            {
                h->ogon=tmp1;
                tmp2=tmp1->nast;
                tmp1->nast=NULL;
                free (tmp2);
                return;
            }
            tmp2=tmp1->nast;
            tmp1->nast=tmp1->nast->nast;
            tmp1->nast->pop=tmp1;
            free (tmp2);
            return;
        }
            tmp1=tmp1->nast;
    }
}


void wypiszKatalogi(struct Handler *h)
{
    printf ("\n");
	Katalog *tmp;
	tmp=h->glowa;
	while (tmp!=NULL)
    {
        printf ("%s\n", tmp->katalog);
        tmp=tmp->nast;
    }
}

int sortujKatalogi (struct Handler *h)
{
    Katalog *tmp, *pom;
    int czyzmiana=1;
    if (h->ogon==NULL)
    {
        printf ("Brak katalogow.\n");
        return 1;
    }
    if (h->glowa==h->ogon)
        return 0;
    while (czyzmiana==1)
    {
        tmp=h->glowa;
        czyzmiana=0;
        while (tmp->nast!=NULL)
        {
            if (strcmp(tmp->katalog, tmp->nast->katalog)>0)
            {
                czyzmiana=1;
                if (tmp==h->glowa && tmp->nast==h->ogon)
                {
                    pom=tmp->nast;
                    tmp->nast=NULL;
                    tmp->pop=pom;
                    pom->pop=NULL;
                    pom->nast=tmp;
                    h->glowa=pom;
                    h->ogon=tmp;
                    break;
                }
                else if (tmp==h->glowa)
                {
                    tmp->nast->pop=NULL;
                    tmp->pop=tmp->nast;
                    tmp->nast=tmp->nast->nast;
                    tmp->nast->pop=tmp;
                    tmp->pop->nast=tmp;
                    h->glowa=tmp->pop;
                    break;
                }
                else if (tmp->nast==h->ogon)
                {
                    h->ogon=tmp;
                    tmp->nast->nast=tmp;
                    tmp->nast->pop=tmp->pop;
                    tmp->pop->nast=tmp->nast;
                    tmp->pop=tmp->nast;
                    tmp->nast=NULL;
                    break;
                }
                else
                {
                    tmp->nast->nast->pop=tmp;
                    tmp->nast->pop=tmp->pop;
                    tmp->pop->nast=tmp->nast;
                    tmp->pop=tmp->nast;
                    tmp->nast=tmp->nast->nast;
                    tmp->pop->nast=tmp;
                    break;
                }
            }
            tmp=tmp->nast;
        }
    }
    return 0;
}



void wypiszKsiazki (struct Handler *h)
{
    int czyzmiana;
    char tmp[16];
    Katalog *tmp1;
    Ksiazka *ks;
    Ksiazka *temp, *pom;
    printf ("\nPodaj nazwe katalogu, ktory chcesz wyswietlic: ");
    fflush(stdin);
    scanf ("%16s", tmp);
    printf ("\n");
	tmp1=h->glowa;
	while (tmp1!=NULL)
    {
        if (strcmp(tmp1->katalog, tmp)==0)
        {
            if (tmp1->ostatnia==NULL)
            {
                printf ("Ten katalog jest pusty.");
                return;
            }
            printf ("           Tytul      Numer       Kraj\n\n");
            if (tmp1->pierwsza==tmp1->ostatnia)
                czyzmiana=0;
                else
            czyzmiana=1;
            while (czyzmiana==1)
            {
                temp=tmp1->pierwsza;
                czyzmiana=0;
                while (temp->nast!=NULL)
                {
                    if (strcmp(temp->tytul, temp->nast->tytul)>0)
                    {
                        czyzmiana=1;
                        if (temp==tmp1->pierwsza && temp->nast==tmp1->ostatnia)
                        {
                            pom=temp->nast;
                            temp->nast=NULL;
                            temp->pop=pom;
                            pom->pop=NULL;
                            pom->nast=temp;
                            tmp1->pierwsza=pom;
                            tmp1->ostatnia=temp;
                            break;
                        }
                        else if (temp==tmp1->pierwsza)
                        {
                            temp->nast->pop=NULL;
                            temp->pop=temp->nast;
                            temp->nast=temp->nast->nast;
                            temp->nast->pop=temp;
                            temp->pop->nast=temp;
                            tmp1->pierwsza=temp->pop;
                            break;
                        }
                        else if (temp->nast==tmp1->ostatnia)
                        {
                            tmp1->ostatnia=temp;
                            temp->nast->nast=temp;
                            temp->nast->pop=temp->pop;
                            temp->pop->nast=temp->nast;
                            temp->pop=temp->nast;
                            temp->nast=NULL;
                            break;
                        }
                        else
                        {
                            temp->nast->nast->pop=temp;
                            temp->nast->pop=temp->pop;
                            temp->pop->nast=temp->nast;
                            temp->pop=temp->nast;
                            temp->nast=temp->nast->nast;
                            temp->pop->nast=temp;
                            break;
                        }
                    }
                    temp=temp->nast;
                }
            }

            ks=tmp1->pierwsza;
            while (ks!=NULL)
            {
                printf ("%21s", ks->tytul);
                printf ("%6s", ks->numer);
                printf ("%16s\n", ks->kraj);
                ks=ks->nast;
            }
            return;
        }
        tmp1=tmp1->nast;
    }
    printf ("Nie ma takiego katalogu.");
    wypiszKsiazki(h);
}

void wypiszWgParametrow (struct Handler h)
{
    Katalog *tmp3;
    Ksiazka *tmp4;
    char a,w[2],tabtyt[21], tabnum[6], tabkraj[16];
    int czyjest,czydrukowano;
    czydrukowano=0;
    tmp3=h.glowa;
    while (tmp3!=NULL)
    {
        tmp4=tmp3->pierwsza;
        if (tmp4!=NULL)
            break;
        tmp3=tmp3->nast;
    }
    printf ("Wypisz ksiazki wg parametru:\n1- Tytul\n2- Numer\n3- Kraj\n");
    do
    {
        czyjest=1;
        printf (" Wybierz opcje: ");
        scanf ("%2s", w);
        if (( w[0]!='1' && w[0]!='2' && w[0]!='3'  ) || strlen(w)!=1)
        {
            printf ("Nie ma takiej czynnosci.\n\n");
            czyjest=0;
            fflush (stdin);
        }
    }
    while (czyjest==0);
    a=w[0];
    switch (a)
    {
        case '1':
        {
            printf ("Tytul: ");
            fflush (stdin);
            tmp3=h.glowa;
            while (tmp3!=NULL)
            {
                tmp4=tmp3->pierwsza;
                if (tmp4!=NULL)
                    break;
                tmp3=tmp3->nast;
            }
            scanf ("%21s", tabtyt);
            while (tmp3!=NULL)
            {
                if (strcmp(tmp4->tytul, tabtyt)==0)
                {
                    czydrukowano++;
                    if (czydrukowano==1)
                        printf ("           Tytul      Numer       Kraj      Katalog\n\n");
                    printf ("%21s", tmp4->tytul);
                    printf ("%6s", tmp4->numer);
                    printf ("%16s", tmp4->kraj);
                    printf ("%16s\n", tmp3->katalog);
                }
                tmp4=tmp4->nast;
                if (tmp4==NULL)
                {
                    tmp3=tmp3->nast;
                    while (tmp3!=NULL)
                    {
                        tmp4=tmp3->pierwsza;
                        if (tmp4!=NULL)
                            break;
                        tmp3=tmp3->nast;
                    }
                }
            }
            if (czydrukowano==0)
                printf ("Nie ma takiej ksiazki.\n");
            break;
        }
        case '2':
            {
                printf ("Numer: ");
                fflush (stdin);
                tmp3=h.glowa;
                while (tmp3!=NULL)
                {
                    tmp4=tmp3->pierwsza;
                    if (tmp4!=NULL)
                        break;
                    tmp3=tmp3->nast;
                }
                scanf ("%6s", tabnum);
                while (tmp3!=NULL)
                {
                    if (strcmp(tmp4->numer, tabnum)==0)
                    {
                        czydrukowano++;
                        if (czydrukowano==1)
                            printf ("           Tytul      Numer       Kraj      Katalog\n\n");
                        printf ("%21s", tmp4->tytul);
                        printf ("%6s", tmp4->numer);
                        printf ("%16s", tmp4->kraj);
                        printf ("%16s\n", tmp3->katalog);
                        break;
                    }
                    tmp4=tmp4->nast;
                    if (tmp4==NULL)
                    {
                        tmp3=tmp3->nast;
                        while (tmp3!=NULL)
                        {
                            tmp4=tmp3->pierwsza;
                            if (tmp4!=NULL)
                                break;
                            tmp3=tmp3->nast;
                        }
                    }
                }
                if (czydrukowano==0)
                    printf ("Nie ma takiej ksiazki.\n");
                break;
            }
        case '3':
            {
                printf ("Kraj: ");
                fflush (stdin);
                tmp3=h.glowa;
                while (tmp3!=NULL)
                {
                    tmp4=tmp3->pierwsza;
                    if (tmp4!=NULL)
                        break;
                    tmp3=tmp3->nast;
                }
                scanf ("%16s", tabkraj);
                while (tmp3!=NULL)
                {
                    if (strcmp(tmp4->kraj, tabkraj)==0)
                    {
                        czydrukowano++;
                        if (czydrukowano==1)
                            printf ("           Tytul      Numer       Kraj           Katalog\n\n");
                        printf ("%21s", tmp4->tytul);
                        printf ("%6s", tmp4->numer);
                        printf ("%16s", tmp4->kraj);
                        printf ("%16s\n", tmp3->katalog);
                    }
                    tmp4=tmp4->nast;
                    if (tmp4==NULL)
                    {
                        tmp3=tmp3->nast;
                        while (tmp3!=NULL)
                        {
                            tmp4=tmp3->pierwsza;
                            if (tmp4!=NULL)
                                break;
                            tmp3=tmp3->nast;
                        }
                    }
                }
                if (czydrukowano==0)
                    printf ("Nie ma takiej ksiazki.\n");
                break;
            }
    }
}



void przeniesRekord (struct Handler *h)
{
    Katalog *tmp1;
    Ksiazka *tmp2, *tmp3;
    Ksiazka *nowy;
    int czyjest=0, czyjest2=0, czyjest3=0;
    char tmp[16], tabtyt[21], katalog[16];
    if (h->ogon==NULL)
    {
        printf ("Brak katalogow.\n");
        return;
    }
    do
    {
        printf ("Podaj nazwe katalogu, z ktorego chcesz przeniesc ksiazke: ");
        fflush(stdin);
        scanf ("%16s", tmp);
        tmp1=h->glowa;
        while (tmp1!=NULL)
        {
            if (strcmp(tmp1->katalog, tmp)==0)
            {
                czyjest=1;
                break;
            }
            tmp1=tmp1->nast;
            if (tmp1==NULL)
                printf ("Nie ma takiego katalogu.\n");
        }
    } while (czyjest==0);
    do
    {
        printf ("Podaj tytul ksiazki, ktora chcesz przeniesc: ");
        fflush(stdin);
        scanf ("%21s", tabtyt);
        tmp2=tmp1->pierwsza;
        while (tmp2!=NULL)
        {
            if (strcmp(tmp2->tytul, tabtyt)==0)
            {
                czyjest2=1;
                break;
            }
            if (tmp2->nast==0)
            {
                printf ("Nie ma takiej ksiazki\n");
                break;
            }
            if (strcmp(tmp2->nast->tytul, tabtyt)==0)
            {
                czyjest2=2;
                break;
            }
            tmp2=tmp2->nast;
        }
    } while (czyjest2==0);
    if (czyjest2==1)
    {
        if (tmp2==tmp1->pierwsza && tmp2==tmp1->ostatnia)
        {
            nowy=(Ksiazka*)malloc(sizeof(Ksiazka));
            strcpy (nowy->tytul, tmp2->tytul);
            strcpy (nowy->numer, tmp2->numer);
            strcpy (nowy->kraj, tmp2->kraj);
            tmp1->pierwsza=NULL;
            tmp1->ostatnia=NULL;
        }
        if (tmp2==tmp1->pierwsza)
        {
            nowy=(Ksiazka*)malloc(sizeof(Ksiazka));
            strcpy (nowy->tytul, tmp2->tytul);
            strcpy (nowy->numer, tmp2->numer);
            strcpy (nowy->kraj, tmp2->kraj);
            tmp1->pierwsza=tmp2->nast;
            tmp2->nast->pop=NULL;
        }
    }
    if (czyjest2==2)
    {
        if (tmp2->nast==tmp1->ostatnia)
        {
            tmp3=tmp2->nast;
            nowy=(Ksiazka*)malloc(sizeof(Ksiazka));
            strcpy (nowy->tytul, tmp3->tytul);
            strcpy (nowy->numer, tmp3->numer);
            strcpy (nowy->kraj, tmp3->kraj);
            tmp1->ostatnia=tmp2;
            tmp2->nast=NULL;
        }
        else
        {
            tmp3=tmp2->nast;
            nowy=(Ksiazka*)malloc(sizeof(Ksiazka));
            strcpy (nowy->tytul, tmp3->tytul);
            strcpy (nowy->numer, tmp3->numer);
            strcpy (nowy->kraj, tmp3->kraj);
            tmp2->nast=tmp2->nast->nast;
            tmp2->nast->pop=tmp2;
        }
    }
    nowy->nast=NULL;
    if (czyjest2==1)
        free (tmp2);
    if (czyjest2==2)
        free (tmp3);
    do
    {
        printf ("Podaj nazwe katalogu, do ktorego chcesz przeniesc ksiazke: ");
        fflush(stdin);
        scanf ("%16s", katalog);
        tmp1=h->glowa;
        while (tmp1!=NULL)
        {
            if (strcmp(tmp1->katalog, katalog)==0)
            {
                czyjest3=1;
                if (tmp1->ostatnia==NULL)
                {
                    tmp1->pierwsza=nowy;
                    tmp1->ostatnia=nowy;
                    nowy->pop=NULL;
                    return;
                }
                    else
                    {
                        tmp1->ostatnia->nast=nowy;
                        nowy->pop=tmp1->ostatnia;
                        tmp1->ostatnia=nowy;
                        return;
                    }
                }
            tmp1=tmp1->nast;
            if (tmp1==NULL)
                printf ("Nie ma takiego katalogu.\n");
        }
    } while (czyjest3==0);
}


int main ()
{
    char a,b,w[2],y[2];
    int czyjest, z;
    struct Handler lista;
    lista.glowa=NULL;
	lista.ogon=NULL;
	printf ("Instrukcja:\n\nProgram automatycznie zamienia pierwsze litery na wielkie.\nWprowadzanie danych:\n Katalog- tylko litery i spacje, max 15 znakow\n Tytul- max 20 znakow\n Numer- 5- cyfrowy, unikalny dla kazdej ksiazki\n Kraj pierwszego wydania- tylko litery i spacje, max 15 znakow\n");
    do
    {
        printf ("\n************************* M E N U *************************\n\nWpisz cyfre odpowiadajaca zadanej przez Ciebie czynnosci:\n1- dodanie katalogu\n2- dodanie ksiazki\n3- wyswietlenie alfabetyczne katalogow\n4- zmiana nazwy katalogu\n5- wyswietlenie wybranego katalogu\n6- usuniecie wybranego katalogu\n7- poprawa danych\n8- wyszukiwanie wg wybranego parametru\n9- przeniesienie rekordu\n*- wyjscie z programu\n\n");
        do
        {
            czyjest=1;
            printf (" Wybierz opcje: ");
            scanf ("%2s", w);
            if (( w[0]!='1' && w[0]!='2' && w[0]!='3' && w[0]!='4' && w[0]!='5' && w[0]!='6' && w[0]!='7' && w[0]!='8' && w[0]!='9' && w[0]!='*' ) || strlen(w)!=1)
            {
                printf ("Nie ma takiej czynnosci.\n\n");
                czyjest=0;
                fflush (stdin);
            }
        }
        while (czyjest==0);
        a=w[0];
      switch (a)
      {
        case '1':
            {
                dodajKatalog(&lista);
                break;
            }
        case '2':
            {
                dodajKsiazke(lista);
                break;
            }
        case '3':
            {
                sortujKatalogi(&lista);
                wypiszKatalogi(&lista);
                printf ("\n");
                break;
            }
        case '4':
            {
                zmienNazwe(&lista);
                break;
            }
        case '5':
            {
                wypiszKsiazki(&lista);
                printf ("\n");
                break;
            }
        case '6':
            {
                usunKatalog(&lista);
                break;
            }
        case '7':
            {
                poprawDane(&lista);
                break;
            }
        case '8':
            {
                z=sortujKatalogi(&lista);
                if (z==1)
                    break;
                wypiszWgParametrow(lista);
                break;
            }
        case '9':
            {
                przeniesRekord(&lista);
                break;
            }
        case '*':
            {
                do
                {
                    czyjest=1;
                    printf ("Czy na pewno chcesz zakonczyc prace programu?\nJesli TAK- wpisz 1\nJesli NIE- wpisz 2: ");
                    scanf ("%2s", y);
                    if (( y[0]!='1' && y[0]!='2' ) || strlen(y)!=1)
                    {
                        printf ("Nie ma takiej czynnosci.\n\n");
                        czyjest=0;
                        fflush (stdin);
                    }
                    else
                    {
                        b=y[0];
                        if (b=='1')
                        {
                            printf ("Do zobaczenia!\n");
                            return 0;
                        }
                        if (b=='2')
                            break;
                    }
                } while (czyjest==0);
            }
      }
    }
    while (1);
}
