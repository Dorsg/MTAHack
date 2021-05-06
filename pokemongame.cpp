#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>
#include<windows.h>
using namespace std;

int user,cpu=0,i,j,usermv,cpumv,dmgmul,clk=0,a,k,c,c1,d,d1,e=0,e1=0,f,x;
int gym1[3]={2,3,4};
int gym2[3]={0,1,5};
int vary=0;
void playgym(int leader,int number);
int gym3[6]={2,0,5,4,6,3};
vector <string> out;

    char moves[20][20]={/*0*/"tackle",/*1*/"scratch",/*2*/"ember",/*3*/"water gun",/*4*/"vine whip",/*5*/"growl",/*6*/"tail whip",/*7*/"sand tomb",/*8*/"thundershock",/*9*/"hydro pump",/*10*/"fire blast",/*11*/"solar beam",/*12*/"thunder",/*13*/"earthquake",/*14*/"gust",/*15*/"sky attack",/*16*/"scary face",/*17*/"agility",/*18*/"aurora beam",/*19*/"ice beam"};
    char atktyp[20]={'n','n','f','w','g','n','n','G','e','w','f','g','e','G','F','F','n','n','i','i'};
    int atkpwr[20]={40,40,40,40,40,0,0,50,40,80,80,80,100,80,40,90,0,0,40,90};
    int atkpp[20]={30,30,15,15,15,10,30,15,15,5,5,5,5,5,15,5,10,10,15,5};
    int tempz[20]={30,30,15,15,15,10,30,15,15,5,5,5,5,5,15,5,10,10,15,5};
    int atkppuser[20]={30,30,15,15,15,10,30,15,15,5,5,5,5,5,15,5,10,10,15,5};
    int atkppcpu[20]={30,30,15,15,15,10,30,15,15,5,5,5,5,5,15,5,10,10,15,5};

void typdisplay(int typch);
int chkspd(int userspd,int cpuspd);
int calcdmgmul(int pktyp,int atktyp);
void colors();
COORD coord={0,0};

///Places the cursor on cordinates x,y
void gotoxy(int x,int y){
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); ///shows that the blinking cursor on x,y
 }

///Function for creating a delay
void delay(int a){
    clock_t start;
    start=clock();
    while(clock() - start < a)
    {

    }
}
///Pokemon Structure
    struct pokemon{
    char name[20];
    float atk;
    float def;
    int spd;
    int hp;
    int moveset[4];
    char typ;
    }p[7]={{"Bulbasaur",11,9,10,60,{0,4,5,11},'g'},{"Charmander",13,8,9,60,{1,2,5,10},'f'},{"Squirtle",10,13,7,60,{0,3,6,9},'w'},{"Pidgey",9,9,12,60,{0,17,14,15},'F'},{"Pikachu",11,8,11,60,{0,6,8,12},'e'},{"Sandshrew",10,12,8,60,{1,5,7,13},'G'},{"Seel",11,12,7,60,{0,16,18,19},'i'}};
///Defining the 7 pokemons
    pokemon cpuone,userone;

///Defing the title
char tempstr[10],title[]={"******************************Pokemon: Battle For Survival******************************\n\n"};

///Defifng the play Area
char maps[15][37] = {"####################################",
                    "#                                  #",
                    "#              ########            #",
                    "#              #  %   #            #",
                    "#              ###  ###            #",
                    "#                #  #              #",
                    "#               ##  ##             #",
                    "#                                  #",
                    "#    #########         #########   #",
                    "#    #   &   #         #   $   #   #",
                    "#    ##     ##         ##     ##   #",
                    "#                                  #",
                    "#                                  #",
                    "#                                  #",
                    "################  @  ###############"};

const int gamespeed=100;
const int level=(1);




///Storing the names of the 7 pokemons
char pokepokemon[7][20]={"Bulbasaur","Charmander","Squirtle","Pidgey","Pikachu","Sandshrew","Seel"};

///Storing the different types of pokemon available
char poketype[7][20]={"Grass","Fire","Water","Flying","Electric","Ground","Ice"};

///Storing the pokemon info
char pokeinfo[7][200]={
"                                 .Bulbasaur resembles a small,      squatting dinosaur that walks on  four legs,but bears three claws oneach of its feet and has no tail.",
"                                 .Charmander is a small, bipedal    dinosaur-like Pokemon.Most of its body is colored orange , while itsunderbelly is a light-yellow color",
"                                 .Squirtle is a small, light-blue   Pokemon with an appearance similarto that of a turtle.",
"                                 .Pidgey resembles a small ,  plump-bodied bird. It is brown in color,with a cream-colored throat and   belly.",
"                                 .Pikachu are small , chubby , and  incredibly cute mouse-like PokemonThey are almost completely coveredby yellow fur.",
"                                 .Sandshrew has a white belly and a yellow back. Its back resembles   bricked pavement or walls. It has a short tail, four short legs and a small head. ",
"                                 .Seel is a Sea Lion Pokemon. It is covered with dense white fur to   keep it warm underwater. The mouthof Seel has jowls and two fangs."};



///Node for linked List Made For Pokemon
struct linklist{
    char ourpokemon[30];
    linklist *next;

}*linky=NULL;

///Insertion At Last of Linked List and Getting the value of "Head" everytime
linklist *newnode(linklist *head ,char x[]){
    if (head == NULL){
        linklist *temp;
        temp=new linklist;
        strcpy(temp->ourpokemon,x);
        temp->next=NULL;
        head=temp;
    }
    else
    {
        head->next  = newnode(head->next,x);
    }
return head;
}

void printnode(linklist* head){
    int i=0;
    if(head==NULL){
            printf("YOU DONT HAVE ANY POKEMON!");
            return;
    }
    if(out.empty()){                                                ///All pokemons are printed only when the out is empty
            while(head!=NULL){
                    i++;
                    cout<<i<<". "<<head->ourpokemon<<"   ";
                    head=head->next;
            }
    }
    else                                                            ///Only those pokemon are printed that are not there in 'out'
            while(head!=NULL){
                int flag=0;
                for(int j=0;j<out.size();j++){
                    if(strcmp(out[j].c_str(),head->ourpokemon)==0){  //checking the particular pokemon in linked list as if it is there in 'out'
                        flag=1;
                    }
                }
                if(flag==0){                                        ///If none of the pokemon is common then only the list is prined else not
                    i++;
                    cout<<i<<". "<<head->ourpokemon<<"   ";
                }
                head=head->next;
            }
///*********************Not Done
    if(i==0)
                cout<<"ALL your Pokemons Fainted!";


}





/*PokeDex*/


///Node for binary tree
struct node{
    int key;
    char data[30];
    node *left, *right;
};

///Insertion in BST
node* ins( node* root , int key ,string data){
if (root == NULL){
    node *temp;
    temp=new node;
    temp->key = key;
    strcpy(temp->data,data.c_str());                   ///c_str() means u r returning a pointer that is null terminated
    temp->left = temp->right = NULL;
    root=temp;
}
if (key < root->key)
        root->left  = ins(root->left, key,data);
else if (key > root->key)
        root->right = ins(root->right, key,data);
return root;
}
///Inorder Printing BST
void inorder(node *root){
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->key<<" "<<root->data;
        inorder(root->right);
    }
}
///Function to form tree using File Handling
node * pokepoke(){

    node * root=NULL;
    int t=0;
    string line;
    ifstream myfile;
    myfile.open("pokedex.txt");
    if(myfile.is_open()){
    while(getline(myfile,line))    {
        t++;
        root=ins(root,t,line);
    }
    }
    return root;
    }
///BST Search
node *binarysearch(node *root,int pno){
    if (root == NULL || root->key == pno)
       return root;
    if (root->key < pno)
       return binarysearch(root->right,pno);
        return binarysearch(root->left,pno);
}
///Function to print the Information
void searchpokeno(node * root){                                                       ///Used for Pokedex
 int i;
system("cls");
gotoxy(43,2);
printf("%c",201);
for(i=24;i<67;i++){
gotoxy(i+20,7-5);
printf("%c",205);
}
gotoxy(87,2);
printf("%c",187);
for(i=0;i<20;i++){
gotoxy(87,3+i);
printf("%c",186);
}
gotoxy(87,23);
printf("%c",188);
for(i=24;i<67;i++){
gotoxy(i+20,23);
printf("%c",205);
}
for(i=0;i<20;i++){
gotoxy(43,i+3);
printf("%c",186);
}
gotoxy(43,23);
printf("%c",200);
gotoxy(49,4);
	   printf("    **********POKEDEX**********");
	   gotoxy(50,6);
printf("%c",201);
for(i=26;i<57;i++){
gotoxy(i+25,6);
printf("%c",205);
}
	   gotoxy(82,6);
	   printf("%c",187);
for(i=0;i<5;i++){
gotoxy(82,7+i);
printf("%c",186);
}
gotoxy(82,12);
printf("%c",188);
for(i=26;i<57;i++){
gotoxy(25+i,12);
printf("%c",205);
}
gotoxy(50,12);
printf("%c",200);
for(i=0;i<5;i++){
gotoxy(50,7+i);
printf("%c",186);
}
for(i=0;i<15;i++){
gotoxy(i+51,15);
printf("%c",205);
}
gotoxy(55,9);
cout<<root->data;
gotoxy(51,14);
cout<<"PokeDex no:      "<<root->key;
gotoxy(51,15);
cout<<"Type      :      "<<poketype[(root->key)-1];
int y=1;
gotoxy(47,17);
int j=17;
 for(int s=0;pokeinfo[(root->key)-1][s]!='\0';s++) {
     y++;
     cout<<pokeinfo[(root->key)-1][s];
     if(y==35)     {
         gotoxy(47,j++);
         y=1;
     }

 }

}
///Search of Pokemon according to the user input
void searchpoke(node *root,char pname[],int pno){                      ///Search only on the basis of PokeName             ///Used for Pokedex
    if((strcmp(pname,"0")==0)&&(pno==0))                                ///Condition : If Pno and poke name both are  wrong
        cout<<"Invalid!! Please enter pokemon name or pokemon number.";
    else
    {
        if(strcmp(pname,"0")==0)                                        ///Condition : If only Poke name is wrong ,So we search by Pno
        {
           root=binarysearch(root,pno);
            searchpokeno(root);
            //cout<<"Done";

        }
        else                                                           ///Condition: If poke Name is right
        {
         for(int w=0;w<7;w++)
         {
             if(strcmp(pokepokemon[w],pname)==0)
                {
                    searchpoke(root,"0",w+1);
                    break;
                    }                              ///Recursive function to get the Details through Pno
         }
        }
}
}

//pair<int,char[20]> x;
//map<int,char[20]> m;

///Start Of Story Mode

void game(){
int u,rnd;
int user;
char choice[30];
srand(time(NULL));
rnd=(rand()%3)+1;                                               ///whenever random value %3 ==2 ; then only pokemon will appear
if(rnd==3){
    srand(time(NULL));
    cpu=(rand()%7);
    cpuone=p[cpu];                                              ///This decides which pokemon is to be selected
    printf("Wild %s has appeared!\n\n",cpuone.name);
    printf("Do you want to 1.Run or 2.Fight?: ");
    cin>>u;
    if(u==2)
    {
     printf("Which out of your pokemon you want to choose? \n");
     printnode(linky);                                          ///Accesing pokemons from linked list
     if(linky==NULL)
     {}
     else
     {
        cout<<"\nType Pokemon name you want to choose(first letter should be capital): ";
        cin>>choice;
        for(int d=0;d<7;d++){
            if(strcmp(choice,pokepokemon[d])==0)               ///checking if the pokemon exist in the list
                user=d;
        }
     }
     A:
     userone=p[user];
    fflush(stdin);
    system("cls");
    c=cpuone.hp;
    c1=c;
    d=userone.hp;
    d1=d;
    nm:
    for(a=0;;a++)                                           ///Displaying the screen of fight mode
    {

        printf("%s\nHP: %d\n", cpuone.name,cpuone.hp);
       if(a==0)                                             ///For the initial state...printing full energy
        {
            for(i=0;i<(cpuone.hp);i++){
            printf("%c",219);                           // printing Dark block
            delay(10);
			}
            e1=1;
        }
        else                                                ///For later states
        {

        	 for(int i1=0;i1<60;i1++)
        	 {
        	 	gotoxy(i1,12);
        	 	printf("%c",177);
			 }
                    gotoxy(0,12);
           for(i=0;i< c - cpuone.hp;i++){

                printf("\r");
                for(k=0;k<c1;k++){
                    printf("%c",219);
                }
                for(i=0;i<c-c1;i++){

                    printf("%c",177);
                }
                c1--;
                delay(20);
                e1=1;
            }


        }
        if(e1==0){
            for(i=0;i<cpuone.hp;i++)
                printf("%c", 219);
        }
        printf("\n\n");

        ///Printing the info of user

        printf("%s\nHP: %d\n", userone.name,userone.hp);
        if(a==0)
        {
            for(i=0;i<userone.hp;i++)
            {
                printf("%c",219);
                delay(10);
            }
            e=1;
        }
        else
        {
        	 for(int i1=0;i1<60;i1++)
        	 {
        	 	gotoxy(i1,15);
        	 	printf("%c",177);
			 }
                    gotoxy(0,15);
            for(i=0;i< d - userone.hp;i++)
            {
                printf("\r");
                for(k=0;k<d1;k++)
                    printf("%c",219);
                for(i=0;i<d-d1;i++)
                    printf("%c",177);
                d1--;
                delay(20);
                e=1;
            }
        }
        if(e==0)
        {
            for(i=0;i<userone.hp;i++)
                printf("%c",219);
        }
        printf("\n");
         c=cpuone.hp;
        c1=c;
        d=userone.hp;
        d1=d;
        e=0;
        e1=0;
        printf("\nSelect a Move from Below: \n\n");
        for(i=0;i<4;i++)
        {
            printf("%d: %d/%d ", i+1,atkppuser[userone.moveset[i]],atkppcpu[userone.moveset[i]]);
            typdisplay(atktyp[userone.moveset[i]]);
            puts(moves[userone.moveset[i]]);
        }
        printf("%d:            Throw PokeBall\n\n",5);

        scanf("%d", &usermv);
        if(usermv==5)
        {
            srand(time(NULL));
            int ball=(rand()%6)+1;
            if(ball>=2)
                {cout<<"**************************!!CAUGHT!!*****************************";
                printf("\nAdding %s in your Pokedex:",cpuone.name);
                cpuone.hp=60;
                userone.hp=60;
                linky=newnode(linky,cpuone.name);
                for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                    atkppcpu[k]=tempz[k];
                }
                out.clear();
                delay(1000);
                return;
                }
            else
                {cout<<"OOPS! You missed it!";
                delay(1000);
                system("cls");
                goto nm;
                }
        }
        else
        {
        while(usermv > 5 || usermv < 1)
        {
            printf("Invailid move try again\n");
            scanf("%d",&usermv);
        }
        while(atkppuser[userone.moveset[usermv-1]]==0)
        {
            if(atkppuser[userone.moveset[usermv-1]]==0)
                printf("No PP left. Try other move\n");
            scanf("%d", &usermv);
        }
        usermv=usermv-1;
        cpumv=rand()%4;
        while(atkppcpu[cpuone.moveset[cpumv]]==0)
        {
            cpumv=rand()%4;
        }
        system("cls");
        if(chkspd(userone.spd,cpuone.spd)==1)
        {
            printf("\n\n%s used ", userone.name);
            puts(moves[userone.moveset[usermv]]);
            atkppuser[userone.moveset[usermv]]--;
            dmgmul=calcdmgmul(cpuone.typ,atktyp[userone.moveset[usermv]]);
            cpuone.hp = cpuone.hp - (((userone.atk*atkpwr[userone.moveset[usermv]])/(cpuone.def*20))*dmgmul);
            if(userone.moveset[usermv]==5)
               {
                   cpuone.atk--;
                   printf("\n%s ATTACK FELL",cpuone.name);
               }
            if(userone.moveset[usermv]==6)
                {
                    cpuone.def--;
                    printf("\n%s DEFENSE FELL",cpuone.name);
                }
                if(userone.moveset[usermv]==16)
               {
                   cpuone.spd--;
                   printf("\n%s SPEED FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==17)
               {
                   userone.spd++;
                   printf("\n%s SPEED ROSE",userone.name);
               }

            if(cpuone.hp<=0)
            {printf("\n\n%s fainted\n\nYOU WIN\n\n", cpuone.name);
                cpuone.hp=60;
                userone.hp=60;
                out.clear();
                 for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                    atkppcpu[k]=tempz[k];
                }
                delay(1000);break;
            }
            printf("\n\n%s used ",cpuone.name);
            puts(moves[cpuone.moveset[cpumv]]);
            atkppcpu[cpuone.moveset[cpumv]]--;
            dmgmul=calcdmgmul(userone.typ,atktyp[cpuone.moveset[cpumv]]);
            userone.hp = userone.hp - (((cpuone.atk*atkpwr[cpuone.moveset[cpumv]])/(userone.def*20))*dmgmul);
            if(cpuone.moveset[cpumv]==5)
                {
                    userone.atk--;
                    printf("\n%s ATTACK FELL",userone.name);
                }
            if(cpuone.moveset[cpumv]==6)
                {
                    userone.def--;
                    printf("\n%s DEFENSE FELL",userone.name);
                }
                if(cpuone.moveset[cpumv]==16)
               {
                   userone.spd--;
                   printf("\n%s SPEED FELL",userone.name);
               }
               if(cpuone.moveset[cpumv]==17)
               {
                   cpuone.spd++;
                   printf("\n%s SPEED ROSE",cpuone.name);
               }
            printf("\n\n");
        }
        else
        {
            printf("\n\n%s used ",cpuone.name);
            puts(moves[cpuone.moveset[cpumv]]);
            atkppcpu[cpuone.moveset[cpumv]]--;
            dmgmul=calcdmgmul(userone.typ,atktyp[cpuone.moveset[cpumv]]);
           userone.hp = userone.hp - (((cpuone.atk*atkpwr[cpuone.moveset[cpumv]])/(userone.def*20))*dmgmul);
            if(cpuone.moveset[cpumv]==5)
               {
                   userone.atk--;
                   printf("\n%s ATTACK FELL",userone.name);
               }
            if(cpuone.moveset[cpumv]==6)
                {
                    userone.def--;
                    printf("\n%s DEFENSE FELL",userone.name);
                }
                if(cpuone.moveset[cpumv]==16)
               {
                   userone.spd--;
                   printf("\n%s SPEED FELL",userone.name);
               }
               if(cpuone.moveset[cpumv]==17)
               {
                   cpuone.spd++;
                   printf("\n%s SPEED ROSE",cpuone.name);
               }
            if(userone.hp<=0)
            {printf("%s fainted\n", userone.name);
            userone.hp=60;
             for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                }
            out.push_back(userone.name);
            cout<<"Choose your next Pokemon ->\n";
            printnode(linky);
            if(linky==NULL)
            {}
            else
            {
            cout<<"\nEnter Pokemon you want to choose: ";
            cin>>choice;
            if(strcmp(choice,"0")==0)
            {
                cpuone.hp=60;
                out.clear();
                delay(3000);
                 for(int k=0;k<20;k++)
                {
                    atkppcpu[k]=tempz[k];
                }

            }
            else
            {
            for(int d=0;d<7;d++)
            {
            if(strcmp(choice,pokepokemon[d])==0)
            user=d;
            }goto A;}

        break;}}
            printf("\n\n%s used ", userone.name);
            puts(moves[userone.moveset[usermv]]);
            atkppuser[userone.moveset[usermv]]--;
            dmgmul=calcdmgmul(cpuone.typ,atktyp[userone.moveset[usermv]]);
           cpuone.hp = cpuone.hp - (((userone.atk*atkpwr[userone.moveset[usermv]])/(cpuone.def*20))*dmgmul);
            if(userone.moveset[usermv]==5)
                {
                    cpuone.atk--;
                    printf("\n%s ATTACK FELL",cpuone.name);
                }
            if(userone.moveset[usermv]==6)
               {
                   cpuone.def--;
                   printf("\n%s DEFENSE FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==16)
               {
                   cpuone.spd--;
                   printf("\n%s SPEED FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==17)
               {
                   userone.spd++;
                   printf("\n%s SPEED ROSE",userone.name);
               }
            printf("\n\n");
        }
        if(userone.hp<=0)
            {printf("%s fainted\n", userone.name);
            userone.hp=60;
             for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                }
            out.push_back(userone.name);
            cout<<"Choose your next Pokemon ->\n";
            printnode(linky);
            if(linky==NULL)
            {}
            else
            {
            cout<<"\nEnter Pokemon you want to choose: ";
            cin>>choice;
            if(strcmp(choice,"0")==0)
            {
                cpuone.hp=60;
                out.clear();
                delay(3000);
                 for(int k=0;k<20;k++)
                {
                    atkppcpu[k]=tempz[k];
                }

            }
            else
            {
            for(int d=0;d<7;d++)
            {
            if(strcmp(choice,pokepokemon[d])==0)
            user=d;
            }goto A;}

        break;}
            }
        if(cpuone.hp<=0)
            {printf("%s fainted\nYOU WIN", cpuone.name);
            cpuone.hp=60;
            userone.hp=60;
            out.clear();
             for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                    atkppcpu[k]=tempz[k];
                }
            delay(2000);
        break;
        }

    }
    }
    }
}}

bool stopgame=false;
int health =100;
void mapgame(){                                                                         ///Story Mode
    while(stopgame==false && level==1){
        system("cls");
        for(int y=0;y<15;y++)
            cout<<maps[y]<<endl;
        cout<<"Health: "<<health<<endl;
        for(int y=0;y<15;y++)
            for(int x=0;x<37;x++)
            switch(maps[y][x])
        {
            case '#':maps[y][x]=219;break;
            /*case '*':{maps[y][x]=219;
                      if(vary==2)
                        maps[y][x]=' ';
                      break;
                     }*/

            case '@':{
                    if(GetAsyncKeyState(VK_UP)!=0)
                    {int y2=y-1;
                    switch(maps[y2][x])
                    {
                        case ' ':{
                                 maps[y][x]=' ';
                                 maps[y2][x]='@';
                                 y--;
                                 game();}break;
                        case '&':playgym(1,3);break;
                        case '$':playgym(2,3);break;
                        case '%':playgym(3,6);break;

                    }
                    }
                    else if(GetAsyncKeyState(VK_DOWN)!=0)
                    {int y2=y+1;
                    switch(maps[y2][x])
                    {
                        case ' ':{
                                 maps[y][x]=' ';
                                 maps[y2][x]='@';
                                 y++;
                                 game();}break;
                        case '&':playgym(1,3);break;
                        case '$':playgym(2,3);break;
                        case '%':playgym(3,6);break;

                    }
                    }
                    else if(GetAsyncKeyState(VK_LEFT)!=0)
                    {int x2=x-1;
                    switch(maps[y][x2])
                    {
                        case ' ':{char temp=maps[y][x];
                                 maps[y][x]=maps[y][x2];
                                 maps[y][x2]=temp;
                                 x--;
                                 game();}break;
                        case '&':playgym(1,3);break;
                        case '$':playgym(2,3);break;
                        case '%':playgym(3,6);break;
                    }
                    }
                    else if(GetAsyncKeyState(VK_RIGHT)!=0)
                    {int x2=x+1;
                    switch(maps[y][x2])
                    {
                        case ' ':{char temp=maps[y][x];
                                 maps[y][x]=maps[y][x2];
                                 maps[y][x2]=temp;
                                 x++;
                                 game();}break;
                        case '&':playgym(1,3);break;
                        case '$':playgym(2,3);break;
                        case '%':playgym(3,6);break;

                    }
                    }
                    }

        }

    }

}



int main(){

  MFF:
    int i;
    char tempstr[10],title[]={"******************************Pokemon: Battle For Survival******************************\n\n"};
    system("color 3e");
    cout<<("\n\n\n\t\t");
	while(title[clk]!='\0')    {
           cout<<("%c", title[clk]);
            clk++;
            delay(40);
    }
    clk=0;
    cout<<("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\n\n\t\t\t\t\t   Version 1.0");
	cout<<("\n\n\n\n\n\n\n\n\t\t\t\t\t  Please wait Game is LOADING....");

    cout<<("\n\t");
	for(int i=0;i<101;i++){
			printf("%c",177); ///ASCII Symbol of 'Loading' (Page 1)

	}
	cout<<("\r\t");
	for(int i=0;i<50;i++){
			printf("%c", 219);  ///ASCII Symbol of completing loading(page 1)
			delay(20);

	}
	for(int i=0;i<=49;i++){
			printf("%c", 219);
			delay(90);

	}

	int x;
	y1:
		int f=0;
        system("cls"); //For clearing the output screen
///Used for Building the box
        gotoxy(43,2);
        printf("%c",201);
for(i=24;i<59;i++){
gotoxy(i+20,7-5);
printf("%c",205);
}
gotoxy(24+55,7-5);
printf("%c",187);
for(i=8;i<21;i++){
gotoxy(43,i-5);
printf("%c",186);
}
gotoxy(43,21-5);
printf("%c",200);
for(i=24;i<59;i++){
gotoxy(i+20,21-5);
printf("%c",205);
}
gotoxy(72+7,21-5);
printf("%c",188);
for(i=20;i>7;i--){
gotoxy(72+7,i-5);
printf("%c",186);
}gotoxy(54,4);

printf("Pokemons Red 2.1"); //delay(500);
    gotoxy(47,8);
    printf("1. Start Story mode ");gotoxy(47,10);delay(500);
	printf("2. Start Random fight");gotoxy(47,12); delay(500);
	printf("3. Pokedex");delay(500);
	gotoxy(2,17);
	delay(1000);
   printf("%c",201);
   gotoxy(3,17); printf("%c",205);
   gotoxy(4,17); printf("%c",205);
   gotoxy(98,21); printf("%c",205);
   gotoxy(97,21); printf("%c",205);
   for(i=1;i<3;i++){
   	gotoxy(2,i+17);
   	printf("%c",186);
   }
    for(i=2;i<=3;i++){
   	gotoxy(99,i+17);
   	printf("%c",186);
   }

   gotoxy(3,17+1);
	printf("Short forms used in game ");gotoxy(3,19);printf("HP->Hit Point . It means Health");gotoxy(3,20);printf("PP->Power points . It means number of attack pokemon can make for particular move in one battle\n");
	gotoxy(99,21);
	 printf("%c",188);
	    delay(1000);

	  	gotoxy(22,22+2);
	  	printf("%c",201);
	  	for(i=0;i<10;i++){
	  			gotoxy(23+i,22+2);

		  	printf("%c",205);
		  }
        for(i=0;i<3;i++){
		  	 gotoxy(22,23+i+2);printf("%c",186);
		  }
		for(i=0;i<3;i++){
		  	 gotoxy(22,23+i+2);printf("%c",186);
		  }
        for(i=0;i<10;i++){
	  			gotoxy(63+i,22+2);
	  		printf("%c",205);
		  }
		  gotoxy(63+i,22+2);
		  printf("%c",187);
        for(i=0;i<3;i++){
		  	 gotoxy(73,23+i+2);printf("%c",186);
		  }
        for(i=0;i<16;i++){
		  		gotoxy(41+i,22+2);printf("%c",205);
			  }
            gotoxy(3+20,25);


	printf("CHOOSE OPTIONS TO CONTINUE: ");gotoxy(23,24+2);
		gotoxy(23,25+2);
    scanf("%d",&x);

if(x==3){
        jj:
 int pno;
 char pname[30];
 node* root=NULL;
system("cls");
gotoxy(43,2);
printf("%c",201);
for(i=24;i<67;i++){
gotoxy(i+20,7-5);
printf("%c",205);
}
gotoxy(87,2);
printf("%c",187);
for(i=0;i<20;i++){
gotoxy(87,3+i);
printf("%c",186);
}
gotoxy(87,23);
printf("%c",188);
for(i=24;i<67;i++){
gotoxy(i+20,23);
printf("%c",205);
}
for(i=0;i<20;i++){
gotoxy(43,i+3);
printf("%c",186);
}
gotoxy(43,23);
printf("%c",200);
gotoxy(49,4);
	   printf("    **********POKEDEX**********");
	   gotoxy(50,6);
printf("%c",201);
for(i=26;i<57;i++){
gotoxy(i+25,6);
printf("%c",205);
}
	   gotoxy(82,6);
	   printf("%c",187);
for(i=0;i<5;i++){
gotoxy(82,7+i);
printf("%c",186);
}
gotoxy(82,12);
printf("%c",188);
for(i=26;i<57;i++){
gotoxy(25+i,12);
printf("%c",205);
}
gotoxy(50,12);
printf("%c",200);
for(i=0;i<5;i++){
gotoxy(50,7+i);
printf("%c",186);
}
for(i=0;i<15;i++){
gotoxy(i+51,15);
printf("%c",205);
}
/**/
gotoxy(50,15);
printf("%c",201);
gotoxy(66,15);
printf("%c",187);
for(i=0;i<1;i++){
gotoxy(66,16+i);
printf("%c",186);
}
gotoxy(66,17);
printf("%c",188);
for(i=0;i<15;i++){
gotoxy(51+i,17);
printf("%c",205);
}
gotoxy(50,17);
printf("%c",200);
for(i=0;i<1;i++){
gotoxy(50,16+i);
printf("%c",186);
}
/**/
gotoxy(67,15);
printf("%c",201);
	   gotoxy(83,15);
	   printf("%c",187);
for(i=0;i<1;i++){
gotoxy(83,16+i);
printf("%c",186);
}
gotoxy(83,17);
printf("%c",188);
for(i=0;i<15;i++){
gotoxy(68+i,17);
printf("%c",205);
}
for(i=0;i<15;i++){
gotoxy(68+i,15);
printf("%c",205);
}

gotoxy(67,17);
printf("%c",200);
for(i=0;i<1;i++){
gotoxy(67,16+i);
printf("%c",186);
}
gotoxy(51,13);
cout<<"Enter name: ";
gotoxy(68,13);
cout<<"Enter P.no:";
gotoxy(56,20);
cout<<"Enter 0 to switch";
gotoxy(51,16);
cin>>pname;
gotoxy(68,16);
cin>>pno;
gotoxy(51,20);
cout<<"Finding your Pokemon....";
delay(10);
root=pokepoke();                                        ///function For Forming the BST
searchpoke(root,pname,pno);                             ///Search Function to find the Pokemon after the inputs from user
    //pokepoke();
    //cout<<"hello";
    gotoxy(2,27);
    char ctt;
	cout<<"Do You Wish to Play Again(Y/N)?";
	cin>>ctt;
	if(ctt=='y'||ctt=='Y'){
		goto jj;
	}
	else if(ctt=='n'||ctt=='N'){
            system("cls");
        main();
    }}
else if(x==1){
        system("cls");
        cout<<"                                           <-Choose your First Pokemon->\n\n\n\n";
        cout<<"1. Bulbasaur                                        2.Charmander                              3.Squirtle\n\n";
        cin>>user;
        user=user-1;
        linky=newnode(linky,p[user].name);    ///inserting Vlaues in Pokemon Linked List
        mapgame();
}
else if(x==2){
system("cls");
gotoxy(43,2);
                    ///Printing upper line of Box
printf("%c",201);
for(i=24;i<59;i++){
gotoxy(i+20,7-5);
printf("%c",205);
}
gotoxy(24+55,7-5);
printf("%c",187);    ///printing Right line of Box
for(i=8;i<21;i++){
gotoxy(43,i-5);
printf("%c",186);
}
gotoxy(43,21-5);       ///printing down line of Box
printf("%c",200);
for(i=24;i<59;i++){     ///printing Left line of Box
gotoxy(i+20,21-5);
printf("%c",205);
}
gotoxy(72+7,21-5);
printf("%c",188);
for(i=20;i>7;i--){
gotoxy(72+7,i-5);
printf("%c",186);
}gotoxy(49,4);

///End of Making Box


	   printf(" BATTLE POKEMON SELECTION"); //delay(500);
	   gotoxy(45,6);
    printf("Index  Pokemon Name       Type");
    gotoxy(47,7);
    printf("1      Pikachu         Electric");delay(500);
    gotoxy(47,8);
    printf("2      Sandshrew       Ground");delay(500);
    gotoxy(47,9);
    printf("3      Bulbasaur       Grass");delay(500);
    gotoxy(47,10);
    printf("4      Charmander      Fire");gotoxy(47,11); delay(500);
	printf("5      Squirtle        Water");gotoxy(47,12); delay(500);
	printf("6      Pidgey          Flying");gotoxy(47,13); delay(500);
	printf("7      Seel            Ice");
	gotoxy(2,17);
	printf("\n\t\t\t\tChoose your pokemon by entering Index : ");
	printf("\n\n\t\t\t\tEXIT    PRESS 8\n\t\t\t\t");
    scanf("%d", &user);
    if(user==8)goto y1;                     ///Goes to Main Screen
    user=user-1;
    srand(time(NULL));
    while(cpu==user){   ///If the option choose by user is same as CPU then we change it ( initially CPU=0) & we find the remainder with 7 because we have only 7 pokemons
    cpu=rand()%7;
    }
    system("cls");
    printf("You chose %s\n\n", p[user].name);
    printf("ASH chose %s\n\n",p[cpu].name);
    printf("Press enter to continue...........");
    fflush(stdin);
    gets(tempstr);  ///NOT DONE
    system("cls");
    c=p[cpu].hp;    /// C =the HP of the pokemon choosed by cpu
    c1=c;
    d=p[user].hp;   ///Storing the HP of the pokemon choosed by user
    d1=d;
    for(a=0;;a++){
        printf("%s\nHP: %d\n", p[cpu].name,p[cpu].hp);
       if(a==0){                ///For the first loop
            for(i=0;i<(p[cpu].hp);i++){
            printf("%c",219);
            delay(10);
			}
            e1=1;
        }
        else{
        	 for(int i1=0;i1<60;i1++){
        	 	gotoxy(i1,12);
        	 	printf("%c",177);
			 }
            gotoxy(0,12);
            for(i=0;i< c - p[cpu].hp;i++){
                printf("\r");
                for(k=0;k<c1;k++){
                    printf("%c",219);
                }
                for(i=0;i<c-c1;i++){

                    printf("%c",177);
                }
                c1--;
                delay(20);
                e1=1;
            }


        }
        if(e1==0){
            for(i=0;i<p[cpu].hp;i++)
                printf("%c", 219);
        }
        printf("\n\n");
        printf("%s\nHP: %d\n", p[user].name,p[user].hp);
        if(a==0){
            for(i=0;i<p[user].hp;i++){
                printf("%c",219);
                delay(10);
            }
            e=1;
        }
        else{
        	 for(int i1=0;i1<60;i1++){
        	 	gotoxy(i1,15);
        	 	printf("%c",177);
			 }
                    gotoxy(0,15);
            for(i=0;i< d - p[user].hp;i++){
                printf("\r");
                for(k=0;k<d1;k++)
                    printf("%c",219);
                for(i=0;i<d-d1;i++)
                    printf("%c",177);
                d1--;
                delay(20);
                e=1;
            }
        }
        if(e==0){
            for(i=0;i<p[user].hp;i++)
                printf("%c",219);
        }
        printf("\n");
         c=p[cpu].hp;
        c1=c;
        d=p[user].hp;
        d1=d;
        e=0;
        e1=0;
        printf("\nSelect a Move from Below \n\n");
        for(i=0;i<4;i++){
            printf("%d: %d/%d ", i+1,atkppuser[p[user].moveset[i]],atkpp[p[user].moveset[i]]);
            typdisplay(atktyp[p[user].moveset[i]]);
            puts(moves[p[user].moveset[i]]);
        }

        scanf("%d", &usermv);
        while(usermv > 4 || usermv < 1){
            printf("Invailid move try again\n");
            scanf("%d",&usermv);
        }
        while(atkppuser[p[user].moveset[usermv-1]]==0){
            if(atkppuser[p[user].moveset[usermv-1]]==0)
                printf("No PP left. Try other move\n");
            scanf("%d", &usermv);
        }
        usermv=usermv-1;
        cpumv=rand()%4;
        while(atkppcpu[p[cpu].moveset[cpumv]]==0){
            cpumv=rand()%4;
        }
        system("cls");
        if(chkspd(p[user].spd,p[cpu].spd)==1){
            printf("\n\n%s used ", p[user].name);
            puts(moves[p[user].moveset[usermv]]);
            atkppuser[p[user].moveset[usermv]]--;
            dmgmul=calcdmgmul(p[cpu].typ,atktyp[p[user].moveset[usermv]]);
            p[cpu].hp = p[cpu].hp - (((p[user].atk*atkpwr[p[user].moveset[usermv]])/(p[cpu].def*20))*dmgmul);
            if(p[user].moveset[usermv]==5){
                   p[cpu].atk--;
                   printf("\n%s ATTACK FELL",p[cpu].name);
               }
            if(p[user].moveset[usermv]==6){
                    p[cpu].def--;
                    printf("\n%s DEFENSE FELL",p[cpu].name);
                }
                if(p[user].moveset[usermv]==16){
                   p[cpu].spd--;
                   printf("\n%s SPEED FELL",p[cpu].name);
               }
               if(p[user].moveset[usermv]==17){
                   p[user].spd++;
                   printf("\n%s SPEED ROSE",p[user].name);
               }
            if(p[cpu].hp<=0){
                printf("\n\n%s fainted\n\nYOU WIN\n\n", p[cpu].name);f=0;
                break;
            }
            printf("\n\n%s used ",p[cpu].name);
            puts(moves[p[cpu].moveset[cpumv]]);
            atkppcpu[p[cpu].moveset[cpumv]]--;
            dmgmul=calcdmgmul(p[user].typ,atktyp[p[cpu].moveset[cpumv]]);
            p[user].hp = p[user].hp - (((p[cpu].atk*atkpwr[p[cpu].moveset[cpumv]])/(p[user].def*20))*dmgmul);
            if(p[cpu].moveset[cpumv]==5)
                {
                    p[user].atk--;
                    printf("\n%s ATTACK FELL",p[user].name);
                }
            if(p[cpu].moveset[cpumv]==6)
                {
                    p[user].def--;
                    printf("\n%s DEFENSE FELL",p[user].name);
                }
                if(p[cpu].moveset[cpumv]==16)
               {
                   p[user].spd--;
                   printf("\n%s SPEED FELL",p[user].name);
               }
               if(p[cpu].moveset[cpumv]==17)
               {
                   p[cpu].spd++;
                   printf("\n%s SPEED ROSE",p[cpu].name);
               }
            printf("\n\n");
        }
        else{
            printf("\n\n%s used ",p[cpu].name);
            puts(moves[p[cpu].moveset[cpumv]]);
            atkppcpu[p[cpu].moveset[cpumv]]--;
            dmgmul=calcdmgmul(p[user].typ,atktyp[p[cpu].moveset[cpumv]]);
           p[user].hp = p[user].hp - (((p[cpu].atk*atkpwr[p[cpu].moveset[cpumv]])/(p[user].def*20))*dmgmul);
            if(p[cpu].moveset[cpumv]==5)
               {
                   p[user].atk--;
                   printf("\n%s ATTACK FELL",p[user].name);
               }
            if(p[cpu].moveset[cpumv]==6)
                {
                    p[user].def--;
                    printf("\n%s DEFENSE FELL",p[user].name);
                }
                if(p[cpu].moveset[cpumv]==16)
               {
                   p[user].spd--;
                   printf("\n%s SPEED FELL",p[user].name);
               }
               if(p[cpu].moveset[cpumv]==17)
               {
                   p[cpu].spd++;
                   printf("\n%s SPEED ROSE",p[cpu].name);
               }
            if(p[user].hp<=0)
            {printf("\n\n%s fainted\n\nYou lose\n\n", p[user].name);f=1;
            break;}
            printf("\n\n%s used ", p[user].name);
            puts(moves[p[user].moveset[usermv]]);
            atkppuser[p[user].moveset[usermv]]--;
            dmgmul=calcdmgmul(p[cpu].typ,atktyp[p[user].moveset[usermv]]);
           p[cpu].hp = p[cpu].hp - (((p[user].atk*atkpwr[p[user].moveset[usermv]])/(p[cpu].def*20))*dmgmul);
            if(p[user].moveset[usermv]==5)
                {
                    p[cpu].atk--;
                    printf("\n%s ATTACK FELL",p[cpu].name);
                }
            if(p[user].moveset[usermv]==6)
               {
                   p[cpu].def--;
                   printf("\n%s DEFENSE FELL",p[cpu].name);
               }
               if(p[user].moveset[usermv]==16)
               {
                   p[cpu].spd--;
                   printf("\n%s SPEED FELL",p[cpu].name);
               }
               if(p[user].moveset[usermv]==17)               {
                   p[user].spd++;
                   printf("\n%s SPEED ROSE",p[user].name);
               }
            printf("\n\n");
        }
        if(p[user].hp<=0){
            printf("%s fainted\nYou lose", p[user].name);f=1;
        break;}
        if(p[cpu].hp<=0){
            printf("%s fainted\nYOU WIN", p[cpu].name);f=0;
        break;
        }

    }

    delay(2000);
    system("cls");
	gotoxy(40,7);
    if(f==1)
    {
    	printf("POKEMON MASTER NEVER LOOSES HOPE");
    	delay(2000);
	}
	if(f==0)
	{
		printf("CONGRATULATIONS!! YOU ARE A POKEMON MASTER");
		delay(2000);
	}
	gotoxy(40,12);
	char ctt,ctt1;
	scanf("%c",&ctt1);
	printf("Do You Wish to Play Again(Y/N)");
	scanf("%c",&ctt);
	if(ctt=='y'||ctt=='Y')
	{
		goto y1;
	}
	else if(ctt=='n'||ctt=='N')
	{gotoxy(40,17);
	printf("THANKYOU  FOR  PLAYING");
	delay(2000);
	system("cls");
	main();
    return 0;
	}

}
}
int chkspd(int userspd,int cpuspd){
    srand(time(NULL));
    if(userspd>cpuspd)
        return 1;
    if(cpuspd>userspd)
        return 2;
}
int calcdmgmul(int pktyp,int atktyp){
    switch(pktyp)
    {
    case 101:
        switch(atktyp)
        {
        case 101:
            return 1;
            break;
        case 71:
            return 3;
            break;
        case 103:
            return 2;
            break;
        case 102:
            return 2;
            break;
        case 119:
            return 2;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 1;
            break;
        case 105:
            return 2;
            break;
        }
        break;
    case 71:
        switch(atktyp)
        {
        case 101:
            return 1;
            break;
        case 71:
            return 2;
            break;
        case 103:
            return 3;
            break;
        case 102:
            return 1;
            break;
        case 119:
            return 3;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 2;
            break;
        case 105:
            return 3;
            break;
        }
        break;
    case 103:
        switch(atktyp)
        {
        case 101:
            return 2;
            break;
        case 71:
            return 2;
            break;
        case 103:
            return 1;
            break;
        case 102:
            return 3;
            break;
        case 119:
            return 2;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 3;
            break;
        case 105:
            return 3;
            break;
        }
        break;
    case 102:
        switch(atktyp)
        {
        case 101:
            return 2;
            break;
        case 71:
            return 3;
            break;
        case 103:
            return 1;
            break;
        case 102:
            return 1;
            break;
        case 119:
            return 3;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 2;
            break;
        case 105:
            return 1;
            break;
        }
        break;
    case 119:
        switch(atktyp)
        {
        case 101:
            return 3;
            break;
        case 71:
            return 2;
            break;
        case 103:
            return 3;
            break;
        case 102:
            return 1;
            break;
        case 119:
            return 1;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 2;
            break;
        case 105:
            return 1;
            break;

        }
        break;
    case 70:
         switch(atktyp)
        {
        case 101:
            return 2;
            break;
        case 71:
            return 2;
            break;
        case 103:
            return 2;
            break;
        case 102:
            return 3;
            break;
        case 119:
            return 2;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 2;
            break;
        case 105:
            return 1;
            break;

        }
        break;
    case 105:
         switch(atktyp)
        {
        case 101:
            return 3;
            break;
        case 71:
            return 1;
            break;
        case 103:
            return 1;
            break;
        case 102:
            return 2;
            break;
        case 119:
            return 2;
            break;
        case 110:
            return 2;
            break;
        case 70:
            return 2;
            break;
        case 105:
            return 3;
            break;

        }
        break;
    }
}
void playgym(int leader,int num){
    int ghost=0;
int u,rnd;
char choice[30];
    int counter=0;
C:
system("cls");
if(leader==1)
{
cpuone=p[gym1[counter]];
}
else if(leader==2)
{
    cpuone=p[gym2[counter]];
}
else
{
    cpuone=p[gym3[counter]];
}
    printf("Gym Leader chose %s!\n\n",cpuone.name);
    delay(2000);
    if(ghost==0)
    {
printf("Which out of your pokemon you want to choose? \n");
     printnode(linky);
     if(linky==NULL)
     {}
     else
     {
     cout<<"\nEnter Pokemon you want to choose: ";
     cin>>choice;
     for(int d=0;d<7;d++)
     {
      if(strcmp(choice,pokepokemon[d])==0)
            user=d;
     }
     }
     KK:
     userone=p[user];
    }
    fflush(stdin);
    system("cls");
    c=cpuone.hp;
    c1=c;
    d=userone.hp;
    d1=d;
    for(a=0;;a++)
    {

        printf("%s\nHP: %d\n", cpuone.name,cpuone.hp);
       if(a==0)
        {
            for(i=0;i<(cpuone.hp);i++)
            {printf("%c",219);
            delay(10);
			}
            e1=1;
        }
        else
        {

        	 for(int i1=0;i1<60;i1++)
        	 {
        	 	gotoxy(i1,12);
        	 	printf("%c",177);
			 }
                    gotoxy(0,12);
           for(i=0;i< c - cpuone.hp;i++)
            {

                printf("\r");
                for(k=0;k<c1;k++)
                {
                    printf("%c",219);
                }
                for(i=0;i<c-c1;i++){

                    printf("%c",177);
                }
                c1--;
                delay(20);
                e1=1;
            }


        }
        if(e1==0)
        {
            for(i=0;i<cpuone.hp;i++)
                printf("%c", 219);
        }
        printf("\n\n");
        printf("%s\nHP: %d\n", userone.name,userone.hp);
        if(a==0)
        {
            for(i=0;i<userone.hp;i++)
            {
                printf("%c",219);
                delay(10);
            }
            e=1;
        }
        else{
        	 for(int i1=0;i1<60;i1++){
        	 	gotoxy(i1,15);
        	 	printf("%c",177);
			 }
                    gotoxy(0,15);
            for(i=0;i< d - userone.hp;i++){
                printf("\r");
                for(k=0;k<d1;k++)
                    printf("%c",219);
                for(i=0;i<d-d1;i++)
                    printf("%c",177);
                d1--;
                delay(20);
                e=1;
            }
        }
        if(e==0){
            for(i=0;i<userone.hp;i++)
                printf("%c",219);
        }
        printf("\n");
         c=cpuone.hp;
        c1=c;
        d=userone.hp;
        d1=d;
        e=0;
        e1=0;
        printf("\nSelect a Move from Below \n\n");
        for(i=0;i<4;i++){
            printf("%d: %d/%d ", i+1,atkppuser[userone.moveset[i]],atkppcpu[userone.moveset[i]]);
            typdisplay(atktyp[userone.moveset[i]]);
            puts(moves[userone.moveset[i]]);
        }

        scanf("%d", &usermv);
        while(usermv > 5 || usermv < 1){
            printf("Invailid move try again\n");
            scanf("%d",&usermv);
        }
        while(atkppuser[userone.moveset[usermv-1]]==0)
        {
            if(atkppuser[userone.moveset[usermv-1]]==0)
                printf("No PP left. Try other move\n");
            scanf("%d", &usermv);
        }
        usermv=usermv-1;
        cpumv=rand()%4;
        while(atkppcpu[cpuone.moveset[cpumv]]==0)
        {
            cpumv=rand()%4;
        }
        system("cls");
        if(chkspd(userone.spd,cpuone.spd)==1)
        {
            printf("\n\n%s used ", userone.name);
            puts(moves[userone.moveset[usermv]]);
            atkppuser[userone.moveset[usermv]]--;
            dmgmul=calcdmgmul(cpuone.typ,atktyp[userone.moveset[usermv]]);
            cpuone.hp = cpuone.hp - (((userone.atk*atkpwr[userone.moveset[usermv]])/(cpuone.def*20))*dmgmul);
            if(userone.moveset[usermv]==5)
               {
                   cpuone.atk--;
                   printf("\n%s ATTACK FELL",cpuone.name);
               }
            if(userone.moveset[usermv]==6)
                {
                    cpuone.def--;
                    printf("\n%s DEFENSE FELL",cpuone.name);
                }
                if(userone.moveset[usermv]==16)
               {
                   cpuone.spd--;
                   printf("\n%s SPEED FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==17)
               {
                   userone.spd++;
                   printf("\n%s SPEED ROSE",userone.name);
               }

            if(cpuone.hp<=0)
            {printf("\n\n%s fainted\n\n\n\n", cpuone.name);
                cpuone.hp=60;
                counter++;
                for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                    atkppcpu[k]=tempz[k];
                }
                if(counter==num)
                {
                    out.clear();
                    userone.hp=60;
                    cout<<"WOW! you won!!Collect your badge\n";
                    vary++;
                     if(vary==2)
                    {
                        delay(2000);
                        mapgame();
                    }
                    if(vary==3)
                    {
                        system("cls");
                        cout<<"******************************!!!You are a Pokemon Master!!!**************************************";
                        main();
                    }
                }
                else
                {
                    ghost=1;
                    goto C;

                }
                delay(1000);break;
            }
            printf("\n\n%s used ",cpuone.name);
            puts(moves[cpuone.moveset[cpumv]]);
            atkppcpu[cpuone.moveset[cpumv]]--;
            dmgmul=calcdmgmul(userone.typ,atktyp[cpuone.moveset[cpumv]]);
            userone.hp = userone.hp - (((cpuone.atk*atkpwr[cpuone.moveset[cpumv]])/(userone.def*20))*dmgmul);
            if(cpuone.moveset[cpumv]==5)
                {
                    userone.atk--;
                    printf("\n%s ATTACK FELL",userone.name);
                }
            if(cpuone.moveset[cpumv]==6)
                {
                    userone.def--;
                    printf("\n%s DEFENSE FELL",userone.name);
                }
                if(cpuone.moveset[cpumv]==16)
               {
                   userone.spd--;
                   printf("\n%s SPEED FELL",userone.name);
               }
               if(cpuone.moveset[cpumv]==17)
               {
                   cpuone.spd++;
                   printf("\n%s SPEED ROSE",cpuone.name);
               }
            printf("\n\n");
        }
        else
        {
            printf("\n\n%s used ",cpuone.name);
            puts(moves[cpuone.moveset[cpumv]]);
            atkppcpu[cpuone.moveset[cpumv]]--;
            dmgmul=calcdmgmul(userone.typ,atktyp[cpuone.moveset[cpumv]]);
           userone.hp = userone.hp - (((cpuone.atk*atkpwr[cpuone.moveset[cpumv]])/(userone.def*20))*dmgmul);
            if(cpuone.moveset[cpumv]==5)
               {
                   userone.atk--;
                   printf("\n%s ATTACK FELL",userone.name);
               }
            if(cpuone.moveset[cpumv]==6)
                {
                    userone.def--;
                    printf("\n%s DEFENSE FELL",userone.name);
                }
                if(cpuone.moveset[cpumv]==16)
               {
                   userone.spd--;
                   printf("\n%s SPEED FELL",userone.name);
               }
               if(cpuone.moveset[cpumv]==17)
               {
                   cpuone.spd++;
                   printf("\n%s SPEED ROSE",cpuone.name);
               }
            if(userone.hp<=0)
            {printf("%s fainted\n", userone.name);
            userone.hp=60;
             for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                }
            out.push_back(cpuone.name);
            cout<<"Choose your next Pokemon ->\n";
            printnode(linky);
            if(linky==NULL)
            {}
            else
            {
            cout<<"\nEnter Pokemon you want to choose: ";
            cin>>choice;
            if(strcmp(choice,"0")==0)
            {
                cpuone.hp=60;
                out.clear();
                delay(3000);
                 for(int k=0;k<20;k++)
                {
                    atkppcpu[k]=tempz[k];
                }

            }
            else
            {
            for(int d=0;d<7;d++)
            {
            if(strcmp(choice,pokepokemon[d])==0)
            user=d;
            }goto KK;}

        break;}}
            printf("\n\n%s used ", userone.name);
            puts(moves[userone.moveset[usermv]]);
            atkppuser[userone.moveset[usermv]]--;
            dmgmul=calcdmgmul(cpuone.typ,atktyp[userone.moveset[usermv]]);
           cpuone.hp = cpuone.hp - (((userone.atk*atkpwr[userone.moveset[usermv]])/(cpuone.def*20))*dmgmul);
            if(userone.moveset[usermv]==5)
                {
                    cpuone.atk--;
                    printf("\n%s ATTACK FELL",cpuone.name);
                }
            if(userone.moveset[usermv]==6)
               {
                   cpuone.def--;
                   printf("\n%s DEFENSE FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==16)
               {
                   cpuone.spd--;
                   printf("\n%s SPEED FELL",cpuone.name);
               }
               if(userone.moveset[usermv]==17)
               {
                   userone.spd++;
                   printf("\n%s SPEED ROSE",userone.name);
               }
            printf("\n\n");
        }
        if(userone.hp<=0)
            {printf("%s fainted\n", userone.name);
            userone.hp=60;
             for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                }
            out.push_back(userone.name);
            cout<<"Choose your next Pokemon ->\n";
            printnode(linky);
            if(linky==NULL)
            {}
            else
            {
            cout<<"\nEnter Pokemon you want to choose: ";
            cin>>choice;
            if(strcmp(choice,"0")==0)
            {
                cpuone.hp=60;
                out.clear();
                delay(3000);
                 for(int k=0;k<20;k++)
                {
                    atkppcpu[k]=tempz[k];
                }

            }
            else
            {
            for(int d=0;d<7;d++)
            {
            if(strcmp(choice,pokepokemon[d])==0)
            user=d;
            }goto KK;}

        break;}
            }
        if(cpuone.hp<=0)
            {printf("\n\n%s fainted\n\n\n\n", cpuone.name);
                cpuone.hp=60;
                counter++;
                for(int k=0;k<20;k++)
                {
                    atkppuser[k]=tempz[k];
                    atkppcpu[k]=tempz[k];
                }
                if(counter==num)
                {
                    userone.hp=60;
                    out.clear();
                    cout<<"WOW! you won!!Collect your badge\n";
                    vary++;
                     cout<<vary<<endl;
                    if(vary==2)
                    {
                        delay(2000);
                        mapgame();
                    }
                    if(vary==3)
                    {
                        delay(3000);
                        system("cls");
                        cout<<"******************************!!!You are a Pokemon Master!!!**************************************";
                        delay(3000);
                        system("cls");
                        main();
                    }
                }
                else
                {
                    ghost=1;
                    goto C;

                }
                delay(2000);break;
        }

    }
    }
void typdisplay(int typch){
    switch(typch)
    {
        case 101:
            printf("  electric  ");
            break;
        case 71:
            printf("  ground    ");
            break;
        case 103:
            printf("  grass     ");
            break;
        case 102:
            printf("  fire      ");
            break;
        case 119:
            printf("  water     ");
            break;
        case 110:
            printf("  normal    ");
            break;
        case 70:
            printf("  flying    ");
            break;
        case 105:
            printf("  ice       ");
            break;
    }
}

