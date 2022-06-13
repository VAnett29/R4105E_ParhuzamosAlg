using System;
using System.Threading;
using System.Diagnostics;
using System.IO;

namespace ParhuzamosCSharp 
{
    public class Program
    {
        // szálak száma
        private static int threadCount = Environment.ProcessorCount;
        // tartomány vége
        private const int maxNumber = 10000;
        // tartomány nagysága
        private static int range = Convert.ToInt32(Math.Ceiling(Convert.ToDouble(maxNumber) / Convert.ToDouble(threadCount)));
        // sync object zároláshoz
        private static object syncobject = new object();
        // végeredmény
        private static int result = 0;

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
                parameters[i] = new ThreadParam(i * range, Math.Min((i + 1) * range, maxNumber), sumOfDigits);
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

            //eredmények kiírása
            using (StreamWriter sw = new StreamWriter("cs_threads.csv"))
            {
                sw.WriteLine("Thread,Milliseconds,Numbers found");
                Console.WriteLine("\nResults:");
                for (int i = 0; i < threadCount; i++)
                {
                    Console.WriteLine($"[Thread {i}]: \t time: {parameters[i].ElapsedMilliseconds,10} millisecs, \t numbers found: {parameters[i].NumbersFound,4}");
                    sw.WriteLine($"Thread {i},{parameters[i].ElapsedMilliseconds},{parameters[i].NumbersFound}");
                }
                sw.Close();
            }

            Console.WriteLine($"\nTotal numbers found with sum of digits {sumOfDigits}: {result}");
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

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            // tartomány vizsgálata
            for (int i = data.From; i < data.To; i++)
            {
                if (SumOfDigits(i) == data.SumOfDigits)
                {
                    lock (syncobject)
                    {
                        result++;
                    }
                    data.NumbersFound++;
                    Console.WriteLine($"[{Thread.CurrentThread.Name}] found {i}.");
                }
            }
            stopwatch.Stop();
            data.ElapsedTimeInTicks = stopwatch.ElapsedTicks;

            Console.WriteLine($"[{Thread.CurrentThread.Name}] finished.");
        }
    }
}