using System;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;

namespace ParhuzamosCSharp 
{
    public class Program
    {
        public static void Main()
        {
            int number;
            // szám bekérése
            do
            {
                Console.WriteLine("Enter a number: ");
            } while (!int.TryParse(Console.ReadLine(), out number));

            for (int i = 1000; i <= 10000; i+= 1000)
            {
                Console.WriteLine($"--- 0-{i}");
                // számjegyek összegének kiszámítása
                int sumOfDigits = Run.SumOfDigits(number);

                List<Run> runs = new List<Run>();

                int maxThreadCount = Environment.ProcessorCount;
                for (int j = 1; j <= maxThreadCount; j *= 2)
                {
                    Run r = new Run(maxNumber: i, threadCount: j, sumOfDigits: sumOfDigits);
                    r.Start();
                    runs.Add(r);
                }

                WriteCSV(i, maxThreadCount, runs);

                foreach (var run in runs)
                {
                    run.PrintResults();
                }
            }

            Console.ReadLine();
        }

        private static void WriteCSV(int maxNumber , int maxThreadCount, List<Run> runs)
        {
            //eredmények kiírása
            using (StreamWriter sw = new StreamWriter($"cs_threads_{maxNumber}.csv"))
            {
                //fejléc elkészítése
                string line = "Thread";
                for (int i = 0; i < runs.Count; i++)
                {
                    line += ",Milliseconds,Numbers found";
                }
                sw.WriteLine(line);

                // mért adatok beírása
                for (int i = 0; i < maxThreadCount; i++)
                {
                    line = $"Thread {i}";
                    foreach (var run in runs)
                    {
                        ThreadParam result = run.GetResult(i);
                        // ha nincs ilyen, mert kevesebb száll volt a futás során,
                        // kihagyás következő futásra lépés
                        if (result == null)
                            continue;

                        line += $",{result.ElapsedMilliseconds},{result.NumbersFound}";
                    }
                    sw.WriteLine(line);
                }

                line = $"Total";
                foreach (var run in runs)
                {
                    line += $",{run.totalMillisecs},{run.result}";
                }
                sw.WriteLine(line);

                sw.Close();
            }
        }
    }
}