using System.Globalization;
using System.Net.Security;
using System.Numerics;
using System.Runtime.Serialization;

namespace _2RT_2nd_task;

public abstract class MatrixEv
{
    
    public static void MatrixOutput( double[][] matrix) {

        for (int i = 0; i < matrix.Length; i++)
        {
            for (int j = 0; j < matrix[0].Length; j++)
            {
                Console.Write($" [ {matrix[i][j]} ] ");
            }
            Console.WriteLine();
        }
        
    }
    public static double[][] Matrixcreate( (int rows, int cols) size)
    {
        double[][] matrix = new double[size.rows][];
        for (int i = 0; i < size.rows; i++)
        {
            matrix[i] = new double[size.cols];
        }
        return matrix;
    }
    
    public static double[][] MatrixFill( ref double[][] matrix) // Заполнитель матрицы 
    {
        foreach (double[] i in matrix)
        {
            string? line = Console.ReadLine(); 
            double[]? row = line?.Split([' ', ',', '\t'], StringSplitOptions.RemoveEmptyEntries).Select(double.Parse).ToArray();
            for (int j = 0; j < i.Length; j++)
            {
                if (row != null) i[j] = row[j];
            }
        }
        
        return matrix;
    }
    
    public static double[][] MatrixFill( ref double[][] matrix, string operation, int border1, int  border2, int seed) // Заполнитель матрицы рандомными числами с границей 
    {
        
        switch (operation)
        {
            case "random":
            {
                Random rnd = new Random(seed);
                foreach (double[] i in matrix)
                {
                    for (int j = 0; j < i.Length; j++)
                    {
                        i[j] = rnd.Next(border1, border2);
                    }
                }
                return matrix;
            }

            case "file":
            {
                
                
                
                return matrix;
            }

            default:
            {
                foreach (double[] i in matrix)
                {
                    string? line = Console.ReadLine(); 
                    double[]? row = line?.Split([' ', ',', '\t'], StringSplitOptions.RemoveEmptyEntries).Select(double.Parse).ToArray();
                    for (int j = 0; j < i.Length; j++)
                    {
                        if (row != null) i[j] = row[j];
                    }
                }
        
                return matrix;
            }
        }
    }

    public static double[][] MatrixAddition(double[][] matrix1, double[][] matrix2) // Реализация операции сложения матрицы 
    {
    
        if (matrix1 == null || matrix2 == null) throw new ArgumentException("Matrices cannot be null");
        if (matrix1.Length != matrix2.Length) throw new ArgumentException("Matrix row counts must match");
        int rows = matrix1.Length;
        double[][] resultMatrix = new double[rows][];
        for (int i = 0; i < rows; i++)
        {
            if (matrix1[i] == null || matrix2[i] == null || matrix1[i].Length != matrix2[i].Length)
                throw new ArgumentException("Matrices must be rectangular and the same size");
            int cols = matrix1[i].Length;
            resultMatrix[i] = new double[cols];
            for (int j = 0; j < cols; j++)
                resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
        return resultMatrix;
    }

    public static double[][] MatrixMultiplication(double[][] matrix1, double[][] matrix2) // Реализация умножения матрицы
    {
        
        // Оптимизация через алгоритм Штрассена не будет произведена, однако ее реализация возможна
    
        
        if (matrix1[0].Length == matrix2.Length)
        {
            (int, int) matrixproportions = (matrix2[0].Length, matrix1.Length);
            double[][] result = new double[matrixproportions.Item1][];
            for (int i = 0; i < matrixproportions.Item1; i++)
            {
                result[i] = new double[matrixproportions.Item2];   // allocate each row
            }
            for (int i = 0; i < matrix1.Length; i++)
            {
                
                for (int j = 0; j < matrix2[0].Length; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < matrix1.Length; k++)
                    {
                        sum += matrix1[i][j] * matrix2[i][j];
                    }

                    result[i][j] = sum;

                }
                
            }
            return result;
            
            
        }
        else
        {
            throw new ArgumentException("Matrices cannot be multiplied");
        }
    }

    public static double MatrixDeterminant(double[][] matrix) // Реализация получения детерминанта матрицы
    {
        double determinant = 0;

        if (matrix.Length != matrix[0].Length) { throw new ArgumentException("Matrix should be a square."); }

        switch (matrix[0].Length)
        {
            case 0:
            {
                determinant = 1;
                return determinant;
            }
            case 1:
            {
                determinant = matrix[0][0];
                return determinant;
            }
            case 2:
            {
                determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
                return determinant;
            }
        }
        
        double[][]? matrixCopy = matrix.Clone() as double[][];
        int s = 1;
        
        if (matrixCopy == null) throw new ArgumentException("Matrix copy cannot be null (error in matrix or matrix copy)");
        
        for (int i = 0; i < matrix.Length; i++)
        {
            int vot = i;
            double maxAbs = Math.Abs(matrix[i][i]);
            for (int r = i + 1; r < matrix.Length; r++)
            {
                if (matrixCopy != null)
                {
                    double v = Math.Abs(matrixCopy[r][i]);
                    if (v > maxAbs) { maxAbs = v; vot = r; }
                }
            }
            if (maxAbs == 0.0) return 0.0;

            if (vot != i)
            {
                for (int j = i; j < matrix.Length; j++)
                {
                    if (matrixCopy != null)
                    {
                        (matrixCopy[i][j], matrixCopy[vot][j]) = (matrixCopy[vot][j], matrixCopy[i][j]);
                    }
                }
                s = -s;
            }

            if (matrixCopy != null)
            {
                double ak = matrixCopy[i][i];

                for (int z = i + 1; z < matrix.Length; z++)
                {
                    double factor = matrixCopy[z][i] / ak;
                    matrixCopy[z][i] = 0.0;
                    for (int l = i + 1; l < matrix.Length; l++)
                    {
                        matrixCopy[z][l] -= factor * matrixCopy[i][l];
                    }
                }
            }
            
            
        }
        
        determinant = s;
        for (int a = 0; a < matrixCopy.Length; a++)
        {
            determinant *= matrixCopy[a][a];
        }
        
        return determinant;
    }

    public static double[][] MatrixInvert(double[][] matrix) // still have finished
    {

        if (matrix == null) throw new ArgumentException("Matrix cannot be null.");
        
        int n = matrix.Length; if (n == 0) throw new ArgumentException("Matrix cannot be empty.");

        for (int i = 0; i < n; i++)
        {
            if (matrix[i] == null || matrix[i].Length != n) throw new ArgumentException("Matrix cannot be null or non square.");
        }
        
        double[][]? augmentMatrix = new double[n][];
        for (int i = 0; i < n; i++)
        {
            augmentMatrix[i] = new double[2*n];
            for (int j = 0; j < n; j++) { augmentMatrix[i][j] = matrix[i][j]; }
            augmentMatrix[i][n + i] = 1.0;
        }

        const double eps = 1e-12;

        for (int col = 0; col < n; col++)
        {
            int votRow = col;
            double maxAbs = Math.Abs(augmentMatrix[votRow][col]);

            for (int row = col + 1; row < n; row++)
            {
                double factor = Math.Abs(augmentMatrix[row][col]);

                if (factor > maxAbs)
                {
                    maxAbs = factor;
                    votRow = row;
                }
                
            }

            if (maxAbs < eps) return null;

            if (votRow != col) { (augmentMatrix[votRow], augmentMatrix[col]) = (augmentMatrix[col], augmentMatrix[votRow]); }

            double votVal = augmentMatrix[col][col];
            for (int j = 0; j < 2 * n; j++)
            {
                augmentMatrix[col][j] /= votVal;
            }

            for (int r = 0; r < n; r++)
            {
                if (r == col) continue;
                double factor = augmentMatrix[r][col];

                if (Math.Abs(factor) < eps)
                {
                    augmentMatrix[r][col] = 0.0;
                    continue;
                }

                for (int jj = 0; jj < 2 * n; jj++) augmentMatrix[r][jj] -= factor * augmentMatrix[col][jj];
                
            }
        }
        
        double[][] inverseMatrix = new double[n][];

        for (int i = 0; i < n; i++)
        {
            inverseMatrix[i] = new double[n];
            Array.Copy(augmentMatrix[i], n, inverseMatrix[i], 0, n);
        }
        
        return inverseMatrix;
    }

    public static double[][] MatrixTranspond(double[][] matrix)
    {
        
        if (matrix == null) throw new ArgumentException("Matrix cannot be null.");
        
        int cols = matrix.Length; if (cols == 0) throw new ArgumentException("Matrix cannot be empty.");

        int rows = matrix[0].Length; if (rows == 0) throw new ArgumentException("Matrix rows cannot be empty.");
        
        for (int i = 0; i < cols; i++)
        {
            if (matrix[i] == null || matrix.Length != cols) throw new ArgumentException("Matrix cannot be null or non rectangular.");
        }
        
        // ---
        
        double[][]? transpondMatrix = new double[rows][];

        for (int i = 0; i < rows; i++)
        {
            transpondMatrix[i] = new double[cols];
        }

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                
                transpondMatrix[j][i] = matrix[i][j];
                
            }
        }

        
        return transpondMatrix;
    }

    public static double[][] MatrixEqSysSolve(double[][] matrix)
    {
        // check for exception
        if (matrix == null) throw new ArgumentException("Matrix cannot be null.");
        int colsL = matrix.Length;
        if (colsL == 0) throw new ArgumentException("Matrix cannot be empty.");
        if (matrix[0] == null) throw new ArgumentException("Rows cannot be null.");
        int rowsL = matrix[0].Length;
        if (rowsL < 2) throw new ArgumentException("Matrix must have at least one variable and RHS.");
        for (int i = 1; i < colsL; i++)
        {
            if (matrix[i] == null || matrix[i].Length != rowsL)
                throw new ArgumentException("Jagged array must be rectangular (all rows same length).");
        }

        int n = rowsL - 1;          
        const double eps = 1e-12;   

      
        double[][] workMatrix = new double[colsL][];
        for (int i = 0; i < colsL; i++)
        {
            workMatrix[i] = new double[rowsL];
            Array.Copy(matrix[i], workMatrix[i], rowsL);
        }
        
        int row = 0;
        for (int col = 0; col < n && row < colsL; col++)
        {
            int pivot = row;
            double maxAbs = Math.Abs(workMatrix[pivot][col]);
            for (int r = row + 1; r < colsL; r++)
            {
                double v = Math.Abs(workMatrix[r][col]);
                if (v > maxAbs)
                {
                    maxAbs = v;
                    pivot = r;
                }
            }
            
            if (maxAbs < eps)
                continue;

  
            if (pivot != row)
            {
                (workMatrix[pivot], workMatrix[row]) = (workMatrix[row], workMatrix[pivot]);
            }

 
            for (int r = row + 1; r < colsL; r++)
            {
                double factor = workMatrix[r][col] / workMatrix[row][col];
                if (Math.Abs(factor) < eps) { workMatrix[r][col] = 0.0; continue; }
                workMatrix[r][col] = 0.0;
                for (int c = col + 1; c < rowsL; c++)
                    workMatrix[r][c] -= factor * workMatrix[row][c];
            }
            row++;
        }


        int rankA = 0;
        bool inconsistent = false;
        for (int i = 0; i < colsL; i++)
        {
            bool allZeroA = true;
            for (int c = 0; c < n; c++)
            {
                if (Math.Abs(workMatrix[i][c]) > eps) { allZeroA = false; break; }
            }
            if (!allZeroA) rankA++;
            else
            {
                if (Math.Abs(workMatrix[i][n]) > eps)
                {
                    inconsistent = true;
                    break;
                }
            }
        }

        if (inconsistent)
        {
            Console.WriteLine("Система несовместна (нет решений).");
            return [];
        }

        if (rankA < n)
        {
            Console.WriteLine("Система имеет бесконечно много решений (недоопределена).");
            return [];
        }


        double[] x = new double[n];


        for (int i = n - 1; i >= 0; i--)
        {
            int lead = -1;
            for (int c = n - 1; c >= 0; c--)
            {
                if (Math.Abs(workMatrix[i][c]) > eps) { lead = c; break; }
            }
            if (lead == -1)
            {
                continue;
            }

            double sum = workMatrix[i][n];
            for (int c = lead + 1; c < n; c++)
                sum -= workMatrix[i][c] * x[c];

            x[lead] = sum / workMatrix[i][lead];
        }


        for (int i = 0; i < n; i++)
            Console.WriteLine($"x[{i}] = {x[i]}");
        
        double[][] outMatrix = new double[n][];
        for (int i = 0; i < n; i++)
        {
            outMatrix[i] = new double[1];
            outMatrix[i][0] = x[i];
        }
        return outMatrix;
        
    }

}