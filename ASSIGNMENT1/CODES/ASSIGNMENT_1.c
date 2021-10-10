#include<stdio.h>
#include<math.h>
#include<stdbool.h>
bool collinearity_value;
double vertex_matrix[3][3];
double reduction_matrix[3][3];
int rank_value;
double area_triangle;
float a[2]={1,1};
float b[2]={3,5};
float c[2]={-2,4};
float d[2]={-1,-5};
double det(float a[2],float b[2], float c[2])
{
    area_triangle = ((b[0]*c[1])-(b[1]*c[0]))-((a[0]*c[1])-(a[1]*c[0]))+((a[0]*b[1])-(a[1]*b[0]));
    printf("\n %.2f",area_triangle);
    return area_triangle;
}
void print_matrix(double matrix[3][3])
{
    
    for(int i=0;i<3;i++)
    {
        printf("\n");    
        for(int j=0;j<3;j++)
        {
            printf("\t %.2f", matrix[i][j]);
        }
        
    }
}
void matrix_formation(float a[2],float b[2],float c[2])
{
    float value[3];
    for(int i=0;i<3;i++)
    {
        switch(i)
        {
            case 0://DIRECTION VECTOR B-A
                value[0]=b[0]-a[0];
                value[1]=b[1]-a[1];
                value[2]=1;
                break;
            case 1://DIRECTION VECTOR C-B
                value[0]=c[0]-b[0];
                value[1]=c[1]-b[1];
                value[2]=1;
                break;
            case 2://DIRECTION VECTOR A-C
                value[0]=a[0]-c[0];
                value[1]=a[1]-c[1];
                value[2]=1;
                break;
            default:
                printf("\n Null matrix");
        }
        
        for(int j=0;j<3;j++)
        {
            vertex_matrix[i][j]=value[j];
        }
        
    }
    printf("\n Vertex matrix = ");
    print_matrix(vertex_matrix);
}
void row_reduction(double rrmatrix[3][3])
{
    int i=0,j=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            reduction_matrix[i][j]=rrmatrix[i][j];
        }
    }
    double scaling_factor_row[2];
    double temp;
    scaling_factor_row[0] = reduction_matrix[1][0]/reduction_matrix[0][0];
    scaling_factor_row[1] = reduction_matrix[2][0]/reduction_matrix[0][0];
    i=2,j=0;
    while(i>0)
    {
        j=0;
        if(reduction_matrix[i-i][j]!=reduction_matrix[i][j])
        {
            while(j<3)
            {
                temp = reduction_matrix[i][j]-(scaling_factor_row[i-1]*reduction_matrix[i-i][j]);
                reduction_matrix[i][j]=temp;
                j++;    
            }
            
        }    
        else
        {
            while(j<3)
            {
                temp = reduction_matrix[i][j]-reduction_matrix[i-i][j];
                reduction_matrix[i][j]=temp;
                j++;
            }
        }
        i--;
    }
    printf("\n Reduction matrix = ");
    print_matrix(reduction_matrix);
    int non_zero_counter[2]={0,0};
    for(i=1;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(reduction_matrix[i][j]!=0)
            {
                non_zero_counter[i-1] = non_zero_counter[i-1]+1;
            }
            
        }
    }
    if(non_zero_counter[0]>=1)
    {
        if(non_zero_counter[1]>=1)
        {
            rank_value=3;
        }
        else
        {
            rank_value=2;
        }
    } 
    else
    {
        if(non_zero_counter[1]>=1)
        {
            rank_value=2;
        }
        else
        {
            rank_value=1;
        }
    }
    printf("\n Rank of the matrix = %d", rank_value);
    
}    
bool collinearity_check(float a[2],float b[2],float c[2])
{
    matrix_formation(a,b,c);
    row_reduction(vertex_matrix);
    if(rank_value == 1 || rank_value == 2)
    {
        collinearity_value = true;
    }
    else if(rank_value == 3)
    {
        collinearity_value = false;
    }
    return collinearity_value;
}
void main(void)
{
    
    double area_1;
    double area_2;
    double area_quad;
    bool collinear_value1=false;
    bool collinear_value2=false;
    
    //Collinearity Check
    collinear_value1 = collinearity_check(a,b,c);
    collinear_value2 = collinearity_check(a,b,d);
    //Area calculation
    if(collinear_value1 || collinear_value2 == true)
    {
        printf("\n Given coordinates are Collinear. Hence they do not form a Qualdrilateral.");
    }
    else
    {
        area_1 = 0.5 * det(a,b,c);
        printf("\n %.2f", area_1);
        area_2 = 0.5 * det(a,c,d);
        printf("\n %.2f", area_2);
        area_quad = area_1 + area_2;
        printf("\n Area of Quadrilateral formed by points A(%.2f,%.2f), B(%.2f,%.2f), C(%.2f,%.2f), D(%.2f,%.2f) = %.2f",a[0],a[1],b[0],b[1],c[0],c[1],d[0],d[1],area_quad);
    }
//return;
}