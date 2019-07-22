#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
    int m, n;
    vector < vector<float> > macierz;
    string nazwa;

public:

    Matrix(string naz)
    {
        nazwa = naz;
        cout << "TWORZENIE NOWEJ MACIERZY" << endl
        << "Podaj liczbe wierszy: ";
        cin >> m;
        cout << "Podaj liczbe kolumn: ";
        cin >> n;
        for (int i=0; i<m; i++)
        {
            int liczba_el = 0;
            vector<float> wiersz;
            cout << "Podaj wartosci z wiersza "
             << i+1 << " (oddzielone spacja): ";
//            while(true)
//            {
//                float liczba;
//                cin >> liczba;
//                if (liczba_el<n)
//                {
//                    wiersz.push_back(liczba);
//                    liczba_el++;
//                }
//                else
//                    break;
//            }
            for (int j=0; j<n; j++)
            {
                float liczba;
                cin >> liczba;
                if (liczba_el<n)
                {
                    wiersz.push_back(liczba);
                    liczba_el++;
                }
            }
            macierz.push_back(wiersz);
        }
    }

    void pokazMacierz()
    {
        cout << endl;
        for (int wiersz=0; wiersz<m; wiersz++)
        {
            for (int kolumna=0; kolumna<n; kolumna++)
            {
                cout << macierz[wiersz][kolumna] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    void zamianaWierszy(int pierwszy, int drugi)
    {
        for (int kolumna=0; kolumna<n; kolumna++)
        {
            float liczba;
            liczba = macierz[pierwszy][kolumna];
            macierz[pierwszy][kolumna]=macierz[drugi][kolumna];
            macierz[drugi][kolumna]=liczba;
        }
    }

    int miejsceJedynkiWiodacej(int wiersz)
    {
        int miejsce = -1;
        for (int kolumna=0; kolumna<n; kolumna++)
        {
            if(macierz[wiersz][kolumna]==1)
            {
                miejsce = kolumna;
                break;
            }
        }
        return miejsce;
    }

    int znajdzWierszZLiczba(int wiersz, int kolumna, int liczba)
    {
        int miejsce = -1;
        for(int r=wiersz+1; r<m; r++)
        {
            if(macierz[r][kolumna]==liczba)
            {
                miejsce = r;
                break;
            }
        }
        return miejsce;
    }

//    void mnozenieWierszaSkalar(int wiersz, float skalar)
//    {
//        for (int kolumna=0; kolumna<n; kolumna++)
//        {
//            macierz[wiersz][kolumna] =
//        }
//    }


    void postacCalkowicieZredukowana()
    {
        for (int k=0; k<m; k++)
        {
            if (macierz[k][k]==0)
            {
                int miejsceJedynki = znajdzWierszZLiczba(k,k,1);
                if (miejsceJedynki!=-1)
                    zamianaWierszy(k,miejsceJedynki);
                else
                {
                    for(int r=k+1; r<m; r++)
                    {
                        if(macierz[r][k]!=0)
                        {
                            zamianaWierszy(k,r);
                            break;
                        }
                    }
                }
                pokazMacierz();
            }
            if (macierz[k][k]!=1 && macierz[k][k]!=0)
            {
                int miejsceJedynki = znajdzWierszZLiczba(k,k,1);
                if (miejsceJedynki != -1)
                    zamianaWierszy(k,miejsceJedynki);
                else
                {
                    float liczba = macierz[k][k];
                    for (int i=k; i<n; i++)  //czy nie powinno startoeac od k a nie od 0?
                        macierz[k][i]=macierz[k][i]/liczba;
                }
                pokazMacierz();
            }
            for (int i=k+1; i<m; i++)
            {
                float x = macierz[i][k];
                for (int j=0; j<n; j++)
                {
                    macierz[i][j]=macierz[i][j]+(macierz[k][j]*x*(-1));
                }
            }
            pokazMacierz();
            int jedynka = miejsceJedynkiWiodacej(k);
            if (jedynka>0)
            {
                for(int wiersz=0; wiersz<k; wiersz++)
                {
                    float x = macierz[wiersz][jedynka];
                    for (int kolumna=0; kolumna<n; kolumna++)
                    {
                        macierz[wiersz][kolumna]=macierz[wiersz][kolumna]+(macierz[k][kolumna]*(-1)*x);
                    }
                }
                pokazMacierz();
            }
        }
    }
};

int main()
{
    while (true)
    {
        cout << "Co chcesz zrobic?" << endl;
        cout << "Nowa macierz - wcisnij 1" << endl;
        cout << "Koniec - wcisnij 2" << endl;
        int decyzja;
        cin >> decyzja;
        if (decyzja==1)
        {
            Matrix m("A");
            cout << "Czy o taka macierz chodzilo?" << endl;
            m.pokazMacierz();
            cout << "Tak - wcisnij 1" << endl;
            cout << "Nie, chce poprawic - wcisnij 2" << endl;
            int decyzja2;
            cin >> decyzja2;
            if (decyzja2==1)
            {
                m.postacCalkowicieZredukowana();
                cout << "POSTAC CALKOWICIE ZREDUKOWANA:" << endl;
                m.pokazMacierz();
                cout << endl;
            }
            if(decyzja2==2)
                continue;
            else
            {
                cout << "Nie ma takiej opcji" << endl;
                continue;
            }
//            m1.znajdzJedynki();
        }
        else if (decyzja==2)
            break;
        else
            cout << "Nie rozumiem. Wybierz jeszcze raz." << endl;
    }
    return 0;
}
