#include <stdio.h>
#include <math.h>

#define MAX_SIZE 20

typedef struct matrix {
    double array[MAX_SIZE][MAX_SIZE];
    int rows, columns;
} matrix;

matrix read_matrix(void);
void print_matrix(matrix mat);
int add_matrix(matrix *mat1, matrix *mat2, matrix *mat3);
int sub_matrix(matrix *mat1, matrix *mat2, matrix *mat3);
int mul_matrix(matrix *mat1, matrix *mat2, matrix *mat3);
matrix transpose_matrix(matrix mat);
double det_matrix(matrix *mat, int *check);
int inverse_matrix(matrix *mat, matrix *inv_mat);
int pow_matrix(matrix *mat, matrix *result, int n);
int finish(matrix *mat1, matrix *mat2, matrix *result);
void minor(matrix *mat1, matrix *mat2, int k, int l);

int main() {
    /* the first label is for getting back to the main menu when we have a matrix as result and the last label (at the last
    of main function) is for gettimg command when we doesn't have any matrix as result */
    int m, n, check, power, finish_check;
    double det;
    matrix mat1, mat2, result;
    puts("\n**((Welcome to the matrix caculator))**\n");
    printf("Please choose the operation:");

first:
    printf("\n\n1.Sum\n2.Subtract\n3.Multiply\n4.power\n5.Transpose\n6.Determinant\n7.Inverse\n\n0.Exit\n->");

    scanf("%d", &m);
    switch (m) {
    case 1:
        puts("Input first matrix:");
        mat1 = read_matrix();
        puts("Input second matrix:");
        mat2 = read_matrix();
        check = add_matrix(&mat1, &mat2, &result);
        if (check == 0) {
            puts("Size of given matrixes are incompatible!\n");
            goto last;
        }
        else {
            print_matrix(result);
            finish_check = finish(&mat1, &mat2, &result);
            if (finish_check == 0)
                return 0;
            else if (finish_check == 2)
                goto first;
        }
        break;

    case 2:
        puts("Input first matrix:");
        mat1 = read_matrix();
        puts("Input second matrix:");
        mat2 = read_matrix();
        check = sub_matrix(&mat1, &mat2, &result);
        if (check == 0) {
            puts("Size of given matrixes are incompatible!\n");
            goto last;
        }
        else {
            print_matrix(result);
            finish_check = finish(&mat1, &mat2, &result);
            if (finish_check == 0)
                return 0;
            else if (finish_check == 2)
                goto first;
        }
        break;

    case 3:
        puts("Input first matrix:");
        mat1 = read_matrix();
        puts("Input second matrix:");
        mat2 = read_matrix();
        check = mul_matrix(&mat1, &mat2, &result);
        if (check == 0) {
            puts("Size of given matrixes are incompatible!\n");
            goto last;
        }
        else {
            print_matrix(result);
            finish_check = finish(&mat1, &mat2, &result);
            if (finish_check == 0)
                return 0;
            else if (finish_check == 2)
                goto first;
        }
        break;

    case 4:
        puts("Input a square matrix:");
        mat1 = read_matrix();
        printf("Inter the power:");
        scanf("%d", &power);
        check = pow_matrix(&mat1, &result, power);
        if (check == 0) {
            puts("You should input a square matrix!\n");
            goto last;
        }
        else {
            print_matrix(result);
            finish_check = finish(&mat1, &mat2, &result);
            if (finish_check == 0)
                return 0;
            else if (finish_check == 2)
                goto first;
        }
        break;

    case 5:
        puts("Input the matrix:");
        mat1 = read_matrix();
        result = transpose_matrix(mat1);
        print_matrix(result);
        finish_check = finish(&mat1, &mat2, &result);
        if (finish_check == 0)
            return 0;
        else if (finish_check == 2)
            goto first;
        break;

    case 6:
        puts("Input a square matrix:");
        mat1 = read_matrix();
        check = 1;
        det = det_matrix(&mat1, &check);
        if (check == 0) {
            puts("You should input a square matrix!\n");
            goto last;
        }
        else {
            printf("\n%lf\n", det);
            goto last;
        }
        break;

    case 7:
        puts("Input a square matrix:");
        mat1 = read_matrix();
        check = inverse_matrix(&mat1, &result);
        if (check == 0) {
            puts("You should input a square matrix!\n");
            goto last;
        }
        else if (check == -1) {
            puts("The given matrix doesn't have inverse!\n");
            goto last;
        }
        else {
            print_matrix(result);
            finish_check = finish(&mat1, &mat2, &result);
            if (finish_check == 0)
                return 0;
            else if (finish_check == 2)
                goto first;
        }
        break;

    case 0:
        return 0;

    default:
        puts("Invalid input!\n");
        goto first;
    }

last:
    printf("1.Getting new matrixes\n\n0.Exit\n->");
    scanf("%d", &n);
    switch (n) {
    case 1:
        goto first;
    case 0:
        return 0;
    default:
        puts("Invalid input!\n");
        goto last;
    }
}

matrix read_matrix(void) {   
    int a , m , n;
    char c;
    matrix mat;
    FILE *stream;
    char name[100];
    first:
    printf("\n1.From keyboard\n2.From file\n->");
    scanf("%d" , &a);
    switch (a) {
    case 1:
        printf("Number of rows: ");
        scanf("%d", &m);

        printf("Number of columns: ");
        scanf("%d", &n);

        printf("matrix:\n");
        for (int i = 0; i < m ; i++)
            for (int j = 0; j < n ; j++)
                scanf("%lf", &mat.array[i][j]);
        break;

    case 2:
            printf("Input file name: ");
            scanf ("%s" , name);
            stream = fopen (name , "r");
            if (stream == NULL) {
                printf("There is no such a file in directory!\n");
                goto first;
            }
            fscanf(stream , "%d %c %d" , &m , &c , &n);
            for (int i = 0; i < m ; i++)
                for (int j = 0; j < n ; j++)
                    fscanf(stream , "%lf", &mat.array[i][j]);
            fclose(stream);
        break;

    default:
        puts("Invalid input!\n");
        goto first;
        break;
    }
   
    mat.rows = m;
    mat.columns = n;
    return mat;
}

void print_matrix(matrix mat) {   
    int a;
    FILE *stream;

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.columns; j++)
            if (fabs(mat.array[i][j]) < 1e-6)
                printf("%9.3lf ", fabs(mat.array[i][j])); /* avoiding from print -0.000 */
            else
                printf("%9.3lf ", mat.array[i][j]);
        putchar('\n');
    }

    first:
    printf("\nDo you wanna save the answer in a file?  (1.Yes / 0.No)\n->");
    scanf("%d" , &a);

    switch (a) {
    case 1:
        stream = fopen("Answer.txt" , "w");
        fprintf(stream , "%d*%d\n" , mat.rows , mat.columns);
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.columns; j++)
                if (fabs(mat.array[i][j]) < 1e-6)
                    fprintf(stream , "%9.3lf ", fabs(mat.array[i][j]));
                else
                    fprintf(stream , "%9.3lf ", mat.array[i][j]);
            fputc('\n' , stream);
        }
        fclose(stream);
        break;

    case 0:
        break;

    default:
        puts("Invalid input!\n");
        goto first;
        break;
    }
}

int add_matrix(matrix *mat1, matrix *mat2, matrix *mat3) {
    if ((mat1->rows != mat2->rows) || (mat1->columns != mat2->columns))
        return 0;

    mat3->rows = mat1->rows;
    mat3->columns = mat1->columns;

    for (int i = 0; i < mat3->rows; i++)
        for (int j = 0; j < mat3->columns; j++)
            mat3->array[i][j] = mat1->array[i][j] + mat2->array[i][j];

    return 1;
}

int sub_matrix(matrix *mat1, matrix *mat2, matrix *mat3) {
    if ((mat1->rows != mat2->rows) || (mat1->columns != mat2->columns))
        return 0;

    mat3->rows = mat1->rows;
    mat3->columns = mat1->columns;

    for (int i = 0; i < mat3->rows; i++)
        for (int j = 0; j < mat3->columns; j++)
            mat3->array[i][j] = mat1->array[i][j] - mat2->array[i][j];

    return 1;
}

int mul_matrix(matrix *mat1, matrix *mat2, matrix *mat3) {
    if (mat1->columns != mat2->rows)
        return 0;

    mat3->rows = mat1->rows;
    mat3->columns = mat2->columns;

    for (int i = 0; i < mat3->rows; i++)
        for (int j = 0; j < mat3->columns; j++) {
            mat3->array[i][j] = 0;
            for (int k = 0; k < mat1->columns; k++)
                mat3->array[i][j] += mat1->array[i][k] * mat2->array[k][j];
        }

    return 1;
}

matrix transpose_matrix(matrix mat) {
    matrix t_mat;

    t_mat.rows = mat.columns;
    t_mat.columns = mat.rows;

    for (int i = 0; i < mat.rows; i++)
        for (int j = 0; j < mat.columns; j++)
            t_mat.array[j][i] = mat.array[i][j];

    return t_mat;
}

void minor(matrix *mat1, matrix *mat2, int k, int l) {
    int p = 0;
    for (int i = 0; i < mat1->rows; i++) {
        int q = 0;
        for (int j = 0; j < mat1->columns; j++)
            if (i != k && j != l)
                mat2->array[p][q++] = mat1->array[i][j];
        if (q != 0)
            p++;
    }
    mat2->columns = mat1->columns - 1;
    mat2->rows = mat1->rows - 1;
}

double det_matrix(matrix *mat, int *check) {

    if (mat->rows != mat->columns) {
        *check = 0;
        return 0;
    }

    /* computing determinant of 1*1 matrix */
    if (mat->rows == 1)
        return (mat->array[0][0]);

    /* computing determinant of 2*2 matrix */
    if (mat->rows == 2)
        return ((mat->array[0][0] * mat->array[1][1]) - (mat->array[0][1] * mat->array[1][0]));

    /*computing determiniant of 3*3 or higher matrixes is based on laplace method*/
    matrix temp;
    double det = 0;
    int n = 1;
    double k;
    for (int i = 0; i < mat->rows; i++) {
        if (mat->array[i][0] != 0) {
            minor(mat, &temp, i, 0);
            k = n * mat->array[i][0] * det_matrix(&temp, NULL);
            n = -n;
            det += k;
        }
    }
    return det;
}

int inverse_matrix(matrix *mat, matrix *inv_mat) {
    if (mat->rows != mat->columns)
        return 0;

    double det = det_matrix(mat, NULL);

    /* if determinant of matrix is 0 it dosen't have inverse */
    if (fabs(det) < 1e-6)
        return -1;

    inv_mat->rows = mat->rows;
    inv_mat->columns = mat->columns;

    if (mat->rows == 1) {
        inv_mat->array[0][0] = 1 / mat->array[0][0];
        return 1;
    }

    /* here we find adjoint of inputed matrix */
    matrix adj_mat;
    adj_mat.columns = mat->columns;
    adj_mat.rows = mat->rows;

    matrix temp;
    double det_k;
    for (int i = 0; i < adj_mat.rows; i++)
        for (int j = 0; j < adj_mat.columns; j++) {
            minor(mat, &temp, i, j);
            det_k = det_matrix(&temp, NULL);
            adj_mat.array[j][i] = ((i + j) % 2 == 0 ? det_k : -det_k);
        }

    /* by dividing adjoint of matrix by determinant of matrix we can find inverse of matrix */

    for (int i = 0; i < inv_mat->rows; i++)
        for (int j = 0; j < inv_mat->columns; j++)
            inv_mat->array[i][j] = adj_mat.array[i][j] / det;

    return 1;
}

int pow_matrix(matrix *mat, matrix *result, int n) {
    if (mat->rows != mat->columns)
        return 0;

    matrix temp;
    *result = *mat;
    for (int i = 0; i < n - 1; i++) {
        temp = *result;
        mul_matrix(mat, &temp, result);
    }
    return 1;
}

int finish(matrix *mat1, matrix *mat2, matrix *result) {
    int n, m, check, power, finish_check;

first1:
    printf("\n1.Doing an operation on result\n2.Getting new matrixes\n\n0.Exit\n->");
    scanf("%d", &n);

    switch (n) {
    case 1:

    first2:
        printf("\n1.Sum\n2.Subtract\n3.Multiply\n4.power\n5.Transpose\n6.Determinant\n7.Inverse\n\n0.Exit\n->");
        scanf("%d", &m);

        switch (m) {
        case 1:
            *mat1 = *result;
            puts("Input second matrix:");
            *mat2 = read_matrix();
            check = add_matrix(mat1, mat2, result);
            if (check == 0) {
                puts("Size of given matrixes are incompatible!\n");
                goto last;
            }
            else {
                print_matrix(*result);
                goto first1;
            }
            break;

        case 2:
            *mat1 = *result;
            puts("Input second matrix:");
            *mat2 = read_matrix();
            check = sub_matrix(mat1, mat2, result);
            if (check == 0) {
                puts("Size of given matrixes are incompatible!\n");
                goto last;
            }
            else {
                print_matrix(*result);
                goto first1;
            }
            break;

        case 3:
            *mat1 = *result;
            puts("Input second matrix:");
            *mat2 = read_matrix();
            check = mul_matrix(mat1, mat2, result);
            if (check == 0) {
                puts("Size of given matrixes are incompatible!\n");
                goto last;
            }
            else {
                print_matrix(*result);
                goto first1;
            }
            break;

        case 4:
            *mat1 = *result;
            printf("Inter the power:");
            scanf("%d", &power);
            check = pow_matrix(mat1, result, power);
            if (check == 0) {
                puts("You should input a square matrix!\n");
                goto last;
            }
            else {
                print_matrix(*result);
                goto first1;
            }
            break;

        case 5:
            *mat1 = *result;
            *result = transpose_matrix(*mat1);
            print_matrix(*result);
            goto first1;
            break;

        case 6:
            *mat1 = *result;
            check = 1;
            double det = det_matrix(mat1, &check);
            if (check == 0) {
                puts("You should input a square matrix!\n");
                goto last;
            }
            else {
                printf("\n%lf\n", det);
                goto last;
            }
            break;

        case 7:
            *mat1 = *result;
            check = inverse_matrix(mat1, result);
            if (check == 0) {
                puts("You should input a square matrix!\n");
                goto last;
            }
            else if (check == -1) {
                puts("The given matrix doesn't have inverse!\n");
                goto last;
            }
            else {
                print_matrix(*result);
                goto first1;
            }
            break;

        case 0:
            return 0;

        default:
            puts("Invalid input!\n");
            goto first2;
        }
        return 1;

    case 2:
        return 2;

    case 0:
        return 0;

    default:
        puts("Invalid input!\n");
        goto first1;
    }

last:
    printf("1.Getting new matrixes\n\n0.Exit\n->");
    scanf("%d", &n);
    switch (n) {
    case 1:
        return 2;
    case 0:
        return 0;
    default:
        puts("Invalid input!\n");
        goto last;
        break;
    }
}
