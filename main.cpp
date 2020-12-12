#include <bits/stdc++.h>
using namespace std;

//#define int float

int B;      //number of books
int L;      //number of libraries
int D;      //number of days

int libUsed = 0;

struct book
{
    int number;
    int score;
    bool used;
};

vector<book> bookValue;

struct library
{
    int number;
    int signupTime;
    int numBooks;
    int scanPerDay;

    vector<int> bookList;

    int score;

    float value;
};

vector<library> storeLib;

bool compLib(library lib1, library lib2)
{
    return (lib1.value < lib2.value);
}

bool compBook(int book1, int book2)
{
    if(bookValue[book1].used && !bookValue[book2].used)
    {
        bookValue[book2].used = true;

        return false;
    }
    else if(bookValue[book2].used && !bookValue[book1].used)
    {
        bookValue[book1].used = true;

        return true;
    }
    else
    {
        bookValue[book1].used = true;
        bookValue[book2].used = true;

        return bookValue[book1].score > bookValue[book2].score;
    }
}

int scoreCalc(library lib)
{
    int tempScore = 0;

    for(int i=0; i<lib.numBooks; i++)
    {
        tempScore += bookValue[lib.bookList[i]].score;
    }

    return tempScore;
}

float valueCalc(library lib)
{
    return ((float)lib.signupTime * (float)lib.score) / (float)lib.scanPerDay;
}


int32_t main()
{


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("d_tough_choices.txt", "r", stdin);
    freopen("d.txt", "w", stdout);

    cin>>B>>L>>D;

    bookValue.resize(B);

    for(int i=0; i<B; ++i)
    {
        bookValue[i].used = false;
        bookValue[i].number = i;
        cin>>bookValue[i].score;
    }

    storeLib.resize(L);

    for(int i=0; i<L; ++i)
    {
        storeLib[i].number = i;

        cin>>storeLib[i].numBooks>>storeLib[i].signupTime>>storeLib[i].scanPerDay;

        storeLib[i].bookList.resize(storeLib[i].numBooks);

        for(int j=0; j<storeLib[i].numBooks; j++)
        {
            cin>>storeLib[i].bookList[j];
        }

        storeLib[i].score = scoreCalc(storeLib[i]);

        storeLib[i].value = valueCalc(storeLib[i]);
    }

    sort(storeLib.begin(), storeLib.end(), compLib);e_so_many_books

    while(D > 0)
    {
        D = D - storeLib[libUsed].signupTime;

        ++libUsed;
    }

    if(libUsed > L)
    {
        libUsed = L;
        cout<<libUsed<<endl;
    }
    else
    {
        cout<<libUsed+1<<endl;
    }

    for(int i=0; i < libUsed; ++i)
    {
        sort(storeLib[i].bookList.begin(), storeLib[i].bookList.end(), compBook);

        cout<<storeLib[i].number<<" "<<storeLib[i].numBooks;

        cout<<endl;

        for(int j=0; j<storeLib[i].numBooks; j++)
        {
            cout<<storeLib[i].bookList[j]<<" ";
        }

        cout<<endl;
    }
}
