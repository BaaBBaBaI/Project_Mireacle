
using System;
namespace _2RT_2nd_task;

class Program
{
    
    // Здесь должен быть реалиована инициализация матрицы
    // Заполнение матрицы должно производиться в матрикслиб (в том числе случайное)
    // Операции с матрицами вызываются отсюда и выполняются в матрикслиб
    
    // Сама задача:
    //
    // Реализуйте программный продукт средствами языка C# со
    //     следующим функционалом:
    // 1) Создание двух матриц размерности n*m (значения n и m вводятся
    //         с клавиатуры); 
    
    // 2) Заполнение матриц значениями с клавиатуры (по выбору
    // пользователя, с последующим выводом результата на экран);
    
    // 3) Заполнение матриц рандомными числами в диапазоне [a; b]
    // (значения a и b вводятся с клавиатуры) (по выбору пользователя, с
    //     последующим выводом результата на экран);
    
    // 4) Сложение матриц (предусмотреть проверку на возможность
    // выполнения операции, с последующим выводом результата на
    // экран);
    
    // 5) Умножение матриц (предусмотреть проверку на возможность
    // выполнения операции, с последующим выводом результата на
    // экран);
    
    // 6) Нахождение детерминанта (определителя) матрицы
    //     (предусмотреть проверку на возможность выполнения операции, с
    // последующим выводом результата на экран);
    
    // 7) Нахождение обратной матрицы (предусмотреть проверку на
    //     возможность выполнения операции, с последующим выводом
    // результата на экран);
    
    // 8) Транспонирование матриц (с последующим выводом результата на
    //         экран);
    
    // 9) Нахождение корней системы уравнений, заданных матрицей (с
    //         последующим выводом результата на экран).
    //     
    // При тестировании продемонстрировать успешное выполнение
    //     всех пунктов (положительный сценарий), а также обработку следующих
    // ситуаций (негативный сценарий):
    //     1) Невозможность сложения матриц по причине несоответствия
    // их размерностей;
    //     2) Невозможность умножения матриц в связи с их
    //     несовместимостью;
    //     3) Невозможность нахождения детерминанта у не квадратных
    // матриц (n!=m);
    //     4) Невозможность нахождения обратной матрицы в случае, если
    // детерминант равен нулю (d=0);
    //     5) Невозможность нахождения корней систему уравнений, если
    //     она не имеет решения или не имеет однозначного решения.
    //     Весь функционал должен быть реализован вами, программы,
    // разработанные с использованием сторонних решений (библиотеки,
    //     фреймворки и т.д.) реализующих функционал, приниматься не будут.



    
    
    static void Main()

    {

        Console.WriteLine("Hello please give n and m as proportions");

        (int n, int m) proportions;

        Console.Write("n: ");
        
        proportions.n = int.Parse(Console.ReadLine() ?? string.Empty);
        
        Console.Write("m: ");
        
        proportions.m = int.Parse(Console.ReadLine() ?? string.Empty);

        double[][] matrix = MatrixEv.Matrixcreate((proportions.n, proportions.m));

        double[][] matrix2 = MatrixEv.Matrixcreate((proportions.n, proportions.m));
        
        
        MatrixEv.MatrixFill(ref matrix, "random", 1, 20, 20);
        
        MatrixEv.MatrixFill(ref matrix2, "random", 1, 20, 10);
        
        MatrixEv.MatrixOutput(matrix);

        Console.WriteLine("-------- Output: --------");
        
        MatrixEv.MatrixOutput(matrix2);
        
        double[][] matrixPlus = MatrixEv.MatrixAddition(matrix, matrix2);
        
        Console.WriteLine("-------- Addition: --------");
        
        MatrixEv.MatrixOutput(matrixPlus);
        
        double[][] matrixMultiply = MatrixEv.MatrixMultiplication(matrix, matrix2);
        
        Console.WriteLine("-------- Multiplication: --------");
        
        MatrixEv.MatrixOutput(matrixMultiply);
        
        double determinant = MatrixEv.MatrixDeterminant(matrix);
        
        Console.WriteLine($"-------- Determinant for first Matrix: -------- \n { determinant }");
        
        double[][] matrixRev = MatrixEv.MatrixInvert(matrix);
        
        Console.WriteLine("-------- Invert first Matrix: --------");

        MatrixEv.MatrixOutput(matrixRev);
        
        double[][] matrixT = MatrixEv.MatrixTranspond(matrix);
        
        Console.WriteLine("-------- Transpond: --------");
        
        MatrixEv.MatrixOutput(matrixT);
        
        double[][] matrixEq = MatrixEv.MatrixEqSysSolve(matrix);
        
        Console.WriteLine("-------- eq: --------");
        
        MatrixEv.MatrixOutput(matrixEq);
        
        
        return;
    }
    
}