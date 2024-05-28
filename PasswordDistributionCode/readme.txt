The source code contains all experiments presented in [SP:BloLiu23] Towards a Rigorous Statistical Analysis of
Empirical Password Datasets and some experiments used in the PIN project, except the LP experiments.
The source code of LP experiments is in the folder LinearProgrammingCode.

This source code was updated in the past four years with tons of password experiments. Not all functions are still in use and not all experiments are presented in the paper. For example, functions in myhelper.h is not used anymore.

Check the comments in the main() function. It contains almost all experiments I ran for Password/PIN projects with this source code.

Check the format of input/output data before running the code. Some similar/duplicate functions are designed to handle different input/output data formats. It's all because  this code was used for different experiments in the past four years so it got messy.

To start with:
Line 427-456 in main.cpp contains experiments used to genrate Figure 1 in [SP:BloBliu23] (i.e., FrequencyUB, SamplingLB, ExtendedLB)
- FrequencyUB: countmostfrequentpasswords() 
- SamplingLB: 
     - recoversamples_shuffled(): we need to first shuffle the input data before generating the lower bound. This step can takes some time. By saving the output shuffled files of this function, we can run the samplingLB function with different parameters without waiting for regerating the shuffled files.
     - experiment_newlowerbound() for yahoo rockyou datsets; experiment_newlowerbound2() for datasets from IEEE S&P 19 paper such as 000webhost, neopets.
-ExtendedLB: experiment_plotguessingcurves2()
-LPLB, LPUB: see main() function in LinearProgrammingCode.


