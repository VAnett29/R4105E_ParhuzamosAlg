using System;
using System.Threading;

public class parhuzamoshazi
{
    /// <summary>
    /// Paraméter osztály adatok átadásához a szálnak
    /// </summary>
    public class ThreadParam
    {
        /// <summary>
        /// Tartomány eleje
        /// </summary>
        public int From { get; set; }
        /// <summary>
        /// Tartomány vége
        /// </summary>
        public int To { get; set; }
        /// <summary>
        /// Keresett számjegyek összege
        /// </summary>
        public int SumOfDigits { get; set; }
        /// <summary>
        /// Szál eredménye
        /// </summary>
        public int Result { get; set; }
        public ThreadParam(int from, int to, int sumOfDigits)
        {
            From = from;
            To = to;
            SumOfDigits = sumOfDigits;
        }
    }

    // szálak száma
    private const int threadCount = 10;
    // tartomány vége
    private const int maxNumber = 10000;
    // tartomány nagysága
    private const int range = maxNumber / threadCount;

    public static void Main()
    {
        int number;
        // szám bekérése
        do
        {
            Console.WriteLine("Enter a number: ");
        } while (!int.TryParse(Console.ReadLine(), out number));

        // számjegyek összegének kiszámítása
        int sumOfDigits = SumOfDigits(number);

        // szálak és paraméterek tömbjének lefoglalása
        Thread[] threads = new Thread[threadCount];
        ThreadParam[] parameters = new ThreadParam[threadCount];

        //felparaméterezés
        for (int i = 0; i < threadCount; i++)
        {
            threads[i] = new Thread(CountSumOfDigits);
            threads[i].Name = $"Thread {i}";
            parameters[i] = new ThreadParam(i * range, (i + 1) * range, sumOfDigits);
        }
        // szálak indítása
        for (int i = 0; i < threadCount; i++)
        {
            threads[i].Start(parameters[i]);
        }
        // szálak bevárása
        foreach (Thread thread in threads)
        {
            thread.Join();
        }

        //eredmányek összegzése
        int total = 0;
        foreach (var tparams in parameters)
        {
            total += tparams.Result;
        }

        Console.WriteLine($"Total numbers found with sum of digits {sumOfDigits}: {total}");
        Console.ReadLine();
    }

    /// <summary>
    /// számjegyek összegének kiszámítása
    /// </summary>
    /// <param name="number">szám aminek ki kell számolni a számjegyeinek összegét</param>
    /// <returns>számjegyek összege</returns>
    private static int SumOfDigits(int number)
    {
        int sumOfDigits = 0;
        while (number != 0) //ha a szám elfogyott kilépés
        {
            sumOfDigits += number % 10; //legkisebb helyiérték hozzáadása
            number /= 10; //legkisebb helyiérték eltüntetése
        }
        return sumOfDigits;
    }
    /// <summary>
    /// Szálfüggvény, tartományban a megegyző számjegyek összegével rendelkez számok összeszámolása
    /// </summary>
    /// <param name="param">ThreadParam</param>
    public static void CountSumOfDigits(object param)
    {
        //kasztolás az adatok eléréséhez
        ThreadParam data = param as ThreadParam;
        Console.WriteLine($"{Thread.CurrentThread.Name} starting from " +
            $"{data.From} to {data.To} finding {data.SumOfDigits}");
        // tartomány vizsgálata
        for (int i = data.From; i < data.To; i++)
        {
            if (SumOfDigits(i) == data.SumOfDigits)
                data.Result++;
        }

        Console.WriteLine($"{Thread.CurrentThread.Name} finished with {data.Result}");
    }
}