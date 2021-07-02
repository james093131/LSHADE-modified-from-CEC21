/*
  L-SHADE implemented by C++ for Special Session & Competition on Real-Parameter Single Objective Optimization at CEC-2014
  See the details of L-SHADE in the following paper:

  * Ryoji Tanabe and Alex Fukunaga: Improving the Search Performance of SHADE Using Linear Population Size Reduction,  Proc. IEEE Congress on Evolutionary Computation (CEC-2014), Beijing, July, 2014.

  Version: 1.0   Date: 16/Apr/2014
  Written by Ryoji Tanabe (rt.ryoji.tanabe [at] gmail.com)
*/

#include "de.h"

// double *OShift,*M,*y,*z,*x_bound;
// int ini_flag=0,n_flag,func_flag,*SS;

int g_function_number;
int g_function_transform;
int g_problem_size;
unsigned int g_max_num_evaluations;

int g_pop_size;
double g_arc_rate;
int g_memory_size;
double g_p_best_rate;
void Run_Classify(double *Run_Result,int F,int F_T,int run,int DIM)
{
    fstream file; 
    string DIR = "./21_RUN_RESULT/";        
    string A = DIR+to_string(DIM)+"D/"+to_string(F)+"_"+to_string(F_T)+"_Run_Classify.txt";
    file.open(A,ios::out);
    file << scientific << setprecision(2);
    for(int i=0;i<run;i++)
    {
        file<<Run_Result[i]<<endl;

    }
}
int main(int argc, const char *argv[]) {

  int size = atoi(argv[1]);
  int Fun  = atoi(argv[2]);
  int Fun_T = atoi(argv[3]);
  //number of runs
  int num_runs = 51;
    //dimension size. please select from 10, 30, 50, 100
  g_problem_size = size;
  //available number of fitness evaluations
  if(g_problem_size == 10)
    g_max_num_evaluations =  200000;
  else if(g_problem_size == 20)
      g_max_num_evaluations =  1000000;

  //random seed is selected based on time according to competition rules
  srand((unsigned)time(NULL));

  //L-SHADE parameters
  g_pop_size = (int)round(g_problem_size * 18);
  g_memory_size = 6;
  g_arc_rate = 2.6;
  g_p_best_rate = 0.11;

 
  g_function_number = Fun;
  g_function_transform = Fun_T;
    // cout << "\n-------------------------------------------------------" << endl;
    // cout << "Function = " << g_function_number << ", Dimension size = " << g_problem_size << "\n" << endl;

    Fitness *bsf_fitness_array = (Fitness*)malloc(sizeof(Fitness) * num_runs);
    Fitness mean_bsf_fitness = 0;
    Fitness std_bsf_fitness = 0;

    for (int j = 0; j < num_runs; j++) {
      searchAlgorithm *alg = new LSHADE();
      bsf_fitness_array[j] = alg->run();
      // cout << j + 1 << "th run, " << "error value = " << bsf_fitness_array[j] << endl;
    }

    for (int j = 0; j < num_runs; j++) mean_bsf_fitness += bsf_fitness_array[j];
    mean_bsf_fitness /= num_runs;

    for (int j = 0; j < num_runs; j++) std_bsf_fitness += pow((mean_bsf_fitness - bsf_fitness_array[j]), 2.0);
    std_bsf_fitness /= num_runs;
    std_bsf_fitness = sqrt(std_bsf_fitness);

    // cout  << "\nmean = " << mean_bsf_fitness << ", std = " << std_bsf_fitness << endl;
    cout<<g_function_number<<' '<<g_function_transform<<' '<<mean_bsf_fitness<<' '<<std_bsf_fitness<<endl;
    Run_Classify( &bsf_fitness_array[0],g_function_number,g_function_transform,num_runs,g_problem_size);
   
    free(bsf_fitness_array);

  return 0;
}
