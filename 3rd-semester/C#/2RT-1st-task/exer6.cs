namespace _2RT_1st_task;

public class Exer6
{
    public static void Petri(int n, int x)
    {
        bool condition = x > 0 || n > 0;
        int count = 0;
        int damage = x * 10;
        while (condition)
        {
            count++;
            n = (n * 2) - damage;
            damage -= x;
            Console.WriteLine($"After {count} hours, there were {n} bacteria left.");
            condition = damage > 0 && n > 0;
            
        }
        
    }
}