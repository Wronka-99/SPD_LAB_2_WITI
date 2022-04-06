#include <iostream>
#include <fstream>
#include <algorithm>


typedef struct task
{
    int W;
    int D;
    int P;
}Task;


int main()
{
    int N, c;
    int N_penalty;

    std::ifstream data("data.txt");
    std::string tmp;
  
    while(tmp!="data.10:")
        data>>tmp;

    data>>N;
    N_penalty= 1<<N;

//    std::cout<<"Wartosc N to"<<N<<"N_penalty"<<N_penalty<<std::endl;

    Task task_array[N]; 
    int *penalty_array= new int[N_penalty];

    std::fill_n(penalty_array, N_penalty, 1000000);

    for(int i=0; i<N; i++)
        data>>task_array[i].P>>task_array[i].W>>task_array[i].D;
    data.close();

    penalty_array[0]=0;

    for(int i=1; i<N_penalty; i++)
    {
        c=0;

        for(int a=0; a<N; a++)
            if(((i>>a)&1)==1)
                c+=task_array[a].P;


        for(int a=0; a<N; a++)
            if((i>>a)&1)
                penalty_array[i]=std::min(penalty_array[i], penalty_array[i-(1<<a)]+task_array[a].W*std::max(c-task_array[a].D,0));        

    }

    std::cout<<"Rozwiazanie za pomoca algorytmu WiTi: "<< penalty_array[N_penalty-1]<<std::endl;

    delete [] penalty_array;

    return 0;
}