#include<stdlib.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
int n[4][4]={{0}};
int backup[4][4]={{0}};
int score = 0;

struct info {
  int score;
  char* name;
};

void display_board();
void random_block();
void move_blocks(char);
void save();
void leaderboard();
char get_control();
void rotate_board(int);
void moveright(int[],int);
int check_done();
int eq(int a[4][4], int b[4][4]);

int main() {
  random_block();
  char ch='x';
  int i,j;
  do{
    if(!eq(backup,n))
    random_block();
    display_board();
    ch = get_control();
    if(ch=='u')
    for(i=0; i<4; i++)
    for(j=0; j<4; j++)
    n[i][j] = backup[i][j];
    else {
      for(i=0; i<4; i++)
      for(j=0; j<4; j++)
      backup[i][j]=n[i][j];
      move_blocks(ch);
    }
  }while(ch!='q' && ch!='Q');
  save();
  leaderboard();
  return 0;
}
void display_board() {
  clrscr();
  cout<<flush;
  cout<<" ";
  cout<<"\t\t\t\t\t\tSCORE::"<<score<<" \n\n\n\n\n\n\n";
  for(int i=0;i<4;i++) {
    cout<<"\t\t\t |";
    for(int j=0;j<4;j++) {
      if(n[i][j])
      printf("%4d |", n[i][j]);
      else
      printf("%4c |",' ');
    }
    cout<<endl<<endl;
  }
}
void random_block() {
  //This function assignes a two in a random place
  randomize();
  int x,y;
  do {
  x = random(4);
  y = random(4);
  }while(n[x][y]!=0);
  n[x][y]=2;
}

char get_control() {
  //This function gets the input from the user on what to do next
  char ch;
  ch=getch();
  if ((int)ch == 0)
    ch=getch();
  if (check_done())
  ch = 'q';
  return ch;
}
void save()
{
  info x;
  fstream f("User.dat", ios::binary, ios::out);
  x.score = score;
  cout<<"Enter name: ";
  gets(x.name);
  f.write((char*)&x ,sizeof(x));
  f.close();
}
void leaderboard() {
  info a[20],temp;
  int i,k=1;
  fstream f("User.dat",ios::binary|ios::in);
  while(!f.eof())
  { f.read((char *)&a[k-1],sizeof(a[k-1]));
    k++;
  }
  for(i=0;i<k;i++)
  { for(int j=0;j<k-i-1;j++)
    { if(a[j].score<a[j+1].score)
      { temp = a[j];
	a[j+1] = a[j];
	a[j] = temp;
      }
    }
  }
  cout<<flush;
  if (k<3) {
    cout<<"Too little information to show the leaderboard\n";
  }
  else {
    for(i=0; i<3; i++) {
      cout<<a[i].score;
      puts(a[i].name);
    }
  }
  f.close();
}

void rotate_board(int r) {
  int b[4][4],i,j;
  if (r==1) { //Rotate Clockwise
    for (i=0; i<4; i++)
    for (j=0; j<4; j++)
    b[i][j] = n[3-j][i];
  }
  if (r==0) {
    for (i=0;i<4;i++)
    for (j=0;j<4;j++)
    b[i][j] = n[j][3-i];
  }
  for (i=0; i<4; i++)
  for (j=0; j<4; j++)
  n[i][j] = b[i][j];
}
int check_done() {
  int d[4][4];
  for(int i=0; i<4; i++)
  for(int j=0; j<4; j++)
  d[i][j] = n[i][j];
  move_blocks('P');
  move_blocks('K');
  move_blocks('H');
  move_blocks('M');
  if(eq(d,n))
  return 1;
  for(i=0; i<4; i++)
  for(j=0; j<4; j++)
  n[i][j] = d[i][j];
  return 0;
}

int eq(int a[4][4], int b[4][4]) {
  for(int i=0;i<4; i++)
  for(int j=0;j<4; j++)
  if(a[i][j]!=b[i][j])
  return 0;
  return 1;
}

void move_blocks(char ch) {
  int control = ch;
  int d[4][4];
  for (int i=0; i<4; i++)
  for (int j=0; j<4; j++)
  d[i][j] = n[i][j];
  switch(control) {
    case 80: //Down
      rotate_board(1);
    case 75: //Left
      rotate_board(1);
    case 72: //Up
      rotate_board(1);
    case 77: //Right
      for(i=0; i<4; i++)
      moveright(n[i],i);
    default:
      break;
  }
  switch(control) {
    case 80: //Down
      rotate_board(0);
    case 75: //Left
      rotate_board(0);
    case 72: //Up
      rotate_board(0);
    default:
      break;
  }
}

void moveright(int a[4], int pos) {
  int c,count=0, e[4]={0};
  int b[4] = {0},k=0,t,j,i;
  for (i=0,j=0; i<4; i++)
  if(a[i]!=0) {
    b[j] = a[i];
    j++;
  }
  for (i=0; i<4; i++)
  if (b[i]==0)
  count++;
  for (i=count; i<4; i++) {
  e[i] = b[k];
  k++;
  }
  for(i=0; i<4; i++)
  b[i]=e[i];
  k = 4-j;
  for (i=0; i<4; i++)
  cout<<b[i];
  cout<<endl;
  for (i=3; i>k; i--) {
  if (b[i]==b[i-1]) {
    score += b[i];
    b[i]*=2;
    b[i-1] = 0;
  }
  if (b[i]==0) {
    b[i] = b[i-1];
    b[i-1] = 0;
  }
  }
  i=0;
  while(i<k) {
    b[i] = 0;
    i++;
  }
  for (int x=0; x<4; x++)
  n[pos][x] = b[x];
}