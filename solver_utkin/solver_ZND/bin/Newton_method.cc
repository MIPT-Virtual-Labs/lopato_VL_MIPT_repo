/*
    функция - метод Ньютона решения системы
    На входе:

        delta_x - шаг
        vector_0 - предыдущий (известный узел)
    На выходе:
        vector - неизвестный узел
    Автор: Лопато А.И.
    Дата написания: 21.01.2014
*/
#include "head.h"
#include "math_utils.h"

/*
void function_Newton_method(double *vector_0, double *vector, double delta_x)
{

    solve_linear_system(  K_GENERAL_CASE,  Matrix, b, 0.000001,
                           x );
    for(i = 1; i <= L - 1; i++)
    {
        for(j = 0; j <= K_GENERAL_CASE - 1; j++)
        {
            A_matrix[i][j] = function_Newton_method(A_matrix[i - 1], delta_x)
        }
    }

}*/
