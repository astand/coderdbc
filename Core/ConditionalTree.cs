using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public enum ConditionalType { Cond, Express, Single };

    public class ConditionalTree
    {
        public ConditionalTree() { }

        public ConditionalTree High { get; set; }

        public ConditionalTree Low { get; set; }

        public ConditionalType conditionalType = ConditionalType.Cond;

        public string ConditionExpresion { get; set; }

        public string Code { get; set; }
    };

    public class ConditionalTreeCWriter
    {
        public string WriteCode(ConditionalTree tree, int indent)
        {
            if (tree != null)
            {
                if (tree.conditionalType == ConditionalType.Cond)
                {
                    PrintCode("".PadRight(indent) + $"if ({tree.ConditionExpresion}) {{");
                    WriteCode(tree.High, indent + 1);

                    if (tree.Low != null)
                    {
                        if (tree.Low.conditionalType == ConditionalType.Express)
                        {
                            PrintCode("".PadRight(indent) + $"}} else if ({tree.Low.ConditionExpresion}) {{");
                        }
                        else
                        {
                            PrintCode("".PadRight(indent) + "} else {");
                        }

                        WriteCode(tree.Low, indent + 1);
                    }
                    else
                    {
                        PrintCode("".PadRight(indent) + "}");
                    }

                    if (tree.Low != null)
                    {
                        PrintCode("".PadRight(indent) + "}");
                    }
                }
                else
                {
                    PrintCode("".PadRight(indent) + $"{tree.Code}");
                }
            }

            return sb.ToString();
        }



        public void Clear()
        {
            sb.Clear();
        }

        void PrintCode(string s)
        {
            Debug.WriteLine(s);
            sb.AppendLine(s);
        }

        StringBuilder sb = new StringBuilder(2048);
    };
}
