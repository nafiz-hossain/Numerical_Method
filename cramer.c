#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    double **elems;
} SquareMatrix;

SquareMatrix init_square_matrix(int n, double elems[n][n]) {
    SquareMatrix A = {
        .n = n,
        .elems = malloc(n * sizeof(double *))
    };
    for(int i = 0; i < n; ++i) {
        A.elems[i] = malloc(n * sizeof(double));
        for(int j = 0; j < n; ++j)
            A.elems[i][j] = elems[i][j];
    }

    return A;
}

SquareMatrix copy_square_matrix(SquareMatrix src) {
    SquareMatrix dest;
    dest.n = src.n;
    dest.elems = malloc(dest.n * sizeof(double *));
    for(int i = 0; i < dest.n; ++i) {
        dest.elems[i] = malloc(dest.n * sizeof(double));
        for(int j = 0; j < dest.n; ++j)
            dest.elems[i][j] = src.elems[i][j];
    }

    return dest;
}

double det(SquareMatrix A) {
    double det = 1;

    for(int j = 0; j < A.n; ++j) {
        int i_max = j;
        for(int i = j; i < A.n; ++i)
            if(A.elems[i][j] > A.elems[i_max][j])
                i_max = i;

        if(i_max != j) {
            for(int k = 0; k < A.n; ++k) {
                double tmp = A.elems[i_max][k];
                A.elems[i_max][k] = A.elems[j][k];
                A.elems[j][k]     = tmp;
            }

            det *= -1;
        }

        if(abs(A.elems[j][j]) < 1e-12) {
            puts("Singular matrix!");
            return NAN;
        }

        for(int i = j + 1; i < A.n; ++i) {
            double mult = -A.elems[i][j] / A.elems[j][j];
            for(int k = 0; k < A.n; ++k)
                A.elems[i][k] += mult * A.elems[j][k];
        }
    }

    for(int i = 0; i < A.n; ++i)
        det *= A.elems[i][i];

    return det;
}

void deinit_square_matrix(SquareMatrix A) {
    for(int i = 0; i < A.n; ++i)
        free(A.elems[i]);
    free(A.elems);
}

double cramer_solve(SquareMatrix A, double det_A, double *b, int var) {
    SquareMatrix tmp = copy_square_matrix(A);
    for(int i = 0; i < tmp.n; ++i)
        tmp.elems[i][var] = b[i];

    double det_tmp = det(tmp);
    deinit_square_matrix(tmp);

    return det_tmp / det_A;
}

int main(int argc, char **argv) {
FILE *inFile, *outFile;
    char name[100];

    inFile = fopen("input.txt","r");
    outFile = fopen("output.txt","w");

    //inFile.open("input.txt");


    double element[25][25];


    double b[25];
    int j=0,k=0;
    int num=0;

    fprintf(outFile,"Given equations:\n");

    while(fgets(name, sizeof(name), inFile))
    {

        fprintf(outFile,"%s\n",name);
        char ptr[100];
        strcpy (ptr, name);

        char x;
        char ch,ch2,ch3,ch4;
        char buff[32];
        double  valArray[32],val;
        int   len = 0;
        int f=0,main_i;
        num = 0;

        memset(buff, 0, 32);
        for (main_i=0; ptr[main_i]!='\0'; main_i++)
        {
            ch=ptr[main_i];

            ch2=ptr[main_i+1];
            ch3 = ptr[main_i-1];
            ch4 = ptr[main_i+2];

            if(!((ch4>='A'&&ch4<='Z')||(ch4>='a'&&ch4<='z' ))&&f>0 && ((ch=='-'  && ch2==' ' && ch3 == ' ')||(ch=='+'  && ch2==' ' && ch3 == ' ')))
            {
                buff[len++] =ch;
                main_i++;

            }



            else if(f>0 && isdigit(ch)  && ((ch3>='A'&&ch3<='Z')||(ch3>='a'&&ch3<='z' )))
            {
                main_i++;

            }


            else if((ch>='A'&&ch<='Z'&& isdigit(ch2))||(ch>='a'&&ch<='z'&& isdigit(ch2))&& f!=0)
            {
                //printf("2nd if ch= %c ch2= %c\n",ch,ch2);
                main_i++;
            }


            else if ((isdigit(ch) && ch != '\0') ||(ch=='-' && isdigit(ch2))||(ch=='+' && isdigit(ch2)))
            {
                buff[len++] =ch;

            }

            else
            {


                if(f==0 && ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
                {
                    valArray[num++] = 1;

                }

                if(ch=='+')
                {

                    if(!isdigit(ch2))
                    {
                        valArray[num++] = 1;
                    }
                }


                if(ch=='-')
                {
                    if(!isdigit(ch2))
                    {
                        valArray[num++] = -1;
                    }
                }

                if (len != 0)
                {
                    val = atoi(buff);
                    valArray[num++] = val;
                    memset(buff, 0, 32);
                    len = 0;
                }
            }

            f++;
        }
        val = atoi(buff);
        valArray[num++] = val;

        for(int i=0; i<num-1; i++)
        {

            if (i==num-2)
                b[j]=valArray[i];
            else
                element[j][i]= valArray[i];

        }

        j++;

        //inFile.close();
    }


    fprintf(outFile,"Generated Matrix:\n");
    for(int i=0; i<num-2; i++)
    {

        for(j=0; j<num-2; j++)
        {
            fprintf(outFile,"%lf   ",element[i][j]);
        }
        puts(" ");
    }

    fprintf(outFile,"\n\nConstant vector:\n");
    for(j=0; j<num-2; j++)
        {
            fprintf(outFile,"%f ",b[j]);
        }


    int N=num-2;
    double elems[N][N];

    int p,q;

    for(p=0;p<N;p++){
        for(q=0;q<N;q++){
            elems[p][q]=element[p][q];
        }
    }
    fprintf(outFile,"\n\nSolution:\n");

    SquareMatrix A = init_square_matrix(N, elems);

    SquareMatrix tmp = copy_square_matrix(A);
    int det_A = det(tmp);
    deinit_square_matrix(tmp);


    for(int i = 0; i < N; ++i)
        fprintf(outFile,"%7.3lf\n", cramer_solve(A, det_A, b, i));

    deinit_square_matrix(A);
    return EXIT_SUCCESS;
}
