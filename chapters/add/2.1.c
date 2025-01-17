/* classes */
struct Atom
{
    int id, type;
    double r[3];
    double reR[3];
    double boxReR[3];
};

/* global variables */
double boxStartPoint[3];
double boxTranVecs[3][3]; // box translation vectors
double boxRecTranVecs[3][3]; //box reciprocal translation vectors

/* function declarations */
void ComputeAtomBoxReR(int n);

/* functions */
void ComputeAtomBoxReR(int n)
{
    int d;
    for (d = 0; d < 3; d++)
    {
        atoms[n].boxReR[d] = boxRecTranVecs[d][0] * (atoms[n].r[0] - boxStartPoint[0]) +
                             boxRecTranVecs[d][1] * (atoms[n].r[1] - boxStartPoint[1]) +
                             boxRecTranVecs[d][2] * (atoms[n].r[2] - boxStartPoint[2]);
        if (atoms[n].boxReR[d] < -1 || atoms[n].boxReR[d] >= 2)
        {
            printf("Lost atom %d!\n", atoms[n].id);
            exit(1);
        }
    }
}

/* main */
int main()
{
    int n, d;
    /* parameters */
    double latticeConstant = 3.14; // unit: angstrom
    latticeSizes[0][0] = 0;
    latticeSizes[0][1] = 4;
    latticeSizes[1][0] = 0;
    latticeSizes[1][1] = 4;
    latticeSizes[2][0] = 0;
    latticeSizes[2][1] = 4;

    priTranVecs[0][0] = 0.5 * latticeConstant;
    priTranVecs[0][1] = 0.5 * latticeConstant;
    priTranVecs[0][2] = -0.5 * latticeConstant;
    priTranVecs[1][0] = 0.5 * latticeConstant;
    priTranVecs[1][1] = -0.5 * latticeConstant;
    priTranVecs[1][2] = 0.5 * latticeConstant;
    priTranVecs[2][0] = -0.5 * latticeConstant;
    priTranVecs[2][1] = 0.5 * latticeConstant;
    priTranVecs[2][2] = 0.5 * latticeConstant;

    cellAtomNumber = 1;
    cellAtomRs[0][0] = 0;
    cellAtomRs[0][1] = 0;
    cellAtomRs[0][2] = 0;
    cellAtomTypes[0] = 1;

    boxStartPoint[0] = 0;
    boxStartPoint[1] = 0;
    boxStartPoint[2] = 0;

    boxTranVecs[0][0] = 0.5 * latticeConstant * 4;
    boxTranVecs[0][1] = 0.5 * latticeConstant * 4;
    boxTranVecs[0][2] = -0.5 * latticeConstant * 4;
    boxTranVecs[1][0] = 0.5 * latticeConstant * 4;
    boxTranVecs[1][1] = -0.5 * latticeConstant * 4;
    boxTranVecs[1][2] = 0.5 * latticeConstant * 4;
    boxTranVecs[2][0] = -0.5 * latticeConstant * 4;
    boxTranVecs[2][1] = 0.5 * latticeConstant * 4;
    boxTranVecs[2][2] = 0.5 * latticeConstant * 4;

    /* processing */
    ComputeRecTranVecs(boxTranVecs, boxRecTranVecs);
    ConstructReducedLattice();
    ConstructLattice();
    ConstructCrystal();
    for (n = 0; n < atomNumber; n++)
    {
        ComputeAtomBoxReR(n);
    }

    /* output */
    printf("             rex              rey              rez\n");
    for (n = 0; n < atomNumber; n++)
    {
        for (d = 0; d < 3; d++)
        {
            printf("%16.6f ", atoms[n].boxReR[d]);
        }
        printf("\n");
    }

    return 0;
}

/* output
0.000000 0.000000 0.000000 
0.000000 0.000000 0.250000 
0.000000 0.000000 0.500000 
0.000000 0.000000 0.750000 
0.000000 0.250000 0.000000 
0.000000 0.250000 0.250000 
0.000000 0.250000 0.500000 
0.000000 0.250000 0.750000 
0.000000 0.500000 0.000000 
0.000000 0.500000 0.250000 
0.000000 0.500000 0.500000 
0.000000 0.500000 0.750000 
0.000000 0.750000 0.000000 
0.000000 0.750000 0.250000 
0.000000 0.750000 0.500000 
0.000000 0.750000 0.750000 
0.250000 0.000000 0.000000 
0.250000 0.000000 0.250000 
0.250000 0.000000 0.500000 
0.250000 0.000000 0.750000 
0.250000 0.250000 0.000000 
0.250000 0.250000 0.250000 
0.250000 0.250000 0.500000 
0.250000 0.250000 0.750000 
0.250000 0.500000 0.000000 
0.250000 0.500000 0.250000 
0.250000 0.500000 0.500000 
0.250000 0.500000 0.750000 
0.250000 0.750000 0.000000 
0.250000 0.750000 0.250000 
0.250000 0.750000 0.500000 
0.250000 0.750000 0.750000 
0.500000 0.000000 0.000000 
0.500000 0.000000 0.250000 
0.500000 0.000000 0.500000 
0.500000 0.000000 0.750000 
0.500000 0.250000 0.000000 
0.500000 0.250000 0.250000 
0.500000 0.250000 0.500000 
0.500000 0.250000 0.750000 
0.500000 0.500000 0.000000 
0.500000 0.500000 0.250000 
0.500000 0.500000 0.500000 
0.500000 0.500000 0.750000 
0.500000 0.750000 0.000000 
0.500000 0.750000 0.250000 
0.500000 0.750000 0.500000 
0.500000 0.750000 0.750000 
0.750000 0.000000 0.000000 
0.750000 0.000000 0.250000 
0.750000 0.000000 0.500000 
0.750000 0.000000 0.750000 
0.750000 0.250000 0.000000 
0.750000 0.250000 0.250000 
0.750000 0.250000 0.500000 
0.750000 0.250000 0.750000 
0.750000 0.500000 0.000000 
0.750000 0.500000 0.250000 
0.750000 0.500000 0.500000 
0.750000 0.500000 0.750000 
0.750000 0.750000 0.000000 
0.750000 0.750000 0.250000 
0.750000 0.750000 0.500000 
0.750000 0.750000 0.750000 
*/