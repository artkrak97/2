#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cmath>
using namespace std;

const int N = 1000000; // Liczebnoœæ zbioru, ilośc elenentów w tablicy


/**************************************************************************************/
//sortowanie introspektywne



static int dzielenie(int* dane, int lewa, int prawa) {
	int pivot = dane[prawa];
	int pomoc;
	int i = lewa;

	for (int j = lewa; j < prawa; ++j)
	{
		if (dane[j] <= pivot)
		{
			pomoc = dane[j];
			dane[j] = dane[i];
			dane[i] = pomoc;
			i++;
		}
	}

	dane[prawa] = dane[i];
	dane[i] = pivot;

	return i;
}

static void QuickSort_introsort(int* dane, int lewa, int prawa) {
	if (lewa < prawa)
	{
		int q = dzielenie(dane, lewa, prawa);
		QuickSort_introsort(dane, lewa, q - 1);
		QuickSort_introsort(dane, q + 1, prawa);
	}
}

static void Max_Kopcowanie_introsort(int* dane, int Kopcowane_wielkosc, int index) {
	int lewa = (index + 1) * 2 - 1;
	int prawa = (index + 1) * 2;
	int Max = 0;

	if (lewa < Kopcowane_wielkosc && dane[lewa] > dane[index])
		Max = lewa;
	else
		Max = index;

	if (prawa < Kopcowane_wielkosc && dane[prawa] > dane[Max])
		Max = prawa;

	if (Max != index)
	{
		int pomoc = dane[index];
		dane[index] = dane[Max];
		dane[Max] = pomoc;

		Max_Kopcowanie_introsort(dane, Kopcowane_wielkosc, Max);
	}
}

static void kopcowanie(int* dane, int ilosc) {
	int Kopcowane_wielkosc = ilosc;

	for (int p = (Kopcowane_wielkosc - 1) / 2; p >= 0; --p)
		Max_Kopcowanie_introsort(dane, Kopcowane_wielkosc, p);

	for (int i = ilosc - 1; i > 0; --i)
	{
		int pomoc = dane[i];
		dane[i] = dane[0];
		dane[0] = pomoc;

		--Kopcowane_wielkosc;
		Max_Kopcowanie_introsort(dane, Kopcowane_wielkosc, 0);
	}
}

static void Wstawianie_introsort(int* dane, int ilosc) {
	for (int i = 1; i < ilosc; ++i)
	{
		int j = i;

		while ((j > 0))
		{
			if (dane[j - 1] > dane[j])
			{
				dane[j - 1] ^= dane[j];
				dane[j] ^= dane[j - 1];
				dane[j - 1] ^= dane[j];

				--j;
			}
			else
			{
				break;
			}
		}
	}
}

static void IntroSort(int *dane, int ilosc) {
	int rozmiar_dzielenia = dzielenie(dane, 0, ilosc - 1);

	if (rozmiar_dzielenia < 16)
	{
		Wstawianie_introsort(dane, ilosc);
	}
	else if (rozmiar_dzielenia >(2 * log(ilosc)))
	{
		kopcowanie(dane, ilosc);
	}
	else
	{
		QuickSort_introsort(dane, 0, ilosc - 1);
	}
}

/**************************************************************************************/

int dane[N];

// sortowanie szybki


void Quick_Sort(int lewy, int prawy)
{
  int i,j,pivot;

  i = (lewy + prawy) / 2;
  pivot = dane[i]; dane[i] = dane[prawy];
  for(j = i = lewy; i < prawy; i++)
  if(dane[i] < pivot)
  {
    swap(dane[i], dane[j]);
    j++;
  }
  dane[prawy] = dane[j]; dane[j] = pivot;
  if(lewy < j - 1)  Quick_Sort(lewy, j - 1);
  if(j + 1 < prawy) Quick_Sort(j + 1, prawy);
}



/**************************************************************************************/
// Sortowanie przez scalanie
int dane2[N];

void Przez_Scalanie(int ind_mlod, int ind_str_o)

/*
ind_mlod-indeks pierwszego elementu w młodszym podzbiorze
ind_str_o - indeks ostatniego elementu w starszym podzbiorze
ind_str - indeks pierwszego w ostatnim podzbiorze

*/
{
  int ind_str,i_1,i_2,i;

  ind_str = (ind_mlod + ind_str_o + 1) / 2;
  if(ind_str - ind_mlod > 1) Przez_Scalanie(ind_mlod, ind_str - 1);
  if(ind_str_o - ind_str > 0) Przez_Scalanie(ind_str, ind_str_o);
  i_1 = ind_mlod; i_2 = ind_str;

  for(i = ind_mlod; i <= ind_str_o; i++)
    dane2[i] = ((i_1 == ind_str) || ((i_2 <= ind_str_o) && (dane[i_1] > dane[i_2]))) ? dane[i_2++] : dane[i_1++];
  for(i = ind_mlod; i <= ind_str_o; i++) dane[i] = dane2[i];
}
/**************************************************************************************/

//Program główny



int main()
{
  int i;
  int x;



  do{
 cout<< " podaj ilosc liczb losowych "<<endl;
 cout<< " 1-10 000 "<<endl;
 cout<< " 2-50 000 "<<endl;
 cout<< " 3-100 000 "<<endl;
 cout<< " 4-500 000 "<<endl;
 cout<< " 5-1 000 000 "<<endl;
  cout<< " 6-odwrocona tablica "<<endl; //narazie tylko jedna wartość
    cout<< " 7-posortowana w 25% "<<endl;
 cout<< " 8-posortowana w 50% "<<endl;
 cout<< " 9-posortowana w 75% "<<endl;
 cout<< " 10-posortowana w 95%"<<endl;
 cout<< " 11-posortowana w 99% "<<endl;
  cout<< "12- posortowana w 99,7%"<<endl;
    cin >> x;


  switch(x)
    {
   case 1:
       {
           const int N = 10000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

  //Wyświetlenie zawartosci danych do posortowanie (wykorzystane tylko w próbach działania algorytmu

  //for(i = 0; i < N; i++) cout << setw(4) << dabe[i];
  cout << endl;

// Sortowanie

        t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

// Wyœwietlamy wynik
//Jak przy wyświetlaniu elementów tablicy, tylko dla małej tablicy przy testowaniu poprawnosci algorytmu

  //cout << "Po sortowaniu:\n\n";
  //for(i = 0; i < N; i++) cout << setw(4) << dane[i];
  //cout << endl;

 for(i = 0; i < N; i++) dane[i] = rand() % 300;


        t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;

// Wyœwietlamy wynik sortowania

// cout << "Po sortowaniu:\n\n";
// for(i = 0; i < N; i++) cout << setw(4) << dane[i];
 // cout << endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;
       t1=GetTickCount();

IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;
  break;
   }
   case 2:
       {

     const int N = 50000;

    DWORD t1, t2;

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

  cout << endl;

        t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

 for(i = 0; i < N; i++) dane[i] = rand() % 300;
        t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;
 for(i = 0; i < N; i++) dane[i] = rand() % 300;

       t1=GetTickCount();

IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;

 break;
    }
       case 3:
       {

     const int N = 100000;

    DWORD t1, t2;

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

  cout << endl;

        t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;
 for(i = 0; i < N; i++) dane[i] = rand() % 300;

        t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;

 for(i = 0; i < N; i++) dane[i] = rand() % 300;
       t1=GetTickCount();

IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;

 break;
    }
       case 4:
       {

     const int N = 500000;

    DWORD t1, t2;

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

  cout << endl;

        t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;
 for(i = 0; i < N; i++) dane[i] = rand() % 300;

        t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;

 for(i = 0; i < N; i++) dane[i] = rand() % 300;
       t1=GetTickCount();

IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;

 break;
    }
       case 5:
       {

     const int N = 1000000;

    DWORD t1, t2;

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

  cout << endl;

        t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

 for(i = 0; i < N; i++) dane[i] = rand() % 300;
        t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;
 for(i = 0; i < N; i++) dane[i] = rand() % 300;

       t1=GetTickCount();

IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;

 break;
    }

    case 6:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

// Sortowanie do odwrocenia tablicy

            Przez_Scalanie(0,N-1);

            for ( i=N-1;i>=0;i--)
    //  cout<< setw(4) << dane[i];
     // cout<<endl;
t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

// Sortowanie do odwrocenia tablicy

            Przez_Scalanie(0,N-1);

            for ( i=N-1;i>=0;i--)
     t1=GetTickCount();

   Przez_Scalanie(0,N-1);
   t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalanie" <<endl;
 cout << t2<<endl;


  for(i = 0; i < N; i++) dane[i] = rand() % 300;

// Sortowanie do odwrocenia tablicy

                Przez_Scalanie(0,N-1);

                for (int i=N-1;i>=0;i--)
 t1=GetTickCount();

   IntroSort(dane, N);
 t2=GetTickCount() - t1;

cout<< "czas sortowania introspektywnegp" <<endl;
 cout << t2<<endl;
  break;
       }

        case 7:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.25*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

 IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;

break;
   }

   case 8:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.5*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

  IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;
break;

   }

   case 9:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.75*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

  IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;
break;

   }
   case 10:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.95*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

  IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;

break;
   }

   case 11:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.99*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

  IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;

break;
   }
   case 12:
       {
           const int N = 1000000;

    DWORD t1, t2; //do mierzenia czasu

  srand((unsigned)time(NULL));
    cout<< "dla liczby danych : " ;
    cout<< N <<endl;


// wypełnienie tablicy dane[i] elementami z funkcji rand
const int N1=0.997*N;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;

 t1=GetTickCount();

  Quick_Sort(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania szybkiego" <<endl;
  cout << t2<<endl;

for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;
 t1=GetTickCount();

  Przez_Scalanie(0,N - 1);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania przez scalenie" <<endl;
  cout << t2<<endl;

  for(i = 0; i < N; i++) dane[i] = rand() % 300;

 for(i = 0; i < N1; i++)
  t1=GetTickCount();

     IntroSort(dane,N1);
t2=GetTickCount() - t1;



  cout << endl;

// Sortowanie

        t1=GetTickCount();

  IntroSort(dane,N);

  t2=GetTickCount() - t1;
 cout<< "czas sortowania introsort" <<endl;
  cout << t2<<endl;

  cout << endl;

break;
   }

    }}

     while (x!=99);



  return 0;
}
