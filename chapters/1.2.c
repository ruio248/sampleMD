/* include */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* constants */
#define MAX_LATTICE_NUMBER 2000 //maximum number of lattices

/* classes */
struct LatticePoint
{
    int id;
    int reR[3];
    double r[3];
};

/* global variables */
struct LatticePoint latticePoints[MAX_LATTICE_NUMBER];
int latticePointNumber;
int latticeSizes[3][2];
double priTranVecs[3][3]; // primitive translation vectors

/* function declarations */
void ConstructReducedLattice();     
void ConstructLattice();


/* functions */
void ConstructReducedLattice()
{
    int n, i, j, k;
    n = 0;
    for (i = latticeSizes[0][0]; i < latticeSizes[0][1]; i++)
    {
        for (j = latticeSizes[1][0]; j < latticeSizes[1][1]; j++)
        {
            for (k = latticeSizes[2][0]; k < latticeSizes[2][1]; k++)
            {
                latticePoints[n].id = n;
                latticePoints[n].reR[0] = i;
                latticePoints[n].reR[1] = j;
                latticePoints[n].reR[2] = k;
                n++;
            }
        }
    }
    latticePointNumber = n;
}


void ConstructLattice()
{
    int n,d;
    for (n = 0; n < latticePointNumber; n++)
    {
        for (d = 0; d < 3; d++)
        {
            latticePoints[n].r[d] = latticePoints[n].reR[0] * priTranVecs[0][d] + latticePoints[n].reR[1] * priTranVecs[1][d] + latticePoints[n].reR[2] * priTranVecs[2][d];
        }
    }
}


/*main*/
int main()
{
    /*parameter*/
    latticeSizes[0][0] = 0;
    latticeSizes[0][1] = 3;
    latticeSizes[1][0] = 0;
    latticeSizes[1][1] = 3;
    latticeSizes[2][0] = 0;
    latticeSizes[2][1] = 3;

    priTranVecs[0][0]=1; priTranVecs[1][0]=0; priTranVecs[2][0]=0;
    priTranVecs[0][1]=0; priTranVecs[1][1]=1; priTranVecs[2][1]=0;
    priTranVecs[0][2]=0; priTranVecs[1][2]=0; priTranVecs[2][2]=1;


    /*processing*/
    ConstructReducedLattice();
    ConstructLattice();

    /*output*/
    int i;
    for (i = 0; i < latticePointNumber; i++)
    {
        printf("%f %f %f\n", latticePoints[i].r[0], latticePoints[i].r[1], latticePoints[i].r[2]);
    }

    return 0;
}
