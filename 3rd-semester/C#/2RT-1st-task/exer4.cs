using System.Numerics;

namespace _2RT_1st_task;

public class Exer4
{
static bool flagg = false;
private static int[] norm;
private static string move = "dn";
    static int Que(int x, int[] border)
    {
        Console.WriteLine($"Is your number {x}? (More(1)/Less(0)/Yes(2)");
        string ans = Console.ReadLine();
        switch (ans)
        {
            case "More":
            case "1":
            case "more":
            {
                int tempo = (border[1] + border[0]) / 2;
                border[0] = tempo;
                return ((border[0] + border[1]) / 2); break;
            }

            case "Less":
            case "0" :
            case "less":
            {
                int tempo = (border[1] + border[0]) / 2;
                border[1] = tempo;
                return ((border[0] + border[1]) / 2); break;
            }

            case "Yes":
            case "yes":
            case "2":
            {
                flagg = true;
                move = "kn";return x; break;
            }
                
        }

        return -1;
    }
    
    public static (int, string) Task4()
    {
        norm = [0, 64];
        int o = 32;
        
        for (int i = 0; i < 7; i++)
        {
            o = Que(o, norm);
            if (flagg || i == 6)
            { flagg = false; break; }
        }
        return (o, move);
    }
}