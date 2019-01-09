using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CoderDbc.Models
{
    public enum BitLayout { Intel = 0, Motorolla };

    public enum SigTypeEnum : Byte { i8 = 0, i16, i32, i64, u8, u16, u32, u64 };

    public class SignalBitsDesc
    {
        public string FieldName { get; private set; }

        public string FieldUnit { get; set; }

        public int StartBit { get; set; }

        public int LengthBit { get; set; }

        public double Factor { get; set; }

        public double Offset { get; set; }

        public int RawOffset { get; set; }

        public BitLayout Order { get; set; }

        public bool Signed { get; set; } = false;

        public SigTypeEnum SigType { get; set; }

        // this array holds expression for convert signal to element of byte array
        // Each signal gathers expressions toByte conversion.
        public string[] SigToByte { get; set; } = new string[8];

        public double MinValue { get; internal set; }

        public double MaxValue { get; internal set; }

        public List<string> Receivers { get; set; } = new List<string>();

        public String CommentText { get; set; }

        public String ValueText { get; set; }

        public override String ToString()
        {
            return $"Start bit:{StartBit}. Length:{LengthBit}. {Order}";
        }

        public void ParseFromVectorDbcString(string line)
        {
            // split signal line into two
            var halfsplit = Regex.Split(line, DbcHalfPattern);
            // split 2nd half of signal
            var split2ndpart = Regex.Split(halfsplit[2], DbcSignalSecondHalfPattern);
            var rawsplit = Regex.Split(split2ndpart[0].Trim(), VectorDbcPattern);
            // split 1st half of signal
            halfsplit = Regex.Split(halfsplit[0], @"[^\w]+");

            try
            {
                //// This is invariant
                //NumberFormatInfo format = new NumberFormatInfo();
                //// Set the decimal seperator
                //format.NumberDecimalSeparator = ".";
                FieldName = halfsplit[2];
                StartBit = int.Parse(rawsplit[0]);
                LengthBit = int.Parse(rawsplit[1]);
                //Factor = double.Parse(rawsplit[3], format);
                //Offset = double.Parse(rawsplit[4], format);
                Factor = double.Parse(rawsplit[3]);
                Offset = double.Parse(rawsplit[4]);
                RawOffset = (int)(Offset / Factor);
                //MinValue = double.Parse(rawsplit[5], format);
                //MaxValue = double.Parse(rawsplit[6], format);
                MinValue = double.Parse(rawsplit[5]);
                MaxValue = double.Parse(rawsplit[6]);
                Order = (rawsplit[2].Contains("1")) ? BitLayout.Intel : BitLayout.Motorolla;
                Signed = (rawsplit[2].Contains("-"));
                SigType = GetSigType();
            }
            catch (Exception e)
            {
                Console.WriteLine($"(!)Parsing exception occured in line'{line}'.{Environment.NewLine}" +
                                  $"Text: {e.Message}");
            }

            FieldUnit = "-";

            if (split2ndpart.Length == 3)
            {
                FieldUnit = split2ndpart[1];
            }

            var receivers = Regex.Split(split2ndpart.Last().Trim(), VectorDbcPattern);
            Receivers.Clear();

            foreach (var rx in receivers)
            {
                Receivers.Add(rx);
            }
        }

        private SigTypeEnum GetSigType()
        {
            var isunsign = 0;
            // for signed add 1 bit
            var len = LengthBit;
            var sizetype = SigTypeEnum.i64;
            // get read signal offset
            Int64 roffset = (Int64)(Offset / Factor);

            if (!Signed)
            {
                UInt64 maxvalue = 0;

                if (LengthBit < 33)
                {
                    if (roffset >= 0)
                    {
                        // this only Unsigned case
                        maxvalue = (UInt64)(Math.Pow(2, LengthBit) - 1 + roffset);
                        isunsign = 1;
                    }
                    else
                    {
                        UInt64 maxPos = (UInt64)(Math.Pow(2, LengthBit + 1) - 1);
                        UInt64 maxNeg = (UInt64)(Math.Abs(roffset * 2));
                        maxvalue = Math.Max(maxPos, maxNeg);
                    }

                    for (int i = 0; i < 4; i++)
                    {
                        if (maxvalue <= __maxvalues[i])
                        {
                            sizetype = (SigTypeEnum)(i + isunsign * 4);
                            break;
                        }
                    }
                }
                // special case for 64 bit signals --> always will be UInt64
                else
                {
                    isunsign = 1;
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (len <= __typeslen[i])
                    {
                        sizetype = (SigTypeEnum)(i + isunsign * 4);
                        break;
                    }
                }
            }

            return sizetype;
        }

        StringBuilder sbuild = new StringBuilder(512);

        //static string[] __stypes = { "int8_t", "int16_t", "int32_t", "int64_t" };
        static UInt64[] __maxvalues = { byte.MaxValue, UInt16.MaxValue, UInt32.MaxValue, UInt64.MaxValue };

        static int[] __typeslen = { 8, 16, 32, 64 };
        static readonly string VectorDbcPattern = @"[^A-Za-z0-9_.+-]+";
        static readonly string DbcHalfPattern = @"(\s+:\s+)";
        static readonly string DbcSignalSecondHalfPattern = @"""";
    }
}
