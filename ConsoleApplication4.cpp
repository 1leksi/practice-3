﻿#include <iostream>
#include "windows.h"
using namespace std;


int getRandomValueFromRange(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit + 1);
}

void matrixBlockReplacement(int* blocks[], int* blocksNew[], const int N) {
    const int distance = (N - 4) / 2;
    for (int i = 0; i < 4; i++) {
        for (int* next = blocks[i], *end = blocks[i] + N / 2 - 1, cnt = 1,
            *next2 = blocksNew[i]; cnt < (N / 2) * (N / 2) - distance; next++, next2++) {
            if (next == end) {
                blocks[i] += N;
                blocksNew[i] += N;

                *next2 = *next;

                next = blocks[i];
                next2 = blocksNew[i];
                end = blocks[i] + N / 2 - 1;
            }
            cnt++;
            if (cnt >= (N / 2) * (N / 2) - distance) break;
            *next2 = *next;
        }
    }
}

void matrixPrint(int* arr, const int N) {
    for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
        if (next - N == prev) {
            cout << "\n";
            prev = next;
        }
        printf("%04d ", *next);
    }
    cout << "\n\n";
}

void matrixFill(int* arr, const int N, const bool isRandom = false, int number = 0) {
    if (isRandom) {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next = getRandomValueFromRange(1, 1000);
        }
    }
    else {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next = number;
        }
    }
}

void matrixOperation(int* arr, const int N, const int operationType, int number = 0) {
    switch (operationType)
    {
    case 0: {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next += number;
        }
        break;
    }
    case 1: {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next -= number;
        }
        break;
    }
    case 2: {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next *= number;
        }
        break;
    }
    case 3: {
        for (int* next = arr, *prev = arr, *end = arr + N * N - 1; next <= end; next++) {
            *next /= number;
        }
        break;
    }
    }
}

void arrayPrint(int* arr, const int N) {
    for (int* next = arr, *prev = arr, *end = arr + N - 1; next <= end; next++) {
        printf("%04d ", *next);
    }
    cout << "\n\n";
}

void insertSort(int* arr, const int N) {
    int key;
    for (int* i = &arr[1], *j = 0, *end = arr + N * N - 1; i <= end; i++) {
        key = *i;
        j = i - 1;

        while (j >= arr && *j > key) {
            *(j + 1) = *j;
            j = j - 1;
        }
        *(j + 1) = key;
    }
}



int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Navigation:" << "\n"
        << "1) Fill a quadratic integer matrix NxN with random numbers" << "\n"
        << "2) Obtains a new matrix from the matrix of (1), rearranging its blocks" << "\n"
        << "3) Using pointer arithmetic, sorts elements (insert sort algorithm)" << "\n"
        << "4) Decrements, increases, multiplies, or divides all elements of a matrix by <number>" << "\n"
        << "5) IDZ #9" << "\n";

    const int N = 6;
    int arr[N * N] = {};

    while (true) {
        cin.clear(); // Clearing the input stream from possible errors
        cin.sync();
        short int workPoint;

        cout << "Select point of work (number 1 to 5): ";
        cin >> workPoint;

        switch (workPoint)
        {
        case 1: {
            const int elementSize = 5;
            int cnt = 1;
            int k = 1;
            system("cls");
            HANDLE hStdout;
            COORD destCoord;
            hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            destCoord.X = -elementSize;

            matrixFill(arr, N); // clear the matrix (for better visibility of the algorithm)



            while (cnt <= N * N) {
                int* upLeftCorner = &arr[(k - 1) * N + (k - 1)];
                int* upRightCorner = &arr[k * N - 1 - (k - 1)];
                int* downLeftCorner = &arr[N * N - (k * N) + (k - 1)];
                int* downRightCorner = &arr[N * N - ((k - 1) * N) - 1 - (k - 1)];

                for (int* next = upLeftCorner, *end = upRightCorner; next <= end; next++) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.X += elementSize;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%04d\r", *next);
                    cout.flush(); // чито на выводе
                    Sleep(200); // видна анимация
                    cnt++;
                }

                for (int* next = upRightCorner + N, *end = downRightCorner; next <= end; next += N) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%04d\r", *next);
                    cout.flush();
                    Sleep(200);
                    cnt++;
                }

                for (int* next = downRightCorner - 1, *end = downLeftCorner; next >= end; next--) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.X -= elementSize;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%04d\r", *next);
                    cout.flush();
                    Sleep(200);
                    cnt++;
                }

                for (int* next = downLeftCorner - N, *end = upLeftCorner + N; next >= end; next -= N) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%04d\r", *next);
                    cout.flush();
                    Sleep(200);
                    cnt++;
                }

                k++;
            }

            system("cls"); // очистка консоли

            destCoord.X = -elementSize;
            destCoord.Y += N * N;
            cout << "\n";

            matrixFill(arr, N); // clear the matrix (for better visibility of the algorithm)

            cnt = 1;
            k = 0;

            int* upBorder = &arr[k];
            int* downBorder = &arr[N * N - N + k];

            while (cnt <= N * N) {
                destCoord.X += elementSize;
                for (int* next = upBorder + k, *end = downBorder + k; next <= end; next += N) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%03d\r", *next);
                    cout.flush();
                    Sleep(200);
                    cnt++;
                }

                k++;
                destCoord.X += 4;

                for (int* next = downBorder + k, *end = upBorder + k; next >= end; next -= N) {
                    *next = getRandomValueFromRange(1, N * N);
                    int posY = (next - arr) / N;
                    destCoord.Y = posY;
                    SetConsoleCursorPosition(hStdout, destCoord);
                    printf("%03d\r", *next);
                    cout.flush();
                    Sleep(200);
                    cnt++;
                }

                k++;
            }
            for (int i = 0; i < N; i++) cout << "\n";
            break;
        }
        case 2: {
            int arrNew[N * N] = {};

            cout << "\n" << "2.A)" << "\n";

            int* blocksA[4] = { &arr[0], &arr[N / 2], &arr[N / 2 + N * (N / 2)], &arr[(N * N) / 2] };   // откуда
            int* blocksNewA[4] = { &arrNew[N / 2], &arrNew[N / 2 + N * (N / 2)], &arrNew[(N * N) / 2], &arrNew[0] };    // куда
            matrixBlockReplacement(blocksA, blocksNewA, N);
            matrixPrint(arrNew, N);

            cout << "\n" << "2.B)" << "\n";
            blocksA[0] = &arr[0];
            blocksA[1] = &arr[N / 2 + N * (N / 2)];
            blocksA[2] = &arr[(N * N) / 2];
            blocksA[3] = &arr[N / 2];
            blocksNewA[0] = &arrNew[N / 2 + N * (N / 2)];
            blocksNewA[1] = &arrNew[0];
            blocksNewA[2] = &arrNew[N / 2];
            blocksNewA[3] = &arrNew[(N * N) / 2];

            matrixBlockReplacement(blocksA, blocksNewA, N);
            matrixPrint(arrNew, N);

            cout << "\n" << "2.C)" << "\n";
            blocksA[0] = &arr[0];
            blocksA[1] = &arr[(N * N) / 2];
            blocksA[2] = &arr[N / 2];
            blocksA[3] = &arr[N / 2 + N * (N / 2)];
            blocksNewA[0] = &arrNew[(N * N) / 2];
            blocksNewA[1] = &arrNew[0];
            blocksNewA[2] = &arrNew[N / 2 + N * (N / 2)];
            blocksNewA[3] = &arrNew[N / 2];

            matrixBlockReplacement(blocksA, blocksNewA, N);
            matrixPrint(arrNew, N);

            cout << "\n" << "2.D)" << "\n";
            blocksA[0] = &arr[0];
            blocksA[1] = &arr[N / 2];
            blocksA[2] = &arr[(N * N) / 2];
            blocksA[3] = &arr[N / 2 + N * (N / 2)];
            blocksNewA[0] = &arrNew[N / 2];
            blocksNewA[1] = &arrNew[0];
            blocksNewA[2] = &arrNew[N / 2 + N * (N / 2)];
            blocksNewA[3] = &arrNew[(N * N) / 2];

            matrixBlockReplacement(blocksA, blocksNewA, N);
            matrixPrint(arrNew, N);

            break;
        }
        case 3: {
            insertSort(arr, N);
            matrixPrint(arr, N);

            break;
        }
        case 4: {
            int operationType;
            cout << "\n" << "Enter an operation type (0:+, 1:-, 2:*. 3:/): ";
            cin >> operationType;

            if (!cin.good() || operationType < 0 || operationType > 3) {
                cout << "\n" << "You entered an incorrect value";
                break;
            }

            int a;
            cout << "\n" << "Enter an integer: ";
            cin >> a;
            if (!cin.good()) {
                cout << "\n" << "You entered an incorrect value";
                break;
            }
            if (operationType == 3 && a == 0) {
                cout << "\n" << "Don't divide by zero (please)";
                break;
            }
            matrixOperation(arr, N, operationType, a);
            matrixPrint(arr, N);

            break;
        }
        case 5: {
            matrixFill(arr, N, true);
            matrixPrint(arr, N);

            int arrNew[N * N] = {};

            int* starty = &arr[0];
            int* endy = &arr[N - 1];

            int* startNew = &arrNew[0];

            for (int* next = starty, *end = endy,
                *next2 = startNew; endy < arr + N * N; next++, next2 += N) {
                if (next == end) {
                    starty += N;
                    startNew += 1;
                    endy = starty + N - 1;

                    *next2 = *next;

                    next = starty;
                    next2 = startNew;
                    end = endy;
                }
                if (end > arr + N * N) break;
                *next2 = *next;
            }

            matrixPrint(arrNew, N);

            break;
        }
        default: {
            cout << "\n" << "You did not enter a number in the range from 1 to 5";
            break;
        }
        }

        cin.clear(); // Clearing the input stream from possible errors
        cin.sync();

        char clearMatrix;
        cout << "\n" << "Clear the result matrix? (Y/N) ";
        cin >> clearMatrix;

        if (clearMatrix == 'Y' || clearMatrix == 'y') {
            matrixFill(arr, N);
        }
        cin.clear();
        cin.sync();

        char stopFlag;
        cout << "\n" << "Continue the program? (Y/N) ";
        cin >> stopFlag;

        if (stopFlag != 'Y' && stopFlag != 'y') {
            break;
        }
    }

    return 0;
}