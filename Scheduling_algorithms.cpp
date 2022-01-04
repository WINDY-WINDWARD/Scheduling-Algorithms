#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

int first_come(int burst[],int arrive[],int proc[],int s1ze);
void result_printer(int proc1[],int arrive1[],int burst1[],int comptime[],int turn_around[],int waitTime[],int s1ze);
int sjf(int burst[],int arrive[],int proc[],int s1ze);
void menu();

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[],int arr2[],int arr3[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)
   {
       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
	   {   if (arr[j] > arr[j+1])
		   {swap(&arr[j], &arr[j+1]);
		    swap(&arr2[j], &arr2[j+1]);
        swap(&arr3[j], &arr3[j+1]);
		   }
		}
    }
}

float averageCalculator(int array[],int count)
{
  int temp=0;
  for (int i = 0; i < count; i++) {
    temp=temp+array[i];
    /* code */
  }
  float average=(float)temp/(float)count;
  return average;
}

void tat(int comptime[],int arrive[],int turn_around[],int count)
{//turnaround time Calculator
  for (int i = 0; i < count; i++) {
    turn_around[i]=comptime[i]-arrive[i];
  }
}

void waitin_time(int comptime[],int burst[],int waitTime[],int count) {
  for (int i = 0; i < count; i++) {
    int temp = comptime[i]-burst[i];
    if (temp > 0)
    {
      waitTime[i]= temp;
    }
    else
      waitTime[i] = 0; 
  }
}

void array_creator(int ar[],int s1ze)
{
  for (int i = 0; i < s1ze; i++) {
    cout<<"PROCESS "<< i+1<< ": ";
    cin >> ar[i];
    if (ar[i]==903633)
      menu();
  }
  system("cls");
}

//to get all the necessary
void input(int choice)
{
  cout << "enter the number of processes: \n";
  int s1ze=0;
  cin >> s1ze;
  int proc[100];
  for (int i=1;i<s1ze+1;i++){
    proc[i-1]=i;
  }
  cout << "enter the arrival times: \n";
  int arrive_time[100];
  array_creator(arrive_time,s1ze);
  cout << "enter burst times: \n";
  int burst_time[100];
  array_creator(burst_time,s1ze);
  if (choice==1)
  {
      first_come(burst_time,arrive_time,proc,s1ze);
}
else if (choice==2)
{
    sjf(burst_time,arrive_time,proc,s1ze);
}
}

//to find the smallest number
int smallest(int array[],int s1ze,int opt)
{
  int smalles=array[0];
  int i,loc=0;
  for(i=0;i<s1ze;i++)
  {
    if (smalles>array[i])
    {
        smalles=array[i];
        loc=i;
      }
  }
  if (opt == 0)
  {
    array[loc]=999;
  }
  return loc;
}
//new part 16:23 17/01/19{
	/*
int smallest1(int array[],int s1ze)
{
  int smalles=array[0];
  int i,loc=0;
  for(i=0;i<s1ze;i++)
  {
    if (smalles>array[i])
    {
        smalles=array[i];
        loc=i;
      }
  }
  return loc;
}
*/
//}
void copy_over(int array1[],int array2[],int s1ze)
{
  for (int i = 0; i < s1ze; i++) {
    array2[i]=array1[i];
    /* code */
  }
}


void make_all_zero(int array[],int s1ze){
  for (int i = 0; i < s1ze; i++) {
    array[i]=0;
  }
}

/*
void debugger_1(int array[],int s1ze){
  for (int i = 0; i < s1ze; i++) {
    cout<< array[i]<<endl;
  }
}
*/

int first_come(int burst[],int arrive[],int proc[],int s1ze)
{
  int temp[100];
  copy_over(arrive,temp,s1ze);
  //solution time
  int completion_time[100];
  make_all_zero(completion_time,s1ze);
  int temp1=0,temp2=0,temp3=0;
  //first run
  temp1=smallest(temp,s1ze,0);//getting the position of the array smallest element
  completion_time[temp1]=arrive[temp1]+burst[temp1];//calculating completion time
  //consecutive runs
  temp2=temp1;
  for(int i=0;i<(s1ze-2);i++){
    temp1=smallest(temp,s1ze,0);//getting the position of the array smallest element
    completion_time[temp1]=arrive[temp1]+burst[temp1];//calculating completion time
    if (arrive[temp1]<completion_time[temp2])
    {
      temp3=completion_time[temp2]-arrive[temp1];
      completion_time[temp1]=completion_time[temp1]+temp3;
    }
    temp2=temp1;//holding the previous temp value
  }
  //last run
  temp1=smallest(temp,s1ze,0);//getting the position of the array smallest element
  completion_time[temp1]=arrive[temp1]+burst[temp1];//calculating completion time
//all new start{
int turn_around[100];
int waitTime[100];
tat(completion_time,arrive,turn_around,s1ze);
waitin_time(turn_around,burst,waitTime,s1ze);
//}
result_printer(proc,arrive,burst,completion_time,turn_around,waitTime,s1ze);
}


//shortest job first programmmmm
int sjf(int burst[],int arrive[],int proc[],int s1ze)
{
  int temp_burst[100],completion_time[100];
  //sort the processess
  bubbleSort(arrive,burst,proc,s1ze);
  copy_over(burst,temp_burst,s1ze);
  int temp1=0,temp2=0,temp3=0;

  //first run
  temp1=smallest(arrive,s1ze,1);
  completion_time[temp1]=arrive[temp1]+burst[temp1];
  temp_burst[temp1]=999;
  temp2=temp1;

  for (int i = 0; i < (s1ze-2); i++) {
    //consecutive runs
    temp1=smallest(temp_burst,s1ze,0);
    completion_time[temp1]=arrive[temp1]+burst[temp1];
    if (arrive[temp1]<completion_time[temp2])
    {
      temp3=completion_time[temp2]-arrive[temp1];
      if (temp3 > 0)
        completion_time[temp1]=completion_time[temp1]+temp3;
      else
        completion_time[temp1]= completion_time[temp1] + 0;
    }
    temp2=temp1;
  }
  //last run
  temp1=smallest(temp_burst,s1ze,0);
  completion_time[temp1]=arrive[temp1]+burst[temp1];
  if (arrive[temp1]<completion_time[temp2])
  {
    temp3=completion_time[temp2]-arrive[temp1];
    if (temp3 > 0)
        completion_time[temp1]=completion_time[temp1]+temp3;
    else
        completion_time[temp1]= completion_time[temp1] + 0;
  }
  bubbleSort(proc,arrive,burst,s1ze);
  int turn_around[100];
  int waitTime[100];
  tat(completion_time,arrive,turn_around,s1ze);
  waitin_time(turn_around,burst,waitTime,s1ze);
  result_printer(proc,arrive,burst,completion_time,turn_around,waitTime,s1ze);
}

void menu()
{
  system("cls");
  system("color e");
  cout << "\t\t\t::::scheduling algorithms:::"<< endl;
  cout << "\t\t\t developed by WINDY_WINDWARD(GITHUB)" << endl;
  Sleep(3000);
  system("cls");
  cout << "::Availabel Options::";
  cout << "\n 1:FCFS (First Come First Serve)";
  cout << "\n 2:SJF (Shortest Job First)";
  cout << "\n::_____________________________::";
  int choice=0;
  cin >> choice;
  input(choice);
}

void result_printer(int proc1[],int arrive1[],int burst1[],int comptime[],int turn_around[],int waitTime[],int s1ze)
{
  cout << "| processes |" << "| arrival time |" << "| Burst time |"<< "| Completion Time |"<<"| Turn around |"<<"| waitTime |"<<endl;
  for (int i = 0; i < s1ze; i++)
  {
    cout << "  | "<< proc1[i] <<" |\t\t" << "| "<< arrive1[i] <<" |\t\t" << "| "<< burst1[i] <<" |\t\t"<< "| "<< comptime[i] <<" |\t\t"<<"| "<<turn_around[i]<<" |\t\t"<<"| "<<waitTime[i]<<" |\t\t"<<endl;
    /* code */
  }
  float avgwait=averageCalculator(waitTime,s1ze);
  float avgturn=averageCalculator(turn_around,s1ze);
  printf("average wait time: %f\n",avgwait);
  printf("average turnaround time: %f\n",avgturn);
  cout<<endl;
  cout<<"thank you for using\n press 1 for main menu\n press 0 to exit";
  int choice=0;
  cin >> choice;
  if (choice==1)
  {
    menu();
  }
  else
    exit(0);
}

int main()
{
  menu();
  return 0;
}
