
namespace _2RT_1st_task;
using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("Select exercise: {1,2}");
        
        int exercise = Convert.ToInt32(Console.ReadLine());
        
        switch (exercise)
        {
            case 1:
            {
                Console.WriteLine("Write x and n");
                double[] xn = Console.ReadLine().Split(' ').Select(x => Convert.ToDouble(x)).ToArray();
                double result = Exer1.CountFormula(xn[0], xn[1]);
                Console.WriteLine($"The result is: {result}");
                break;
            }
            case 2:
            {
                Console.WriteLine("insert ticket number (######):");
                bool lucky = Exer2.LuckyBilet(Console.ReadLine());
                Console.WriteLine(lucky? "Its a lucky ticket" : "its not a lucky ticket");
                break;
            }
        }
    }
}