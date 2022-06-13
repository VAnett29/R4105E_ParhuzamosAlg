using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ParhuzamosCSharp
{
    /// <summary>
    /// Paraméter osztály adatok átadásához a szálnak
    /// </summary>
    public class ThreadParam
    {
        /// <summary>
        /// Tartomány eleje
        /// </summary>
        public int From { get; private set; }
        /// <summary>
        /// Tartomány vége
        /// </summary>
        public int To { get; private set; }
        /// <summary>
        /// Keresett számjegyek összege
        /// </summary>
        public int SumOfDigits { get; private set; }
        /// <summary>
        /// Eltelt idő "tick"-ben, 10000 tick = 1 millisec.
        /// </summary>
        public long ElapsedTimeInTicks { get; set; }
        /// <summary>
        /// Formázott kiírása a futási időnek millisec-ben
        /// </summary>
        public string ElapsedMilliseconds 
        { 
            get 
            {
                return $"{ElapsedTimeInTicks / 10000}.{ElapsedTimeInTicks % 10000}";
            } 
        }
        /// <summary>
        /// Talált számok egyező számjegy összeggel
        /// </summary>
        public int NumbersFound { get; set; }
        public ThreadParam(int from, int to, int sumOfDigits)
        {
            From = from;
            To = to;
            SumOfDigits = sumOfDigits;
        }
    }
}
