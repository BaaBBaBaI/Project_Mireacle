namespace _2RT_1st_task;

public class Exer3
{
    public static int Task3(int x, int y)
    {
        int a = x, b = y;
        while (a != 0 && b != 0)
        {
            if (a > b) { a = a % b; }
            else { b = b % a; }
        }

        int nod = a + b;

        if (nod != 1)
        {
            a = x / nod;
            b = y / nod;
            Console.WriteLine($"Result: {a} / {b}.");
        } else
        {
            Console.WriteLine("Same result.");
        }

        return nod;
    }
}