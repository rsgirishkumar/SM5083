//Question: The opposite vertices of a sqaure are (0,-1), (0,3). Find the equations of four sides.
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#define arr_size 2
#define angle 0.7853981634
double a[]={0,-1}, c[]={0,3};
double *va,*vb,*vc,*vd;
void print_vertex(double *a)
{
    double *pa;
    pa = (double *)malloc(arr_size*sizeof(double));
    pa = 0;
    pa = realloc(pa, arr_size*sizeof(double));
    pa = a;
    printf("\n[ %.2f , %.2f ]",pa[0],pa[1]);
    //free(pa);
}
double* affine_translation(double *a, double *tf)
{
    double *temp_a,*trns_a, *trans_fact;
    temp_a = (double *) malloc(arr_size*sizeof(double));
    temp_a = 0;
    temp_a = realloc(temp_a, arr_size*sizeof(double));
    temp_a = a;
    trans_fact = (double *) malloc(arr_size*sizeof(double));
    trans_fact = 0;
    trans_fact = realloc(trans_fact, arr_size*sizeof(double));
    trans_fact = tf;
    //Translating to Origin
    trns_a = (double *) malloc(arr_size*sizeof(double));
    trns_a = 0;
    trns_a = realloc(trns_a, arr_size*sizeof(double));
    
    *trns_a = *temp_a-*trans_fact;
    *(trns_a+1) = *(temp_a+1)-*(trans_fact+1);
    //free(temp_a);
    //free(trans_fact);
    return trns_a;
}
double* line_gen_coeff(double *a, double *c)
{
    double *coeff, *la, *lc;
    //Line in Quadratic form ax+by+c=0;
    la = (double *)malloc(arr_size*sizeof(double));
    la = 0;
    la = realloc(la,arr_size*sizeof(double));
    la = a;

    lc = (double *)malloc(arr_size*sizeof(double));
    lc = 0;
    lc = realloc(lc,arr_size*sizeof(double));
    lc = c;
    
    coeff = (double *)malloc((arr_size+1)*sizeof(double));
    coeff = 0;
    coeff = realloc(coeff,(arr_size+1)*sizeof(double));
    
    coeff[0] = la[1]-lc[1];
    coeff[1] = lc[0]-lc[0];
    coeff[2] = (la[0]*lc[1])-(la[1]*lc[0]);

    //free(la);
    //free(lc);
    return coeff;
}
double rot_fact_calc(double *a, double *c)
{
    double *line_coeff1, *line_coeff2, angle_with_x_axis;
    double *ra, *rc;
    ra = (double *)malloc(arr_size*sizeof(double));
    ra = 0;
    ra = realloc(ra,arr_size*sizeof(double));
    ra = a;

    rc = (double *)malloc(arr_size*sizeof(double));
    rc = 0;
    rc = realloc(rc,arr_size*sizeof(double));
    rc = c;
    
    /*line_coeff1 = (double *)malloc((arr_size+1)*sizeof(double));
    line_coeff1 =0;
    line_coeff1 =realloc(rc,(arr_size+1)*sizeof(double));
    
    line_coeff1 = line_coeff_gen(ra,rc);

    line_coeff2 = (double *)malloc((arr_size+1)*sizeof(double));
    line_coeff2 =0;
    line_coeff2 =realloc(rc,(arr_size+1)*sizeof(double));
    
    line_coeff2 = {0,1,0};*/

    angle_with_x_axis = atan((rc[1]-ra[1])/(rc[0]-ra[0]));
    //free(ra);
   //free(rc);
    return angle_with_x_axis;
}
double norm(double *a, double *c)
{
    double *na, *nc, norm_ac;

    na = (double *)malloc(arr_size*sizeof(double));
    na = 0;
    na = realloc(na,arr_size*sizeof(double));
    na = a;

    nc = (double *)malloc(arr_size*sizeof(double));
    nc = 0;
    nc = realloc(nc,arr_size*sizeof(double));
    nc = c;

    norm_ac = sqrt(pow(na[0]-nc[0],2)+pow(na[1]-nc[1],2));
    //free(na);
    //free(nc);
    return norm_ac;
}
double* affine_rotation(double *a, double rot_fact)
{
    double *ar_a, *temp_a, (*rotan_fact_matrix)[2];
    ar_a = (double*)malloc(arr_size*sizeof(double));
    ar_a = 0;
    ar_a = realloc(ar_a, arr_size*sizeof(double));
    ar_a = a;

    rotan_fact_matrix = (double *)malloc(arr_size*arr_size*sizeof(double));
    **rotan_fact_matrix = cos(rot_fact);
    *(*(rotan_fact_matrix)+1) = sin(rot_fact);
    *(*(rotan_fact_matrix+1)) = -sin(rot_fact);
    *(*(rotan_fact_matrix+1)+1) = cos(rot_fact);

    temp_a = (double*)malloc(arr_size*sizeof(double));
    temp_a = 0;
    temp_a = realloc(temp_a, arr_size*sizeof(double));
    temp_a[0] = **rotan_fact_matrix * ar_a[0] + *(*(rotan_fact_matrix)+1) * ar_a[1];
    temp_a[1] = *(*(rotan_fact_matrix+1)) * ar_a[0] + *(*(rotan_fact_matrix+1)+1) * ar_a[1];
    free(ar_a);
    ar_a = (double*)malloc(arr_size*sizeof(double));
    ar_a = 0;
    ar_a = realloc(ar_a, arr_size*sizeof(double));
    ar_a = temp_a;
    //free(temp_a);
    //free(rotan_fact_matrix);
    return ar_a;
}
double* rev_affine(double *a, double *trns_fact, double rot_fact)
{
    double *aa,*ab,*ac;
    double *aff_a,*aff_b,*aff_c;
    double *trans_fact;
    double rotn_fact;

    aa = (double *)malloc(arr_size*sizeof(double));
    aa = 0;
    aa = realloc(aa,arr_size*sizeof(double));
    aa = a;

    trans_fact = (double *)malloc(arr_size*sizeof(double));
    trans_fact = 0;
    trans_fact = realloc(trans_fact,arr_size*sizeof(double));
    trans_fact[0] = trns_fact[0];
    trans_fact[1] = trns_fact[1];

    rotn_fact = rot_fact;

    aff_a = (double *)malloc(arr_size*sizeof(double));
    aff_a = 0;
    aff_a = realloc(aff_a,arr_size*sizeof(double));

    aff_a = affine_rotation(aa, rotn_fact);
    aff_b = affine_translation(aff_a, trans_fact);

    free(aff_a);

    aff_a = (double *)malloc(arr_size*sizeof(double));
    aff_a = 0;
    aff_a = realloc(aff_a,arr_size*sizeof(double));
    aff_a = aff_b;
    
    return aff_a;
}

double* affine(double *a, double *trns_fact, double rot_fact)
{
    double *aa,*ab,*ac;
    double *aff_a,*aff_b,*aff_c;
    double *trans_fact;
    double rotn_fact;

    aa = (double *)malloc(arr_size*sizeof(double));
    aa = 0;
    aa = realloc(aa,arr_size*sizeof(double));
    aa = a;

    trans_fact = (double *)malloc(arr_size*sizeof(double));
    trans_fact = 0;
    trans_fact = realloc(trans_fact,arr_size*sizeof(double));
    trans_fact[0] = trns_fact[0];
    trans_fact[1] = trns_fact[1];

    rotn_fact = rot_fact;

    aff_a = (double *)malloc(arr_size*sizeof(double));
    aff_a = 0;
    aff_a = realloc(aff_a,arr_size*sizeof(double));

    aff_a = affine_translation(aa, trans_fact);
    aff_b = affine_rotation(aff_a, rot_fact);

    free(aff_a);

    aff_a = (double *)malloc(arr_size*sizeof(double));
    aff_a = 0;
    aff_a = realloc(aff_a,arr_size*sizeof(double));
    aff_a = aff_b;
    
    return aff_a;
}

int main(void)
{
    double *ma, *mb, *mc, *md;
    double *trns_fact;
    double rot_fact;
    double norm_ac, norm_ab;
    double *line_1_coeff,*line_2_coeff,*line_3_coeff,*line_4_coeff;

    ma = (double *)malloc(arr_size*sizeof(double));
    ma = 0;
    ma = realloc(ma,arr_size*sizeof(double));
    ma = a;
    printf("\n Vertex A:");
    print_vertex(ma);
    mc = (double *)malloc(arr_size*sizeof(double));
    mc = 0;
    mc = realloc(mc,arr_size*sizeof(double));
    mc = c;
    printf("\n Vertex C:");
    print_vertex(mc);
    trns_fact = (double *)malloc(arr_size*sizeof(double));
    trns_fact = 0;
    trns_fact = realloc(trns_fact,arr_size*sizeof(double));
    trns_fact[0] = ma[0]-0;
    trns_fact[1] = ma[1]-0;
    printf("\n Translation Matrix:");
    print_vertex(trns_fact);
    rot_fact = rot_fact_calc(ma,mc)-angle;
    printf("\n Rotation angle"); 
    printf("\n%.2f", rot_fact);
    va = (double *)malloc(arr_size*sizeof(double));
    va = 0;
    va = realloc(va,arr_size*sizeof(double));
    va = affine(ma, trns_fact, rot_fact);
    printf("\n After Affine Transformation, Vertex A:");
    print_vertex(va);
    vc = (double *)malloc(arr_size*sizeof(double));
    vc = 0;
    vc = realloc(vc,arr_size*sizeof(double));
    vc = affine(mc, trns_fact, rot_fact);
    printf("\n After Affine Transformation, Vertex C:");
    print_vertex(vc);
    //free(ma);
    //free(mc);
    printf("\n Norm of A-C:");
    norm_ac = norm(va,vc);
    printf("\n%.2f", norm_ac);
    norm_ab = norm_ac/sqrt(2);
    vb = (double *)malloc(arr_size*sizeof(double));
    vb = 0;
    vb = realloc(vb,arr_size*sizeof(double));
    vb[0] = va[0]+norm_ab;
    vb[1] = va[1];
    printf("\n After Affine Transformation, Vertex B:");
    print_vertex(vb);
    vd = (double *)malloc(arr_size*sizeof(double));
    vd = 0;
    vd = realloc(vd,arr_size*sizeof(double));
    vd[0] = va[0];
    vd[1] = va[1]+norm_ab;
    printf("\n After Affine Transformation, Vertex D:");
    print_vertex(vd);
    free(trns_fact);
    trns_fact = (double *)malloc(arr_size*sizeof(double));
    trns_fact = 0;
    trns_fact = realloc(trns_fact,arr_size*sizeof(double));
    trns_fact[0] = 0 - ma[0];
    trns_fact[1] = 0 - ma[1];
    printf("\n Translation Vector for Reverse Afine:");
    print_vertex(trns_fact);
    rot_fact = -1 * rot_fact;
    printf("\n Rotation angle for Reverse Affine");
    printf("\n%.2f",rot_fact);
    ma = (double *)malloc(arr_size*sizeof(double));
    ma = 0;
    ma = realloc(ma,arr_size*sizeof(double));
    ma = rev_affine(va, trns_fact, rot_fact);
    printf("\n After Reverse Affine Transformation, Vertex A:");
    print_vertex(ma);
    //print_vertex(vb);
    mb = (double *)malloc(arr_size*sizeof(double));
    mb = 0;
    mb = realloc(mb,arr_size*sizeof(double));
    mb = rev_affine(vb, trns_fact, rot_fact);
    printf("\n After Reverse Affine Transformation, Vertex B:");
    print_vertex(mb);
    mc = (double *)malloc(arr_size*sizeof(double));
    mc = 0;
    mc = realloc(mc,arr_size*sizeof(double));
    mc = rev_affine(vc,trns_fact, rot_fact);
    printf("\n After Reverse Affine Transformation, Vertex C:");
    print_vertex(mc);
    //print_vertex(vd);
    md = (double *)malloc(arr_size*sizeof(double));
    md = 0;
    md = realloc(md,arr_size*sizeof(double));
    md = rev_affine(vd,trns_fact, rot_fact);
    printf("\n After Reverse Affine Transformation, Vertex D:");
    print_vertex(md);
    line_1_coeff = (double *)malloc((arr_size+1)*sizeof(double));
    line_1_coeff = 0;
    line_1_coeff = realloc(line_1_coeff,(arr_size+1)*sizeof(double));
    line_1_coeff = line_gen_coeff(ma,mb);
    
    line_2_coeff = (double *)malloc((arr_size+1)*sizeof(double));
    line_2_coeff = 0;
    line_2_coeff = realloc(line_2_coeff,(arr_size+1)*sizeof(double));
    line_2_coeff = line_gen_coeff(mb,mc);
    
    line_3_coeff = (double *)malloc((arr_size+1)*sizeof(double));
    line_3_coeff = 0;
    line_3_coeff = realloc(line_3_coeff,(arr_size+1)*sizeof(double));
    line_3_coeff = line_gen_coeff(mc,md);
    
    line_4_coeff = (double *)malloc((arr_size+1)*sizeof(double));
    line_4_coeff = 0;
    line_4_coeff = realloc(line_4_coeff,(arr_size+1)*sizeof(double));
    line_4_coeff = line_gen_coeff(md,ma);
    
    printf("\nLine Equations are:");
    printf("\n A-B = %.2f x + %.2f y + %.2f = 0", line_1_coeff[0],line_1_coeff[1],line_1_coeff[2]);
    printf("\n B-C = %.2f x + %.2f y + %.2f = 0", line_2_coeff[0],line_2_coeff[1],line_2_coeff[2]);
    printf("\n C-D = %.2f x + %.2f y + %.2f = 0", line_3_coeff[0],line_3_coeff[1],line_3_coeff[2]);
    printf("\n D-A = %.2f x + %.2f y + %.2f = 0", line_4_coeff[0],line_4_coeff[1],line_4_coeff[2]);
   
   return 0;
}