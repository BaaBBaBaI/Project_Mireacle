namespace _2RT_1st_task; using System; using System.Linq;
public class Exer1
{

    public static double CountFormula(double x, double n)
    { // Мой вариант является 4
        double result = 0;
        for (int i = 0; i < n; i++)
        {
            int factorial = Enumerable.Range(1, 2*i).Aggregate(1, (p, item) => p * item);
            result += Math.Pow(-1, i) * (Math.Pow(x, i*2) / factorial);
        }
        
        return result;
    }
    
}