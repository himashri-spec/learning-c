#include<stdio.h>
#include<stdlib.h>
float computeAverage (float *scores, int numSubjects)
{
    float sum = 0;
    for (int i=0; i<numSubjects; i++)
    {
        sum += *(scores + i);
    }
    return (numSubjects>0) ? (sum/numSubjects):0;
}
int main ()
{
    int n; 
    printf("Enter the number of students:");
    scanf("%d", &n);
    int *subjects = (int *)malloc(n * sizeof(int));
    float **scores = (float **)malloc(n * sizeof(float*));
    for (int i=0; i<n; i++)
    {
        printf("Enter the number of subjects for student %d:\n", i+1);
        scanf("%d", &subjects[i]);
        scores[i] = (float*)malloc(subjects[i] * sizeof(float));
        for (int j=0; j<subjects[i]; j++)
        {
            printf("Enter the scores for subject %d:\n", j+1);
            scanf("%f", &scores[i][j]);
        }
    }
    for (int i=0; i<n; i++)
    {
        float avg = computeAverage (scores[i], subjects[i]);
        printf("Average for student %d:%.2f\n", i+1, avg);
    }
    float highest = -1e9;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<subjects[i]; j++)
        {
            if (scores[i][j]>highest)
            {
                highest = scores[i][j];
            }
        }
    }
    printf("Overall highest score among all student is:%.2f\n", highest);
    for(int i=0; i<n; i++)
    {
        free(scores[i]);
    }
    free(scores);
    free(subjects);
    return 0;
}