#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void Check_for_error(int local_ok, char fname[], char message[],
      MPI_Comm comm);
void Get_dims(int* m_p, int* local_m_p, int* n_p, int* local_n_p,
      int my_rank, int comm_sz, MPI_Comm comm);
void Allocate_arrays(double** local_A_pp, double** local_x_pp,
      double** local_y_pp, int local_m, int n, int local_n,
      MPI_Comm comm);
void Read_matrix(char prompt[], double local_A[], int m, int local_m,
      int n, int my_rank, MPI_Comm comm);
void Read_vector(char prompt[], double local_vec[], int n, int local_n,
      int my_rank, MPI_Comm comm);
void Print_matrix(char title[], double local_A[], int m, int local_m,
      int n, int my_rank, MPI_Comm comm);
void Print_vector(char title[], double local_vec[], int n,
      int local_n, int my_rank, MPI_Comm comm);
void Mat_vect_mult(double local_A[], double local_x[],
      double local_y[], int local_m, int n, int local_n,
      MPI_Comm comm);

int main(void) {

   double* local_A;
   double* local_x;
   double* local_y;
   int m, local_m, n, local_n;
   int my_rank, comm_sz;
   MPI_Comm comm;
   //srand(time(NULL) + my_rank);

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &comm_sz);
   MPI_Comm_rank(comm, &my_rank);

   Get_dims(&m, &local_m, &n, &local_n, my_rank, comm_sz, comm);
   Allocate_arrays(&local_A, &local_x, &local_y, local_m, n, local_n, comm);
   Read_matrix("A", local_A, m, local_m, n, my_rank, comm);
#  ifdef DEBUG
 //  Print_matrix("A", local_A, m, local_m, n, my_rank, comm);
#  endif
   Read_vector("x", local_x, n, local_n, my_rank, comm);
#  ifdef DEBUG
   //Print_vector("x", local_x, n, local_n, my_rank, comm);
#  endif
   double t1, t2; 
   t1 = MPI_Wtime(); 
   Mat_vect_mult(local_A, local_x, local_y, local_m, n, local_n, comm); 
   t2 = MPI_Wtime(); 
   printf( "Elapsed time is %f\n", t2 - t1 ); 

   

   //Print_vector("y", local_y, m, local_m, my_rank, comm);

   free(local_A);
   free(local_x);
   free(local_y);
   MPI_Finalize();
   return 0;
}  /* main */


void Check_for_error(
      int       local_ok   /* in */,
      char      fname[]    /* in */,
      char      message[]  /* in */,
      MPI_Comm  comm       /* in */) {
   int ok;

   MPI_Allreduce(&local_ok, &ok, 1, MPI_INT, MPI_MIN, comm);
   if (ok == 0) {
      int my_rank;
      MPI_Comm_rank(comm, &my_rank);
      if (my_rank == 0) {
         fprintf(stderr, "Proc %d > En %s, %s\n", my_rank, fname,
               message);
         fflush(stderr);
      }
      MPI_Finalize();
      exit(-1);
   }
}  /* Check_for_error */


/*-------------------------------------------------------------------
 * Function:  Get_dims
 * Purpose:   Leer las dimensiones de la matriz y los vectores, y
 *            propagar los valores a todos los procesos
 * In args:   my_rank:   rango del proceso dentro del comunicador
 *            comm_sz:   número de procesos en el comunicador
 *            comm:      comunicador que contiene a todos los procesos
 *                       que llaman a Get_dims
 * Out args:  m_p:       número global de filas de A y componentes de y
 *            local_m_p: número local de filas de A y componentes de y
 *            n_p:       número global de cols de A y componentes de x
 *            local_n_p: número local de cols de A y componentes de x
 *
 * Errors:    se verifica que m y n sean positivos y divisibles para comm_sz
 *
 * Note:
 *    All processes in comm should call Get_dims
 */
void Get_dims(
      int*      m_p        /* out */,
      int*      local_m_p  /* out */,
      int*      n_p        /* out */,
      int*      local_n_p  /* out */,
      int       my_rank    /* in  */,
      int       comm_sz    /* in  */,
      MPI_Comm  comm       /* in  */) {
   int local_ok = 1;

   if (my_rank == 0) {
      // leer los valores de m y n desde el teclado (proc. 0)
      printf("Ingrese el número de filas\n");
      scanf("%d", m_p);
      printf("Ingrese el número de columnas\n");
      scanf("%d", n_p);
   }
   // Propagar estos valores con broadcast
   MPI_Bcast(m_p, 1, MPI_INT, 0, comm);
   MPI_Bcast(n_p, 1, MPI_INT, 0, comm);
   if (*m_p <= 0 || *n_p <= 0 || *m_p % comm_sz != 0
         || *n_p % comm_sz != 0) local_ok = 0;
   Check_for_error(local_ok, "Get_dims",
      "m y n deben ser positivos y divisibles para comm_sz",
      comm);

   *local_m_p = *m_p/comm_sz;
   *local_n_p = *n_p/comm_sz;
}  /* Get_dims */

/*-------------------------------------------------------------------
 * Function:   Allocate_arrays
 * Purpose:    Asignar memoria para las partes locales de A, x, y
 * In args:    local_m:    número local de filas de A y componentes de y
 *             n:          número global de cols de A y componentes de x
 *             local_n:    número local de cols de A y componentes de x
 *             comm:       comunicador que contiene a los procesos que llaman
 *                         a esta función
 * Out args:   local_A_pp: (puntero a) matriz local A (m/comm_sz filas, n cols)
 *             local_x_pp: (puntero a) vector local x (n/comm_sz componentes)
 *             local_y_pp: (puntero a) vector local y (m/comm_sz componentes)
 *
 * Errors:     se verifican errores en los llamados a malloc
 *
 * Note:
 *    Communicator should be MPI_COMM_WORLD because of call to
 * Check_for_errors
 */
void Allocate_arrays(
      double**  local_A_pp  /* out */,
      double**  local_x_pp  /* out */,
      double**  local_y_pp  /* out */,
      int       local_m     /* in  */,
      int       n           /* in  */,
      int       local_n     /* in  */,
      MPI_Comm  comm        /* in  */) {

   int local_ok = 1;

   *local_A_pp = malloc(local_m*n*sizeof(double));
   *local_x_pp = malloc(local_n*sizeof(double));
   *local_y_pp = malloc(local_m*sizeof(double));

   if (*local_A_pp == NULL || local_x_pp == NULL ||
         local_y_pp == NULL) local_ok = 0;
   Check_for_error(local_ok, "Allocate_arrays",
         "no pudo asignarse memoria para los arreglos locales", comm);
}  /* Allocate_arrays */

/*-------------------------------------------------------------------
 * Function:  Read_matrix
 * Purpose:   Lee una matriz y la distribuye utilizando un
 *            particionamiento por filas
 * In args:   prompt:  descripción de la matriz (e.g., "A")
 *            m:       número global de filas de A
 *            local_m: número local de filas de A
 *            n:       número global y local de filas de A
 *            my_rank: rango del proceso que llama a la función
 *            comm:    comunicador que contiene a todos los procesos
 *                     que llaman a la función
 * Out args:  local_A: matriz local
 *
 * Errors:    se verifican errores en el llamado a malloc paralelo
 *            crear la estructura temporal
 * Note:
 * 1. Communicator should be MPI_COMM_WORLD because of call to
 *    Check_for_errors
 * 2. local_m and n should be the same on each process
 */
void Read_matrix(
      char      prompt[]   /* in  */,
      double    local_A[]  /* out */,
      int       m          /* in  */,
      int       local_m    /* in  */,
      int       n          /* in  */,
      int       my_rank    /* in  */,
      MPI_Comm  comm       /* in  */) {
   double* A = NULL;
   int local_ok = 1;
   int i, j;

   if (my_rank == 0) {
     // Proceso 0 lee la matriz desde la consola de entrada...
      A = malloc(m*n*sizeof(double));
      if (A == NULL) local_ok = 0;
      Check_for_error(local_ok, "Read_matrix",
            "No pudo asignarse memoria para la matriz temporal", comm);
      printf("Ingrese la matriz %s\n", prompt);
      for (i = 0; i < m; i++)
         for (j = 0; j < n; j++)
            A[i*n+j]=i;
            //scanf("%lf", &A[i*n+j]);
      // ... y la distribuye con MPI_Scatter
      MPI_Scatter(A, local_m*n, MPI_DOUBLE,
            local_A, local_m*n, MPI_DOUBLE, 0, comm);
      free(A);
   } else {
      Check_for_error(local_ok, "Read_matrix",
            "No pudo asignarse memoria para la matriz temporal", comm);
      // Los otros procesos esperan a recibir la matriz local por MPI_Scatter
      MPI_Scatter(A, local_m*n, MPI_DOUBLE,
            local_A, local_m*n, MPI_DOUBLE, 0, comm);
   }
}  /* Read_matrix */

/*-------------------------------------------------------------------
 * Function:  Read_vector
 * Purpose:   Lee un vector de entrada y lo distribuye hacia
 *            todos los procesos usando una partición por bloques.
 * In args:   prompt:  nombre del vector a leer (e.g., "x")
 *            n:       tamaño del vector global
 *            local_n: tamaño de los vectores locales (n/comm_sz)
 *            my_rank:  rango del proceso que llama a la función
 *            comm: comunicador que contiene a todos los procesos
 *                  que llaman a la función
 * Out arg:   local_vec:  vector local leído
 *
 * Errors:    se verifican errores en el llamado a malloc
 *
 * Notes:
 * 1. Communicator should be MPI_COMM_WORLD because of call to
 *    Check_for_errors
 * 2. local_n should be the same on all processes
 */
void Read_vector(
      char      prompt[]     /* in  */,
      double    local_vec[]  /* out */,
      int       n            /* in  */,
      int       local_n      /* in  */,
      int       my_rank      /* in  */,
      MPI_Comm  comm         /* in  */) {
   double* vec = NULL;
   int i, local_ok = 1;

   if (my_rank == 0) {
      // Proceso 0 lee el vector desde la consola de entrada...
      vec = malloc(n*sizeof(double));
      if (vec == NULL) local_ok = 0;
      Check_for_error(local_ok, "Read_vector",
            "No pudo asignarse memoria para el vector temporal", comm);
      printf("Ingrese el vector %s\n", prompt);
      for (i = 0; i < n; i++)
         vec[i]=2;
         //scanf("%lf", &vec[i]);
      // ... y lo distribuye con MPI_Scatter
      MPI_Scatter(vec, local_n, MPI_DOUBLE,
            local_vec, local_n, MPI_DOUBLE, 0, comm);
      free(vec);
   } else {
      Check_for_error(local_ok, "Read_vector",
            "No pudo asignarse memoria para el vector temporal", comm);
      // Los otros procesos esperan a recibir el vector local por MPI_Scatter
      MPI_Scatter(vec, local_n, MPI_DOUBLE,
            local_vec, local_n, MPI_DOUBLE, 0, comm);
   }
}  /* Read_vector */

/*-------------------------------------------------------------------
 * Function:  Print_matrix
 * Purpose:   Escribe una matriz distribuida por filas
 * In args:   title:    nombre de la matriz
 *            local_A:  (puntero a) parte local de la matriz
 *            m:        número global de filas
 *            local_m:  número local de filas (m/comm_sz)
 *            n:        número global (y local) de columnas
 *            my_rank:  rango del proceso
 *            comm: comunicador que contiene a todos los procesos
 *                  que llaman a la función
 * Errors:    if malloc of local storage on process 0 fails, all
 *            processes quit.
 * Notes:
 * 1.  comm should be MPI_COMM_WORLD because of call to Check_for_errors
 * 2.  local_m should be the same on all the processes
 */
void Print_matrix(
      char      title[]    /* in */,
      double    local_A[]  /* in */,
      int       m          /* in */,
      int       local_m    /* in */,
      int       n          /* in */,
      int       my_rank    /* in */,
      MPI_Comm  comm       /* in */) {
   double* A = NULL;
   int i, j, local_ok = 1;

   if (my_rank == 0) {
      // El proceso 0 ensambla la matriz...
      A = malloc(m*n*sizeof(double));
      if (A == NULL) local_ok = 0;
      Check_for_error(local_ok, "Print_matrix",
            "No pudo asignarse memoria para la matriz temporal", comm);
      MPI_Gather(local_A, local_m*n, MPI_DOUBLE,
            A, local_m*n, MPI_DOUBLE, 0, comm);
      // ... y luego la escribe en la pantalla
      printf("\nThe matrix %s\n", title);
      for (i = 0; i < m; i++) {
         for (j = 0; j < n; j++)
            printf("%f ", A[i*n+j]);
         printf("\n");
      }
      printf("\n");
      free(A);
   } else {
      // Los demás procesos envían su parte de la matriz al proceso cero
      Check_for_error(local_ok, "Print_matrix",
            "No pudo asignarse memoria para la matriz temporal", comm);
      MPI_Gather(local_A, local_m*n, MPI_DOUBLE,
            A, local_m*n, MPI_DOUBLE, 0, comm);
   }
}  /* Print_matrix */

/*-------------------------------------------------------------------
 * Function:  Print_vector
 * Purpose:   Escribir un vector particionado por bloques
 * In args:   title:      nombre del vector
 *            local_vec:  (puntero a) vector local
 *            n:          número global de componentes
 *            local_n:    número local de componentes (n/comm_sz)
 *            my_rank:  rango del proceso
 *            comm: comunicador que contiene a todos los procesos
 *                  que llaman a la función
 * Errors:    if malloc of local storage on process 0 fails, all
 *            processes quit.
 * Notes:
 * 1.  comm should be MPI_COMM_WORLD because of call to Check_for_errors
 * 2.  local_n should be the same on all the processes
 */
void Print_vector(
      char      title[]     /* in */,
      double    local_vec[] /* in */,
      int       n           /* in */,
      int       local_n     /* in */,
      int       my_rank     /* in */,
      MPI_Comm  comm        /* in */) {
   double* vec = NULL;
   int i, local_ok = 1;

   if (my_rank == 0) {
     // El proceso 0 ensambla el vector...
      vec = malloc(n*sizeof(double));
      if (vec == NULL) local_ok = 0;
      Check_for_error(local_ok, "Print_vector",
            "No pudo asignarse memoria para el vector temporal", comm);
      MPI_Gather(local_vec, local_n, MPI_DOUBLE,
            vec, local_n, MPI_DOUBLE, 0, comm);
      printf("\nThe vector %s\n", title);
      // ... y luego la escribe en la pantalla
      for (i = 0; i < n; i++)
         printf("%f ", vec[i]);
      printf("\n");
      free(vec);
   }  else {
      Check_for_error(local_ok, "Print_vector",
            "No pudo asignarse memoria para el vector temporal", comm);
      // Los demás procesos envían su parte del vector al proceso cero
      MPI_Gather(local_vec, local_n, MPI_DOUBLE,
            vec, local_n, MPI_DOUBLE, 0, comm);
   }
}  /* Print_vector */

/*-------------------------------------------------------------------
 * Function:  Mat_vect_mult
 * Purpose:   Calcular el producto matricial y:=Ax.  La matriz
              está particionada por filas, y los vectores están
              particionados por bloques.
 * In args:   local_A:  (puntero a) arreglo que contiene matriz local A
 *            local_x:  (puntero a) arreglo que contiene vector local x
 *            local_m:  número local de filas
 *            n:        número global de columnas
 *            local_n:  dimensión del vector local x
 *            comm: comunicador que contiene a todos los procesos
 *                  que llaman a la función
 * Errors:    if malloc of local storage on any process fails, all
 *            processes quit.
 * Notes:
 * 1.  comm should be MPI_COMM_WORLD because of call to Check_for_errors
 * 2.  local_m and local_n should be the same on all the processes
 */
void Mat_vect_mult(
      double    local_A[]  /* in  */,
      double    local_x[]  /* in  */,
      double    local_y[]  /* out */,
      int       local_m    /* in  */,
      int       n          /* in  */,
      int       local_n    /* in  */,
      MPI_Comm  comm       /* in  */) {
   double* x;
   int local_i, j;
   int local_ok = 1;

   x = malloc(n*sizeof(double));
   if (x == NULL) local_ok = 0;
   Check_for_error(local_ok, "Mat_vect_mult",
         "No pudo asignarse memoria para el vector temporal", comm);
   // El vector x es ensamblado y replicado en todos los procesos
   MPI_Allgather(local_x, local_n, MPI_DOUBLE,
         x, local_n, MPI_DOUBLE, comm);

   // Se calcula y=Ax para el conjunto de filas que le corresponden al proceso
   for (local_i = 0; local_i < local_m; local_i++) {
      local_y[local_i] = 0.0;
      for (j = 0; j < n; j++)
         local_y[local_i] += local_A[local_i*n+j]*x[j];
   }
   free(x);
}  /* Mat_vect_mult */