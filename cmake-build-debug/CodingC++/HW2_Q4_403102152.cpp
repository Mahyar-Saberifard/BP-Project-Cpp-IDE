#include<iostream>
#include<math.h>
using namespace std;
int main()
{
      int a,b,c;
      char x,y,z;
      cin >> x >> y >> z;
      switch(x)
      {
            case 'C': a=1;
                  break;
            case 'c': a=2;
                  break;
            case 'D': a=3;
                  break;
            case 'd': a=4;
                  break;
            case 'E': a=5;
                  break;
            case 'F': a=6;
                  break;
            case 'f': a=7;
                  break;
            case 'G': a=8;
                  break;
            case 'g': a=9;
                  break;
            case 'A': a=10;
                  break;
            case 'B': a=11;
                  break;
            case 'H': a=12;
                  break;
      }
            
      switch(y)
      {
            case 'C': b=1;
                  break;
            case 'c': b=2;
                  break;
            case 'D': b=3;
                  break;
            case 'd': b=4;
                  break;
            case 'E': b=5;
                  break;
            case 'F': b=6;
                  break;
            case 'f': b=7;
                  break;
            case 'G': b=8;
                  break;
            case 'g': b=9;
                  break;
            case 'A': b=10;
                  break;
            case 'B': b=11;
                  break;
            case 'H': b=12;
                  break;

      }
      
      switch(z)
      {
            case 'C': c=1;
                  break;
            case 'c': c=2;
                  break;
            case 'D': c=3;
                  break;
            case 'd': c=4;
                  break;
            case 'E': c=5;
                  break;
            case 'F': c=6;
                  break;
            case 'f': c=7;
                  break;
            case 'G': c=8;
                  break;
            case 'g': c=9;
                  break;
            case 'A': c=10;
                  break;
            case 'B': c=11;
                  break;
            case 'H': c=12;
                  break;

      }
      
      if( ((b-a)==4 && (c-b)==3) || ((b-a)==4 && (b-c)==9) || ((a-b)==8 && (c-b)==3) )
            cout<< "Arpeggio";//abc
      else if( ((a-c)==4 && (b-a)==3) || ((a-c)==4 && (a-b)==9) || ((c-a)==8 && (b-a)==3) )
            cout<< "Chord";//cab
      else if( ((c-b)==4 && (a-c)==3) || ((c-b)==4 && (c-a)==9) || ((b-c)==8 && (a-c)==3) )
            cout<< "Chord";//bca
      else if( ((a-b)==4 && (c-a)==3) || ((a-b)==4 && (a-c)==9) || ((b-a)==8 && (c-a)==3) )
            cout<< "Chord";//bac
      else if( ((c-a)==4 && (b-c)==3) || ((c-a)==4 && (c-b)==9) || ((a-c)==8 && (b-c)==3) )
            cout<< "Chord";//acb
      else if( ((b-c)==4 && (a-b)==3) || ((b-c)==4 && (b-a)==9) || ((c-b)==8 && (a-b)==3) )
            cout<< "Chord";//cba
      else cout<<"Strange";
}







    