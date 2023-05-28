#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

struct Numbers{
	int num_c_tv;
	int num_fc;
	int num_fd;
	int random[5];
	int total;
	int num_words;
	int wrong;
	int count;
	int complete; 
	int present[10];
};

struct Values{
	char load_tv[100][25];
	char fic_chars[100][25];
	char food_drink[100][25];
	char combined[300][25];
};

using namespace std;


int load_values(char array[][25], char line[],int i){
	
int x=0;
	
	while (line[x]!='\0'){
		array[i][x]=line[x];
		x++;
	}
	array[i][x]='\0';
	
	return x;
}

int load_lines(char array[][25],char line[],char filename[]){
	
	ifstream fin;
     fin.open(filename);
     
int i=0,x;
int num;

fin>>line;

while (line != "END" && !fin.eof()){
	
	num=load_values(array,line,i);

	i++;
	fin>>line;
}
return i;
}

int combined_array(Numbers q,char combined[][25],Values v){
int i,x,a;

	q.total=q.num_c_tv+q.num_fc+q.num_fd;
	
	for(i=0;i<q.num_c_tv;i++){
	x=0;
	
	while (v.load_tv[i][x] != '\0'){
		combined[i][x]=v.load_tv[i][x];
		x++;
	}	
	combined[i][x]='\0';	
	}
	////
	a=0;
	
	for(i=q.num_c_tv ; i < q.num_c_tv+q.num_fc ; i++){
	x=0;
	
	while (v.fic_chars[a][x]!='\0'){
		combined[i][x]=v.fic_chars[a][x];
		x++;
	}
	combined[i][x]='\0';
	a++;
	}
	
	a=0;
	////
	for(i=q.num_c_tv+q.num_fc ; i<q.total;i++){
	x=0;
	
	while (v.food_drink[a][x]!='\0'){
		combined[i][x]=v.food_drink[a][x];
		x++;
	}	
	combined[i][x]='\0';
	a++;
	}
	
	return q.total;
	
}

int generate_num(Numbers q){
int n;


n=0 + rand () % (q.total-0+1);

return n;
}

int generate_loc(){
int n;


n=1 + rand () % (6-1+1);

return n;
}

bool classic_tv_clue(Numbers q,Values v,int row){
int i,x=0;


for(i=0; i<q.num_c_tv;i++){

	while(v.combined[row][x] != '\0'){
	
	if(v.combined[row][x]==v.load_tv[i][x])
	return true;
	
	x++;
}

}

return false;
}

bool fic_char_clue(Numbers q,Values v,int row){
int i,x=0;


for(i=0; i<q.num_fc;i++){

	while(v.combined[row][x] != '\0'){
	
	if(v.combined[row][x]==v.fic_chars[i][x])
	return true;
	
	x++;
}
}

return false;
}

bool food_drink_clue(Numbers q,Values v,int row){
int i,x=0;

for(i=0; i<q.num_fd;i++){

	while(v.combined[row][x] != '\0'){
	
	if(v.combined[row][x]==v.food_drink[i][x])
	return true;
	
	x++;
}
}

return false;
}

void clues(Numbers q,Values v){
int i;
	
	for(i=1;i<=q.num_words;i++){


	if(fic_char_clue(q,v,q.random[i]))	
	cout<<"The clue for word "<<i<<" is : Fictional Characters"<<endl;
	else
	if(food_drink_clue( q,v,q.random[i]))
	cout<<"The clue for word "<<i<<" is : Food and Drink"<<endl;
	else
	if(classic_tv_clue(q,v,q.random[i]))
	cout<<"The clue for word "<<i<<" is : Classic TV"<<endl;

	}
	
cout<<endl;
}


int start_row(Numbers q){
int row;
	
if(q.num_words==1 ||q.num_words==2)
row=4;

if(q.num_words==3 ||q.num_words==4)
row=3;

if(q.num_words==5) 
row=2;

return row;
}

bool verrified(char c){
	
	if(c=='r'||c=='R'
	||c=='s'||c=='S'
	||c=='t'||c=='T'
	||c=='l'||c=='L'
	||c=='n'||c=='N'
	||c=='.'||c==' '
	||c=='-')
	return true;
	
	return false;
	
}

void setboard(char b[10][50],Numbers q,Values v,int start){

int row,col,i;

for( row = 0; row < 10; row++)
for ( col = 0; col < 50; col++)
b[row][col] = ' ';

for( row = 0; row < 10; row++)
for ( col = 0; col < 50; col++){

if(row==0 ||row==9||col==0||col==49||col==39)
b[row][col] = '*';}


for(i=1;i<=q.num_words;i++){

int c=0;
	
	while(v.combined[q.random[i]][c] != '\0')
	c++;
	
col= (39/2)-(c/2);

int x=0;

while(v.combined[q.random[i]][x] != '\0'){
	
	if(!verrified(v.combined[q.random[i]][x]))
	b[start][col]='*';
	else
	b[start][col]=v.combined[q.random[i]][x];
	col++;
	x++;
	
}
start++;
}
}

void head(char b[10][50]){
int row,col;

for(col=42;col<=48;col++){
	b[1][col]='-';
	b[4][col]='-';
}

for(row=1;row<=4;row++){
b[row][41]='|';
b[row][48]='|';}

b[2][43]='*';
b[2][46]='*';
b[3][44]='~';

}

void neck(char b[10][50]){
int col=44;
int row;

for(row=5;row<7;row++)
b[row][col]='|';

}

void leftarm(char b[10][50]){

b[5][41]='_';
b[5][42]='_';
b[5][43]='_';

}

void rightarm(char b[10][50]){
b[5][45]='_';
b[5][46]='_';
b[5][47]='_';
}

void leftfoot(char b[10][50]){

b[8][42]='(';
b[7][43]='(';

}

void rightfoot(char b[10][50]){

b[7][45]=')';
b[8][46]=')';

}

void draw_part(int i,char b[10][50])
{
	if (i==1)
	head(b);
	else
	if (i==2)
	neck(b);
	else
	if (i==3)
	leftarm(b);
	else
	if (i==4)
	rightarm(b);
	else
	if (i==5)
	leftfoot(b);
	else
	if (i==6)
	rightfoot(b);
	
}

void displayboard(char b[10][50],Numbers q,Values v){
int i;
	
	if(q.wrong==6)
	cout<<"GAME OVER!!"<<endl;
	
	cout<<"You solved "<<q.complete<<" of "<< q.num_words<<" words."<<endl;

	
	for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 50; col++)
            cout << b[row][col];
        cout << endl;
    }
 
if(q.wrong==6){
	head(b);
	neck(b);
	leftarm(b);
	rightarm(b);
	leftfoot(b);
	rightfoot(b);
} 
    
clues( q,v);

if(q.wrong==6 || q.complete==q.num_words){
	cout<<"The correct words are: "<<endl;
	
	for(i=1;i<=q.num_words;i++){


int x=0;

while(v.combined[q.random[i]][x] != '\0'){
	
	cout<<v.combined[q.random[i]][x];
	x++;
}
cout<<endl;
} 
cout<<endl;
}
}

bool upperCase (char c) {
 if (c >= 'A' && c <= 'Z')
 return true;
 
 return false;
} 

bool lowerCase (char c) {
if (c >= 'a' && c <= 'z')
return true;

return false;
}

char lowerToUpper(char ch) {
 if (lowerCase(ch))
 ch = ch - 32;
 return ch;
} 

char upperToLower(char ch ){
 if (upperCase(ch))
 ch = ch + 32;
 return ch;
}

int search_word(char b[][50],int start,Numbers q){
int col,count=0;

for(col=2;col<38;col++){
	
	if(b[start][col]=='*')
	count++;

}

return count;

}

int char_count(Numbers q,Values v,char choice){
int i,x,count=0;


for(i=1;i<=q.num_words;i++){
	
	 x=0;

while(v.combined[q.random[i]][x] != '\0'){
	
if(lowerToUpper(choice)==v.combined[q.random[i]][x] || 
upperToLower(choice)==v.combined[q.random[i]][x])
	count++;
	
	x++;
}
	
}
return count;
}

void char_locations(char b[10][50],Numbers q,Values v,int start,char choice){
int i,c=0,col;

for(i=1;i<=q.num_words;i++){
	
	int n=0;
	
	while(v.combined[q.random[i]][n] != '\0')
	n++;
	
col= (39/2)-(n/2);

int x=0;


while(v.combined[q.random[i]][x] != '\0'){
	
if(lowerToUpper(choice)==v.combined[q.random[i]][x])
b[start][col]=lowerToUpper(choice);
else
if(upperToLower(choice)==v.combined[q.random[i]][x])
b[start][col]=upperToLower(choice);
	

	col++;
	x++;
	
}

start++;
c++;
}
}

bool used(char array[],int n){
	
	if(array[n]==true)
	return true;
	
	return false;
}

bool usedNum(int array[],int n){
	
	if(array[n]==true)
	return true;
	
	return false;
}

void game(Numbers q,Values v){

	
srand ((time (0))); 

int x,i,n,unchanged,random[7],completed[7];
char b[10][50],choice[7],char_loc[20],bodypart[7];
bool found[8];


q.num_words= 1 + rand () % (5-1+1);

while(usedNum(random, q.num_words))
	q.num_words= 1 + rand () % (5-1+1);
	
	random[q.num_words]=true;

int start=start_row(q);

for(i=1;i<=q.num_words;i++){
	
	q.random[i]= generate_num( q);
	
	for(x=1;x<=i;x++){
		if(q.random[i]==q.random[x] )
		q.count++;
	}
	
	if(q.count>=1)//generates a new value if current value was previously used
	q.random[i]= generate_num( q);	

}

setboard(b,q,v,start);

displayboard(b,q,v);

i=0;

cout<<"Guess a letter:";
cin>>choice[i];
cout<<endl<<endl;

while(q.wrong<6 && q.complete<q.num_words){
	
	if(verrified(choice[i]))
	q.present[i]=0;
	else 
	q.present[i]=char_count( q,v,choice[i]); //finds a count of characters present
	
	for(x=0;x<i;x++){ //checks current char against prev chars
		if(choice[i]==lowerToUpper(choice[x]) || choice[i]==upperToLower(choice[x]) ) 
		q.present[i]=0;
	}		
	
	if(q.present[i]==0 ){ 
	cout<<"No "<<choice[i]<<"'s found... try again !!"<<endl;
	q.wrong++;
	
	n=generate_loc(); 
	
	while(used(bodypart, n)) //generates a new body part
	n=generate_loc();
	
	bodypart[n]=true;
	
	draw_part(n,b);
	
	}
	
	
	if(q.present[i]>0 ) {  //search for and highlight chars 
	cout<<"Great "<<q.present[i]<<" "<<choice[i]<<"'s found! Keep going !"<<endl;
	char_locations(b, q,v,start,choice[i]);
	}
	
	
	
	int row=start;
	
	for(x=1;x<=q.num_words;x++){
		
	if(completed[x]!=row){
	unchanged=search_word( b, row, q); //checks individual words for completion status
	
	if(unchanged==0){
	q.complete++;
	completed[x]=row;}	
}

	row++;
}

displayboard(b,q,v);
	i++;

if(q.wrong<6 && q.complete<q.num_words){
cout<<"Guess a letter:";
cin>>choice[i];
cout<<endl<<endl;}

}

}

int main(){
	
	char line[25],c;
	char file1[25]="classic_tv.txt",file2[25]="fictional_characters.txt",file3[25]="food_and_drink.txt";
	int x,i;
	
	Numbers q;
	Values v;
	
	q.num_c_tv=load_lines(v.load_tv,line,file1);
	q.num_fc=load_lines(v.fic_chars,line,file2);
	q.num_fd=load_lines(v.food_drink,line,file3);
	q.total=combined_array(q,v.combined,v);

	
game(q,v);

cout<<"Continue playing enter Y for Yes or N for No:";
cin>>c;
cout<<endl;

while(c=='Y' || c=='y'){

game(q,v);

cout<<"Continue playing enter Y for Yes or N for No:";
cin>>c;
cout<<endl;

}

cout<<endl;

cout<<"THANK YOU FOR PLAYING !!!"<<endl;
	return 0;
}
