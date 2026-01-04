#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
    float velocity;
    float angle;
    float timeOfFlight;
    float range;
    float maxHeight;
}Proj;
float degToRad (float degrees)
{
    return degrees * M_PI/180.0;
}
void inputData(Proj *arr, int n)
{
    for (int i=0; i<n; i++)
    {
        printf("Experiments %d:\n", i+1);
        printf("Enter the velocity(m/s):");
        scanf("%f", &(arr[i].velocity));
        printf("Enter the angle(deg):");
        scanf("%f", &(arr[i].angle));
        printf("Enter the time(s):");
        scanf("%f", &(arr[i].timeOfFlight));
    }
}
void computeResult(Proj *arr, int n)
{
    const float g = 9.8f;
    for(int i=0; i<n; i++)
    {
        float angleRad = degToRad(arr[i].angle);
        float v = arr[i].velocity;
        float sinAngle = sin(angleRad);
        float sin2Angle = sin(2 * angleRad);
        arr[i].maxHeight = (v*v*sinAngle*sinAngle)/(2*g);
        arr[i].range = (v*v*sin2Angle)/g;
    }
}
void displayData(const Proj *arr, int n)
{
    printf("\n%-10s %-10s %-12s %-12s %-12s\n", "Vel(m/s)", "Angle(deg)", "Time(s)", "Range(m)", "maxHeight(m)");
    printf("---------------------------------------------------------------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("%-10.2f %-10.2f %-12.2f %-12.2f %-12.2f\n", arr[i].velocity, arr[i].angle, arr[i].timeOfFlight, arr[i].range, arr[i].maxHeight);
    }
}
int findMaxRange(const Proj *arr, int n)
{
    int maxIndex = 0;
    for (int i=1; i<n; i++)
    {
        if (arr[i].range > arr[maxIndex].range)
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}
void compareMaxHeight(const Proj *a, const Proj *b)
{
    printf("Comparing max height of two experiments:");
    printf("Experiment 1 maxHeight is:%.2f", a->maxHeight);
    printf("Experiment 2 maxHeight is:%.2f", b->maxHeight);
    if (fabs(a->maxHeight - b->maxHeight) < 1e-6)
    {
        printf("Bothe experiments are having same height");
    }
    else 
    {
        printf("Both are different heights");
    }
}
int main()
{
    int n;
    printf("Enter the number of experiments:");
    scanf("%d", &n);
    Proj *experiments = (Proj *)malloc(n * sizeof(Proj));
    if (!experiments)
    {
        printf("Memory allocation failed");
        return 1;
    }
    inputData(experiments, n);
    computeResult(experiments, n);
    displayData(experiments, n);
    int maxIndex = findMaxRange(experiments, n);
    printf("Experiment %d has the maximum range of %.2f", maxIndex + 1, experiments[maxIndex].range);
    if (n >= 2)
    {
        Proj copyOfFirst = experiments[0];
        compareMaxHeight(&copyOfFirst, &experiments[1]);
    }
    free(experiments);
    return 0;
}