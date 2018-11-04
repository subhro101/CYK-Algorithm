/* *************************************Final Project******************************************************************* 
Subhrajyoti Pradhan
U79333962
This algorithm will employ the use of Cocke‚Younger‚Kasami algorithm 
which is u parsing algorithm employed on CFG
This algorithm only accepts CFG in Chomsky normal form
We are employing the use of bottom up parsing and dynamic programming
*/

//Declaring headers
#include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
using namespace std;
 
 
 //defining macros
#define Upper_limit 100
#define for(i,x,y) for(i=x;i<y; i++)    //personal practice. I define the whole loop statment
 
string Grammar[Upper_limit][Upper_limit];  //to store entered grammar
string str1[Upper_limit];
int Production,No_Production;       //No_Production-> number of productions
 
 
//referencing functions
inline string concatinate( string u, string v);
inline void break_gram(string u);
inline int Left_chomsky(string u);
inline int Right_chomsky(string u);
inline string SearchingProduct(string Production);
inline string GeneralCombination(string u, string v); 
 
 /*______________________________________________________________________________________________________*/

 
int main()
{
    int i,pt,j,l,k;
    string u,str,r,pr,start;
    cout<<"\nPlease enter the start Variable ";
    cin >> start;
    cout<<"\nPlease enter the number of productions ";
    cin >> No_Production;
    for(i,0,No_Production)
    {
        cin >> u;
        pt=u.find("->");
        Grammar[i][0] = u.substr(0,pt);
        if (Left_chomsky(Grammar[i][0]) == 0)
        {
            cout<<"\nThis grammar is not in Chomsky Form";
            abort();
        }
        u = u.substr(pt+2, u.length());
        break_gram(u);
        for(j,0,Production)
        {
            Grammar[i][j+1]=str1[j];
            if (Right_chomsky(str1[j]) == 0)
            {
                cout<<"\nThis grammar is not in Chomsky Form";
                abort();
            }
        }
    }
    string matrix[Upper_limit][Upper_limit],st;
    cout<<"\nPlease enter the string: ";
    cin >> str;
	//We will now assign the values to the principal diagonal of the matrix
    for(i,0,str.length())       
    {
        r="";
        st = "";
        st+=str[i];
        for(j,0,No_Production)
        {
            k=1;
            while(Grammar[j][k] != "")
            {
                if(Grammar[j][k] == st)
                {
                    r=concatinate(r,Grammar[j][0]);
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
	//Now we will assign the values to the upper half of the matrix
    for(k,1,str.length())       
    {
        for(j,k,str.length())
        {
            r="";
            for(l,j-k,j)
            {
                pr = GeneralCombination(matrix[j-k][l],matrix[l+1][j]);
                r = concatinate(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }
 
	//Now we will print the matrix
    for(i,0,str.length())   
    {
        k=0;
        l=str.length()-i-1;
        for(j,l,str.length())
        {
            cout<<setw(5)<<matrix[k++][j]<<" ";
        }
        cout<<endl;
    }
             
    int f=0;
    for(i,0,start.length())
		//Now we will check if the last element of the first row contains the Start variable
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   
        {
            cout<<"The entered string can be geneated from the given CFG\n";
            return 0;
        }
    cout<<"The entered string can not be generated from the given CFG\n";
    return 0;
}

//We will now concatenate the unique non-terminals
inline string concatinate( string u, string v)   
{
    int j;
    string r=u;
    for(j,0,v.length())
        if(r.find(v[j]) > r.length())
            r+=v[j];
    return (r);
}
//This functions seperates the right hand side of entered grammar
inline void break_gram(string u)    
{
    int i;
    Production=0;
    while(u.length())
    {
        i=u.find("|");
        if(i>u.length())
        {
            str1[Production++] = u;
            u="";
        }
        else
        {
            str1[Production++] = u.substr(0,i);
            u=u.substr(i+1,u.length());
        }
    }
}
 
 
 //We will now check if the left side of the entered grammar is in the form of Chomsky form
inline int Left_chomsky(string u)   
{
    if(u.length()==1 && u[0]>='A' && u[0]<='Z')
        return 1;
    return 0;
}
 
//checks if right side of grammar is in Chomsky form
inline int Right_chomsky(string u)
{
    if (u.length() == 1 && u[0]>='a' && u[0] <='z')
        return 1;
    if (u.length()==2 && u[0]>='A' && u[0]<='Z' && u[1]>='A' && u[1]<='Z' )
        return 1;
    return 0;
}
 
 
 // We wooll mpw return a0 concatenated string of variables which can produce string Production
inline string SearchingProduct(string Production) 
{
    int j,k;
    string r="";
    for(j,0,No_Production)
    {
        k=1;
        while(Grammar[j][k] != "")
        {
            if(Grammar[j][k] == Production)
            {
                r=concatinate(r,Grammar[j][0]);
            }
            k++;
        }
    }   
    return r;
}
 
 //We will mmow create every combination of variables from u and v . 
inline string GeneralCombination(string u, string v)  
{
    int i,j;
    string pribt=u,returns="";
    for(i,0,u.length())
        for(j,0,v.length())
        {
            pribt="";
            pribt=pribt+u[i]+v[j];
			//we now search if the generated productions can be created or not
            returns=returns+SearchingProduct(pribt);     
        }       
    return returns;
}
