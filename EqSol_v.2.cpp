 #include <stdio.h>
 #include <math.h>
 #include <assert.h>

/*!

     Global parameter responsible for situations with infinity number of roots.

*/

const int infinity = -5;


/*!

     Global parameter responsible for infelicity of non-integer types.

*/

const double infelicity = 1E-7;


//-----------------------------------------------------------------------------

int is_Zero           (double val);

void coeffNormalizing (double *a, double *b, double *c);

int comparer          (double A,  double B);

void checker          (double *a, double *b, double *c);

int Square            (double a,  double b,  double c, double *root1, double *root2);

int Linear            (double b,  double c,  double *root1);

int solver            (double a,  double b,  double c, double *root1, double *root2);

//-----------------------------------------------------------------------------


/*!

     Main function.

*/


int main()
    {

    printf ("# Equation solver ( square (a * x^2 + b * x + c = 0) version )\n"
            "# (c) Ferrum, 2020\n\n");


    printf ("# Enter your a, b, c: ");


    double a = 0, b = 0, c = 0;


    checker ( &a, &b, &c );


    coeffNormalizing (&a, &b, &c);


    double x1 = 0, x2 = 0;


    int n_of_roots = solver (a, b, c, &x1, &x2);


    printf ("Answer: ");


    switch ( n_of_roots )
        {

        case -1:

        printf ("no roots.\n");

        break;


        case 0:

        printf ("one root x1 = %lg.\n", x1);

        break;


        case 1:

        printf ("two roots x1 = %lg, x2 = %lg.\n", x1, x2);

        break;


        case infinity:

        printf ("any number.\n");

        break;


        default:

        printf ("main(): ERROR: roots = %d.\n", n_of_roots);

        return 1;

        }
    }



//-----------------------------------------------------------------------------


/*!

     \brief Comparing a number with zero.
     \param[in] val - compared number.
     \return 0 - number is zero, 1 - number is not a zero.

     This function allows you to compare a number with zero if the infelicity of this number is 1E-7.
*/


int is_Zero (double val)
    {

    return ( fabs (val) <= infelicity ) ? 0 : 1;

    }


//-----------------------------------------------------------------------------


/*!

     \brief Normalizing of odds.
     \param[in] a, b, c - odds of equation.

     This function makes the equation reduced (leads to the form in which a = 1).
*/


void coeffNormalizing (double *a, double *b, double *c)
    {

    if ( is_Zero (*a) == 0 ) return;


    *b = *b / *a; *c = *c / *a; *a = 1;

    }


//-----------------------------------------------------------------------------


/*!

     \brief Compare a number with number.
     \param[in] A, B - compared numbers.
     \return -1 - À less than Â, 0 - À and Â are equal, 1 - À more than Â.

     This function allows you to compare two numbers.
*/


int comparer (double A, double B)
    {

    if ( fabs ( A - B ) <= infelicity )

    return 0;


    if        ( A < B )

    return -1;


    if        ( A > B )

    return 1;


    return 2;

    }


//-----------------------------------------------------------------------------

/*!

     \brief Add to scanf().
     \param[in] a, b, c - input parameters (odds in this situation).

     This function prevents user input errors.
*/

void checker (double* a, double* b, double* c)
    {

    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);


    int check = scanf ("%lg, %lg, %lg", a, b, c);


    while ( check != 3 )
        {

        printf ("# Sorry, try to input CORRECT information\n\n"
                "# Enter your a, b, c: ");


        fflush (stdin);


        check = scanf ("%lg, %lg, %lg", a, b, c);

        }
    }


//-----------------------------------------------------------------------------

/*!

     \param[in] a, b, c - odds of square equation.
     \return 0 - equation have no roots,
             1 - equation have 1 root,
             2 - equation have 2 roots.

     Function that solves square equation of the form a*x^2 + b*x + c = 0.

*/

int Square (double a, double b, double c, double* root1, double* root2)
    {

    assert (root1 != NULL);
    assert (root2 != NULL);

    double discr = b * b - 4 * a * c;

    double  zero = 0;


    int res = comparer (discr, zero);


    switch (res)
        {

        case -1:

        return res;


        case 0:

        *root1 = -b / 2 / a;

        return res;


        case 1:

        *root1 = ( -b + sqrt(discr) ) / 2 / a;

        *root2 = ( -b - sqrt(discr) ) / 2 / a;

        return res;


        default:

        printf ("Square (): ERROR: discriminant = %lf.\n", discr);

        return res;

        }
    }


//-----------------------------------------------------------------------------

/*!

     \param[in] b, c - odds of linear equation.
     \return -1 - equation have no roots,
             0 - equation have 1 root,
             -5 (infinity) - equation have infinity number of roots.

     Function that solves linear equation of the form b*x + c = 0.

*/

int Linear (double b, double c, double* root1)
    {

    assert (root1 != NULL);


    if     ( is_Zero (b) == 0 )

    return ( is_Zero (c) == 0 ) ? infinity : -1;


    *root1 = -c / b;

    return 0;

    }


//-----------------------------------------------------------------------------

/*!

     \brief Function, that solves the equation.
     \param[in] a, b, c - odds of equation.
     \return The value of the called function is Linear() if equation was linear,
                                                 Square() - if equation was square.

      Calls function Square() or Linear() depending on which equation is given (square or linear).
*/

int solver (double a, double b, double c, double* root1, double* root2)
    {

    assert (root1 != NULL);
    assert (root2 != NULL);


    if ( is_Zero (a) == 0 )

    return Linear (b, c, root1);


    return Square (a, b, c, root1, root2);

    }


//-----------------------------------------------------------------------------

