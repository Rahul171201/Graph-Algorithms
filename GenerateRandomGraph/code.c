#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void generateRandomGraph(int n, double p, int w, char *file_name)
{
    int adjacencyMatrix[n + 1][n + 1];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i==j){
                adjacencyMatrix[i][j] = -1;
                adjacencyMatrix[j][i] = -1;
                continue;
            }
            double c_outcomes = p * 100.00;
            int correct_outcomes = c_outcomes;
            int total_outcomes = 100;
            int outcome = (rand() % (100 - 1 + 1)) + 1;
            if(outcome>=1 && outcome<=correct_outcomes){
                int weight = (rand() % (w - 1 + 1)) + 1;
                adjacencyMatrix[i][j] = weight;
                adjacencyMatrix[j][i] = weight;
            }
            else{
                adjacencyMatrix[i][j] = -1;
                adjacencyMatrix[j][i] = -1;
            }
        }
    }

    FILE *fp;
    fp = fopen(file_name, "w");

    if(fp == NULL) {
        printf("file can't be opened\n");
        exit(1);
    }

    fprintf(fp, "%d\n%f\n%d\n", n, p, w);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(adjacencyMatrix[i][j]!=-1){
                fprintf(fp, "%d %d %d\n", i, j, adjacencyMatrix[i][j]);
            }
        }
    }

    fclose(fp);
}

int main(int argc, char **argv)
{
    // printf("You have entered : %d arguments:\n",  argc);

    // for (int i = 0; i < argc; ++i)
    //     printf("%s\n", argv[i]);

    srand(time(0));

    int n = atoi(argv[1]);
    double p = atof(argv[2]);
    int maximum_weight = atoi(argv[3]);
    char *file_name = argv[4];

    generateRandomGraph(n, p, maximum_weight, file_name);

    // printf("%d %d %d %s",n,p,maximum_weight,file_name);

    return 0;
}