#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void prefix_table(char pattern[],int prefix[],int n)
{
    prefix[0] = 0;
    int len = 0;
    int i = 1;

    while(i<n)
    {
        if(pattern[i] == pattern[len])
        {
            len++;
            prefix[i] = len;
            i++;
        }
        else
        {
            if(len>0)
                 len = prefix[len-1];
            else
            {
                prefix[i] = len;
                i++;
            }
        }
    }
}

void move_prefix_table(int prefix[],int n)
{
    int i;
    for(i=n-1;i>0;i--)
    {
        prefix[i] = prefix[i-1];
    }

    prefix[0] = -1;
}

void kmp_search(char text[],char pattern[])
{
    int n = strlen(pattern);
    int m = strlen(text);
    int* prefix = (int*)malloc(sizeof(int)*n);
    prefix_table(pattern,prefix,n);
    move_prefix_table(prefix,n);

    //text[i] len(text) = m
    //pattern[j] len(pattern) = n

    int i=0;
    int j=0;
    while(i<m)
    {
        if(j ==n-1 && text[i] == pattern[j])
        {
            cout<<"found pattern at "<<i-j<<endl;
            j = prefix[j];
        }
        if(text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j = prefix[j];
            if(j == -1)
            {
                i++;
                j++;
            }
        }
    }

}

int main()
{
    char pattern[] = "ABABCABAA";
    char text[] = "ABCAHBKHABABCABAAHJDUSI";

    kmp_search(text,pattern);
    /*   int prefix[9];
    int n = 9;

    prefix_table(pattern,prefix,n);
    move_prefix_table(prefix,n);

    int i;
    for(i=0;i<n;i++)
        cout<<prefix[i];

    cout<<endl;
   */ return 0;
}
