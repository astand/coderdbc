using CoderDbc.Models;
using System;
using System.Text;

namespace CoderDbc.Core
{
    internal class MathSignalPrinter
    {
        public MathSignalPrinter()
        {
        }

        internal string PrintMathData(MessageDescriptor msg)
        {
            sb.Clear();
            sb.Append($"    '{msg.MessageName.ToString() + "_m"}', ... ");
            sb.AppendLine("    '', ... ");
            sb.AppendLine("    '', ...       ");
            sb.AppendLine("    'Auto', ...   ");
            sb.AppendLine("    '-1', {...    ");

            foreach (var sig in msg.Signals)
            {
                var type = "'uint8',";
                var frmt = "F0";

                if (sig.SigType == SigTypeEnum.i8)
                {
                    type = "'double',";
                    frmt = "F3";
                }

                type = type.PadRight(10, ' ');
                var name = ("'" + sig.FieldName + "',").PadRight(30, ' ');
                var min = sig.MinValue.ToString(frmt);
                var max = sig.MaxValue.ToString(frmt);
                var st = "{";
                st += String.Format("{0}1, {1} -1, 'real', 'Sample', 'Fixed', {2}, {3}, '', ''", name, type, min, max);
                st += "}; ...";
                sb.AppendLine(st);
            }

            sb.AppendLine();
            sb.AppendLine();
            return sb.ToString();
        }

        StringBuilder sb = new StringBuilder(512);
    }
}