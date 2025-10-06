namespace _2RT_1st_task; using System; using System.Linq;
public class Exer1
{
    public static double CosByMacl(double x, double epsilon, int maxTerms = 1000)
    {
        
        double tau = 2.0 * Math.PI;
        x = x % tau;
        if (x > Math.PI) x -= tau; else if (x < -Math.PI) x += tau;

        double sum = 1.0; 
        double term = 1.0; 
        int k = 0;

        while (Math.Abs(term) > epsilon && k < maxTerms)
        {
            term *= -(x * x) / ((2.0 * k + 2.0) * (2.0 * k + 1.0));
            sum += term;
            k++;
        }
        return sum;
    }
    public static double CountFormula(double x, double n)
    { // Мой вариант является 4
        double result = 0;
        for (int i = 0; i < n; i++)
        {
            int factorial = Enumerable.Range(1, 2*i).Aggregate(1, (p, item) => p * item);
            result += Math.Pow(-1, i) * (Math.Pow(x, i*2) / factorial);
        }
        
        return result;
    } // Хрень какая-то
    
    
}