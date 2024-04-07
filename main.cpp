#include <iostream>

//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double **newMatrix) {
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol = 0; //Смещение индекса столбца в матрице
    for(int i = 0; i < size-1; i++) {
        //Пропустить row-ую строку
        if(i == row) {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }

        offsetCol = 0; //Обнулить смещение столбца
        for(int j = 0; j < size-1; j++) {
            //Пропустить col-ый столбец
            if(j == col) {
                offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
            }

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

int matrixDet(double **matrix, int size) {
    int det = 0;
    int degree = 1; // (-1)^(1+j) из формулы определителя

    //Условие выхода из рекурсии
    if(size == 1) {
        return matrix[0][0];
    }
    //Условие выхода из рекурсии
    else if(size == 2) {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    else {
        //Матрица без строки и столбца
        double **newMatrix = new double*[size-1];
        for(int i = 0; i < size-1; i++) {
            newMatrix[i] = new double[size-1];
        }

        //Раскладываем по 0-ой строке, цикл бежит по столбцам
        for(int j = 0; j < size; j++) {
            //Удалить из матрицы i-ю строку и j-ый столбец
            //Результат в newMatrix
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            //Рекурсивный вызов
            //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
            //где minor_j - дополнительный минор элемента matrix[0][j]
            // (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size-1));
            //"Накручиваем" степень множителя
            degree = -degree;
        }

        //Чистим память на каждом шаге рекурсии(важно!)
        for(int i = 0; i < size-1; i++) {
            delete [] newMatrix[i];
        }
        delete [] newMatrix;
    }

    return det;
}


int main(){
    int n;
    std::cout << "input size = " << std::endl;
    std::cin >> n;
    std::cout << std::endl;
    double **array = new double* [n];

    for (int i = 0; i < n; i++){
        array[i] = new double [n];
        for (int j = 0; j < n; j++){
            array[i][j] = 1;
        }
    }

    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         std::cout << array[i][j] << " ";
    //     }
    //     std:: cout << std::endl;
    // }

    int otv = matrixDet(array, n);
    std:: cout << otv << std::endl;

    // for (int i = 0; i < n; i++){
    //     delete [] array[i];
    // }
    // delete[] array;
    return 0;
}