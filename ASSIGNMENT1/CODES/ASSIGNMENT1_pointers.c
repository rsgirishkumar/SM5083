#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#define arr_size 2
int a[]={1,1}, b[]={3,5}, c[]={-2,4}, d[]={-1,-5};
int *va,*vb,*vc,*vd; 
int (*vertex_matrix)[arr_size+1];
int (*vertex_matrix)[arr_size+1];
int (*print_mat)[arr_size+1];
double area_triangle;
int rank_value;
double det(int *a,int *b, int *c)
{
    int *da,*db,*dc;
    da = (int *)malloc(arr_size*sizeof(int));
    da=0;
    da =realloc(da,arr_size*sizeof(int));
    da=a;

    db = (int *)malloc(arr_size*sizeof(int));
    db=0;
    db =realloc(db,arr_size*sizeof(int));
    db=b;

    dc = (int *)malloc(arr_size*sizeof(int));
    dc=0;
    dc =realloc(dc,arr_size*sizeof(int));
    dc=c;
    area_triangle = ((db[0]*dc[1])-(db[1]*dc[0]))-((da[0]*dc[1])-(da[1]*dc[0]))+((da[0]*db[1])-(da[1]*db[0]));
    printf("\n %.2f",area_triangle);
    return area_triangle;
}
void print_matrix()
{
    int i,j, matrix_size;
    matrix_size = sizeof(vertex_matrix)+1;
    //printf("\n%d",matrix_size);

    print_mat = (int *)malloc(matrix_size*sizeof(int)); 
    print_mat=0;
    print_mat = realloc(print_mat, matrix_size*sizeof(int));
    print_mat = vertex_matrix;
    for(i=0;i<3;i++)
    {
        printf("\n");    
        for(j=0;j<3;j++)
        {
            printf("\t%d", *(*(print_mat+i)+j));
        }
        
    }
}
int matrix_formation(int *a,int *b,int *c)
{
    int value[arr_size+1][arr_size+1],i,j;
    int matrix_size;
    int *ma,*mb,*mc;
    int non_zero_counter[2];
    double scaling_factor_row[2];
    double temp;
    ma = (int *)malloc(arr_size*sizeof(int));
    ma=0;
    ma =realloc(ma,arr_size*sizeof(int));
    ma=a;

    mb = (int *)malloc(arr_size*sizeof(int));
    mb=0;
    mb =realloc(mb,arr_size*sizeof(int));
    mb=b;

    mc = (int *)malloc(arr_size*sizeof(int));
    mc=0;
    mc =realloc(mc,arr_size*sizeof(int));
    mc=c;
    /*printf("\n");
    printf("\n");
    for(i=0;i<arr_size;i++){
    printf("\t%d", mb[i]);
    }
    value=(int *) malloc(3*arr_size*sizeof(int));
    value=0;
    value = realloc(value,3*arr_size*sizeof(int));*/
    for(i=0;i<arr_size+1;i++)
    {
        switch(i)
        {
            case 0://DIRECTION VECTOR B-A
                value[0][0]=mb[0]-ma[0];
                value[0][1]=mb[1]-ma[1];
                value[0][2]=1;
                break;
            case 1://DIRECTION VECTOR C-B
                value[1][0]=mc[0]-mb[0];
                value[1][1]=mc[1]-mb[1];
                value[1][2]=1;
                break;
            case 2://DIRECTION VECTOR A-C
                value[2][0]=ma[0]-mc[0];
                value[2][1]=ma[1]-mc[1];
                value[2][2]=1;
                break;
            default:
                printf("\n Null matrix");
        }
    }
    /*for(i=0;i<3;i++)
    {
        printf("\n");
        for(j=0;j<3;j++)
        {
            printf("%d\t",value[i][j]);
        }
    }*/
    vertex_matrix =(int *)malloc(sizeof(value));
    vertex_matrix = 0;
    vertex_matrix = realloc(vertex_matrix, sizeof(value));
    vertex_matrix = value;
    printf("\n Vertex matrix = ");
    print_matrix();
    scaling_factor_row[0] = *(*(vertex_matrix+1)+0)/ **vertex_matrix;
    scaling_factor_row[1] = *(*(vertex_matrix+2)+0)/ **vertex_matrix;
    i=2,j=0;
    while(i>0)
    {
        j=0;
        if((*(*(vertex_matrix+(i-i))+j))!=(*(*(vertex_matrix+i)+j)))
        {
            while(j<3)
            {
                temp = *(*(vertex_matrix+i)+j)-(*(scaling_factor_row+(i-1)) * *(*(vertex_matrix+(i-i)+j)));
                *(*(vertex_matrix+i)+j)=temp;
                j++;
            }
        }    
        else
        {
            while(j<3)
            {
                temp = *(*(vertex_matrix+i)+j)-*(*(vertex_matrix+(i-i)+j));
                *(*(vertex_matrix+i)+j)=temp;
                j++;
            }
        }
        i--;
    }
    printf("\n Reduced matrix = ");
    print_matrix();
    for(i=1;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(*(*(vertex_matrix+i)+j)!=0)
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
    return rank_value;
}    
bool collinearity_check(int *a, int *b, int *c)
{   
    int (*result_matrix)[3];
    bool collinearity_value;
    int *ca,*cb,*cc,i,j;
    ca = (int *)malloc(arr_size*sizeof(int));
    ca=0;
    ca =realloc(ca,arr_size*sizeof(int));
    ca=a;

    cb = (int *)malloc(arr_size*sizeof(int));
    cb=0;
    cb =realloc(cb,arr_size*sizeof(int));
    cb=b;

    cc = (int *)malloc(arr_size*sizeof(int));
    cc=0;
    cc =realloc(cc,arr_size*sizeof(int));
    cc=c;
    /*printf("\n");
    for(i=0;i<arr_size;i++){
    printf("\t%d", cb[i]);
    }*/
    rank_value = matrix_formation(ca,cb,cc);
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
    bool cval1,cval2;
    double area_1;
    double area_2;
    double area_quad;
    va = (int *)malloc(arr_size*sizeof(int));
    vb = (int *)malloc(arr_size*sizeof(int));
    vc = (int *)malloc(arr_size*sizeof(int));
    vd = (int *)malloc(arr_size*sizeof(int));
    int i=0;
    va=0;
    va = (int *)realloc(va,arr_size*sizeof(int));
    
    for(i=0;i<arr_size;i++)
    {
        *(va+i)=a[i];
    }
    for(i=0;i<arr_size;i++){
    printf("\t%d", va[i]);
    }
    vb=0;
    vb = (int *)realloc(vb,arr_size*sizeof(int));
    
    for(i=0;i<arr_size;i++)
    {
        *(vb+i)=b[i];
    }
    printf("\n");
    for(i=0;i<arr_size;i++){
    printf("\t%d", vb[i]);
    }
    vc=0;
    vc = (int *)realloc(vc,arr_size*sizeof(int));
   
    for(i=0;i<arr_size;i++)
    {
        *(vc+i)=c[i];
    }
    printf("\n");
    for(i=0;i<arr_size;i++){
    printf("\t%d", vc[i]);
    }
    vd=0;
    vd = (int *)realloc(vd,arr_size*sizeof(int));
    for(i=0;i<arr_size;i++)
    {
        *(vd+i)=d[i];
    }
    printf("\n");
    for(i=0;i<arr_size;i++){
    printf("\t%d", vd[i]);
    }
    cval1 = collinearity_check(va,vb,vc);
    cval2 = collinearity_check(va,vb,vd);
    if(cval1 || cval2 == true)
    {
        printf("\n Given coordinates are Collinear. Hence they do not form a Qualdrilateral.");
    }
    else
    {
        area_1 = 0.5 * det(va,vb,vc);
        printf("\n %.2f", area_1);
        area_2 = 0.5 * det(va,vc,vd);
        printf("\n %.2f", area_2);
        area_quad = area_1 + area_2;
        printf("\n Area of Quadrilateral formed by points A(%d,%d), B(%d,%d), C(%d,%d), D(%d,%d) = %.2f",*va,*(va+1),*vb,*(vb+1),vc[0],vc[1],vd[0],vd[1],area_quad);
    }
    return;
    //matrix_formation(va,vc,vd);
}